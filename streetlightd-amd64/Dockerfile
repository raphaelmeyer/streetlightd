FROM ubuntu:xenial

RUN apt-get update
RUN apt-get -y install --fix-missing \
  build-essential \
  cmake \
  dbus-x11 \
  doxygen \
  git \
  graphviz \
  libcrypto++-dev \
  libcurl4-openssl-dev \
  libdbus-c++-dev \
  libjsoncpp-dev \
  libmosquittopp-dev \
  libpoco-dev \
  libssl-dev \
  mosquitto \
  pkg-config \
  python-dbus \
  python-gobject \
  python-pip \
  uuid-dev

RUN pip install behave paho-mqtt

COPY gmock-install.sh /home/root/
RUN /home/root/gmock-install.sh

RUN mkdir -p /workspace

VOLUME ["/workspace"]
WORKDIR /workspace

