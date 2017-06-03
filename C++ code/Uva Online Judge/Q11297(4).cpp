#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,Q,GRID[500][500],MN[2000][2000],MX[2000][2000],X,Y,V,X1,Y1,X2,Y2,O;
bool LEAF;
void Modify2D(int id,int l,int r)
{
	if(l==r)
	{
		if(LEAF){MX[O][id]=MN[O][id]=V;return;}
		MX[O][id]=max(MX[O*2][id],MX[O*2+1][id]);
		MN[O][id]=min(MN[O*2][id],MN[O*2+1][id]);
		return;
	}
	int mid=(l+r)/2;
	if(Y<=mid)Modify2D(id*2,l,mid);
	else Modify2D(id*2+1,mid+1,r);
	MX[O][id]=max(MX[O][id*2],MX[O][id*2+1]);
	MN[O][id]=min(MN[O][id*2],MN[O][id*2+1]);
}
void Modify1D(int id,int l,int r)
{
	if(l<r)
	{
		int mid=(l+r)/2;
		if(X<=mid)Modify1D(id*2,l,mid);
		else Modify1D(id*2+1,mid+1,r);
	}
	LEAF=(l==r);
	O=id;
	Modify2D(1,1,N);
}
void Query2D(int id,int l,int r,int &mx,int &mn)
{
	if(Y1<=l&&r<=Y2)
	{
		mx=max(mx,MX[O][id]);
		mn=min(mn,MN[O][id]);
		return;
	}
	int mid=(l+r)/2;
	if(Y1<=mid)Query2D(id*2,l,mid,mx,mn);
	if(Y2>mid)Query2D(id*2+1,mid+1,r,mx,mn);
}
void Query1D(int id,int l,int r,int &mx,int &mn)
{
	if(X1<=l&&r<=X2)
	{
		O=id;
		Query2D(1,1,N,mx,mn);
		return;
	}
	int mid=(l+r)/2;
	if(X1<=mid)Query1D(id*2,l,mid,mx,mn);
	if(X2>mid)Query1D(id*2+1,mid+1,r,mx,mn);
}
void Build2D(int id,int l,int r)
{
	if(l==r)
	{
		if(LEAF){MX[O][id]=MN[O][id]=GRID[X-1][l-1];return;}
		MX[O][id]=max(MX[O*2][id],MX[O*2+1][id]);
		MN[O][id]=min(MN[O*2][id],MN[O*2+1][id]);
		return;
	}
	int mid=(l+r)/2;
	Build2D(id*2,l,mid);
	Build2D(id*2+1,mid+1,r);
	MX[O][id]=max(MX[O][id*2],MX[O][id*2+1]);
	MN[O][id]=min(MN[O][id*2],MN[O][id*2+1]);
}
void Build1D(int id,int l,int r)
{
	if(l<r)
	{
		int mid=(l+r)/2;
		Build1D(id*2,l,mid);
		Build1D(id*2+1,mid+1,r);
	}
	LEAF=(l==r);
	O=id,X=l;
	int a=LEAF,b=O,c=X;
	Build2D(1,1,N);
//	if(a!=LEAF||b!=O||c!=X)printf("error\n");
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				scanf("%d",&GRID[i][j]);
			}
		}
		Build1D(1,1,N);
		scanf("%d",&Q);
		while(Q--)
		{
			static char type[2];
			scanf("%s",type);
			if(type[0]=='q')
			{
				scanf("%d%d%d%d",&X1,&Y1,&X2,&Y2);
				static int mx,mn;
				mx=-INF,mn=INF;
				Query1D(1,1,N,mx,mn);
				printf("%d %d\n",mx,mn);
			}
			else
			{
				scanf("%d%d%d",&X,&Y,&V);
				Modify1D(1,1,N);
			}
		}
	}
	return 0;
}
