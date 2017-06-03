#include<cstdio>
#include<cstdlib>
#include<vector>
#include<cmath>
using namespace std; 
int N;
struct Point
{
	int x,y;
};
vector<Point> SITE;
double DP[1000][1000];
void getmin(double &a,double b){if(b<a)a=b;}
double pow(double a){return a*a;}
double dis(Point a,Point b)
{
	return sqrt(pow(a.x-b.x)+pow(a.y-b.y));
}
double getDP()
{
	//DP[i][j]->DP[i+1][j],DP[i+1][i]
	DP[1][0]=dis(SITE[0],SITE[1]);
	for(int i=1;i<N;i++)
	{
		for(int j=0;j<i;j++)
		{
			DP[i+1][j]=DP[i][j]+dis(SITE[i],SITE[i+1]);
		}
		DP[i+1][i]=DP[i][0]+dis(SITE[0],SITE[i+1]);
		for(int j=1;j<i;j++)
		{
			getmin(DP[i+1][i],DP[i][j]+dis(SITE[j],SITE[i+1]));
		}
	}
	double ans=DP[N-1][0]+dis(SITE[0],SITE[N-1]);
	for(int i=1;i<N-1;i++)getmin(ans,DP[N-1][i]+dis(SITE[i],SITE[N-1]));
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		SITE.clear();
		for(int i=0;i<N;i++)
		{
			int x,y;scanf("%d%d",&x,&y);
			SITE.push_back((Point){x,y});
		}
		printf("%.2lf\n",getDP());
	}
	return 0;
}
