#include<cstdio>
#include<cassert>
using namespace std;
struct Point
{
	int X,Y;
};
struct Vector
{
	int X,Y;
	Vector(){}
	Vector(const int _X,const int _Y):X(_X),Y(_Y){}
};
Vector operator-(const Point &a,const Point &b){return Vector(a.X-b.X,a.Y-b.Y);}
int Cross(const Vector &a,const Vector &b){return a.X*b.Y-a.Y*b.X;}
int Dot(const Vector &a,const Vector &b){return a.X*b.X+a.Y*b.Y;}
int N,K,MOD;
Point P[600],S[20000];
bool VALID[600][600];
int CNT[600][600];
typedef long long LL;
const LL INF=9223372036854775807LL;
LL DP[600][600][2],ONE[600][600];
int main()
{
//	freopen("in.txt","r",stdin);
//	printf("%d\n",Cross(Vector(1,0),Vector(0,1)));
	while(scanf("%d%d%d",&N,&K,&MOD)==3)
	{
		for(int i=0;i<N;i++)scanf("%d%d",&P[i].X,&P[i].Y);
		for(int i=0;i<K;i++)scanf("%d%d",&S[i].X,&S[i].Y);
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)VALID[i][j]=true,CNT[i][j]=0;
		for(int i=0;i<K;i++)
		{
			for(int j=0,k=0;j<N;j++)
			{
				if(k==j)k=(k+1)%N;
				while(Cross(S[i]-P[j],P[k]-P[j])>0)k=(k+1)%N;
				if(Cross(S[i]-P[j],P[k]-P[j])==0)VALID[j][k]=VALID[k][j]=false;
				++CNT[j][k];
			}
		}
		for(int i=0;i<N;i++)for(int j=(i+1)%N,pre=i;j!=i;pre=j,j=(j+1)%N)CNT[i][j]+=CNT[i][pre];
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)ONE[i][j]=0LL;
//		for(int i=0;i<N;i++)for(int j=0;j<N;j++)printf("(%d,%d)=%d\n",i,j,CNT[i][j]);
		for(int i=0;i<N;i++)++ONE[i][(i+1)%N];
		for(int gap=2;gap<N;gap++)
		{
			for(int i=0;i<N;i++)
			{
				const int j=(i+gap)%N;
				if(VALID[i][j])
				{
					for(int _k=1;_k<gap;_k++)
					{
						const int k=(i+_k)%N;
						if((CNT[i][j]-(CNT[i][k]+CNT[k][j]))%2==0)ONE[i][j]+=ONE[i][k]*ONE[k][j];
					}
				}
			}
		}
		LL ans=ONE[1][N-1];
		for(int i=2;i+1<N;i++)if(VALID[0][i])ans+=ONE[0][i]*ONE[i][0];//,printf("%d\n",ONE[0][i]*ONE[i][0]);
		printf("%lld\n",ans);
	}
	return 0;
}
