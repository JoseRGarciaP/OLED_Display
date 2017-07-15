#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "SeeedGrayOLED.h"

int i2c_fd;


#define COMMAND_MODE 0x80
// cmd will be a hex code specifying a command defined in the
// display’s datasheet

void sendCommand(unsigned char cmd) {
	
	char buf[2];
	buf[0] = COMMAND_MODE;
	buf[1] = cmd;
	int result = write(i2c_fd, buf, 2);
	if(result != 2) {
		printf("Unable to write to i2c register\n");
		exit(-1);
	}
}


#define DATA_MODE 0x40
// c will contain the data you wish to display
void sendData(unsigned char c) {
	
	char buf[2];
	buf[0] = DATA_MODE;
	buf[1] = c;
	int result = write(i2c_fd, buf, 2);
	if(result != 2) {
		printf("Error sending data...\n");
		exit(-1);
	}
}


int main(int argc, char *argv[])
{
	
	// Create I2C bus
	char *bus = "/dev/i2c-2";
	if((i2c_fd = open(bus, O_RDWR)) < 0)
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, I2C address is 0x3c
	ioctl(i2c_fd, I2C_SLAVE, 0x3c);

	init();
	clearDisplay();
	setVerticalMode();
	for (int i = 0; i < 12; i++) {
		setTextXY(i,0);
		setGrayLevel(i);
		putString("hello world");
	}

	return 0;
	
}
