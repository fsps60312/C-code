#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<utility>
#include<queue>
using namespace std;
typedef long long LL;
int N,M,R,T,K;
struct Hungary
{
	vector<int>EDGE[500];
	int MATCH[500];
	bool VIS[500];
	bool Match(const int _u)
	{
		static int prenxt[500],preu[500];
		queue<int>q;
		q.push(_u);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			const int reflect=u%N;
			for(int i=0;i<(int)EDGE[reflect].size();i++)
			{
				const int nxt=EDGE[reflect][i];
				if(!VIS[nxt])
				{
					VIS[nxt]=true,preu[nxt]=u;
					if(MATCH[nxt]==-1)
					{
						for(int cu=u,cnxt=nxt;;)
						{
							MATCH[cnxt]=cu;
							if(cu==_u)return true;
							cnxt=prenxt[cu],cu=preu[cnxt];
						}
					}
					else
					{
						prenxt[MATCH[nxt]]=nxt;
						q.push(MATCH[nxt]);
					}
				}
			}
		}
		return false;
	}
	void Solve(LL &penalty,vector<pair<int,int> >&ans)
	{
		for(int i=0;i<M;i++)MATCH[i]=-1;
		penalty=0LL;
		vector<int>inque;
		for(int i=0;i<N;i++)inque.push_back(i);
		for(int round=0;(round+1)*R<=T;round++)
		{
			assert(round<M);
			int cnt=0;
			for(int i=0;i<(int)inque.size();i++)
			{
				for(int j=0;j<M;j++)VIS[j]=false;
				if(Match(round*N+inque[i]))cnt++;
				else swap(inque[i],inque.back()),inque.pop_back(),--i;
			}
			if(!cnt)break;
			penalty+=(LL)cnt*(round+1LL)*R;
		}
		for(int i=0;i<M;i++)if(MATCH[i]!=-1)ans.push_back(make_pair(MATCH[i],i));
	}
}HUNGARY;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d%d",&N,&M,&R,&T,&K)==5)
	{
		for(int i=0;i<N;i++)HUNGARY.EDGE[i].clear();
		for(int i=0,a,b;i<K;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			HUNGARY.EDGE[a].push_back(b);
		}
		LL penalty;
		vector<pair<int,int> >ans;
		HUNGARY.Solve(penalty,ans);
		printf("%d %lld\n",(int)ans.size(),penalty);
		for(int i=0;i<(int)ans.size();i++)
		{
			printf("%d %d %d\n",ans[i].first%N+1,ans[i].second+1,(ans[i].first/N)*R);
		}
	}
	return 0;
}
