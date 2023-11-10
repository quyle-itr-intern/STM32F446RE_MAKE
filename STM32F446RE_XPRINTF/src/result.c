#include "result.h"

int u32RESULT __attribute__((section(".result")));
int u32DEBUG __attribute__((section(".debug"))) = 20;

void CHECK_RESULT( int a, int b)
{
	u32RESULT = 0;
	if( a != b )
		u32RESULT = 1;
}
