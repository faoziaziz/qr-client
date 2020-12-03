#include "usb_set.h"
#include<stdio.h>


#define EP_DATA_IN 0x83
#define EP_DATA_OUT 0x01
#define DEVICE_CONFIGURATION 0

/* 
 * 	
 *	@desc : this function used to write to the device, maybe
 * */
int write_to_usb(char * data_qr)
{
/*
	 *	author : declarasi variable 
	 * */
	int rc;
	libusb_context *ctx=NULL;
	libusb_device_handle *dev_handle;

	int actual = 0;
	

	

	/* libusb initialization */
	rc=libusb_init(&ctx);
	if(rc<0){
		printf("Telah terjadi error.i\n");
		return 1;
	
	}

	/* to get log debug in this usb */
	libusb_set_debug(ctx, 6);
	
	/* dev handle usb to open vid pid */
	dev_handle = libusb_open_device_with_vid_pid(ctx, 0x28e0, 0x0a05);
	if(!dev_handle){
		fprintf(stderr, "error finding usb device\n");
		return 2;
	}

	/* device configuration kernel active*/
	if(libusb_kernel_driver_active(dev_handle, DEVICE_CONFIGURATION)==0){
		printf("Kernel driver active\n");
		if(libusb_detach_kernel_driver(dev_handle, DEVICE_CONFIGURATION)==0){
		
			printf("Kernel driver detached!");
		}
	
	} else {
		printf("kernel driver inactive \n");
	
	}

	/* harus detach kernel kayaknya */

	libusb_set_auto_detach_kernel_driver(dev_handle, 1);	
	
	/* usb interfave claim usb */
	rc = libusb_claim_interface(dev_handle, DEVICE_CONFIGURATION);
	if(rc!=0){
		printf("Cannot Claim Interface\n");
		return 3;
	
	}
	
	/* what is set interface alt setting */	
	//rc = libusb_set_interface_alt_setting(dev_handle, DEVICE_CONFIGURATION, 1);
	//if(rc !=0){
	//	printf("tidak bisa configurasi alternatif setting\n");
	//	return 3;
	
//	}
//


	printf("Data \n");
	printf("S : %s \n", data_qr);
	printf("panjang qr : %d \n", strlen(data_qr));
	/* i think we need reset the device */
	libusb_reset_device(dev_handle);
	usleep(10000);
	libusb_clear_halt(dev_handle, EP_DATA_OUT);
	libusb_clear_halt(dev_handle, EP_DATA_IN);
	usleep(10000);

	/* write to device */
	rc= libusb_bulk_transfer(dev_handle, EP_DATA_OUT, data_qr, strlen(data_qr), &actual, 100);

	if(rc==0 && actual==strlen(data_qr)){
		printf("Writing sukses\n");
	} else {
		printf("Eror dalam menulis");
	}


	/* check relase usb */
	rc = libusb_release_interface(dev_handle, 0);
	if(rc!=0){
		printf("Cannot release interface \n");
	}

	if(dev_handle){
		libusb_close(dev_handle);
	}


	/* lexit program */
	libusb_exit(ctx);
	return 0;

	//return EXIT_SUCCESS;
}
