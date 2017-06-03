#include<cstdio>
#include<vector>
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
int BitCnt(LL a)
{
	a=((a&0xaaaaaaaaaaaaaaaa)>>1)+(a&0x5555555555555555);
	a=((a&0xcccccccccccccccc)>>2)+(a&0x3333333333333333);
	a=((a&0xf0f0f0f0f0f0f0f0)>>4)+(a&0x0f0f0f0f0f0f0f0f);
	a=((a&0xff00ff00ff00ff00)>>8)+(a&0x00ff00ff00ff00ff);
	a=((a&0xffff0000ffff0000)>>16)+(a&0x0000ffff0000ffff);
	a=((a&0xffffffff00000000)>>32)+(a&0x00000000ffffffff);
	return (int)a;
}
void ExGcd(const int a,const int b,int &g,int &x,int &y)
{
	if(b==0){g=a,x=1,y=0;return;}
	ExGcd(b,a%b,g,y,x);
	y-=a/b*x;
}
int Inv(const int a)
{
	int g,x,y;
	ExGcd(a,MOD,g,x,y);
	assert(g==1);
	return ((x%=MOD)+=MOD)%=MOD;
}
int DP[9881][41];
int EDGE[9881][41][41];
int C[41][41];
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=1;i<=40;i++)
	{
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
	}
	while(scanf("%d%d",&N,&K)==2&&(N||K))
	{
		for(int i=0;i<=K;i++)for(int j=0;j<=N;j++)DP[i][j]=0;
		for(int i=0;i<=K;i++)for(int j=0;j<=N;j++)for(int k=0;k<=N;k++)EDGE[i][j][k]=0;
		DP[0][0]=1;
		for(int i=1;i<=K;i++)for(int j=0;j<=N;j++)
		{
			if(j-3>=0)
			{
				int &e=EDGE[i][j-3][j]=DP[i-1][j-3];
				(e*=C[N-(j-3)][3])%=MOD;
				(((e-=EDGE[i-1][j][j-3])%=MOD)+=MOD)%=MOD;
				(DP[i][j]+=e)%=MOD;
			}
			if(j-1>=1&&N-(j-1)>=2)
			{
				int &e=EDGE[i][j-1][j]=DP[i-1][j-1];
				(e*=C[j-1][1])%=MOD;
				(e*=C[N-(j-1)][2])%=MOD;
				(((e-=EDGE[i-1][j][j-1])%=MOD)+=MOD)%=MOD;
				(DP[i][j]+=e)%=MOD;
			}
			if(j+1>=2&&N-(j+1)>=1)
			{
				int &e=EDGE[i][j+1][j]=DP[i-1][j+1];
				(e*=C[j+1][2])%=MOD;
				(e*=C[N-(j+1)][1])%=MOD;
				(((e-=EDGE[i-1][j][j+1])%=MOD)+=MOD)%=MOD;
				(DP[i][j]+=e)%=MOD;
			}
			if(j+3<=N)
			{
				int &e=EDGE[i][j+3][j]=DP[i-1][j+3];
				(e*=C[j+3][3])%=MOD;
				(((e-=EDGE[i-1][j][j+3])%=MOD)+=MOD)%=MOD;
				(DP[i][j]+=e)%=MOD;
			}
			(DP[i][j]*=Inv(i))%=MOD;
		}
		int cnt=BitCnt(GetBinary()^GetBinary());
		int ans=DP[K][cnt];
		(ans*=Inv(C[N][cnt]))%=MOD;
		static int kase=1;
		printf("Case #%d: %d\n",kase++,ans);
	}
	return 0;
}
