#include<cstdio>
#include<vector>
#include<cassert>
#include<utility>
using namespace std;
int N,M;
vector<int>ET[100000];
vector<pair<int,int> >ANS;
bool Solve()
{
	int cnt=0;
	for(int u=0;u<N&&cnt<M;u++)
	{
		for(int nxt=u+1;nxt<N&&cnt<M;nxt++)
		{
			for(const int v:ET[u])if(nxt==v)goto do_continue;
			ANS.push_back(make_pair(u,nxt)),cnt++;
			do_continue:;
		}
	}
	return cnt==M;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		ANS.clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		if(Solve())
		{
			for(const auto &p:ANS)printf("%d %d\n",p.first+1,p.second+1);
		}
		else puts("-1");
		break;
	}
	return 0;
}
