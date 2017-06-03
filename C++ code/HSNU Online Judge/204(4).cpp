#include<bits/stdc++.h>
using namespace std;
int N,DP[1<<10];
bool VIS[1<<20];
vector<int>M[2];
map<int,set<int> >S[2];
void GetDif(vector<int>&m,map<int,set<int> >&mv)
{
	int n=m.size();
	for(int s=0;s<(1<<n);s++)
	{
		int &dp=DP[s]=0;
		for(int i=0;i<n;i++)if(s&(1<<i))dp+=m[i];
	}
	mv.clear();
	for(int s=0;s<(1<<n);s++)
	{
		for(int a=s;;a=(a-1)&s)
		{
			if(DP[a]>=DP[s^a])mv[DP[a]-DP[s^a]].insert(s);
			if(!a)break;
		}
	}
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		M[0].clear(),M[1].clear();
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			M[i&1].push_back(v);
		}
//		puts("a");
		GetDif(M[0],S[0]),GetDif(M[1],S[1]);
//		puts("b");
		for(int i=0;i<(1<<N);i++)VIS[i]=false;
		int ans=0;
		int tmp=M[0].size();
		for(auto i:S[0])
		{
			auto j=S[1].find(i.first);
			if(j==S[1].end())continue;
			for(int a:i.second)for(int b:j->second)if(!VIS[a+(b<<tmp)])VIS[a+(b<<tmp)]=true,ans++;
		}
		printf("%d\n",--ans);
	}
	return 0;
}
