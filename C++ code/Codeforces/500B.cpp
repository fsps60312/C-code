#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,DJ[300],S[300];
vector<int>G[300];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)DJ[i]=i;
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=0;i<N;i++)
		{
			static char str[301];scanf("%s",str);
			for(int j=0;j<N;j++)if(str[j]=='1')DJ[Find(i)]=Find(j);
		}
		for(int i=0;i<N;i++)G[i].clear();
		for(int i=0;i<N;i++)G[Find(i)].push_back(i);
		for(int i=0;i<N;i++)if(!G[i].empty())
		{
			vector<int>s;
			for(const int v:G[i])s.push_back(S[v]);
			sort(s.begin(),s.end());
			for(int j=0;j<(int)s.size();j++)S[G[i][j]]=s[j];
		}
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",S[i]);
		}
		puts("");
	}
	return 0;
}
