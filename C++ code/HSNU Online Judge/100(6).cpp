#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
#include<set>
#include<stack>
#include<map>
using namespace std;
int N,M;
bool ANS[100000];
set<int>EO[100000];
vector<int>ET[100000];
int PRE[100000],LOW[100000],PRE_CNT,BCC[100000],BCC_CNT;
stack<int>STK;
int IN[100000];
int GetHead()
{
	for(int i=0;i<BCC_CNT;i++)IN[i]=0;
	for(int i=0;i<M;i++)
	{
		for(int j=0;j<ET[i].size();j++)
		{
			if(BCC[i]==BCC[ET[i][j]])continue;
			IN[BCC[ET[i][j]]]++;
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
void Dfs(const int u)
{
	STK.push(u);
	PRE[u]=LOW[u]=++PRE_CNT;
	for(int i=0;i<ET[u].size();i++)
	{
		const int nxt=ET[u][i];
//		if(nxt==fa)continue;
		if(!PRE[nxt])
		{
			Dfs(nxt);
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
map<int,int>IDX;
int DJ[100000];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
void Solve()
{
	for(int i=0;i<M;i++)BCC[i]=-1,PRE[i]=0;
	PRE_CNT=BCC_CNT=0;
	for(int i=0;i<M;i++)if(!PRE[i])Dfs(i);
	int head=GetHead();
//	printf("head=%d\n",head);
	for(int i=0;i<N;i++)
	{
		if(BCC[IDX[Find(i)]]!=head)ANS[i]=false;
		else ANS[i]=true;
	}
}
set<int>S;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	S.clear();
	for(int i=0;i<N;i++)EO[i].clear(),DJ[i]=i,S.insert(i);
	for(int i=0,cnt,v;i<N;i++)
	{
		scanf("%d",&cnt);
		while(cnt--)
		{
			scanf("%d",&v);
			EO[--v].insert(i);
		}
	}
	for(int i=0,cnt,v;i<N;i++)
	{
		vector<int>tomerge;
		for(auto it=S.begin();it!=S.end();it++)
		{
			if(EO[i].find(*it)!=EO[i].end())continue;//lose
			if(EO[*it].find(Find(i))==EO[*it].end())tomerge.push_back(*it);
		}
		for(int j=0;j<tomerge.size();j++)
		{
			int a=Find(i),b=Find(tomerge[j]);
			if(a==b)continue;
			if(EO[a].size()>EO[b].size())swap(a,b);
			S.erase(a);
			DJ[a]=b;
			set<int>tmp;
			for(auto it=EO[a].begin();it!=EO[a].end();it++)if(EO[b].find(*it)!=EO[b].end())tmp.insert(Find(*it));
			EO[a].clear(),EO[b].clear();
			EO[b]=tmp;
		}
	}
	IDX.clear();
	M=0;
	for(auto i1=S.begin();i1!=S.end();i1++,M++)
	{
		IDX[*i1]=M;
		ET[M].clear();
	}
	do
	{
		int i=0;
		for(auto i1=S.begin();i1!=S.end();i1++,i++)
		{
			ET[i].clear();
			set<int>s;
			s.insert(i);
//			for(auto i2=EO[*i1].begin();i2!=EO[*i1].end();i2++)if(IDX[Find(*i2)]!=i)ET[i].push_back(IDX[Find(*i2)]);
			for(auto i2=EO[*i1].begin();i2!=EO[*i1].end();i2++)if(IDX[Find(*i2)]!=i)s.insert(IDX[Find(*i2)]);
			for(int j=0;j<M;j++)if(s.find(j)==s.end())ET[i].push_back(j);
			sort(ET[i].begin(),ET[i].end());
			ET[i].resize(unique(ET[i].begin(),ET[i].end())-ET[i].begin());
//			printf("from %d:",i);
//			for(int j=0;j<ET[i].size();j++)printf(" %d",ET[i][j]);puts("");
		}
	}while(0);
//	for(int i=0;i<N;i++)printf("%d->%d\n",i,IDX[Find(i)]);
	Solve();
	int ans=0;
	for(int i=0;i<N;i++)if(ANS[i])ans++;
	printf("%d",ans);
	for(int i=0;i<N;i++)if(ANS[i])printf(" %d",i+1);
	puts("");
	return 0;
}
