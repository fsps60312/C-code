#include<cstdio>
#include<cassert>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
const int INF=2147483647;
int N,S[1000000],DP[1000000][3];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	for(int i=0;i<N;i++)for(int j=0;j<3;j++)DP[i][j]=INF;
	DP[0][1+S[0]]=0;
	for(int i=1;i<N;i++)
	{
		switch(S[i])
		{
			case -1:
			{
				if(DP[i-1][0]!=INF)getmin(DP[i][0],DP[i-1][0]);
				if(DP[i-1][2]!=INF)getmin(DP[i][2],DP[i-1][2]+2);
			}break;
			case 0:
			{
				if(DP[i-1][0]!=INF)getmin(DP[i][1],DP[i-1][0]),getmin(DP[i][0],DP[i-1][0]+1);
				if(DP[i-1][1]!=INF)getmin(DP[i][1],DP[i-1][1]);
				if(DP[i-1][2]!=INF)getmin(DP[i][2],DP[i-1][2]+1);
			}break;
			case 1:
			{
				if(DP[i-1][0]!=INF)getmin(DP[i][2],DP[i-1][0]),getmin(DP[i][1],DP[i-1][0]+1),getmin(DP[i][0],DP[i-1][0]+2);
				if(DP[i-1][1]!=INF)getmin(DP[i][2],DP[i-1][1]);
				if(DP[i-1][2]!=INF)getmin(DP[i][2],DP[i-1][2]);
			}break;
			default:assert(0);break;
		}
	}
	int ans=INF;
	for(int i=0;i<3;i++)getmin(ans,DP[N-1][i]);
	if(ans==INF)puts("BRAK");
	else printf("%d\n",ans);
	return 0;
}
