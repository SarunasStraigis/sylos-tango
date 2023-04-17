FROM ubuntu:xenial

RUN printf -- "\
-----BEGIN PGP PUBLIC KEY BLOCK-----\n\
Version: SKS 1.1.5\n\
Comment: Hostname: keyserver.ubuntu.com\n\
\n\
mQINBFdyZtMBEADeaE8OOeq762xn9M5UjZv8n4hmGPuRjjz9ouUKCMBFxCvqc7JZ9WYupZ14\n\
o5Mg+pmtC8e6XnbRM/NUZigB53pqSpCEcaANs7WQrCXGl6a0BxNjLGqMY9nZE0o1Bi2Mj40k\n\
OH5OhU17dWMcPgIOvRbQCh7ER4HqxSZM5uuWDwRbrbzE3hfdXOqm6ZN4yuOdhruycF2rOhAk\n\
dgc7FbZb7BtK54Cu9JOwhYnZYa395f8tDNqXHkhjNsMauIROH7kqvS3ZxsYMd06ajGJP4YZN\n\
cABLtC19o8fBf0tfFqtgBHCjWFDPkY2k+wW2+E5DW/luHXASKq7NEEqGlcDNnPTkwYvcttsa\n\
G+uh7XFQjunSbidX7Uzh+erYEklspAO8FgoEFZ1u2uI/SEEryjMajPyShp9VdJMc3/sKnzbm\n\
uyA+z5h/6CZp+YYZi3FYMV632UE8gghDsudpOc7OxmDNBoHj874A3zjathalhnh3/Su9vao2\n\
lW+cbl+Mm6jFMa+wyRHUlD1i4LsfzijWCOq3dL6352ByWy4G2q964jgCZsTyFMTvnUdSVmS3\n\
mqwKSOnK6AozACXeV7YohwYJWbYN+yd6tmrof6KFl12sM29FD/2BLsclCC0gAGhjXbzgEF6f\n\
/GYiK6hHyeYirzErVeogD4GVK0UOBHK7F7WgTWFwN6Zw9Ek2QQARAQABtBpMYXVuY2hwYWQg\n\
UFBBIGZvciBUZWFtIExNQ4kCOAQTAQIAIgUCV3Jm0wIbAwYLCQgHAwIGFQgCCQoLBBYCAwEC\n\
HgECF4AACgkQWtDMgUIcOotVsg//bdEISm3ZZnURwoGSn1BWjXCLX6h2mmyaPbBvyY7cIi0Z\n\
zQBNt2iSPnJKdL3c5m25eRAKttMSag+Ikhqci95swWMc2PVXLFGN+IMFIc8ljgBgmySyGsXu\n\
TcbcM8qBJ/mUkkwtgVBmpFiMk7QSVC+5Aji2FQaZbyBb8THkthoIhZ1Mquf+gAlG+GcAnbqU\n\
oajuqXkCJPrpxfuRqG29izQbCiTlh9CldZsLr0vVzJ88/wB7W8FH0q5QfZfTIURAJapAEv0S\n\
mCPJaPTd0bmezVDGXiJlIaQr5Fj7oonSZ5vigc6eYSTBs69s0GBZRbQaYUFbUP88evk1OjHG\n\
J8rCl7bu/sepsztm/mZ0TJpS6XNaJBA5+eqSdSpNCQnjriaCgpRh5skaNo4IvELE2VoKQdV3\n\
Ukv9/sfS33sutOM/Stl5QJYB/vzMRUHAzFk25Ss4z9GnAg43GwCChN0ms/FsBDTtks+WkCMf\n\
AUSbgcPPvx/ZBeusopCGgP+z/VFCoW3IEdztRXpjhAyoGkHi17v9xfH9/FTOSM03oX67rkqx\n\
GR8SVy4+JED2hxLH4AB21EgH5vXNQ6kwuW0CKXqLnt55LaxioqFsFSwANcWnxv+mETzKf6xT\n\
as9YreF0xcsYOaQwRP3vo9eeg/VtZ3BR3djbIW+9Ez3LSN3Z9xDOo1KVUlUVVTQ=\n\
=TMVS\n\
-----END PGP PUBLIC KEY BLOCK-----\n\
" | apt-key add -

RUN printf -- "\
deb http://ppa.launchpad.net/lmc-cam-ska/tango/ubuntu xenial main \n\
" >  /etc/apt/sources.list.d/tango9.list 

ENV DEBIAN_FRONTEND=noninteractive \
    TANGO_DATABASE=tango \
    MYSQL_PASSWORD=tango \
    TANGO_DB_USER=tangouser \
    DB_ROOT_PASSWORD=P@ssw0rD \
    TANGO_ADMIN_PASSWORD=P@ssw0rD \
    TANGO_APP_PASSWORD= \
    MYSQL_SERVER=localhost \
    MYSQL_PORT=3306 \
    MYSQL_HOST=localhost:3306 \
    TANGO_INSTALL_HOST=127.0.0.1:10000 \
    ORB_PORT=10000 \
    DB_HOST=localhost:3306

