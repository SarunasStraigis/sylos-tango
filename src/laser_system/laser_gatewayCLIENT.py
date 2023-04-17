#!/usr/bin/python3
"""
Laser Gateway client module
"""

import threading
import PyTango
import datetime
import time
import logging
from laser_system.settings import Settings

condition = threading.Condition()


def change_attribute_cbk(event):
    if event.attr_value is not None:
        logging.info("Callback for %s called", event.attr_value.name)
    with condition:
        condition.notify()


if __name__ == "__main__":
    settings = Settings()
    logging.basicConfig(level=settings.logging_level, format="[CLIENT][%(process)d:%(threadName)s] - %(message)s")

    laser_gateway_proxy = PyTango.DeviceProxy("laser/gateway/1")
    laser_gateway_proxy.set_timeout_millis(5000)

    time.sleep(2)
    laser_gateway_proxy.subscribe_event("ENERGY", PyTango.EventType.CHANGE_EVENT, change_attribute_cbk, [])
    laser_gateway_proxy.MODE="LOCAL" 
    time.sleep(2)
    laser_gateway_proxy.MODE="REMOTE" 
    for i in range(5):
        logging.info("---------------------------------------------------------")
        enenergy_setpoint=20.0+( i * 8.0);
        logging.info("Write ENERGY_SET_POINT to %f",enenergy_setpoint)
        try:
            laser_gateway_proxy.ENERGY_SET_POINT = enenergy_setpoint
        except PyTango.DevFailed as e:
            if e.args[0].reason=='Argument value is invalid':
                logging.warn("caught exception when writting ENERGY_SET_POINT = "+ str(enenergy_setpoint)+", value is invalid")
            else:
                raise 
        beampos = laser_gateway_proxy.BEAMPOS
        energy = laser_gateway_proxy.ENERGY
        tlpd = laser_gateway_proxy.TLPD
        dscan_time = laser_gateway_proxy.DSCAN_TIME
        logging.info("bandw: %f", tlpd)
        logging.info("energy: %f", energy)
        logging.info("BEAMPOS X: %f , Y: %f", beampos[0], beampos[1])
        logging.info("dscan time: "+ datetime.datetime.fromtimestamp(dscan_time/1000.0).strftime('%Y-%m-%d %H:%M:%S.%f'))
        #laser_gateway_proxy.ENERGY_STAB_LOOP = (i % 2 == 0)
        laser_gateway_proxy.CEP_STAB_LOOP = (i % 3 == 1)
        time.sleep(4)

    #laser_gateway_proxy.switch_off()
    laser_gateway_proxy.SHUTTER = not laser_gateway_proxy.SHUTTER

    if settings.events_frequency > 0.0:
        with condition:
            logging.info("Observer activated. Waiting for event ..")
            condition.wait()
            logging.info("Condition released")

    #laser_gateway_proxy.stop()
