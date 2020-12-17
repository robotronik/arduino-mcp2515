/*
 * A more pleasant layer that uses the Jetson SPI functions.
 * Free software
 */

#include "jetson-spi.h"
#include <time.h>
#include <unistd.h>

#ifndef __JETSON_CAN
#define __JETSON_CAN

typedef enum{
    CAN_5KBPS,
    CAN_10KBPS,
    CAN_20KBPS,
    CAN_31K25BPS,
    CAN_33KBPS,
    CAN_40KBPS,
    CAN_50KBPS,
    CAN_80KBPS,
    CAN_83K3BPS,
    CAN_95KBPS,
    CAN_100KBPS,
    CAN_125KBPS,
    CAN_200KBPS,
    CAN_250KBPS,
    CAN_500KBPS,
    CAN_1000KBPS
} mcpspeed;

typedef enum{
    MCP_OK,
    MCP_ERR
} mcperror;

typedef enum{
    NORMAL,
    LOOPBACK,
    CONFIG,
    LISTENONLY
} mcpmode;

#define CAN_MAX_DLEN 8
typedef struct{
    __u32 can_id;
    __u8 can_dlc;
    __u8 data[CAN_MAX_DLEN] __attribute__((aligned(8)));
} can_frame;

mcperror mcpReset();
mcperror mcpRead();
mcperror mcpWrite(can_frame data);
mcperror mcpBitrate(mcpspeed speed);
mcperror mcpModeSet(mcpmode mode);

#endif
