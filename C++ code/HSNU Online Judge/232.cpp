#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
int M,K,S[50000];
LL R,DP[50000][4][10];
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d%d%lld",&M,&K,&R)==3)
	{
		static char tmp[50001];
		scanf("%s",tmp);
		for(int i=0;i<M;i++)
		{
			switch(tmp[i])
			{
				case'A':S[i]=0;break;
				case'C':S[i]=1;break;
				case'G':S[i]=2;break;
				case'T':S[i]=3;break;
				case'N':S[i]=-1;break;
				default:assert(0);
			}
			for(int j=0;j<4;j++)for(int k=0;k<K;k++)DP[i][j][k]=0LL;
		}
		for(int c=0;c<4;c++)if(S[M-1]==-1||S[M-1]==c)for(int k=0;k<K;k++)DP[M-1][c][k]=1LL;
		for(int i=M-2;i>=0;i--)
		{
			for(int c1=0;c1<4;c1++)//i
			{
				if(S[i]!=-1&&S[i]!=c1)continue;
				for(int k=0;k<K;k++)
				{
					LL &dp=DP[i][c1][k];
//					if(k>0)dp+=DP[i][c1][k-1];
					for(int c2=0;c2<4;c2++)//i+1
					{
						if(c1<=c2)dp+=DP[i+1][c2][k];
						if(k>0&&c1>c2)dp+=DP[i+1][c2][k-1];
					}
				}
//				for(int k=0;k<K;k++)printf("DP[%d][%d][%d]=%lld\n",i,c1,k,DP[i][c1][k]);
			}
		}
		R--;
		for(int i=0,k=K-1,pre=0;i<M;i++)
		{
//			printf("R=%lld,",R);
			int c=0;
			if(k>0)for(;DP[i][c][k-1]<=R&&c<pre;R-=DP[i][c][k-1],c++);
			else c=pre;
			if(c==pre)for(;DP[i][c][k]<=R;R-=DP[i][c][k],c++);
			static char charactor[4]={'A','C','G','T'};
//			printf("i=%d,c=%d,k=%d,R=%lld\n",i,c,k,R);
			printf("%c",charactor[c]);
			if(c<pre)k--;
			pre=c;
		}
		puts("");
	}
	return 0;
}
