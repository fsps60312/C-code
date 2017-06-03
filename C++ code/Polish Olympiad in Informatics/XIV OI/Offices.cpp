#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;
int N,M;
bool CmpDegree
struct DegreeComparer{bool operator()(const int a,const int b)const
{
	return ET[a].size()!=ET[b].size()?ET[a].size()<ET[b].size():a<b;
};};
set<int,DegreeComparer>ET[100000],REMAIN;
int Bfs(const int source)
{
	int ans=1;
	queue<int>q;
	q.push(source),REMAIN.erase(source);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(set<int>::iterator it1=REMAIN.begin(),it2=ET[u].begin();it1!=REMAIN.end();)
		{
			while(it2!=ET[u].end()&&)
			if(ET[u].find(*it)==ET[u].end())
			{
				set<int>::iterator tmp=it++;
				q.push(*tmp),REMAIN.erase(tmp);
				ans++;
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
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].insert(b),ET[b].insert(a);
		}
		REMAIN.clear();
		for(int i=0;i<N;i++)REMAIN.insert(i);
		vector<int>ans;
		while(!REMAIN.empty())ans.push_back(Bfs(*REMAIN.begin()));
		printf("%d\n",(int)ans.size());
		sort(ans.begin(),ans.end());
		for(int i=0;i<(int)ans.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]);
		}
		puts("");
	}
	return 0;
}
