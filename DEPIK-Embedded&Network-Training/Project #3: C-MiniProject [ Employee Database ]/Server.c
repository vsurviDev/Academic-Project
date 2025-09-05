			/* Server Program */
#include "Header.h"

void msgToServer(char *reqMsg,char *resMsg)
{
  switch(reqMsg[0])
  {
    case ADD:
      addDataBase(&reqMsg[0],&resMsg[0]);
      break;
    case DEL:
      delDataBase(&reqMsg[0],&resMsg[0]);
      break;
    case GET:
      getDataBase(&reqMsg[0],&resMsg[0]);
      break;
    case MOD:
      modDataBase(&reqMsg[0],&resMsg[0]);
      break;
    case DIS:
      disDataBase(&reqMsg[0],&resMsg[0]);
      break;
    default:
      resMsg[0]=INVALID_COMMAND;
      printf("\n\t\tSend Message To The Server Is ! VALID\n");
  }
}
