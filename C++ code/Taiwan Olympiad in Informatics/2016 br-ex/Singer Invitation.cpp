#include<cstdio>
#include<cassert>
using namespace std;
int M,N;
int S[50][3];
bool VIS[40];
int ANS,NOW;
void Dfs(const int dep)
{
	if(NOW>=ANS)return;
	if(dep==M){ANS=NOW;return;}
	for(int i=0;i<3;i++)if(VIS[S[dep][i]])
	{
		Dfs(dep+1);
		return;
	}
	for(int i=0;i<3;i++)
	{
		VIS[S[dep][i]]=true,++NOW;
		Dfs(dep+1);
		VIS[S[dep][i]]=false,--NOW;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&M,&N);
		for(int i=0;i<M;i++)for(int j=0;j<3;j++)scanf("%d",&S[i][j]);
		for(int i=0;i<N;i++)VIS[i]=false;
		ANS=N;NOW=0;
		Dfs(0);
		printf("%d\n",ANS);
	}
	return 0;
}
