#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,M,MN[8000000],MX[8000000];
void getmax(int &a,const int b){if(b>a)a=b;}
void getmin(int &a,const int b){if(b<a)a=b;}
void Build(const int id,const int l,const int r)
{
	MN[id]=MX[id]=0;
	if(l==r)return;
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
}
void PutDown(const int id)
{
	if(MN[id]>MN[id*2])getmax(MX[id*2],MN[id*2]=MN[id]);
	if(MX[id]<MX[id*2])getmin(MN[id*2],MX[id*2]=MX[id]);
	if(MN[id]>MN[id*2+1])getmax(MX[id*2+1],MN[id*2+1]=MN[id]);
	if(MX[id]<MX[id*2+1])getmin(MN[id*2+1],MX[id*2+1]=MX[id]);
}
void Modify(const int id,const int l,const int r,const int lb,const int rb,const int v,const int op)
{
	if(r<lb||rb<l)return;
	if(lb<=l&&r<=rb)
	{
		if(op==1)getmax(MN[id],v),getmax(MX[id],MN[id]);
		else getmin(MX[id],v),getmin(MN[id],MX[id]);
		return;
	}
	PutDown(id);
	const int mid=(l+r)/2;
	Modify(id*2,l,mid,lb,rb,v,op);
	Modify(id*2+1,mid+1,r,lb,rb,v,op);
	MN[id]=min(MN[id*2],MN[id*2+1]);
	MX[id]=max(MX[id*2],MX[id*2+1]);
}
void Print(const int id,const int l,const int r)
{
	if(l==r){assert(MN[id]==MX[id]),printf("%d\n",MN[id]);return;}
	PutDown(id);
	const int mid=(l+r)/2;
	Print(id*2,l,mid),Print(id*2+1,mid+1,r);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		Build(1,0,N-1);
		while(M--)
		{
			static int op,l,r,h;
			scanf("%d%d%d%d",&op,&l,&r,&h);
			assert(op==1||op==2);
			Modify(1,0,N-1,l,r,h,op);
		}
		Print(1,0,N-1);
	}
	return 0;
}
