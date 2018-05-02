#include <stdio.h>
#include <stdint.h>

uint8_t getNibble(uint8_t c)
{
	if(c >= '0' && c<= '9')
		return c - '0';
	else if(c >= 'a' && c<= 'f')
		return c - 'a' + 10;
	else if(c >= 'A' && c<= 'F')
		return c - 'A' + 10;
	else
		return -1;
}

uint8_t get_hexcode(uint8_t msb, uint8_t lsb)
{
	uint8_t a1 = getNibble(msb);
	uint8_t a2 = getNibble(lsb);
	if (a1 == -1 || a2 == -1)
		return -1;
	else
		return (((a1 & 0x0F) << 4) | (a2 & 0x0F));
}

