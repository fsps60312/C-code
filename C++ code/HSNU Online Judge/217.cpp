#include<cstdio>
#include<vector>
using namespace std;
bool getmax(int &a,const int &b){if(b>a){a=b;return true;}return false;}
const int INF=2147483647;
int T,N,K,A,B;
char LINE[5001];
int S[5000],DP[2][5000],PRE[500][5000];
vector<int>V[2];
void Update(const int &i,const int &pre,const int &d,const int &s,const int &v)
{
	if(DP[d][s]==-INF)V[d].push_back(s);
	if(getmax(DP[d][s],v))
	{
//		printf("(%d,%d),%d\n",i,s,pre);
		PRE[i][s]=pre;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&N,&K,&A,&B);
		scanf("%s",LINE);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=0;i<N;i++)DP[0][i]=DP[1][i]=-INF;
		V[0].clear(),V[1].clear();
		for(int i=A-1;i<B;i++)Update(0,0,0,i,S[i]);
		for(int i=0,d=0;i<K-1;i++,d^=1)
		{
//			printf("i=%d:",i);
			for(int &s:V[d])
			{
//				printf(" %d",s);
				int &dp=DP[d][s];
				for(int j=A;j<=B&&s+j<N;j++)Update(i+1,s,d^1,s+j,dp+(i+2)*S[s+j]);
				dp=-INF;
			}
//			puts("");
			V[d].clear();
		}
		int d=(K-1)&1;
		static int kase=1;
		printf("Case #%d:\n",kase++);
		if(DP[d][N-1]==-INF)puts("Sorry, you're milk cheese.");
		else
		{
			printf("%d\n",DP[d][N-1]);
			vector<int>ans;
//			for(int i=0;i<K;i++)
//			{
//				for(int j=0;j<N;j++)printf(" %d",PRE[i][j]);
//				puts("");
//			}
//			printf("pre=%d\n",PRE[K-1][N-1]);
			for(int i=K-1,pre=N-1;i>=0;i--)
			{
				ans.push_back(pre);
//				printf("pre=%d\n",pre);
				pre=PRE[i][pre];
			}
			for(int i=ans.size()-1,idx=0;i>=0;i--)
			{
				int &v=ans[i];
				for(;idx<=v;idx++)printf("%c",LINE[idx]);
				puts("");
			}
		}
	}
	return 0;
}
