
/*
 * A more pleasant layer that uses the Jetson SPI functions.
 * Free software
 */

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define RX_SIZE 32
#define SPEED 500000
#define BITS 8

int spi_init();
void spi_close(int);                     //TODO
int spi_send(int fd, uint8_t * data, int len);             //TODO
int spi_receive(int fd,uint8_t * data);          //TODO
int spi_full_duplex(int fd,uint8_t * data, uint8_t * dati, int len);          //TODO
int error(char * err);        //TODO
