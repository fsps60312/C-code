#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<vector>
using namespace std;
struct Pair{double x,y;};
double squa(double a){return a*a;}
double disq(Pair a,Pair b){return squa(a.x-b.x)+squa(a.y-b.y);}
vector<Pair> ROCK;
double DIS[200][200];
int N;
#define max(x,y) (x)>(y)?(x):(y)
#define min(x,y) (x)<(y)?(x):(y)
double qDIS(int i1,int i2){if(i1<i2)i1^=i2^=i1^=i2;return DIS[i1][i2];}
double solve()
{
	for(int k=0;k<N;k++)
	{
		for(int i1=0;i1<N;i1++)
		{
			for(int i2=0;i2<i1;i2++)
			{
				DIS[i1][i2]=min(DIS[i1][i2],max(qDIS(i1,k),qDIS(k,i2)));
			}
		}
	}
	return sqrt(DIS[1][0]);
}
int main()
{
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		ROCK.clear();
		for(int i=0;i<N;i++)
		{
			double a,b;scanf("%lf%lf",&a,&b);
			ROCK.push_back((Pair){a,b});
		}
		for(int i=0;i<N;i++)for(int j=0;j<=i;j++)DIS[i][j]=disq(ROCK[i],ROCK[j]);
		printf("Scenario #%d\nFrog Distance = %.3lf\n\n",kase++,solve());
	}
	return 0;
}
