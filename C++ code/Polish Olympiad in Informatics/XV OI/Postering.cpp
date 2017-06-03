#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
using namespace std;
//struct DisjointSets
//{
//	int S[250000];
//	void Clear(const int n){for(int i=0;i<n;i++)S[i]=i;}
//	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
//	
//}DJ;
int N,H[250000];
map<int,vector<int>,greater<int> >S;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0,d;i<N;i++)scanf("%d%d",&d,&H[i]);
		S.clear();
		static bool vis[250000];
		for(int i=0;i<N;i++)S[H[i]].push_back(i),vis[i]=false;
		long long ans=0LL;
		int cnt=0;
//		DJ.Clear();
		for(map<int,vector<int>,greater<int> >::iterator it=S.begin();it!=S.end();++it)
		{
			for(int i=0;i<(int)it->second.size();i++)
			{
				const int u=it->second[i];
				vis[u]=true,++cnt;
				if(u-1>=0&&vis[u-1])--cnt;
				if(u+1<N&&vis[u+1])--cnt;
			}
			ans+=cnt;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
