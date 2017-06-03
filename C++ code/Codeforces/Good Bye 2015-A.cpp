#include<cstdio>
#include<cassert>
using namespace std;
int N;
int Month()
{
	if(N<=29)return 12;
	else if(N<=30)return 11;
	else return 7;
}
int main()
{
	static char s1[100],s2[100];
	assert(scanf("%d%s%s",&N,s1,s2)==3);
	if(s2[0]=='w')
	{
		switch(N)
		{
			case 1:
			case 2:
			case 3:
			case 4:puts("52");break;
			case 5:
			case 6:puts("53");break;
			case 7:puts("52");break;
			default:assert(0);break;
		}
	}
	else if(s2[0]=='m')
	{
		printf("%d\n",Month());
	}
	else assert(0);
	return 0;
}
