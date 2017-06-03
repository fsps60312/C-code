#include<cstdio>
#include<vector>
using namespace std;
int N,IN[100000],OUT[100000];
vector<int>ET[100000];
bool VIS[100000];
void Dfs(const int &u)
{
	if(VIS[u])return;
	VIS[u]=true;
	for(int i=0;i<ET[u].size();i++)Dfs(ET[u][i]);
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)ET[i].clear(),IN[i]=OUT[i]=0,VIS[i]=false;
	for(int a=0,b;a<N;a++)while(scanf("%d",&b)==1&&b)ET[a].push_back(--b),OUT[a]++,IN[b]++;
	int a=0,b=0;
	for(int i=0;i<N;i++)
	{
		if(IN[i]==0)Dfs(i),printf("i=%d\n",i);
		if(IN[i]==0)a++;
		if(OUT[i]==0)b++;
	}
	printf("(%d,%d)\n",a,b);
	for(int i=0;i<N;i++)
	{
		if(VIS[i])continue;
		printf("i=%d\n",i);
		Dfs(i);
		a++,b++;
	}
	printf("%d\n",a>b?a:b);
	return 0;
}
