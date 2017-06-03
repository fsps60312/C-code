#include<cstdio>
#include<vector>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int DP[2][5][5];
vector<int>S;
int Cost(const int a,const int b)
{
	if(a==0)return 2;
	if(a==b)return 1;
	return (a-b)%2==0?4:3;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		S.clear();
		for(int v;scanf("%d",&v)&&v;)S.push_back(v);
		if(S.empty())break;
		for(int i=0;i<25;i++)DP[0][i/5][i%5]=INF;
		DP[0][0][0]=0;
		int d=0;
		for(int i=0;i<(int)S.size();i++,d^=1)
		{
			for(int j=0;j<25;j++)DP[d^1][j/5][j%5]=INF;
			for(int left=0;left<=4;left++)for(int right=0;right<=4;right++)if(DP[d][left][right]!=INF)
			{
				if(S[i]!=right)getmin(DP[d^1][S[i]][right],DP[d][left][right]+Cost(left,S[i]));
				if(S[i]!=left)getmin(DP[d^1][left][S[i]],DP[d][left][right]+Cost(right,S[i]));
			}
		}
		int ans=INF;
		for(int i=0;i<25;i++)getmin(ans,DP[d][i/5][i%5]);
		printf("%d\n",ans);
	}
	return 0;
}
