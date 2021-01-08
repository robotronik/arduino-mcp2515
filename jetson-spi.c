/*
 * A more pleasant layer that uses the Jetson SPI functions.
 * Free software
 */

#include "jetson-spi.h"


/*
 * Initialise the SPI parameters to what is specified in jetson-spi.h. Returns a
 * file descriptor pointing to the SPI device that was opened. Remeber to close it.
 */

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

int error(const char *err){
  printf("%s",err);
  return 1;
}

/*
 * Sends a SPI packet without reading the response.
 * Parameters: fd: The file descriptor opened with spi_init(),
 * data: an array of uint8_t to be transmitted over spi.
 * len: the lenght of the provided data array.
 * returns 1 if something went wrong
 */

int spi_send(const int fd, spiframe send_data){

  struct spi_ioc_transfer tr = {
    .tx_buf = (unsigned long)send_data.data,
    .len = send_data.len,
    .cs_change = 1,
    .speed_hz = SPEED,
    .bits_per_word = BITS,
  };

  int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
  if(ret<0) return error("Error sending SPI message");
  free(send_data.data);
  return 0;
}

/*
 * Sends a SPI packet and reads the answer.
 * Parameters: fd: The file descriptor opened with spi_init(),
 * tx: an array of uint8_t to be transmitted over spi.
 * rx: a pointer to the array where the response will be
 * stored. Can only be as long as tx.
 * len: the lenght of the provided data array.
 * returns 1 if something went wrong
 */
int spi_full_duplex(const int fd, spiframe send_data, spiframe receive_data){

    struct spi_ioc_transfer tr = {
      .tx_buf = (unsigned long)send_data.data,
      .rx_buf = (unsigned long)receive_data.data,
      .len = send_data.len,
      .speed_hz = SPEED,
      .cs_change = 1,
      .bits_per_word = BITS,
    };

    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if(ret<0) return error("Error during the transmission of the message");
    free(send_data.data);
    return 0;
}


/*
 * Closes the SPI device pointed by the file descriptor.
 * Remeber to use this!
 */
void spi_close(int fd){
  close(fd);
}

spiframe spi_make_frame(uint8_t* data, const int len){
  spiframe frame;
  frame.len = len;
  frame.data = data;
  return frame;
}

spiframe spi_make_void_frame(const int len){
    uint8_t* data;
    data = (uint8_t*)calloc(len, sizeof(*data));
    memset(data, 0, len * sizeof(*data));
    spiframe frame = spi_make_frame(data, len);
    return frame;
}

void append_data(uint8_t* data, int* point, const uint8_t* add, const int addlen){
    const int addend = *point+addlen;
    while(*point<addend){
        data[*point] = add[*point];
        (*point)++;
    }
}

void append_single_data(uint8_t* data, int* point, const uint8_t add){
    data[*point] = add;
    (*point)++;
}

/*
 * Temporary test code //TODO does not work after spi_full_duplex parameters change
 */
/*int main(){*/
  /*int err;*/
  /*int fd = spi_init();*/

  /*uint8_t data[] = {*/
    /*0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,*/
    /*0x40, 0x00, 0x00, 0x00, 0x00, 0x95,*/
    /*0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,*/
    /*0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,*/
    /*0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,*/
    /*0xDE, 0xAD, 0xBE, 0xEF, 0xBA, 0xAD,*/
    /*0xF0, 0x0D,*/
  /*};*/

  /*uint8_t *dati = calloc(RX_SIZE,sizeof(uint8_t));*/
  /*err = spi_full_duplex(fd, data, dati);*/
  /*if(err==1) printf("spi receive error");*/
  /*for(int i=0;i<(int)RX_SIZE;i++){*/
    /*printf("%.2X ",dati[i]);*/
  /*}*/
  /*printf("\n");*/
  /*free(dati);*/
  /*spi_close(fd);*/
  /*return 0;*/
/*}*/

