#define SELF
#ifndef SELF
#include"lib1899.h"
#endif
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
void getmax(LL &a,const LL b){if(b>a)a=b;}
LL SUM[100001];
LL Sum(const int l,const int r){return SUM[r+1]-SUM[l];}
LL findMaxAttraction(int N,int START,int D,int ATTRACTION[])
{
	SUM[0]=0;
	for(int i=0;i<N;i++)SUM[i+1]=SUM[i]+ATTRACTION[i];
	LL ans=0LL;
	for(int l=START;l>=0&&1+((START-1-l)+1)*2<=D;l--)getmax(ans,Sum(l,START));
	for(int r=START;r<N&&1+((r-(START+1))+1)*2<=D;r++)getmax(ans,Sum(START,r));
	for(int l=START-1;l>=0&&((START-1-l)+1)*2<=D;l--)getmax(ans,Sum(l,START-1));
	for(int r=START+1;r<N&&((r-(START+1))+1)*2<=D;r++)getmax(ans,Sum(START+1,r));
	for(int l=START-1;l>=0;l--)
	{
		const int day=1+((START-1)-l+1)*2+(START-l);
		const int d=(D-day)/2;
		if(d<=0)break;
		getmax(ans,Sum(l,min(START+d,N-1)));
	}
	for(int r=START+1;r<N;r++)
	{
		const int day=1+(r-(START+1)+1)*2+(r-START);
		const int d=(D-day)/2;
		if(d<=0)break;
		getmax(ans,Sum(max(START-d,0),r));
	}
	return ans;
}
#ifdef SELF
int main(){printf("%lld\n",findMaxAttraction(5,2,7,new int[5]{10,2,20,30,1}));}
#endif
