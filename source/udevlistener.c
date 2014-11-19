#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#define unless( a ) if(!(a))

typedef unsigned char uchar;
uchar DEVZERO_FAILED_INIT;


int main (void)
{
    struct udev *udev;
    udev = udev_new();
    unless ( udev ) {
	fprintf(stderr,"failure to retrieve udev");
	return DEVZERO_FAILED_INIT;
    }
    
    struct udev_enumerate *enumerate;
    enumerate = udev_enumerate_new(udev);
    //udev_enumerate_add_match_subsystem( enumerate, "block");
    udev_enumerate_add_match_subsystem( enumerate, "scsi_device");
    udev_enumerate_scan_devices(enumerate);
    struct udev_list_entry *devices;
    devices = udev_enumerate_get_list_entry ( enumerate);
    struct udev_list_entry *dev_list_entry;
    udev_list_entry_foreach( dev_list_entry, devices) {
	const char *path;
	path = udev_list_entry_get_name(dev_list_entry);
	printf( "%s\n", path);
    }
}
