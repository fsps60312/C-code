#include "encoder.h"
#include "encoderlib.h"

void encode(int N, int M[])
{
	int cur=0,now=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<8;j++,cur++)
		{
			if((now&(1<<j))!=(M[i]&(1<<j)))send(cur),now^=(1<<j);
		}
	}
}
