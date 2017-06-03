#include<cstdio>
#include<queue>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,TWO[1000][1000],FIVE[1000][1000],DT[1000][1000],DF[1000][1000];
int Add(const int &a,const int &b){if(a==INF||b==INF)return INF;return a+b;}
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			static int v;
			scanf("%d",&v);
			if(v==0)TWO[i][j]=FIVE[i][j]=INF;
			else
			{
				TWO[i][j]=FIVE[i][j]=0;
				while(v&&v%2==0)v/=2,TWO[i][j]++;
				while(v&&v%5==0)v/=5,FIVE[i][j]++;
			}
		}
	}
	DT[0][0]=TWO[0][0],DF[0][0]=FIVE[0][0];
	for(int i=1;i<N;i++)DT[i][0]=Add(DT[i-1][0],TWO[i][0]),DT[0][i]=Add(DT[0][i-1],TWO[0][i]);
	for(int i=1;i<N;i++)DF[i][0]=Add(DF[i-1][0],FIVE[i][0]),DF[0][i]=Add(DF[0][i-1],FIVE[0][i]);
	for(int i=1;i<N;i++)
	{
		for(int j=1;j<N;j++)
		{
			DT[i][j]=Add(min(DT[i-1][j],DT[i][j-1]),TWO[i][j]);
			DF[i][j]=Add(min(DF[i-1][j],DF[i][j-1]),FIVE[i][j]);
		}
	}
	printf("%d\n",min(DT[N-1][N-1],DF[N-1][N-1]));
	return 0;
}
