#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Djset
{
	int data[100000],sz[100000];
	void clear(const int n){for(int i=0;i<n;i++)data[i]=i,sz[i]=1;}
	int find(const int a){return data[a]==a?a:(data[a]=find(data[a]));}
	bool Merge(int a,int b){if((a=find(a))==(b=find(b)))return false;sz[b]+=sz[a],sz[a]=0,data[a]=b;return true;}
	int operator[](const int idx){return find(idx);}
}COMP,ID;
int N,M;
vector<int>ET[100000],FA[100000];
void BuildFA(const int u,const int fa)
{
	FA[u].clear();
	if(fa!=-1)
	{
		for(int cur=fa,i=0;;cur=FA[cur][i++])
		{
			FA[u].push_back(cur);
			if(i>=FA[cur].size())break;
		}
	}
	for(const int nxt:ET[u])if(nxt!=fa)BuildFA(nxt,u);
}
int main()
{
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)ET[i].clear();
		COMP.clear(),ID.clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			if(ID[a]==ID[b])continue;
			else if(COMP[a]!=COMP[b])
			{
				ET[a].push_back(b),ET[b].push_back(a);
				if(COMP.size[COMP[a]]>COMP.size[COMP[b]])swap(a,b);
				BuildFA(a,b);
				assert(COMP.Merge(a,b));
			}
			else
			{
				
			}
		}
	}
	return 0;
}
