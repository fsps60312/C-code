#include<cstdio>
#include<cassert>
#include<map>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
void Modify(LL *dif,const int bl,const int br,const LL val)
{
	(dif[bl]+=val)%=MOD;
	(dif[br+1]-=val)%=MOD;
}
LL DIF[2][100001];
int N,S[1000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		sort(S,S+N);
		const int M=S[0];
		for(int i=1;i<=M;i++)DIF[0][i]=0LL;
		Modify(DIF[0],S[0],S[0],1LL);
		int d=0;
		for(int i=1;i<N;i++,d^=1)
		{
			for(int j=1;j<=M;j++)DIF[d^1][j]=0LL;
			LL val=0LL;
			for(int j=1;j<=M;j++)if((val+=DIF[d][j])%=MOD)
			{
				Modify(DIF[d^1],j,j,val*(S[i]-j+1));
				Modify(DIF[d^1],1,j-1,val*2LL);
			}
		}
		LL ans=0LL;
		LL val=0LL;
		for(int i=1;i<=M;i++)
		{
			(val+=DIF[d][i])%=MOD;
			(ans+=val*(1+i/2)%MOD*(i/2))%=MOD;
			if(i%2==0)(ans-=val*(i/2))%=MOD;
		}
		printf("%lld\n",(ans%MOD+MOD)%MOD);
	}
	return 0;
}
