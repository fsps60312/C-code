#include<cstdio>
#include<cassert>
using namespace std;
int N,SUM[2096][2096],O,X,Y,X1,Y1,X2,Y2,V;
void Build2D(const int &id,const int &l,const int &r)
{
	if(l<r)
	{
		int mid=(l+r)/2;
		Build2D(id*2,l,mid);
		Build2D(id*2+1,mid+1,r);
	}
	SUM[O][id]=0;
}
void Build1D(const int &id,const int &l,const int &r)
{
	if(l<r)
	{
		int mid=(l+r)/2;
		Build1D(id*2,l,mid);
		Build1D(id*2+1,mid+1,r);
	}
	O=id;
	Build2D(1,0,N-1);
}
bool LEAF;
void Add2D(const int &id,const int &l,const int &r)
{
	if(l==r)
	{
		if(LEAF)SUM[O][id]+=V;
		else SUM[O][id]=SUM[O*2][id]+SUM[O*2+1][id];
		return;
	}
	int mid=(l+r)/2;
	if(Y<=mid)Add2D(id*2,l,mid);
	else Add2D(id*2+1,mid+1,r);
	SUM[O][id]=SUM[O][id*2]+SUM[O][id*2+1];
}
void Add1D(const int &id,const int &l,const int &r)
{
	if(l<r)
	{
		int mid=(l+r)/2;
		if(X<=mid)Add1D(id*2,l,mid);
		else Add1D(id*2+1,mid+1,r);
	}
	LEAF=(l==r),O=id;
	Add2D(1,0,N-1);
}
void Query2D(const int &id,const int &l,const int &r,int &sum)
{
	if(r<Y1||l>Y2)return;
	if(Y1<=l&&r<=Y2){sum+=SUM[O][id];return;}
	int mid=(l+r)/2;
	Query2D(id*2,l,mid,sum);
	Query2D(id*2+1,mid+1,r,sum);
} 
void Query1D(const int &id,const int &l,const int &r,int &sum)
{
	if(r<X1||l>X2)return;
	if(X1<=l&&r<=X2){O=id;Query2D(1,0,N-1,sum);return;}
	int mid=(l+r)/2;
	Query1D(id*2,l,mid,sum);
	Query1D(id*2+1,mid+1,r,sum);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	Build1D(1,0,N-1);
	int type;
	while(scanf("%d",&type)==1)
	{
		if(type==1)
		{
			scanf("%d%d%d",&X,&Y,&V);
			Add1D(1,0,N-1);
		}
		else if(type==2)
		{
			int sum=0;
			scanf("%d%d%d%d",&X1,&Y1,&X2,&Y2);
			Query1D(1,0,N-1,sum);
			printf("%d\n",sum);
		}
		else assert(0);
	}
	return 0;
}
