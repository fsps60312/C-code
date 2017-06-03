#define SELF
#ifndef SELF
#include"lib1898.h"
#endif
#include<cassert>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int findSample(int N,int CONFIDENCE[],int HOST[],int PROTOCOL[])
{
	static int *INCLUDE[100000],*EXCLUDE[100000];
	INCLUDE[0]=new int(CONFIDENCE[0]),EXCLUDE[0]=new int(0);
	for(int i=1;i<N;i++)
	{
		switch(PROTOCOL[i])
		{
			//I'm your friend
			case 0:
				EXCLUDE[i]=EXCLUDE[HOST[i]];
				INCLUDE[i]=EXCLUDE[HOST[i]],*INCLUDE[i]+=CONFIDENCE[i];
				break;
			//my friend is your friend
			case 1:
				EXCLUDE[i]=INCLUDE[HOST[i]];
				INCLUDE[i]=new int(CONFIDENCE[i]+CONFIDENCE[HOST[i]]);
				if(*INCLUDE[i]>=*INCLUDE[HOST[i]])INCLUDE[HOST[i]]=INCLUDE[i];
				break;
			//we're all your friend
			case 2:
				INCLUDE[i]=new int(CONFIDENCE[i]);
				EXCLUDE[i]=new int(0);
				break;
			default:assert(0);break;
		}
	}
	int ans=0;
	for(int i=0;i<N;i++)getmax(ans,*INCLUDE[i]),getmax(ans,*EXCLUDE[i]);
	return ans;
}
#ifdef SELF
#include<cstdio>
int main()
{
	printf("%d\n",findSample(6,new int[6]{13,3,6,20,10,15},new int[6]{-1,0,0,1,2,0},new int[6]{-1,0,1,2,1,0}));
}
#endif
