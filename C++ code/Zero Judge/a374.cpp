#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=2147483647;
char A[801],B[801];
int K,N,M,DP[800][800];
int LIMIT[26];
int MX[2400][2400],X,O;
bool LEAF;
void Build2D(const int &id,const int &l,const int &r)
{
	if(l==r)
	{
		if(LEAF)MX[O][id]=DP[X][l];
		else MX[O][id]=max(MX[O*2][id],MX[O*2+1][id]);
		return;
	}
	int mid=(l+r)/2;
	Build2D(id*2,l,mid);
	Build2D(id*2+1,mid+1,r);
	MX[O][id]=max(MX[O][id*2],MX[O][id*2+1]);
}
void Build1D(const int &id,const int &l,const int &r)
{
	if(l<r)
	{
		int mid=(l+r)/2;
		Build1D(id*2,l,mid);
		Build1D(id*2+1,mid+1,r);
	}
	LEAF=(l==r);
	O=id;
	X=l;
	Build2D(1,0,M-1);
}
int Y,V,X1,Y1,X2,Y2;
void Modify2D(const int &id,const int &l,const int &r)
{
	if(l==r)
	{
		if(LEAF)MX[O][id]=V;
		else MX[O][id]=max(MX[O*2][id],MX[O*2+1][id]);
		return;
	}
	int mid=(l+r)/2;
	if(Y<=mid)Modify2D(id*2,l,mid);
	else Modify2D(id*2+1,mid+1,r);
	MX[O][id]=max(MX[O][id*2],MX[O][id*2+1]);
}
void Modify1D(const int &id,const int &l,const int &r)
{
	if(l<r)
	{
		int mid=(l+r)/2;
		if(X<=mid)Modify1D(id*2,l,mid);
		else Modify1D(id*2+1,mid+1,r);
	}
	LEAF=(l==r);
	O=id;
	Modify2D(1,0,M-1);
}
void Query2D(const int &id,const int &l,const int &r,int &ans)
{
	if(l>Y2||r<Y1)return;
	if(Y1<=l&&r<=Y2){ans=max(ans,MX[O][id]);return;}
	int mid=(l+r)/2;
	Query2D(id*2,l,mid,ans);
	Query2D(id*2+1,mid+1,r,ans);
}
void Query1D(const int &id,const int &l,const int &r,int &ans)
{
	if(l>X2||r<X1)return;
	if(X1<=l&&r<=X2){O=id;Query2D(1,0,M-1,ans);return;}
	int mid=(l+r)/2;
	Query1D(id*2,l,mid,ans);
	Query1D(id*2+1,mid+1,r,ans);
}
int Max(const int &x1,const int &y1,const int &x2,const int &y2)
{
	X1=x1,Y1=y1,X2=x2,Y2=y2;
	int ans=-INF;
	Query1D(1,0,N-1,ans);
	return ans;
}
int Solve()
{
	N=-1;while(A[++N]);
	M=-1;while(B[++M]);
	for(int i=0;i<N;i++)for(int j=0;j<M;j++)DP[i][j]=0;
	for(int i=0;i<N;i++)DP[i][0]=(A[i]==B[0]?1:0);
	for(int i=0;i<M;i++)DP[0][i]=(A[0]==B[i]?1:0);
	Build1D(1,0,N-1);
	for(int i=1;i<N;i++)
	{
		for(int j=1;j<M;j++)
		{
			if(A[i]!=B[j])continue;
			const int limit=LIMIT[A[i]-'A'];
			int &dp=DP[i][j];
			dp=Max(max(0,i-limit),max(0,j-limit),i-1,j-1)+1;
			V=dp,X=i,Y=j;
			Modify1D(1,0,N-1);
		}
	}
	int ans=0;
	for(int i=0;i<N;i++)for(int j=0;j<M;j++)ans=max(ans,DP[i][j]);
	static int kase=1;
//	printf("Case %d:\n",kase++);
//	for(int i=0;i<N;i++)
//	{
//		for(int j=0;j<M;j++)printf(" %d",DP[i][j]);
//		puts("");
//	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s%s%d",A,B,&K)==3)
	{
		while(K--)
		{
			for(int i=0;i<26;i++)LIMIT[i]=INF;
			for(;;)
			{
				static char a[2];
				scanf("%s",a);
				if(a[0]=='$')break;
				else
				{
					static int v;scanf("%d",&v);
					LIMIT[a[0]-'A']=v+1;
				}
			}
			printf("%d",Solve());
			if(K)printf(" ");
		}
		puts("");
		break;
	}
	return 0;
}
