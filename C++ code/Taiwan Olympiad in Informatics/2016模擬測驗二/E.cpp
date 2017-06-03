//#define SELF
#ifndef SELF
#include"wall.h"
#endif
#include<algorithm>
#include<cassert>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
int MN[8000000],MX[8000000];
void Build(const int id,const int l,const int r)
{
	MN[id]=MX[id]=0;
	if(l<r)
	{
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
}
void BuildDown(const int id,const int l,const int r,const int bl,const int br,const int val)
{
	if(r<bl||br<l)return;
	if(l<r)
	{
		getmax(MN[id*2],MN[id]),getmax(MN[id*2+1],MN[id]);
		getmax(MX[id*2],MN[id]),getmax(MX[id*2+1],MN[id]);
	}
	getmin(MN[id],val);
	if(bl<=l&&r<=br){getmin(MX[id],val);return;}
	const int mid=(l+r)/2;
	BuildDown(id*2,l,mid,bl,br,val),BuildDown(id*2+1,mid+1,r,bl,br,val);
}
void BuildUp(const int id,const int l,const int r,const int bl,const int br,const int val)
{
	if(r<bl||br<l)return;
	if(l<r)
	{
		getmin(MX[id*2],MX[id]),getmin(MX[id*2+1],MX[id]);
		getmin(MN[id*2],MX[id]),getmin(MN[id*2+1],MX[id]);
	}
	getmax(MX[id],val);
	if(bl<=l&&r<=br){getmax(MN[id],val);return;}
	const int mid=(l+r)/2;
	BuildUp(id*2,l,mid,bl,br,val),BuildUp(id*2+1,mid+1,r,bl,br,val);
}
void Output(const int id,const int l,const int r,int *ans)
{
	if(l==r){assert(MX[id]==MN[id]);ans[r]=MX[id];return;}
	getmax(MN[id*2],MN[id]),getmax(MN[id*2+1],MN[id]);
	getmax(MX[id*2],MN[id]),getmax(MX[id*2+1],MN[id]);
	getmin(MX[id*2],MX[id]),getmin(MX[id*2+1],MX[id]);
	getmin(MN[id*2],MX[id]),getmin(MN[id*2+1],MX[id]);
	const int mid=(l+r)/2;
	Output(id*2,l,mid,ans),Output(id*2+1,mid+1,r,ans);
}
void buildWall(const int N,const int K,int O[],int L[],int R[],int H[],int ANS[])
{
	Build(1,0,N-1);
	for(int i=0;i<K;i++)
	{
		if(O[i]==1)BuildUp(1,0,N-1,L[i],R[i],H[i]);
		else if(O[i]==2)BuildDown(1,0,N-1,L[i],R[i],H[i]);
		else assert(0);
	}
	Output(1,0,N-1,ANS);
}
#ifdef SELF
int main()
{
  const int n=10;
  const int k=6;

  int i, j;  

  int* op = new int[6]{1,2,2,1,1,2};
  int* left = new int[6]{1,4,3,0,2,6};
  int* right = new int[6]{8,9,6,5,2,7};
  int* height = new int[6]{4,1,5,3,5,0};
  int* finalHeight = new int[n];
  buildWall(n, k, op, left, right, height, finalHeight);

  for (j = 0; j < n; j++)
    printf("%d\n", finalHeight[j]);
  
  return 0;
}
#endif
