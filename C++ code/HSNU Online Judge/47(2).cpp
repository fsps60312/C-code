#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,M;
int S[2][15000],V[15000];
int main()
{
	static char line[1501];
	gets(line);sscanf(line,"%d%d",&N,&M);
	for(int i=0;i<M;i++)S[1][i]=0;
	int ans=0;
	for(int i=0,d=0;i<N;i++,d^=1)
	{
		gets(line);
		for(int j=0,now;j<M;j++)
		{
			if(line[j]=='1')now=S[d^1][j]+1;
			else now=0;
			S[d][j]=V[j]=now;
		}
		sort(V,V+M,greater<int>());
		for(int j=0;j<M;j++)
		{
			if((j+1)*V[j]>ans)ans=(j+1)*V[j];
		}
	}
	printf("%d\n",ans);
	return 0;
}
