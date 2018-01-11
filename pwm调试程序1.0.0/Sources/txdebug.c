#include "txdebug.h"

void TXD(uint8 num,uint8 *str)
{
    SCISendN(1,3,"TXD");
    SCISend1(1,num+48);
    SCISend1(1,':');
    SCISendN(1, strlen(str), str);
}