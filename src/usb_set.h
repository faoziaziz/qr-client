/* 

   author : Aziz Amerul Faozi
   description : this header use to acces usb 
*/

#ifndef __USB_SET_H
#define __USB_SET_H

#include <libusb-1.0/libusb.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
int write_to_usb(char * data_qr);



#endif
