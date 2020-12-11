/*
 * A more pleasant layer that uses the Jetson SPI functions.
 * Free software
 */

#include "jetson-spi.h"


int main(int argc, char *argv[]){

  /*
   * Initialisation
   */

  int file_descriptor;
  int ret;
  const char *device = "/dev/spidev0.0";
  uint8_t bits = 8;
  uint32_t speed = 500000;

  //reading arguments
  state_t state;
  state = init(argc,argv);

  //opening SPI device
  file_descriptor = open(device, O_RDWR);
  if(file_descriptor<0){
    print_and_abort("Device cannot be opened.");
  }

  /*
   * Writing, then fetching, spi parameters
   */

  //Spi Mode
	ret = ioctl(file_descriptor, SPI_IOC_WR_MODE, &(state.spi_mode));
	if (ret == -1) print_and_abort("can't set spi mode");

	ret = ioctl(file_descriptor, SPI_IOC_RD_MODE, &(state.spi_mode));
	if (ret == -1) print_and_abort("can't get spi mode");

  //Number of bits per word
	ret = ioctl(file_descriptor, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1) print_and_abort("can't set bits per word");

	ret = ioctl(file_descriptor, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1) print_and_abort("can't get bits per word");
  
  //Max frequency
 	ret = ioctl(file_descriptor, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1) print_and_abort("can't set max speed hz");

	ret = ioctl(file_descriptor, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1) print_and_abort("can't get max speed hz");

  //Printing state if verbosity is on
  if(state.verbose != 0){
    printf("spi mode: %d\n", state.spi_mode);
    printf("direction: %s\n", state.rt?"SEND":"RECEIVE");
    printf("bits per word: %d\n", bits);
    printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);
  }

}
