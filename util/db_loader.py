#!/usr/bin/python3

import PyTango
import argparse


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", "--name", help="Device name", type=str)
    parser.add_argument("-d", "--deviceclass", help="Device Class", type=str)
    parser.add_argument("-s", "--server", help="Device Server", type=str)
    parser.add_argument("-i", "--ip", help="Laser Device address", type=str)
    args = parser.parse_args()

    if args.name is None or args.deviceclass is None or args.server is None:
        exit(-1)

    ip = args.ip if args.ip is not None else "localhost"

    print("Register %s/%s:%s" % (args.server, args.deviceclass, args.name))

    dev_info = PyTango.DbDevInfo()
    dev_info.name = args.name
    dev_info._class = args.deviceclass
    dev_info.server = args.server
    db = PyTango.Database()
    db.add_device(dev_info)
    db.put_device_property(args.name, {"laser_device_ip": ip})
