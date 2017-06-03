#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
typedef long long LL;
int N,M,R,T,K;
struct Hungary
{
	vector<bool>EDGE[500];
	int MATCH[500];
	bool VIS[500];
	bool Match(const int u)
	{
		const int reflect=u%N;
		for(int nxt=0;nxt<M;nxt++)if(EDGE[reflect][nxt]&&!VIS[nxt])
		{
			VIS[nxt]=true;
			if(MATCH[nxt]==-1||Match(MATCH[nxt]))
			{
				MATCH[nxt]=u;
				return true;
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
		for(int i=0;i<N;i++)HUNGARY.EDGE[i].clear(),HUNGARY.EDGE[i].resize(M,false);
		for(int i=0,a,b;i<K;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			HUNGARY.EDGE[a][b]=true;
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
