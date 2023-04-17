#!/usr/bin/env python3
"""
Laser Gateway module
"""

import logging
import threading
import time
import requests
import PyTango
from PyTango import DevState, AttrWriteType, AttrSerialModel, Util, SerialModel, Attr, SpectrumAttr, Except
from PyTango.server import Device, DeviceMeta, attribute, run, command
from laser_system.settings import Settings
from pprint import pprint


class LaserGateway(Device, metaclass=DeviceMeta):
    baseAddress = None
    REST_timeout = 5

    stateParamNames = []

   

    def __init__(self, cl, name):
        """
        :param cl: Device Class
        :param name: Device name
        """
        super().__init__(cl, name)

        self.settings = Settings()
        self.lock = threading.Lock()
        logging.debug("start adding  attributes")
        #every attribute name is written only once!
        self.add_attribute_mod(Attr("ENERGY_SET_POINT", PyTango.DevDouble, PyTango.READ_WRITE))
        self.add_attribute_mod(Attr("DURATION", PyTango.DevDouble, PyTango.READ_WRITE))
        self.add_attribute_mod(Attr("TLPD", PyTango.DevDouble, PyTango.READ))
        self.add_attribute_mod(Attr("CWL", PyTango.DevDouble, PyTango.READ))
        self.add_attribute_mod(Attr("PD", PyTango.DevDouble, PyTango.READ))
        self.add_attribute_mod(Attr("ENERGY", PyTango.DevDouble, PyTango.READ))
        self.add_attribute_mod(SpectrumAttr("BEAMPOINT",  PyTango.DevDouble, PyTango.READ, 2))
        self.add_attribute_mod(Attr("SHUTTER", PyTango.DevBoolean, PyTango.READ_WRITE))
        self.add_attribute_mod(Attr("ENERGY_STAB_LOOP", PyTango.DevBoolean, PyTango.READ_WRITE))
        self.add_attribute_mod(Attr("PPL_BEAM4_ATT", PyTango.DevDouble, PyTango.READ))
        self.add_attribute_mod(Attr("DSCAN_TIME", PyTango.DevULong64, PyTango.READ))
        self.add_attribute_mod(Attr("CEP_STAB_LOOP", PyTango.DevBoolean, PyTango.READ_WRITE))
        self.add_attribute_mod(Attr("CEP_SET_POINT", PyTango.DevDouble, PyTango.READ_WRITE))
        self.add_attribute_mod(SpectrumAttr("BEAMPOS", PyTango.DevDouble, PyTango.READ, 2))
        self.add_attribute_mod(Attr("MODE", PyTango.DevString, PyTango.READ_WRITE)) #MODE can be "LOCAL" or "REMOTE". 
        # TODO Not sure who can change MODE when


        logging.debug("added all attributes")
        if self.settings.use_tango_synchronization is False: #todo not sure what is the meaning of this param
            util = Util.instance()
            util.set_serial_model(SerialModel.NO_SYNC)
        for name in self.stateParamNames:
            setattr(self, name + "_value", None)
            self.set_change_event(name, True, False)
        
        

        self.baseAddress = "http://" + self.settings.device_ip + ":" + str(self.settings.device_port) + "/v0/TangoGateway/" 
        ok = self.update_state()
        logging.info("return from initial update_state")
        if (ok):
            self.set_state(DevState.ON)
        else:
            self.set_state(DevState.UNKNOWN)
            logging.error("could not initialize")

        logging.info("start update thread")
        thread = threading.Thread(target = self.run, args = ())
        thread.daemon = True                            # Daemonize thread
        thread.start()                                  # Start the execution




    def get(self, url):
        return (requests.get(self.baseAddress + url, timeout=self.REST_timeout)).json()

    def put(self, url, data=None):
        return (requests.put(self.baseAddress + url,  timeout=self.REST_timeout, json =data))



    def run(self):
        """ Method that runs forever """
        while True:
            ok = self.update_state()
            if (ok):
                self.set_state(DevState.ON)
            else:
                self.set_state(DevState.UNKNOWN)
            time.sleep(1)


    def init_device(self):
        Device.init_device(self)

    def add_attribute_mod(self, attr):
        logging.debug("add attr")
        self.add_attribute(attr,self.read_General, self.write_General)
        self.stateParamNames.append(attr.get_name())

    def read_General(self,attr):
        logging.debug("read general called")
        name = attr.get_name()
        localValue = getattr(self, name + "_value")
        logging.debug("local value for " + name + " : " + str(localValue))
        attr.set_value(localValue)
        return localValue


    def write_General(self,attr):
        logging.debug("write general called")
        value = attr.get_write_value()
        name = attr.get_name()
        logging.debug("write called " + name + " = " + str(value))
        response=self.put(name, value)
        if (response.ok == False):
            description="failed writing parameter "+name+" = "+str(value)+". Response code: "+str(response.status_code)+", message: "+response.json()
            logging.warn(description)
            PyTango.Except.throw_exception(response.json(), description, "write "+name, PyTango.ErrSeverity.ERR)


  
    def update_state(self):

        """
        get new state and update accordingly
        """
        try:
            _temp_state = self.get("State")
        except Exception as e:
            logging.warn("failed to update state")
            logging.warn(e)
            return False
        for name in self.stateParamNames:
            self.attr_maybe_changed(name, _temp_state[name])
        return True

    
    def attr_maybe_changed(self, attr_name, value):
        if (getattr(self, attr_name + "_value") == value):
            return
        logging.debug("change attr " + attr_name + " to value " + str(value))
        setattr(self, attr_name + "_value", value)
        self.push_change_event(attr_name, value)


    @command
    def stop(self):
        self.put('STOP')


   

    @command()
    def switch_off(self):
        self.put('SWITCH_OFF')

    def handle_timeout(self, value):
        """
        No connection to laser method? todo it seems this method is never used?
        :param value:
        :return:
        """
        #with self.lock:
        logging.warning("Timeout! Set STANDBY state")
        self.set_state(DevState.STANDBY)
