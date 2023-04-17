# Tango tutorial for developing TANGO device for the SYLOS Laser

## 1. Introduction

- TANGO: a free, open-source library implemented in C++ for controlling physical devices 
- PyTango package: complete python binding for TANGO
- TANGO Device: controls a physical Device (Motor, Gauge, Valve, Laser Source, ..)
- TANGO Device name: "domain/class/member" triplet
- Device Server: a process that will host one or more TANGO Devices
- Device Proxy: a proxy object to a TANGO Device
- Device Class: each TANGO Device belongs to a Device Class which contains a complete description and implementation of the
 behavior of all instances of that class. Devices belonging to the same Class will have the same set of attributes, properties, commands, ..
- TANGO DB: stores TANGO Device Server and TANGO Device information (e.g. registered TANGO Devices for a given Device Server)


```
             +---------------+
             | Device Server |
             +-------+-------+
                     |
          +----------|------------+
          |                       |
          |                       |
+--------+------+         +-------+------+                   +--------------+
| TANGO Device  |    ...  | TANGO Device |<--- TANGO Bus --- | Device Proxy |
+-------+------+          +-------+------+                   +--------------+
        |                         |
    ~~~~~~ (Socket, Modbus, USB) ~~~~~~~~~~~~~~
        |                         |
+--------+--------+       +---------+-------+
| Physical Device |  ...  | Physical Device |
+-----------------+       +-----------------+
```


For controlling a physical device through TANGO, the following steps are needed:

1. implement the Device Server/Device in Python (or C++)
2. register the Device, Device Class and Instance in the TANGO DB
3. start the Device Server that hosts the Device
4. create a Device Proxy to the Device to read/write attribute data of the Device, send commands to the Device, etc.

Note that the communication between a TANGO Device and the corresponding Physical Device needs to be established by the developer. The
communication channel can be a socket, USB, modbus, etc. depending on the physical interface of the Device.

## 2. Example Project (Laser Control System with Laser Gateway, Laser Device and Gateway Client)

The project is packed in a Docker container.

### Running/removing the container:

1. Creating the image (really takes some time from scratch, only needed when Dockerfile has changed)

```bash
cd ~/ELI/tango-gateway-framework/docker/SYLOS-Gateway/tango9
make image
```

2. Starting the container

```bash
cd ~/ELI/tango-gateway-framework/docker/SYLOS-Gateway/tango9
make HOST=$(hostname --short) container
```

3. removing the container (leave the image intact)

```bash
cd ~/ELI/tango-gateway-framework/docker/SYLOS-Gateway/tango9
make remove
```

4. remove container and image

```bash
cd ~/ELI/tango-gateway-framework/docker/SYLOS-Gateway/tango9
make clean
```

5. clean-up all unused images

```bash
docker image prune
```

### Using the container

#### CLI access
The following command starts an interactive shell inside the containered environment.

default username: tangouser

```bash
docker exec -it tango9 bash
```

#### ssh (with GUI app support)
The containered environment can be accessed via ssh on port 10022. In case of restricted network environment (f.e. 10022 port is not accessible) it is also possible to use an ssh tunnel accessing the container.

The ssh infrastructure is not built in the image, needs some work for a newly started container:

```bash
tangoway$ docker cp ~/.ssh/authorized_keys tango9:
tangoway$ docker exec -it tango9 bash
```

```bash
sudo apt-get update
sudo apt-get -y install openssh-server
mkdir -m 700 .ssh
sudo install -m 600 -o tangouser.tangouser authorized_keys .ssh
sudo sed -i -e 's/^Port 22$/Port 10022/' /etc/ssh/sshd_config
sudo service ssh start
```

1. direct access to the containeter's ssh:

```bash
ssh -p 10022 <usual access parameters> tangouser@52.174.37.8
```

2. start an ssh session to the host OS building a tunnel:

```bash
ssh -L 10022:localhost:10022 <usual access parameters to SYLOS gateway>
```
  - connect the containered environment over the tunnel with X11 forwarding:

```bash
ssh -p 10022 -X tangouser@localhost
```

### Components


1. Sylos_Main: main control application for the whole laser system. It that can provide information (parameters) on demand via REST and or allows to change some parameters / execute command via REST too 
2. Laser Gateway Device: TANGO Device, hosted by LaserGateway Device Server (laser_gatewayDS.py)
3. Client to the Laser Gateway (laser_gatewayCLIENT.py)

```
        +--------------------+
        |  Laser Gateway DS  |
        +----------+---------+
                   |
                   |
         +---------+--------+                 +--------------------+
         |  Laser Gateway   |<-- TANGO Bus -- |Laser Gateway Client|
         +---------+--------+                 +--------------------+
                   |
                   |
~~~~~~~~~~~~~ (REST (HTTP)) ~~~~~~~~~~~~~~~~
                   |
                   |
       +-----------+----------------------------------------+
       |       Sylos_Main (aka Laser External Device)       |
       +----------------------------------------------------+ 


```




Usage:

- register laser_gatewayDS and one Laser Gateway Device in TANGO DB. This step is only needed once. 

```
 ~/01-init.sh
```


- launch Laser Gateway Device Server. The Laser Gateway will use REST calls to communicate with Sylos_Main

```
 ~/03-start-gateway.sh
```

- run test client

```
 ~/04-start-client.sh
```

The client will send commands to the Sylos_Main through the Laser Gateway and read/write attributes from it. You can launch the test client multiple times.

To launch all the steps at once:

```
~/start-all.sh
```

### Configuration


config.ini can be used to set the network address (IP:port) of the Laser External Device and the Laser Gateway. By default, both components will be serving on localhost. Also, the config file can be used to tweak some parameters of the components. Find comments in config.ini for details.


### Details of the Example

- Laser External Device has number of attributes. Some of are read-write and and some read-only. All values are read via single REST GET call. All changes are made through PUT or POST reqeusts.
- Laser Gateway has an Proxy (peer) to the Laser External Device. The Proxy is a registered observer of the attribute changes of its peer (Laser External Device)
- Laser Gateway reflects the Laser External Device: it has the same attribute and command set. It polls laser external device and  caches last values of all attributes. If change in value is detected, notification is sent to gateway clients who are subscribed. All attribute value reads from gateway clients are served with the last cached value.
- Laser Gateway client: a TANGO Device Proxy is created for Laser Gateway. It will read/write attributes in the Gateway which will forward these operations to the Laser External Device. Also, it is getting notified from the internal changes 
in the Laser External Device through observers. 

A sequence of Laser External Device notification:


```
+-------------------+                +---------------------+                        +----------------------+
| Laser Ext. Device |< REST POLLING--|Laser Gateway Device |-------CALL(TANGO BUS)->| Laser Gateway Client |
+-------------------+                +---------------------+                        +----------------------+

```


## 3. Design Concept



#### 1. Examples

Requirements for using these examples on a standard Linux system:
- python3 installed
- pyzmq package installed (pip3 install zmq)
- PYTHONPATH set to 'src' directory (export PYTHONPATH="${PYTHONPATH}:{path of tango-gateway-framework}/src")


Find other examples in 'examples' directories below the package directories.