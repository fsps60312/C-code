#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?a=b,true:false;}
struct DJset
{
	int S[300000];
	void Clear(const int N){for(int i=0;i<N;i++)S[i]=i;}
	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
	bool Merge(int a,int b){return (a=Find(a))==(b=Find(b))?false:S[a]=b,true;}
}DJ;
int N,M;
vector<int>TYPE[300000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)TYPE[i].clear();
		DJ.Clear(M);
		for(int i=0,s;i<N;i++)
		{
			scanf("%d",&s);
			for(int v;s--;)
			{
				scanf("%d",&v);
				TYPE[i].push_back(--v);
			}
			for(int j=1;j<(int)TYPE[i].size();j++)DJ.Merge(TYPE[i][j-1],TYPE[i][j]);
		}
		for(int i=0,a,b;i<N-1;i++)scanf("%d%d",&a,&b);
		static int mx[300000];
		for(int i=0;i<M;i++)mx[i]=1;
		for(int i=0;i<N;i++)if(!TYPE[i].empty())getmax(mx[DJ.Find(TYPE[i][0])],(int)TYPE[i].size());
		static int color[300000];
		for(int i=0;i<M;i++)color[i]=-1;
		set<int>remain;
		for(int i=0;i<M;i++)remain.insert(i);
		for(int i=0;i<N;i++)if(!TYPE[i].empty())
		{
			const int k=mx[DJ.Find(TYPE[i][0])];
			for(const int t:TYPE[i])if(color[t]!=-1)remain.erase(color[t]);
			for(const int t:TYPE[i])if(color[t]==-1)color[t]=*remain.begin(),remain.erase(remain.begin());
			for(const int t:TYPE[i])assert(color[t]<k),remain.insert(color[t]);
		}
		for(int i=0;i<M;i++)if(color[i]==-1)color[i]=0;
		int ans=0;
		for(int i=0;i<M;i++)getmax(ans,mx[i]);
		printf("%d\n",ans);
		for(int i=0;i<M;i++)
		{
			if(i)putchar(' ');
			printf("%d",color[i]+1);
		}
		puts("");
	}
	return 0;
}
