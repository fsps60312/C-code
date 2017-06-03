#include<cstdio>
//#include<cassert>
#include<vector>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
bool Contains(const vector<int>&s,const int v)
{
	const int i=lower_bound(s.begin(),s.end(),v)-s.begin();
	return i<(int)s.size()&&s[i]==v;
}
int N,M;
vector<int>ET[100000];
set<int>REMAIN;
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
			if(!Contains(ET[u],*it)&&!Contains(ET[*it],u))
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
			ET[a].push_back(b);
		}
		for(int i=0;i<N;i++)sort(ET[i].begin(),ET[i].end());
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
