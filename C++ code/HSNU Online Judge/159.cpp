#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int N,M;
bool EDGE[3000][3000];
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)EDGE[i][j]=false;
	for(int i=0;i<N;i++)EDGE[i][i]=true;
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		EDGE[a][b]=EDGE[b][a]=true;
	}
	srand(7122);
	static int tmp[3000];
	for(int i=0;i<N;i++)tmp[i]=i;
	re_shuffle:;
	random_shuffle(tmp,tmp+N);
	for(int i=0;i<N/3;i++)for(int j=i+1;j<N/3;j++)if(!EDGE[tmp[i]][tmp[j]])goto re_shuffle;
	for(int i=0;i<N/3;i++)printf("%d\n",tmp[i]);
	return 0;
}
