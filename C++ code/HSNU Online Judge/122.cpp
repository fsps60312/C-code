#include"interactive/122.h"
#include<cstdio>
#include<cassert>
using namespace std;
//void init(int &N,int &X0,int &Y0){N=19,X0=7,Y0=4;}
//bool examine(int X,int Y)
//{
//	X-=4,Y-=1;
//	if(X<1||Y<1)return false;
//	X--,Y--;
//	X/=3,Y/=3;
//	return (X+Y)%2==0&&X<5&&Y<5;
//}
//void solution(int Xc,int Yc)
//{
//	printf("solution(%d,%d)\n",Xc,Yc);
//	puts(Xc==12&&Yc==9?"AC":"WA");
//	for(;;);
//}
//////////////////////////////////////////////////
int N,X0,Y0,M;
bool Examine(int x,int y)
{
	if(x<1||x>N||y<1||y>N)return false;
	return examine(x,y);
}
int main()
{
	init(N,X0,Y0);
//	printf("%d\n",examine(X0,Y0));
//	for(int i=19;i>=1;i--)
//	{
//		for(int j=1;j<=19;j++)printf("%d",examine(j,i));
//		puts("");
//	}
	int right=X0;
	for(int d=0;;d++)
	{
		right+=1<<d;
		if(!Examine(right,Y0))
		{
			right-=1<<d;
			for(d--;d>=0;d--)if(Examine(right+(1<<d),Y0))right+=1<<d;
			break;
		}
	}
	int left=X0;
	for(int d=0;;d++)
	{
		left-=1<<d;
		if(!Examine(left,Y0))
		{
			left+=1<<d;
			for(d--;d>=0;d--)if(Examine(left-(1<<d),Y0))left-=1<<d;
			break;
		}
	}
	M=right-left+1;
	assert(M%2==1);
	int down=Y0;
	for(int d=0;;d++)
	{
		down-=1<<d;
		if(!Examine(X0,down))
		{
			down+=1<<d;
			for(d--;d>=0;d--)if(Examine(X0,down-(1<<d)))down-=1<<d;
			break;
		}
	}
	int up=down+M-1;
//	printf("(%d,%d),(%d,%d)\n",left,right,down,up);
	X0=left+(right-left)/2;
	Y0=down+(up-down)/2;
	while(Examine(X0-M,Y0-M))X0-=M,Y0-=M;
	while(Examine(X0-M*2,Y0))X0-=M*2;
	while(Examine(X0,Y0-M*2))Y0-=M*2;
	solution(X0+M*2,Y0+M*2);
	return 0;
}
