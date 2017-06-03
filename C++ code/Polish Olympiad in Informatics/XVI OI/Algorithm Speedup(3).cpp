#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
const int INF=2147483647;
const LL BASE=217LL,MOD=2147483447LL;
LL GetHash(const int N,const int *S)
{
	static LL left_hash[2][100000],rigt_hash[2][100000];
	for(int i=0;i<N;i++)left_hash[0][i]=rigt_hash[0][i]=S[i];
	static int tmp[100];
	for(int i=0;i<100;i++)tmp[i]=0;
	int total_color=0;
	for(int i=0;i<N;i++)if(!tmp[S[i]]++)++total_color;
	int d=0;
	for(int color_cnt=2;color_cnt<=total_color;color_cnt++,d^=1)
	{
		for(int i=0;i<100;i++)tmp[i]=0;
		for(int i=0,l=0,cnt=0;i<N;i++)
		{
			if(!tmp[S[i]]++)++cnt;
			while(cnt>color_cnt)if(!--tmp[S[l++]])--cnt;
			rigt_hash[d^1][i]=(left_hash[d][l]*BASE+rigt_hash[d][i])%MOD;
		}
		for(int i=0;i<100;i++)tmp[i]=0;
		for(int i=N-1,r=N-1,cnt=0;i>=0;i--)
		{
			if(!tmp[S[i]]++)++cnt;
			while(cnt>color_cnt)if(!--tmp[S[r--]])--cnt;
			left_hash[d^1][i]=(left_hash[d][i]*BASE+rigt_hash[d][r])%MOD;
		}
	}
	assert(left_hash[d][0]==rigt_hash[d][N-1]);
	return left_hash[d][0];
}
int N,M,A[100000],B[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		vector<int>a,b;
		for(int i=0;i<N;i++)scanf("%d",&A[i]),--A[i];
		for(int i=0;i<M;i++)scanf("%d",&B[i]),--B[i];
		printf("%d\n",GetHash(N,A)==GetHash(M,B)?1:0);
	}
	return 0;
}
