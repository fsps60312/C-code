#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
#include<set>
#include<stack>
#include<map>
using namespace std;
int N;
bool ANS[100000];
vector<int>WIN[100000];
set<int>S;
struct Dj
{
	int dj[100000];
	void clear(){S.clear();for(int i=0;i<N;i++)dj[i]=i,S.insert(i);}
	int Find(const int a){return dj[a]==a?a:(dj[a]=Find(dj[a]));}
	bool Merge(const int _a,const int _b){int a=Find(_a),b=Find(_b);if(a==b)return false;dj[a]=b,assert(S.find(a)!=S.end()),S.erase(a);return true;}
}DJ;
void Unique(vector<int>&s)
{
	sort(s.begin(),s.end());
	s.resize(unique(s.begin(),s.end())-s.begin());
}
vector<int>EO[100000];
map<int,int>IDX;
int PRE[100000],LOW[100000],PRE_CNT,BCC[100000],BCC_CNT;
stack<int>STK;
int IN[100000];
int GetHead()
{
	for(int i=0;i<BCC_CNT;i++)IN[i]=0;
	for(int i=0;i<IDX.size();i++)
	{
		for(int j=0;j<EO[i].size();j++)
		{
			IN[BCC[EO[i][j]]]++;
		}
	}
	int ans=-1;
	for(int i=0;i<BCC_CNT;i++)
	{
		if(IN[i]==0)
		{
			if(ans!=-1)return -1;
			ans=i;
		}
	}
	assert(ans!=-1);
	return ans;
}
void Dfs(const int u,const int fa)
{
	STK.push(u);
	PRE[u]=LOW[u]=++PRE_CNT;
	for(int i=0;i<EO[u].size();i++)
	{
		const int nxt=EO[u][i];
		if(nxt==fa)continue;
		if(!PRE[nxt])
		{
			Dfs(nxt,u);
			LOW[u]=min(LOW[u],LOW[nxt]);
		}
		else if(BCC[nxt]==-1)LOW[u]=min(LOW[u],PRE[nxt]);
	}
	if(LOW[u]==PRE[u])
	{
		while(STK.top()!=u)
		{
			const int i=STK.top();STK.pop();
			BCC[i]=BCC_CNT;
		}
		STK.pop();
		BCC[u]=BCC_CNT++;
	}
}
void BuildEO()
{
	IDX.clear();
	int cnt=0;
	for(auto it=S.begin();it!=S.end();it++)IDX[*it]=cnt++;
	for(int i=0;i<IDX.size();i++)EO[i].clear();
	for(int i=0;i<N;i++)
	{
		const int u=IDX[DJ.Find(i)];
		for(int j=0;j<WIN[i].size();j++)EO[u].push_back(IDX[DJ.Find(WIN[i][j])]);
	}
for(int i=0;i<IDX.size();i++)
{
printf("from %d:",i);
for(int j=0;j<EO[i].size();j++)printf(" %d",EO[i][j]);
puts("");
}
	for(int i=0;i<IDX.size();i++)Unique(EO[i]),PRE[i]=0,BCC[i]=-1;
	PRE_CNT=BCC_CNT=0;
	for(int i=0;i<IDX.size();i++)
	{
		if(PRE[i])continue;
		Dfs(i,-1);
	}
}
void Solve()
{
	for(int i=0;i<N;i++)ANS[i]=true;
	DJ.clear();
	for(int i=0;i<N;i++)
	{
		vector<int>win;
		for(int j=0;j<WIN[i].size();j++)win.push_back(DJ.Find(WIN[i][j]));
		Unique(win);
		S.erase(DJ.Find(i));
		for(int j=0;j<win.size();j++)S.erase(win[j]);
		vector<int>tomerge;
		for(auto it=S.begin();it!=S.end();it++)tomerge.push_back(*it);
		S.insert(DJ.Find(i));
		for(int j=0;j<win.size();j++)S.insert(win[j]);
		for(int j=0;j<tomerge.size();j++)DJ.Merge(i,tomerge[j]);
	}
for(auto it=S.begin();it!=S.end();it++)printf(" %d",*it);puts("");
	BuildEO();
	int head=GetHead();
	for(int i=0;i<N;i++)if(BCC[IDX[DJ.Find(i)]]!=head)ANS[i]=false;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)WIN[i].clear();
	for(int i=0,cnt,v;i<N;i++)
	{
		scanf("%d",&cnt);
		while(cnt--)
		{
			scanf("%d",&v);
			v--;
			WIN[i].push_back(v);
		}
	}
	Solve();
	int ans=0;
	for(int i=0;i<N;i++)if(ANS[i])ans++;
	printf("%d",ans);
	for(int i=0;i<N;i++)if(ANS[i])printf(" %d",i+1);
	puts("");
	return 0;
}
