#include"friend.h"
#include<algorithm>
#include<cassert>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int findSample(int n,int confidence[],int host[],int protocol[])
{
	int cnt=0;
	for(int i=n-1;i>0;i--)
	{
		switch(protocol[i])
		{
			case 0:cnt+=confidence[i],confidence[host[i]]=max(0,confidence[host[i]]-confidence[i]);break;
			case 1:confidence[host[i]]+=confidence[i];break;
			case 2:getmax(confidence[host[i]],confidence[i]);break;
			default:assert(0);break;
		}
	}
	return cnt+confidence[0];
}
