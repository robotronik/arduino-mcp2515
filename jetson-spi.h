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

typedef struct{
 uint8_t * data;
 int len;
} spiframe;

typedef int spiid;

int error(char * err);

spiid spi_init();
void spi_close(spiid);
int spi_send(spiid fd, spiframe send_data);
int spi_full_duplex(spiid fd, spiframe send_data, spiframe receive_data);
int error(char * err);
