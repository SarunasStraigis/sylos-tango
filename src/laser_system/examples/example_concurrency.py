#!/usr/bin/env python3
import threading
import PyTango


def read_write():
    laser_gateway_proxy = PyTango.DeviceProxy("laser/gateway/1")
    laser_gateway_proxy.set_timeout_millis(5000)

    for i in range(10):
        laser_gateway_proxy.BANDW = float(i)


if __name__ == "__main__":
    threads = []

    for r in range(4):
        worker = threading.Thread(target=read_write)
        worker.start()
        threads.append(worker)

    for r in range(4):
        threads[r].join()
