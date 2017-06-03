#include<cstdio>
#include<cassert>
using namespace std;
int F[10001];
int main()
{
//	freopen("out.txt","w",stdout);
	F[2]=1;
	for(int i=3;i<=10000;i++)
	{
		for(int j=2;;j++)
		{
			assert(j<i);
			if(i%j){F[i]=j;break;}
		}
	}
	for(int i=2;i<=10000;i+=2)printf("F(%d)=%d\n",i,F[i]);
	//2:2+2n
	//3:6+6n
	//4:12+12n
	//5:60+60n
	//6:60+60n
	
	return 0;
}
