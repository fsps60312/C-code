#include<cstdio>
#include<cassert>
using namespace std;
int main()
{
	for(int z=1,cnt=0;cnt<40;z++)
	{
		bool valid=true;
		for(int x=1,y;(y=(z-x/2)/(x+1))>=1;x++)
		{
			if((x+1)*y+x/2==z){valid=false;break;}
		}
		if(valid)
		{
			cnt++;
			printf("z[%d]=%d\n",cnt,z);
		}
	}
	return 0;
}
