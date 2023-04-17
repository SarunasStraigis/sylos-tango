#!/usr/bin/python3

"""
Laser Gateway Device Server module
"""

import logging
from PyTango.server import run

from laser_system.settings import Settings
from laser_system.laser_gateway import LaserGateway



if __name__ == "__main__":
    settings = Settings()
    logging.basicConfig(level=settings.logging_level, format="[SERVER] [%(process)d:%(threadName)s] - %(message)s")
    run([LaserGateway])
