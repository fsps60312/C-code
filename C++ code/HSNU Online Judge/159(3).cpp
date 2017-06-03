#include<cstdio>
#include<map>
#include<vector>
#include<cassert>
using namespace std;
int N,M;
bool EDGE[3000][3000];
bool DELETE[3000];
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)EDGE[i][j]=false;
	for(int i=0;i<N;i++)DELETE[i]=false;
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		EDGE[a][b]=EDGE[b][a]=true;
	}
	int cnt=0;
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(i!=j&&!EDGE[i][j]&&!DELETE[i]&&!DELETE[j])
	{
		DELETE[i]=DELETE[j]=true;
		if(++cnt==N/3)goto do_break;
	}
	do_break:;
	cnt=0;
	for(int i=0;i<N&&cnt<N/3;i++)if(!DELETE[i])printf("%d\n",i+1),cnt++;
	return 0;
}
