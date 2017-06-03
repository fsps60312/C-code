#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
char S[100001];
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s",S)==1)
	{
		LL cnt[2][2]={{0LL,0LL},{0LL,0LL}};
		LL ans[2]={0LL,0LL};
		for(N=0;S[N];N++)
		{
			const int v=S[N]-'a';
			LL nxt[2][2]={{0LL,0LL},{0LL,0LL}};
			for(int d=0;d<2;d++)for(int i=0;i<2;i++)nxt[d][i]+=cnt[d^1][i];
			nxt[1][v]++;
			ans[0]+=nxt[0][v];
			ans[1]+=nxt[1][v];
//			printf("(%I64d,%I64d)\n",nxt[0][v],nxt[1][v]);
			for(int i=0;i<4;i++)cnt[i>>1][i&1]=nxt[i>>1][i&1];
		}
		N--;
		printf("%I64d %I64d\n",ans[0],ans[1]);
	}
	return 0;
}
