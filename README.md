cgenerator
=============================

boilerplate for small C programs with autotools

Installation
------------

Execute the following commands:

    $ ./configure
    $ make
    $ sudo make install



# TODO:6000 Update the README.md file with a complete description
# TODO:6000 and some usage instructions.
## Installation Dependency
The library should you must be installed
1. Jansson
Jansson must be used for json communications
```bash
wget https://digip.org/jansson/releases/jansson-2.13.1.tar.gz
tar -zxvf jansson-2.13.1.tar.gz
cd jansson-2.13.1
./configure --prefix=/usr
make
sudo make install
```

2. Libusb
libusb need to acces usb to the host pc
```bash
wget https://github.com/libusb/libusb/releases/download/v1.0.23/libusb-1.0.23.tar.bz2
tar -xf libusb-1.0.23.tar.bz2
cd libusb-1.0.23
make
sudo make install
```
# qr-client

3. Libmicro httpd
LIbmicrohttpd digunakan sebagai aplikasi server dalam qr generator ini. Tujuannya untuk melakukan pertukaran data antara
web api dengan usb.
```bash
wget https://ftpmirror.gnu.org/libmicrohttpd/libmicrohttpd-latest.tar.gz
tar -zxvf tar -zxvf libmicrohttpd-latest.tar.gz
cd libmicrohttpd-0.9.71/
./configure --prefix=/usr
make
sudo make install
```