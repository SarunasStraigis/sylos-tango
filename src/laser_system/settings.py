"""
Configuration module
"""

import configparser
import os


class Settings:
    FILE_PATH = os.path.join(os.environ["HOME"], "ELI", "tango-gateway-framework", "config.ini")
    SECTION_LOGGING = "logging"
    SECTION_GATEWAY = "gateway"
    SECTION_DEVICE = "device"
    SECTION_TWEAKS = "tweaks"

    def __init__(self, file_path: str=FILE_PATH):
        super().__init__()
        self.__config = configparser.RawConfigParser()

        with open(file_path, "r") as file:
            self.__config.read_file(file)
            self.logging_format = self.__config.get(Settings.SECTION_LOGGING, "format", fallback="[%(thread)d] - %(message)s")
            self.logging_level = self.__config.getint(Settings.SECTION_LOGGING, "level", fallback=10)
            self.gateway_ip = self.__config.get(Settings.SECTION_GATEWAY, "ip", fallback="localhost")
            self.gateway_port = self.__config.getint(Settings.SECTION_GATEWAY, "port", fallback=5055)
            self.device_ip = self.__config.get(Settings.SECTION_DEVICE, "ip", fallback="localhost")
            self.device_port = self.__config.getint(Settings.SECTION_DEVICE, "port", fallback=5056)
            self.timeout = self.__config.getfloat(Settings.SECTION_TWEAKS, "timeout", fallback=0.0)
            self.events_frequency = self.__config.getfloat(Settings.SECTION_TWEAKS, "events_frequency", fallback=0.0)
            self.use_tango_synchronization = self.__config.getboolean(Settings.SECTION_TWEAKS, "use_tango_synchronization", fallback=True)


if __name__ == "__main__":
    _settings = Settings()
