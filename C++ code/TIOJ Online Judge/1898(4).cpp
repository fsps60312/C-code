//#define SELF
#ifndef SELF
#include"lib1898.h"
#endif
#include<cassert>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int findSample(int N,int CONFIDENCE[],int HOST[],int PROTOCOL[])
{
	int cnt=0;
	for(int i=N-1;i>0;i--)
	{
		switch(PROTOCOL[i])
		{
			//I'm your friend
			case 0:
				if(HOST[i]!=0)
				{
					switch(PROTOCOL[HOST[i]])
					{
						case 0:
//							CONFIDENCE[HOST[HOST[i]]]+=CONFIDENCE[i];
//							CONFIDENCE[HOST[i]]-=CONFIDENCE[i];
//							if(CONFIDENCE[HOST[i]]<0)CONFIDENCE[HOST[i]]=0;
							getmax(CONFIDENCE[HOST[i]],CONFIDENCE[i]);
							CONFIDENCE[HOST[HOST[i]]]+=CONFIDENCE[i];
							break;
						case 1:
							CONFIDENCE[HOST[HOST[i]]]+=CONFIDENCE[i];
							CONFIDENCE[HOST[i]]-=CONFIDENCE[i];
							if(CONFIDENCE[HOST[i]]<0)CONFIDENCE[HOST[i]]=0;
//							getmax(CONFIDENCE[HOST[i]]<CONFIDENCE[HOST[HOST[i]]]?CONFIDENCE[HOST[i]]:CONFIDENCE[HOST[HOST[i]]],CONFIDENCE[i]);
							break;
						case 2:
//							CONFIDENCE[HOST[HOST[i]]]+=CONFIDENCE[i];
//							CONFIDENCE[HOST[i]]-=CONFIDENCE[i];
//							if(CONFIDENCE[HOST[i]]<0)CONFIDENCE[HOST[i]]=0;
							getmax(CONFIDENCE[HOST[i]],CONFIDENCE[i]);
							CONFIDENCE[HOST[HOST[i]]]+=CONFIDENCE[i];
							break;
						default:assert(0);break;
					}
				}
				else
				{
					cnt+=CONFIDENCE[i],CONFIDENCE[0]-=CONFIDENCE[i];
					if(CONFIDENCE[0]<0)CONFIDENCE[0]=0;
				}
				break;
			//my friend is your friend
			case 1:
				CONFIDENCE[HOST[i]]+=CONFIDENCE[i];
				break;
			//we're friends
			case 2:
				getmax(CONFIDENCE[HOST[i]],CONFIDENCE[i]);
				break;
			default:assert(0);break;
		}
	}
	return cnt+CONFIDENCE[0];
}
#ifdef SELF
#include<cstdio>
int main()
{
	printf("%d\n",findSample(6,new int[6]{13,3,6,20,10,15},new int[6]{-1,0,0,1,2,0},new int[6]{-1,0,1,2,1,0}));
}
#endif
