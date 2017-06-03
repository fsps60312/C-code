#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
void getmax(int &a,const int &b){if(b>a)a=b;}
const int INF=2147483647;
int N,K;
vector<int>C[10];
int MX[10][2001],DP[10][2001];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&K);
	for(int i=0;i<10;i++)C[i].clear();
	for(int i=0,c,g;i<N;i++)
	{
		scanf("%d%d",&c,&g);
		C[--g].push_back(c);
	}
	for(int i=0;i<10;i++)
	{
		sort(C[i].begin(),C[i].end(),greater<int>());
		MX[i][0]=-1;
		for(int j=0;j<C[i].size();j++)MX[i][j+1]=MX[i][j]+(j+1)+C[i][j];
		MX[i][0]=0;
	}
	for(int i=0;i<10;i++)for(int j=0;j<=K;j++)DP[i][j]=-INF;
	for(int i=0;i<=C[0].size();i++)DP[0][i]=MX[0][i];
	for(int i=1;i<10;i++)
	{
		for(int j=0;j<=K;j++)
		{
			for(int k=max(0,j-(int)C[i].size());k<=j;k++)getmax(DP[i][j],DP[i-1][k]+MX[i][j-k]);
		}
	}
	printf("%d\n",DP[9][K]);
	return 0;
}
