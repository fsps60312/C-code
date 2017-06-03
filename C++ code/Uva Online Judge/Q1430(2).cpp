#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const int MOD=10007;
int N,K;
LL GetBinary()
{
	LL ans=0LL;
	char c=getchar();
	while(c!='0'&&c!='1')c=getchar();
	for(int i=0;i<N;i++)assert(c=='0'||c=='1'),(ans<<=1)|=(c-'0'),c=getchar();
	return ans;
}
LL BitCnt(LL a)
{
	a=((a&0xaaaaaaaaaaaaaaaa)>>1)+(a&0x5555555555555555);
	a=((a&0xcccccccccccccccc)>>2)+(a&0x3333333333333333);
	a=((a&0xf0f0f0f0f0f0f0f0)>>4)+(a&0x0f0f0f0f0f0f0f0f);
	a=((a&0xff00ff00ff00ff00)>>8)+(a&0x00ff00ff00ff00ff);
	a=((a&0xffff0000ffff0000)>>16)+(a&0x0000ffff0000ffff);
	a=((a&0xffffffff00000000)>>32)+(a&0x00000000ffffffff);
	return a;
}
LL DP[9881][41];
LL EDGE[9881][41][41];
int C[41][41];
int LEVEL[41];
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	LEVEL[0]=1;
	for(int i=1;i<=40;i++)LEVEL[i]=LEVEL[i-1]*i;
	for(int i=1;i<=40;i++)
	{
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	//DP[i][j]=DP[i-3][j-1]*C[i][3]
	while(scanf("%d%d",&N,&K)==2&&(N||K))
	{
		for(int i=0;i<=K;i++)for(int j=0;j<=N;j++)DP[i][j]=0;
		for(int i=0;i<=K;i++)for(int j=0;j<=N;j++)for(int k=0;k<=N;k++)EDGE[i][j][k]=0;
		DP[0][0]=1;
		for(int i=1;i<=K;i++)for(int j=0;j<=N;j++)
		{
			if(j-3>=0)            DP[i][j]+=(EDGE[i][j-3][j]=DP[i-1][j-3]*C[N-(j-3)][3]          -EDGE[i-1][j][j-3]);
			if(j-1>=1&&N-(j-1)>=2)DP[i][j]+=(EDGE[i][j-1][j]=DP[i-1][j-1]*C[j-1][1]*C[N-(j-1)][2]-EDGE[i-1][j][j-1]);
			if(j+1>=2&&N-(j+1)>=1)DP[i][j]+=(EDGE[i][j+1][j]=DP[i-1][j+1]*C[j+1][2]*C[N-(j+1)][1]-EDGE[i-1][j][j+1]);
			if(j+3<=N)            DP[i][j]+=(EDGE[i][j+3][j]=DP[i-1][j+3]*C[j+3][3]              -EDGE[i-1][j][j+3]);
			assert(DP[i][j]%i==0);
			DP[i][j]/=i;
		}
		for(int i=0;i<=K;i++)
		{
			printf("cnt=%d\n",i);
			for(int j=0;j<=N;j++)printf(" %lld",DP[i][j]);puts("");
		}
		continue;
		int cnt=BitCnt(GetBinary()^GetBinary());
		int ans=DP[K][cnt];
		assert(ans%C[N][cnt]==0);
		ans/=C[N][cnt];
//		for(int i=K,d=1;i>=0;i-=2,d*=-1)ans+=DP[i][cnt]*d,printf("%c%d\n",d==1?'+':'-',DP[i][cnt]);
		static int kase=1;
		printf("Case #%d: %d\n",kase++,ans);
	}
	return 0;
}
