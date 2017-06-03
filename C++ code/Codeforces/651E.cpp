#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,M;
int GRID[1000000],DJ[1000000];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
void MergeSameValues()
{
	for(int i=0;i<N*M;i++)DJ[i]=i;
	vector<int>s;
	for(int i=0;i<N;i++)
	{
		s.clear();
		for(int j=0;j<M;j++)s.push_back(i*M+j);
		sort(s.begin(),s.end(),[](const int a,const int b)->bool{return GRID[a]<GRID[b];});
		for(int j=1;j<M;j++)if(GRID[s[j-1]]==GRID[s[j]])DJ[Find(s[j-1])]=Find(s[j]);
	}
	for(int i=0;i<M;i++)
	{
		s.clear();
		for(int j=0;j<N;j++)s.push_back(j*M+i);
		sort(s.begin(),s.end(),[](const int a,const int b)->bool{return GRID[a]<GRID[b];});
		for(int j=1;j<N;j++)if(GRID[s[j-1]]==GRID[s[j]])DJ[Find(s[j-1])]=Find(s[j]);
	}
	vector<int>().swap(s);
}
vector<int>ET[1000000];
void BuildGraph()
{
	for(int i=0;i<N*M;i++)ET[i].clear();
	vector<int>s;
	for(int i=0;i<N;i++)
	{
		s.clear();
		for(int j=0;j<M;j++)s.push_back(i*M+j);
		sort(s.begin(),s.end(),[](const int a,const int b)->bool{return GRID[a]<GRID[b];});
		for(int j=1;j<M;j++)if(GRID[s[j-1]]!=GRID[s[j]])ET[Find(s[j])].push_back(Find(s[j-1]));
	}
	for(int i=0;i<M;i++)
	{
		s.clear();
		for(int j=0;j<N;j++)s.push_back(j*M+i);
		sort(s.begin(),s.end(),[](const int a,const int b)->bool{return GRID[a]<GRID[b];});
		for(int j=1;j<N;j++)if(GRID[s[j-1]]!=GRID[s[j]])ET[Find(s[j])].push_back(Find(s[j-1]));
	}
	vector<int>().swap(s);
}
int DP[1000000];
int GetDP(const int u)
{
	int &ans=DP[u];
	if(ans!=-1)return ans;
	ans=1;
	for(const int nxt:ET[u])getmax(ans,GetDP(nxt)+1);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)scanf("%d",&GRID[i*M+j]);
		MergeSameValues();
		BuildGraph();
		for(int i=0;i<N*M;i++)DP[i]=-1;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				if(j)putchar(' ');
				printf("%d",GetDP(Find(i*M+j)));
			}
			puts("");
		}
	}
	return 0;
}
