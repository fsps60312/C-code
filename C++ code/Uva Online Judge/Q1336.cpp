#include<cstdio>
#include<algorithm>
using namespace std;
int N;
double V,X,DP[1001][1001][2];//from i to j , at left or right
struct Damage
{
	double x,c,d;
}DAMAGE[1001];
bool cmp_DAMAGE(Damage a,Damage b){return a.x<b.x;}
double TADD[1001];
double get_ADSUM(int l,int r,int len)
{
	if(len<0)len*=-1;
	return ((TADD[N]-TADD[0])-(TADD[r]-TADD[l-1]))*len/V;
}
void getmin(double &a,double b){if(b<a)a=b;}
int find_nearpos()
{
	int l=1,r=N;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(DAMAGE[mid].x<X)l=mid+1;
		else r=mid;
	}
	return l;
}
double min(double a,double b){return a<b?a:b;}
double get_len(int a,int b){return DAMAGE[a].x-DAMAGE[b].x;}
void merge(int l,int r)
{
	getmin(DP[l][r][0],DP[l+1][r][0]+get_ADSUM(l+1,r,get_len(l+1,l)));
	getmin(DP[l][r][0],DP[l+1][r][1]+get_ADSUM(l+1,r,get_len(r,l)));
	getmin(DP[l][r][1],DP[l][r-1][0]+get_ADSUM(l,r-1,get_len(l,r)));
	getmin(DP[l][r][1],DP[l][r-1][1]+get_ADSUM(l,r-1,get_len(r-1,r)));
}
int main()
{
	//freopen("in.txt","r",stdin); 
	while(scanf("%d%lf%lf",&N,&V,&X)==3&&(N||V||X))
	{
		double cost=0;
		for(int i=1;i<=N;i++)
		{
			Damage &d=DAMAGE[i];
			scanf("%lf%lf%lf",&d.x,&d.c,&d.d);
			cost+=d.c;
		}
		sort(DAMAGE,DAMAGE+N,cmp_DAMAGE);
		TADD[0]=0;
		for(int i=1;i<=N;i++)TADD[i]=TADD[i-1]+DAMAGE[i].d;
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=N;j++)
			{
				DP[i][j][0]=DP[i][j][1]=1e10;
			}
		}
		int tp=find_nearpos();
		double p;
		if(DAMAGE[tp].x>X)
		{
			DP[tp][tp][0]=DP[tp][tp][1]=cost+get_ADSUM(tp,tp-1,X-DAMAGE[tp].x);
			if(tp>=1)
			{
				DP[tp-1][tp-1][0]=DP[tp-1][tp-1][1]=cost+get_ADSUM(tp,tp-1,X-DAMAGE[tp-1].x);//in the mid of two point
				p=tp-0.5;
			}
			else//too left at first
			{
				p=tp-0.5;
			}
		}
		else
		{
			DP[tp][tp][0]=DP[tp][tp][1]=cost+get_ADSUM(tp,tp-1,X-DAMAGE[tp].x);//too right at first
			p=tp+0.5;
		}
//		printf("p=%.1lf between %.1lf and %.1lf\n",p);
		for(int l=1;l<N;l++)
		{
			for(int i=1;i+l<=N;i++)
			{
				if(i-p>1||p-(i+l)>1)continue;
				merge(i,i+l);
			}
		}
		printf("%d\n",(int)(min(DP[1][N][0],DP[1][N][1])+1e-8));
	}
	return 0;
}
