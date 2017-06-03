#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
struct Djset
{
	int s[100000];
	void clear(const int n){for(int i=0;i<n;i++)s[i]=i;}
	int find(const int a){return s[a]==a?a:(s[a]=find(s[a]));}
	bool merge(int a,int b){if((a=find(a))==(b=find(b)))return false;s[a]=b;return true;}
	bool merge(const pair<int,int>&p){return merge(p.first,p.second);}
}DJ;
int N,M,Q[100000],ANS[100000];
vector<pair<int,int> >EDGE; 
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		EDGE.clear();
		for(int i=0,a,b;i<M;i++)scanf("%d%d",&a,&b),EDGE.push_back(make_pair(--a,--b));
		int querycount;scanf("%d",&querycount);
		for(int i=0;i<M;i++)ANS[i]=1;
		for(int i=0;i<querycount;i++)scanf("%d",&Q[i]),ANS[--Q[i]]=0;
		DJ.clear(N);
		int ans=N;
		for(int i=0;i<M;i++)if(ANS[i]&&DJ.merge(EDGE[i]))ans--;
		for(int i=querycount-1;i>=0;i--)
		{
			ANS[i]=ans;
			if(DJ.merge(EDGE[Q[i]]))ans--;
		}
		for(int i=0;i<querycount;i++)
		{
			if(i)putchar(' ');
			printf("%d",ANS[i]);
		}
		puts("");
	}
	return 0;
}
