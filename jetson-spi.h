/*
 * A more pleasant layer that uses the Jetson SPI functions.
 * Free software
 */

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define RX_SIZE 32
#define SPEED 500000
#define BITS 8

typedef struct{
 uint8_t * data;
 int len;
} spiframe;

int error(char * err);

int spi_init();
spiframe spi_make_frame(uint8_t* data, int len);
spiframe spi_make_void_frame(int len);
void append_data(uint8_t* data, int* point, uint8_t* add, int addlen);
void append_single_data(uint8_t* data, int* point, uint8_t add);
void spi_close(int);
int spi_send(int fd, spiframe send_data);
int spi_full_duplex(int fd, spiframe send_data, spiframe receive_data);
int error(char * err);
