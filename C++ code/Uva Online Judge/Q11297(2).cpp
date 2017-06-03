#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,GRID[500][500];
int MN[2000][2000],MX[2000][2000];
void PutDown(int fa,int id)
{
	if(MN[fa][id]<MX[fa][id])return;
	MN[fa][id*2]=MN[fa][id*2+1]=
	MX[fa][id*2]=MX[fa][id*2+1]=MN[fa][id];
}
void PutUp(int fa,int id)
{
	MN[fa][id]=min(MN[fa][id*2],MN[fa][id*2+1]);
	MX[fa][id]=max(MX[fa][id*2],MX[fa][id*2+1]);
}
void Modify2(int fa,int id,int l,int r,int y1,int y2,int v)
{
	if(l>y2||r<y1)return;
	if(y1<=l&&r<=y2)
	{
		printf(" (%d,%d)\n",l,r);
		MN[fa][id]=MX[fa][id]=v;
	}
	if(l==r)return;
	int mid=(l+r)/2;
	Modify2(fa,id*2,l,mid,y1,y2,v);
	Modify2(fa,id*2+1,mid+1,r,y1,y2,v);
	MN[fa][id]=min(MN[fa][id*2],MN[fa][id*2+1]);
	MX[fa][id]=max(MX[fa][id*2],MX[fa][id*2+1]);
	if(MX[fa][id]==10)printf(" (%d,%d)\n",l,r);
}
void Modify1(int id,int l,int r,int x1,int x2,int y1,int y2,int v)
{
	if(l>x2||r<x1)return;
	int mid=(l+r)/2;
	if(x1<=l&&r<=x2)
	{
		printf("(%d,%d)\n",l,r);
		Modify2(id,1,0,N-1,y1,y2,v);
	}
	if(l==r)return;
	Modify1(id*2,l,mid,x1,x2,y1,y2,v);
	Modify1(id*2+1,mid+1,r,x1,x2,y1,y2,v);
}
void Query2(int fa,int id,int l,int r,int y1,int y2,int &mn,int &mx)
{
//	printf(" (%d,%d)\n",l,r);
	if(l>y2||r<y1)return;
	if(y1<=l&&r<=y2)
	{
//		printf("pass\n");
		mn=min(mn,MN[fa][id]);
		mx=max(mx,MX[fa][id]);
		return;
	}
	PutDown(fa,id);
	int mid=(l+r)/2;
	Query2(fa,id*2,l,mid,y1,y2,mn,mx);
	Query2(fa,id*2+1,mid+1,r,y1,y2,mn,mx);
}
void Query1(int id,int l,int r,int x1,int x2,int y1,int y2,int &mn,int &mx)
{
	if(l>x2||r<x1)return;
	if(x1<=l&&r<=x2)
	{
//		printf("(%d,%d)\n",l,r);
		Query2(id,1,0,N-1,y1,y2,mn,mx);
		return;
	}
	int mid=(l+r)/2;
	Query1(id*2,l,mid,x1,x2,y1,y2,mn,mx);
	Query1(id*2+1,mid+1,r,x1,x2,y1,y2,mn,mx);
}
void Build2(int fa,int id,int l,int r,int fl,int fr)
{
	if(l==r)
	{
		if(fl==fr)MX[fa][id]=MN[fa][id]=GRID[fl][l];
		else
		{
			MX[fa][id]=max(MX[fa*2][id],MX[fa*2+1][id]);
			MN[fa][id]=min(MN[fa*2][id],MN[fa*2+1][id]);
		}
		return;
	}
	int mid=(l+r)/2;
	Build2(fa,id*2,l,mid,fl,fr);
	Build2(fa,id*2+1,mid+1,r,fl,fr);
	PutUp(fa,id);
}
void Build1(int id,int l,int r)
{
	if(l==r)
	{
		Build2(id,1,0,N-1,l,r);
		return;
	}
	int mid=(l+r)/2;
	Build1(id*2,l,mid);
	Build1(id*2+1,mid+1,r);
	Build2(id,1,0,N-1,l,r);
}
int Q;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				scanf("%d",&GRID[i][j]);
			}
		}
		Build1(1,0,N-1);
		scanf("%d",&Q);
		while(Q--)
		{
			static char type[2];
			scanf("%s",type);
			if(type[0]=='q')
			{
				static int x1,y1,x2,y2,mn,mx;
				scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
				x1--,y1--,x2--,y2--;
				mn=INF,mx=-INF;
				Query1(1,0,N-1,x1,x2,y1,y2,mn,mx);
				printf("%d %d\n",mx,mn);
			}
			else if(type[0]=='c')
			{
				static int x,y,v;
				scanf("%d%d%d",&x,&y,&v);
				x--,y--;
				Modify1(1,0,N-1,x,x,y,y,v);
			}
			else assert(0);
		}
	}
	return 0;
}
