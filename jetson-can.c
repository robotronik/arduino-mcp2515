/*
 * A more pleasant layer that uses the Jetson SPI functions.
 * Free software
 */

#include "jetson-can.h"

spiframe mcpResetFrame(){
  uint8_t data[1] = { (unsigned char)0xC0 };
  spiframe frame;
  frame.data = data;
  frame.len = 1;
  return frame;
}

mcperror mcpReset(){

  spiid file_descriptor = spi_init();
  spi_send(file_descriptor, mcpResetFrame());

  usleep(10000); //10 ns
  return MCP_OK;

}

