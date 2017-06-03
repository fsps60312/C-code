#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int MX[2000][2000],MN[2000][2000],N,Q,X1,Y1,X2,Y2,X,Y,V,O;
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
void Query2D(int id,int l,int r,int &mn,int &mx)
{
	if(Y1<=l&&r<=Y2)
	{
//		printf(" (%d,%d)\n",l,r);
		mn=min(mn,MN[O][id]);
		mx=max(mx,MX[O][id]);
		return;
	}
	int mid=(l+r)/2;
	if(Y1<=mid)Query2D(id*2,l,mid,mn,mx);
	if(Y2>mid)Query2D(id*2+1,mid+1,r,mn,mx);
}
void Query1D(int id,int l,int r,int &mn,int &mx)
{
	if(X1<=l&&r<=X2)
	{
		O=id;
//		printf("(%d,%d)\n",l,r);
		Query2D(1,1,N,mn,mx);
		return;
	}
	int mid=(l+r)/2;
	if(X1<=mid)Query1D(id*2,l,mid,mn,mx);
	if(X2>mid)Query1D(id*2+1,mid+1,r,mn,mx);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(X=1;X<=N;X++)
		{
			for(Y=1;Y<=N;Y++)
			{
				scanf("%d",&V);
				Modify1D(1,1,N);
			}
		}
		scanf("%d",&Q);
		while(Q--)
		{
			static char type[2];
			scanf("%s",type);
			if(type[0]=='c')
			{
				scanf("%d%d%d",&X,&Y,&V);
				Modify1D(1,1,N);
			}
			else
			{
				scanf("%d%d%d%d",&X1,&Y1,&X2,&Y2);
				static int mn,mx;
				mn=INF,mx=-INF;
				Query1D(1,1,N,mn,mx);
				printf("%d %d\n",mx,mn);
			}
		}
	}
	return 0;
}