RUN apt-get update && apt-get install -y \
    apt-utils

RUN apt-get update && apt-get install -y \
    sudo \
    debconf-utils

RUN printf "\
mysql-server mysql-server/root_password password ${DB_ROOT_PASSWORD}\n\
mysql-server mysql-server/root_password_again password ${DB_ROOT_PASSWORD}\n\
tango-common tango-common/tango-host string ${TANGO_INSTALL_HOST}\n\
tango-db tango-db/dbconfig-install boolean true\n\
tango-db tango-db/mysql/admin-pass password ${TANGO_ADMIN_PASSWORD}\n\
tango-db tango-db/mysql/app-pass password ${TANGO_APP_PASSWORD}\n\
tango-db tango-db/mysql/method string TCP/IP\n\
tango-db tango-db/remote/host string ${MYSQL_SERVER}\n\
tango-db tango-db/remote/port string ${MYSQL_PORT}\n" \
| debconf-set-selections

RUN apt-get update && apt-get install -y --no-install-recommends \
    sudo \
    curl \
    wget \
    rsyslog \
    git \
    openssh-client \
    vim-nox \
    less \
    net-tools \
    iputils-ping \
    patch


RUN wget -O /tmp/tango_java-9.2.2.tgz https://lightconupdater.blob.core.windows.net/sylos/tango_java-9.2.2.tgz \
 && tar -xzf /tmp/tango_java-9.2.2.tgz \
 && rm tmp/tango_java-9.2.2.tgz


RUN apt-get update && apt-get install -y \
    monit \
    openjdk-8-jre

RUN apt-get update && apt-get install -y --no-install-recommends \
    mysql-server-5.7 

RUN sed -i -e "s/^#\(general_log_file.*\)/\1/" /etc/mysql/my.cnf

RUN printf "\
[mysqld]\n\
sql_mode = \"STRICT_TRANS_TABLES,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION\"\n" \
> /etc/mysql/conf.d/tango.cnf &&\
    service mysql restart && \
    apt-get update && apt-get install -y --no-install-recommends \
        libtango9 \
        tango-db \
        tango-accesscontrol \
        tango-starter

RUN service mysql stop

RUN apt-get update &&\
    apt-get install -y --no-install-recommends \
    tango-db \
    tango-accesscontrol\
    pkg-config

RUN apt-get update &&\
    apt-get install -y --no-install-recommends \
    python-pkg-resources \
    python-lxml \
    python-numpy \
    python-zmq \
    python-yaml \
    python-pyqt5.qtsvg \
    python-pydispatch\
    python-enum34\
    ipython\
    python-gevent\
    python-qt4\
    python-qwt5-qt4\
    python-guiqwt

RUN apt-get update &&\
    apt-get install -y --no-install-recommends \
    python3-pkg-resources \
    python3-lxml \
    python3-numpy \
    python3-zmq \
    python3-yaml \
    python3-pyqt5.qtsvg \
    python3-pydispatch\
    ipython3 \
    python3-gevent

RUN apt-get update &&\
    apt-get install -y --no-install-recommends \
    build-essential \
    python-setuptools \
    libboost-python-dev \
    python-sphinx \
    libtango-dev \
    python-dev \
    libxml2-dev \
    libxslt-dev

RUN apt-get update &&\
    apt-get install -y --no-install-recommends \
    build-essential \
    python3-setuptools \
    libboost-python-dev \
    python3-sphinx \
    libtango-dev \
    python3-dev \
    libxml2-dev \
    libxslt-dev
#
RUN apt-get update && \
    apt-get -y install python-pip python3-pip

RUN python2 -m pip install --upgrade pip && apt-get -y remove python-pip
RUN pip --cert /etc/ssl/certs install pytango==9.2.2 itango taurus || /bin/true
#
RUN python3 -m pip install --upgrade pip && apt-get -y remove python3-pip
RUN python3 -m pip install --upgrade pip && python3 -m pip --cert /etc/ssl/certs install pytango==9.2.2 itango taurus || /bin/true
#
RUN useradd --uid 1000 -ms /bin/bash tangouser
RUN usermod -a -G adm,tango tangouser
#
#ADD files/pytango9.patch /home/tangouser
#RUN patch /usr/local/lib/python3.5/dist-packages/tango/server.py </home/tangouser/pytango9.patch  && \
#    rm -f /usr/local/lib/python3.5/dist-packages/tango/server.pyc
#

ADD files/sudo-tangouser /etc/sudoers.d/tangouser

ADD files/monit-tango9.conf /etc/monit/conf.d/tango9.conf



ADD files/init.sh /tmp

ADD files/requirements.txt /tmp
WORKDIR /tmp
RUN pip install -r requirements.txt

USER tangouser
WORKDIR /home/tangouser

CMD bash -c "/tmp/init.sh" && while true; do sudo monit -Ic /etc/monit/monitrc; done
