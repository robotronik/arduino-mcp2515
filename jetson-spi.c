/*
 * A more pleasant layer that uses the Jetson SPI functions.
 * Free software
 */

#include "jetson-spi.h"


int spi_init(){

  /*
   * Initialisation
   */

  int file_descriptor;
  int ret;
  const char *device = "/dev/spidev0.0";
  uint8_t bits = 8;
  uint32_t speed = 500000;

  //opening SPI device
  file_descriptor = open(device, O_RDWR);
  if(file_descriptor<0) return error("Device cannot be opened.");

  /*
   * Writing, then fetching, spi parameters
   */

  //Number of bits per word
	ret = ioctl(file_descriptor, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1) return error("can't set bits per word");

	ret = ioctl(file_descriptor, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1) return error("can't get bits per word");
  
  //Max frequency
 	ret = ioctl(file_descriptor, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1) return error("can't set max speed hz");

	ret = ioctl(file_descriptor, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1) return error("can't get max speed hz");

  return file_descriptor;
}

int error(char *err){
  printf("%s",err);
  return 1;
}

int spi_send(int fd, uint8_t *data, int len){

  struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)data,
		.len = len,
		.speed_hz = SPEED,
		.bits_per_word = BITS,
	};

  int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
  if(ret<0) return error("Error sending SPI message");
  return 0;
}

int spi_receive(int fd, uint8_t *data){

  calloc(RX_SIZE,sizeof(uint8_t));

  struct spi_ioc_transfer tr = {
    .rx_buf = (unsigned long)data,
		.len = RX_SIZE,
		.speed_hz = SPEED,
		.bits_per_word = BITS,
	};

  int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
  if(ret<0) return error("Error receiving message");
  return 0;
}
