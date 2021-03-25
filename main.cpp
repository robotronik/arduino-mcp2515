#include "mcp2515.h"

int main(int argc, char * argv[]){
  printf("Début !\n");
  MCP2515 mcp = MCP2515();
  printf("Constructeur terminé !\n");
  mcp.reset();
  printf("Reset terminé !\n");
  mcp.setNormalMode();
  mcp.setClkOut(CLKOUT_DIV1);
  mcp.setBitrate(CAN_5KBPS, MCP_8MHZ);
  printf("Sets terminé !\n");
  struct can_frame* frame = (struct can_frame*)malloc(sizeof *frame);
  frame->can_id=0x5;
  frame->can_dlc=0x5;
  int i;
  for(i=0;i<CAN_MAX_DLEN;i++){frame->data[i]=i;}
  printf("Début de l'envoie !\n");
  mcp.sendMessage(frame);
  printf("Travail terminé !\n");
  return 0;
}

