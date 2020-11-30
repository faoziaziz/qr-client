#include "usb_set.h"
#include<stdio.h>


/* this file variable */
int done = 0;
libusb_device_handle *handle=NULL;

static int LIBUSB_CALL hotplug_callback(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data) {
  
  /* this code use for hotplug callback */
  struct libusb_device_descriptor desc;
  int rc;

  (void)ctx;
  (void)dev;
  (void)event;
  (void)user_data;

  rc = libusb_get_device_descriptor(dev, &desc);
  if (LIBUSB_SUCCESS != rc) {
    fprintf (stderr, "Error getting device descriptor\n");
  }

  printf ("Device attached: %04x:%04x\n", desc.idVendor, desc.idProduct);

  if (handle) {
    libusb_close (handle);
    handle = NULL;
  }

  rc = libusb_open (dev, &handle);
  if (LIBUSB_SUCCESS != rc) {
    fprintf (stderr, "Error opening device\n");
  }

  done++;

  return 0;
  

}

/* USB callback */
static int LIBUSB_CALL hotplug_callback_detach(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data)
{
	(void)ctx;
	(void)dev;
	(void)event;
	(void)user_data;

	printf ("Device detached\n");

	if (handle) {
		libusb_close (handle);
		handle = NULL;
	}

	done++;

	return 0;
}



/* this should be function to write usb */
static void print_devs(libusb_device **devs){
  libusb_device *dev;
  int i=0, j=0;
  uint8_t path[8];
  while((dev=devs[i++])!=NULL){
    struct libusb_device_descriptor desc;
    int r= libusb_get_device_descriptor(dev, &desc);

    if(r<0){
      fprintf(stderr, "failed to get descriptor ");
      return;
    }
    printf("%04x:%04x (bus %d, device %d)",
	   desc.idVendor, desc.idProduct,
	   libusb_get_bus_number(dev), libusb_get_device_address(dev));

    r = libusb_get_port_numbers(dev, path, sizeof(path));
    if (r > 0) {
      printf(" path: %d", path[0]);
      for (j = 1; j < r; j++)
	printf(".%d", path[j]);
    }
    printf("\n");
  }

}

/* untuk menulis ke usb */
void write_to_usbi_test(){
  printf("Write to usb \n");
  libusb_device **devs;
  int r;
  ssize_t cnt;

  r =libusb_init(NULL);
  if (r<0){
    return r;

  }
  cnt = libusb_get_device_list(NULL, &devs);

  if(cnt<0){
    libusb_exit(NULL);
    return (int)cnt;


  }

  print_devs(devs);
  libusb_free_device_list(devs, 1);
  libusb_exit(NULL);

  return 0;

};

void write_to_usb()
{
	libusb_hotplug_callback_handle hp[2];
	int product_id, vendor_id, class_id;
	int rc;

	vendor_id  = 0x0930;
	product_id = 0x6544;
	class_id   = LIBUSB_HOTPLUG_MATCH_ANY;

	rc = libusb_init (NULL);
	if (rc < 0)
	{
		printf("failed to initialise libusb: %s\n", libusb_error_name(rc));
		//return EXIT_FAILURE;
	}

	if (!libusb_has_capability (LIBUSB_CAP_HAS_HOTPLUG)) {
		printf ("Hotplug capabilities are not supported on this platform\n");
		libusb_exit (NULL);
		//return EXIT_FAILURE;
	}

	rc = libusb_hotplug_register_callback (NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED, 0, vendor_id,
		product_id, class_id, hotplug_callback, NULL, &hp[0]);
	if (LIBUSB_SUCCESS != rc) {
		fprintf (stderr, "Error registering callback 0\n");
		libusb_exit (NULL);
		//return EXIT_FAILURE;
	}

	rc = libusb_hotplug_register_callback (NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT, 0, vendor_id,
		product_id,class_id, hotplug_callback_detach, NULL, &hp[1]);
	if (LIBUSB_SUCCESS != rc) {
		fprintf (stderr, "Error registering callback 1\n");
		libusb_exit (NULL);
		//	return EXIT_FAILURE;
	}

	while (done < 2) {
		rc = libusb_handle_events (NULL);
		if (rc < 0)
			printf("libusb_handle_events() failed: %s\n", libusb_error_name(rc));
	}

	if (handle) {
		libusb_close (handle);
	}

	libusb_exit (NULL);

	//return EXIT_SUCCESS;
}
