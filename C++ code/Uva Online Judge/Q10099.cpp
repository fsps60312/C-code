#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int N,R;
vector<int> CITY[101];
vector<int> VIS;
struct Pair
{
	int x,y;
	bool operator<(Pair a)const{return x<a.x;}
};
vector<Pair> RD;
void getmax(int &a,int b){if(b>a)a=b;}
#define min(x,y) (x)<(y)?(x):(y)
int solve(int sp,int ep)
{
	priority_queue<Pair> pq;
	pq.push((Pair){2147483647,sp});
	int ans=0;
	while(!pq.empty())
	{
		Pair p=pq.top();pq.pop();
		if(p.y==ep)
		{
			getmax(ans,p.x);
			continue;
		}
		for(int i=0;i<CITY[p.y].size();i++)
		{
			int j=CITY[p.y][i];
			if(VIS[j])continue;
			VIS[j]=1;
			pq.push((Pair){min(p.x,RD[j].x),RD[j].y});
		}
	}
	return ans;
}
int caltrip(int p,int a){return (p+a-1)/a;}
int main()
{
	VIS.reserve(20000);
	int kase=1;
	while(scanf("%d%d",&N,&R)==2&&(N||R))
	{
		RD.clear(),VIS.clear();
		for(int i=1;i<=N;i++)CITY[i].clear();
		while(R--)
		{
			int a,b,l;scanf("%d%d%d",&a,&b,&l);
			int sz=RD.size();
			RD.push_back((Pair){l,b});
			VIS.push_back(0);
			CITY[a].push_back(sz++);
			RD.push_back((Pair){l,a});
			VIS.push_back(0);
			CITY[b].push_back(sz);
		}
		int a,b,p;scanf("%d%d%d",&a,&b,&p);
		printf("Scenario #%d\nMinimum Number of Trips = %d\n\n",kase++,caltrip(p,solve(a,b)-1));
	}
	return 0;
}
