			/* Communication Program */
#include "Header.h"

void sendMsg(char *reqMsg,char *resMsg)
{
  msgToServer(&reqMsg[0],&resMsg[0]);
}
