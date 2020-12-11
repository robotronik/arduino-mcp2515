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
  uint8_t bits = BITS;
  uint32_t speed = SPEED;

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

int spi_full_duplex(int fd, uint8_t *data, uint8_t *dati, int len){

    struct spi_ioc_transfer tr = {
            .tx_buf = (unsigned long)data,
            .rx_buf = (unsigned long)dati,
            .len = len,
            .speed_hz = SPEED,
            .bits_per_word = BITS,
    };

    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if(ret<0) return error("Error receiving message");
    return 0;
}

void spi_close(int fd){
  close(fd);
}


int main(){
  int err;
  int fd = spi_init();

	uint8_t data[] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x40, 0x00, 0x00, 0x00, 0x00, 0x95,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xDE, 0xAD, 0xBE, 0xEF, 0xBA, 0xAD,
		0xF0, 0x0D,
	};

  uint8_t *dati = calloc(RX_SIZE,sizeof(uint8_t));
  err = spi_full_duplex(fd, data, dati, RX_SIZE);
  if(err==1) printf("spi receive error");
  for(int i=0;i<(int)RX_SIZE;i++){
    printf("%.2X ",dati[i]);
  }
  free(dati);
  spi_close(fd);
  return 0;
}
