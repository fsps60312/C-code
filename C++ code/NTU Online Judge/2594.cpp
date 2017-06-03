#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
const double EPS=1e-9;
double DP[625];
bool INQ[625];
vector<int>ET[625];
int A,B,C,D;
int Get(int a,int b,int c,int d){return ((a*(B+1)+b)*(C+1)+c)*(D+1)+d;}
void Set(int id,int &a,int &b,int &c,int &d)
{
	d=id%(D+1),id/=D+1;
	c=id%(C+1),id/=C+1;
	b=id%(B+1),id/=B+1;
	a=id%(A+1),id/=A+1;
}
int main()
{
	freopen("school.in","r",stdin);
	freopen("school.out","w",stdout);
	while(scanf("%d%d%d%d",&A,&B,&C,&D)==4)
	{
		#define REP(x,y) for(int x=0;x<=y;x++)
		REP(a,A)REP(b,B)REP(c,C)REP(d,D)ET[Get(a,b,c,d)].clear();
		REP(a,A)REP(b,B)REP(c,C)REP(d,D)
		{
			const int i=Get(a,b,c,d);
			DP[i]=0.0;
			if(a==A&&b==B&&c==C&&d==D)continue;
			else
			{
				#define REP2(x,y,z)for(int x=max(0,y-1);x<=min(z,y+1);x++)
				REP2(ai,a,A)REP2(bi,b,B)REP2(ci,c,C)REP2(di,d,D)
				{
					ET[Get(ai,bi,ci,di)].push_back(i);
				}
				#undef REP2
			}
		}
		#undef REP
		queue<int>q;
		for(int i=0;i<=Get(A,B,C,D);i++)INQ[i]=false;
		for(int i=0;i<Get(A,B,C,D);i++)q.push(i),INQ[i]=true;
		for(int a,b,c,d;!q.empty();)
		{
			const int u=q.front();q.pop();
			INQ[u]=false;
			Set(u,a,b,c,d);
			double best=1e100;
			#define REP2(x,y,z)for(int x=max(0,y-1);x<=min(z,y+1);x++)
			if(a+1<=A)
			{
				double ta=1.0;
				int cnt=0;
				REP2(b2,b,B)REP2(c2,c,C)REP2(d2,d,D)++cnt;
				REP2(b2,b,B)REP2(c2,c,C)REP2(d2,d,D)
				{
					ta+=DP[Get(a+1,b2,c2,d2)]/cnt;
				}
				if(ta<best)best=ta;
			}
			if(b+1<=B)
			{
				double ta=1.0;
				int cnt=0;
				REP2(a2,a,A)REP2(c2,c,C)REP2(d2,d,D)++cnt;
				REP2(a2,a,A)REP2(c2,c,C)REP2(d2,d,D)
				{
					ta+=DP[Get(a2,b+1,c2,d2)]/cnt;
				}
				if(ta<best)best=ta;
			}
			if(c+1<=C)
			{
				double ta=1.0;
				int cnt=0;
				REP2(a2,a,A)REP2(b2,b,B)REP2(d2,d,D)++cnt;
				REP2(a2,a,A)REP2(b2,b,B)REP2(d2,d,D)
				{
					ta+=DP[Get(a2,b2,c+1,d2)]/cnt;
				}
				if(ta<best)best=ta;
			}
			if(d+1<=D)
			{
				double ta=1.0;
				int cnt=0;
				REP2(a2,a,A)REP2(b2,b,B)REP2(c2,c,C)++cnt;
				REP2(a2,a,A)REP2(b2,b,B)REP2(c2,c,C)
				{
					ta+=DP[Get(a2,b2,c2,d+1)]/cnt;
				}
				if(ta<best)best=ta;
			}
			#undef REP2
//			printf("best=%.10f\n",best);
			if(fabs(best-DP[u])>=EPS)
			{
				for(const int nxt:ET[u])if(!INQ[nxt])q.push(nxt),INQ[nxt]=true;
			}
			DP[u]=best;
		}
		printf("%.10f\n",DP[Get(0,0,0,0)]);
	}
	return 0;
}
