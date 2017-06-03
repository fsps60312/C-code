#include<cstdio>
#include<vector>
using namespace std;
int T,VIS[26],GN,CNT[27];
char S[27];
vector<int> G[26];
void getPERI(int fa)
{
	if(VIS[fa])return;
	VIS[fa]=1;
	G[GN].push_back(fa);
	for(int u=S[fa];u!=fa;VIS[u]=1,u=S[u])G[GN].push_back(u);
	CNT[G[GN].size()]++;
	GN++;
}
bool solve()
{
	for(int i=0;i<=26;i+=2)
	{
		if(CNT[i]&1)return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",S);
		GN=0,CNT[26]=0;
		for(int i=0;i<26;i++)
		{
			S[i]-='A';
			VIS[i]=0;
			G[i].clear();
			CNT[i]=0;
		}
		for(int i=0;i<26;i++)getPERI(i);
		printf(solve()?"Yes\n":"No\n");
	}
	return 0;
}
