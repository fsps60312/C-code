#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,M;
vector<int>S[15000];
int main()
{
	static char line[1501];
	gets(line);sscanf(line,"%d%d",&N,&M);
	for(int i=0;i<N;i++)
	{
		gets(line);
		for(int j=0,now;j<M;j++)
		{
			if(line[j]=='1')now=(i?S[i-1][j]:0)+1;
			else now=0;
			S[i].push_back(now);
		}
	}
	int ans=0;
	for(int i=0;i<N;i++)
	{
		sort(S[i].begin(),S[i].end(),greater<int>());
		for(int j=0;j<M;j++)
		{
//			printf("S[%d][%d]=%d\n",i,j,S[i][j]);
			if((j+1)*S[i][j]>ans)ans=(j+1)*S[i][j];
		} 
	}
	printf("%d\n",ans);
	return 0;
}
