#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
LL A,B;
LL DP[32][100][1000];
LL GetDP(const int a,const int b,const int c)
{
	if(a<0||b<0||c<0)return 0LL;
	LL &ans=DP[a][b][c];
	if(ans!=-1)return ans;
	ans=0LL;
	for(int i=0;i<10;i++)ans+=GetDP(a-1,b-i,c-i*i);
	return ans;
}
vector<int>P;
LL Solve(LL n)
{
	vector<int>digit;
	for(;n;n/=10)digit.push_back(n%10);
	LL ans=0LL;
	int add=0,mul=0;
	for(int i=(int)digit.size()-1;i>=1;i--)
	{
		for(int d=0;d<digit[i];d++)
		{
			for(int j=0;P[j]<100;j++)for(int k=0;P[k]<1000;k++)
			{
				ans+=GetDP(i-1,P[j]-(add+d),P[k]-(mul+d*d));
			}
		}
		add+=digit[i],mul+=digit[i]*digit[i];
	}
	return ans;
}
int main()
{
	P.push_back(2),P.push_back(3);
	for(int i=2,j;;i++)
	{
		P.push_back(P[i-1]);
		do
		{
			P[i]+=2;
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j];j++);
		}while(P[i]%P[j]==0);
		if(P[i]>1000)break;
	}
	for(int i=0;i<32;i++)for(int j=0;j<100;j++)for(int k=0;k<1000;k++)DP[i][j][k]=-1LL;
	for(int i=0;i<10;i++)DP[0][i][i*i]=1LL;
	freopen("inn.txt","r",stdin);
	while(scanf("%lld%lld",&A,&B)==2)
	{
//		printf("%lld %lld\n",Solve(B),Solve(A-1));
		printf("%lld\n",Solve(B)-Solve(A-1));
	}
	return 0;
}
