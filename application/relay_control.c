/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		Ameripino Relay Controller
		  2014 Juan J. Lamas
		  EA1NK - SCQ Devices

15.01.2014 First version.
04.03.2014 Added status info via ftdi_read_pin.
04.03.2014 Added filter by serial number device.
04.03.2014 Added -s status command.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ftdi.h>

#define REL8 0x80
#define REL7 0x40
#define REL6 0x20
#define REL5 0x10
#define REL4 0x08
#define REL3 0x04
#define REL2 0x02
#define REL1 0x01
#define ALL_OFF  0b00000000
#define ALL_ON   0xFF
#define STATUS	0x53

int main(int argc,char **argv){    
	struct ftdi_context *ftdi;
	int f,i;
	unsigned char buf[1];
	unsigned char stat[1];
	//unsigned char *ant_snumber="AAABBBCC";
	char *msg="Invalid parameters.\nAll Relays turned OFF!"; // If invalid parameter this message will be displayed.
	buf[0] = ALL_OFF; // If argv is not valid, all relays OFF.
	int retval = 0;
	char* relay;

	if(argc < 2){printf("Error:\nUsage: relay_control -r[n]\n"); return(retval);};

	if((ftdi = ftdi_new()) == 0){
			
			fprintf(stderr,"Error: missing libftdi.\n");
			return EXIT_FAILURE;
 				}
	f = ftdi_usb_open(ftdi,0x0403,0x6001); // If filter by serial not needed.
	
	//f = ftdi_usb_open_desc(ftdi, 0x0403,0x6001,NULL,ant_snumber);
	
	if(f < 0 && f != -5){ // No FTDI present

		fprintf(stderr, "Error: %d (%s) \n", f, ftdi_get_error_string(ftdi));
		retval = 1;
		goto done;
				}
	
	printf("Info: Opened ftdi %d device\n",f);
	relay = argv[1];	
	printf("Enabling bitbang mode\n");
	ftdi_set_bitmode(ftdi, 0xFF, BITMODE_BITBANG);
	usleep(1 * 500000);
	relay = argv[1];

	if(strcmp(relay,"-r1")==0){buf[0]=REL1;msg = "Relay 1 ON";};
	if(strcmp(relay,"-r2")==0){buf[0]=REL2;msg = "Relay 2 ON";};
	if(strcmp(relay,"-r3")==0){buf[0]=REL3;msg = "Relay 3 ON";};
	if(strcmp(relay,"-r4")==0){buf[0]=REL4;msg = "Relay 4 ON";};
	if(strcmp(relay,"-r5")==0){buf[0]=REL5;msg = "Relay 5 ON";};
	if(strcmp(relay,"-r6")==0){buf[0]=REL6;msg = "Relay 6 ON";};
	if(strcmp(relay,"-r7")==0){buf[0]=REL7;msg = "Relay 7 ON";};
	if(strcmp(relay,"-r8")==0){buf[0]=REL8;msg = "Relay 8 ON";};
	if(strcmp(relay,"-ra")==0){buf[0]=ALL_ON;msg = "All Relay ON";};
	if(strcmp(relay,"-rn")==0){buf[0]=ALL_OFF;msg ="All Relay OFF";};
	if(strcmp(relay,"-rs")==0){buf[0]=STATUS;goto done;};	

	f= ftdi_write_data(ftdi, buf,1);
	usleep(1*500000);	
	if (f <0){
	
	fprintf(stderr, "Error: Failed to write 0x%x, error  %d (%s)\n", buf[0],f,ftdi_get_error_string(ftdi));

	} else {

	//printf("%s\n",msg);

	}
	usleep(1 * 500000);

done:
	ftdi_read_pins(ftdi,stat);
	ftdi_free(ftdi);
	if(buf[0]==STATUS){
		printf("%s:%i\n",ant_snumber,stat[0]);
		};
	if(buf[0] == stat[0]){
		printf("%s:%i|%i\n",ant_snumber,stat[0],buf[0]); // read_ping and argv match
		} else {
		return(retval);
	}

}

