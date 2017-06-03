#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
//const int CNT[16]={0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
int N,C[1000],PA[1000],D[1000];
vector<int>ET[1000];
void Build(const int u,const int pa,const int d)
{
	PA[u]=pa,D[u]=d;
	for(const int nxt:ET[u])if(nxt!=pa)
	{
		Build(nxt,u,d+1);
	}
}
int LCA(int a,int b)
{
	while(D[a]>D[b])a=PA[a];
	while(D[b]>D[a])b=PA[b];
	while(a!=b)a=PA[a],b=PA[b];
	return a;
}
vector<int>Dfs(const int u,const int pa)
{
	if(C[u])return vector<int>{u};
	vector<int>ans;
	for(const int nxt:ET[u])if(nxt!=pa)
	{
		for(const int v:Dfs(nxt,u))ans.push_back(v);
	}
	return ans;
}
void Answer(const int u,const int c)
{
	assert(C[u]==0);
	C[u]=c;
	for(const int nxt:ET[u])assert(C[nxt]!=C[u]);
	printf("%d %d\n",u+1,c);
	fflush(stdout);
}
int ValidColor(const int u)
{
	assert(C[u]==0);
	int v=0;
	for(const int nxt:ET[u])v|=1<<C[nxt];
	for(int i=1;i<=4;i++)if(!(v&(1<<i)))return i;
	assert(0);return -1;
}
bool Read()
{
	int u,c;
	scanf("%d%d",&u,&c);
	if(u==-1&&c==-1)return false;
	--u;
	assert(C[u]==0);
	C[u]=c;
	for(const int nxt:ET[u])
	{
		const auto &s=Dfs(nxt,u);
		assert(s.size()<=2);
		if(s.size()==2)
		{
			const int v=LCA(u,s[0])^LCA(u,s[1])^LCA(s[0],s[1]);
			Answer(v,ValidColor(v));
			return true;
		}
	}
	for(int i=0;i<N;i++)if(C[i])
	{
		for(const int nxt:ET[i])if(C[nxt]==0)
		{
			Answer(nxt,ValidColor(nxt));
			return true;
		}
	}
	assert(0);return false;
}
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)C[i]=0,ET[i].clear();
	for(int i=0,a,b;i<N-1;i++)
	{
		scanf("%d%d",&a,&b),--a,--b;
		ET[a].push_back(b);
		ET[b].push_back(a);
	}
	Build(0,-1,0);
	Answer(0,1);
	while(Read());
	return 0;
}
