#include "lib1895.h"
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int MX[16000000],MN[16000000];
void Build(const int id,const int l,const int r)
{
	MX[id]=MN[id]=0;
	if(l<r)
	{
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
}
void getmax(int &a,const int b){if(b>a)a=b;}
void getmin(int &a,const int b){if(b<a)a=b;}
void BuildUp(const int id,const int l,const int r,const int bl,const int br,const int val)
{
	if(r<bl||br<l)return;
	getmin(MX[id*2],MX[id]),getmin(MX[id*2+1],MX[id]);
	getmin(MN[id*2],MX[id]),getmin(MN[id*2+1],MX[id]);
	getmax(MX[id],val);
	if(bl<=l&&r<=br){getmax(MN[id],val);return;}
	const int mid=(l+r)/2;
	BuildUp(id*2,l,mid,bl,br,val),BuildUp(id*2+1,mid+1,r,bl,br,val);
}
void BuildDown(const int id,const int l,const int r,const int bl,const int br,const int val)
{
	if(r<bl||br<l)return;
	getmax(MN[id*2],MN[id]),getmax(MN[id*2+1],MN[id]);
	getmax(MX[id*2],MN[id]),getmax(MX[id*2+1],MN[id]);
	getmin(MN[id],val);
	if(bl<=l&&r<=br){getmin(MX[id],val);return;}
	const int mid=(l+r)/2;
	BuildDown(id*2,l,mid,bl,br,val),BuildDown(id*2+1,mid+1,r,bl,br,val);
}
void Output(const int id,const int l,const int r,int *ans)
{
	if(l==r){assert(MN[id]==MX[id]);ans[r]=MN[id];return;}
	getmax(MN[id*2],MN[id]),getmax(MN[id*2+1],MN[id]);
	getmax(MX[id*2],MN[id]),getmax(MX[id*2+1],MN[id]);
	getmin(MX[id*2],MX[id]),getmin(MX[id*2+1],MX[id]);
	getmin(MN[id*2],MX[id]),getmin(MN[id*2+1],MX[id]);
	const int mid=(l+r)/2;
	Output(id*2,l,mid,ans),Output(id*2+1,mid+1,r,ans);
}
void buildWall(int N,int K,int T[],int L[],int R[],int H[],int ANS[])
{
	Build(1,0,N-1);
	for(int i=0;i<K;i++)
	{
		if(T[i]==1)
		{
			BuildUp(1,0,N-1,L[i],R[i],H[i]);
		}
		else if(T[i]==2)
		{
			BuildDown(1,0,N-1,L[i],R[i],H[i]);
		}
		else assert(0);
	}
	Output(1,0,N-1,ANS);
}
