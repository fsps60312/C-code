#include"wall.h"
#include<bits/stdc++.h>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
void getmin(int &a,const int b){if(b<a)a=b;}
int MN[16000000],MX[16000000];
void Build(const int id,const int l,const int r)
{
	MN[id]=MX[id]=0;
	if(l<r)
	{
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
}
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
	if(l==r){assert(MX[id]==MN[id]),ans[r]=MX[id];return;}
	const int mid=(l+r)/2;
	getmax(MN[id*2],MN[id]),getmax(MN[id*2+1],MN[id]);
	getmax(MX[id*2],MN[id]),getmax(MX[id*2+1],MN[id]);
	getmin(MX[id*2],MX[id]),getmin(MX[id*2+1],MX[id]);
	getmin(MN[id*2],MX[id]),getmin(MN[id*2+1],MX[id]);
	Output(id*2,l,mid,ans),Output(id*2+1,mid+1,r,ans);
}
void buildWall(int N,int K,int O[],int L[],int R[],int H[],int ANS[])
{
	Build(1,0,N-1);
	for(int i=0;i<K;i++)
	{
		if(O[i]==1)BuildUp(1,0,N-1,L[i],R[i],H[i]);
		else BuildDown(1,0,N-1,L[i],R[i],H[i]);
	}
	Output(1,0,N-1,ANS);
}
