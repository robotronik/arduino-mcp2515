
/*
 * A more pleasant layer that uses the Jetson SPI functions.
 * Free software
 */

#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


typedef enum{SEND,RECEIVE} direction;

typedef struct{
  direction rt;
  uint8_t spi_mode;
  uint32_t * data;
  uint32_t len;
  uint32_t verbose;
} state_t;


int spi_init();                      //TODO
int spi_close();                     //TODO
int spi_send( uint8_t* );            //TODO
int spi_receive();                   //TODO
void print_and_abort(char *);        //TODO
