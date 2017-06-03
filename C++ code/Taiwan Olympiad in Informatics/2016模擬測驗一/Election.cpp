#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const double EPS=1e-9;
const int INF=2147483647;
int N,SEAT;
vector<int>CLUB;
vector<vector<int> >ANS;
void Dfs(const int u,vector<int>&now,const int sum,const int mn)
{
	if(sum*2>SEAT)
	{
		if((sum-mn)*2<=SEAT)ANS.push_back(now);
		return;
	}
	if(u==N)return;
	if(CLUB[u])
	{
		now.push_back(u);
		Dfs(u+1,now,sum+CLUB[u],min(mn,CLUB[u]));
		now.pop_back();
	}
	Dfs(u+1,now,sum,mn);
}
char Id(const int i)
{
	if(i<26)return 'A'+i;
	return 'a'+(i-26);
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int total_seat;scanf("%d%d",&N,&total_seat)==2;)
	{
		CLUB.clear();
		for(int i=0,v;i<N;i++)scanf("%d",&v),CLUB.push_back(total_seat*0.01*v+EPS);
		SEAT=0;
		for(int i=0;i<N;i++)SEAT+=CLUB[i];
//		printf("total_seat=%d,SEAT=%d\n",total_seat,SEAT);
		ANS.clear();
		vector<int>now;
		Dfs(0,now,0,INF);
		assert(now.empty());
		printf("%d\n",(int)ANS.size());
		for(const vector<int>&s:ANS)
		{
			int sum=0;
			for(const int v:s)putchar(Id(v)),sum+=CLUB[v];
			printf(" %d\n",sum);
		}
	}
	return 0;
}
