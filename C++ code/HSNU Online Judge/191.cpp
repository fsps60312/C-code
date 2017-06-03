#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,M,W[200000],ANS[200000];
vector<int>ET[200000];
struct Treasure
{
	multiset<int>s;
	int dif=INF;
	void Insert(const int v)
	{
		auto it=s.upper_bound(v);
		if(it!=s.begin())getmin(dif,v-(*--it));
		it=s.lower_bound(v);
		if(it!=s.end())getmin(dif,(*it)-v);
		s.insert(v);
	}
};
Treasure *Merge(Treasure *a,Treasure *b)
{
	if(a->s.size()>b->s.size())swap(a,b);
	for(const int v:a->s)b->Insert(v);
	delete a;
	return b; 
}
Treasure *Dfs(const int u)
{
	Treasure *ans=new Treasure();
	if(W[u]!=-INF)ans->Insert(W[u]);
	for(const int nxt:ET[u])ans=Merge(ans,Dfs(nxt));
	ANS[u]=ans->dif;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),W[i]=-INF;
		for(int i=1,fa;i<N;i++)scanf("%d",&fa),ET[--fa].push_back(i);
		for(int i=N-M;i<N;i++)scanf("%d",&W[i]);
		delete Dfs(0);
		for(int i=0;i<N-M;i++)printf("%s%d",i?" ":"",ANS[i]);
		puts("");
	}
	return 0;
}
