#include<cstdio>
//#include<cassert>
#include<vector>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
int N,M;
set<int>ET[100000],REMAIN;
int Bfs()
{
	int ans=0;
	static queue<int>q;assert(q.empty());
	q.push(*REMAIN.begin()),REMAIN.erase(REMAIN.begin());
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		ans++;
		for(set<int>::iterator it=REMAIN.begin();it!=REMAIN.end();)
		{
			if(ET[u].find(*it)==ET[u].end()&&ET[*it].find(u)==ET[*it].end())
			{
				set<int>::iterator tmp=it++;
				q.push(*tmp),REMAIN.erase(tmp);
			}
			else it++;
		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		assert(2<=N&&N<=100000&&1<=M&&M<=2000000);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			assert(0<=a&&a<N&&0<=b&&b<N);
			ET[a].insert(b);
		}
		REMAIN.clear();
		for(int i=0;i<N;i++)REMAIN.insert(i);
		vector<int>ans;
		while(!REMAIN.empty())ans.push_back(Bfs());
		printf("%d\n",(int)ans.size());
		sort(ans.begin(),ans.end());
		for(int i=0;i<(int)ans.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]);
		}
		puts("");
		break;
	}
	return 0;
}
