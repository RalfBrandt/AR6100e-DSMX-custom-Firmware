#include "config.h"

extern CHAR  E2PROM_1_bE2Write(WORD wAddr, BYTE * pbData, WORD wByteCount, CHAR cTemperature);
extern void  E2PROM_1_E2Read(WORD wAddr, BYTE * pbDataDest, WORD wByteCount);

RAM_D mem;
#define buf mem.buf


void SaveConfig(void *Data,BYTE Cnt)
{
BYTE n;	
#ifndef DEBUG
E2PROM_1_E2Read(0,buf,32);
#endif
buf[0]=CONFIG_ID;
for (n=0;n<Cnt;n++)
	buf[n+1]=((BYTE *)Data)[n];
#ifndef DEBUG
E2PROM_1_bE2Write(0,buf,64,25);
#endif
}

BOOL ReadConfig(void *Data,BYTE Cnt)
{
BYTE n;	
#ifndef DEBUG
E2PROM_1_E2Read(0,buf,32);
#endif
if(buf[0]!=CONFIG_ID)
	{
		return FALSE;
	}
else
	{
	for (n=0;n<Cnt;n++)
		((BYTE *)Data)[n]=buf[n+1];
	}
return TRUE;
}



