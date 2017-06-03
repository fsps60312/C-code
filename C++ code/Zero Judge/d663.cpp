#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647;
int DP[1001],S,T;
vector<int>P;
void getmin(int &a,const int b){if(b<a)a=b;}
int Solve()
{
	if(T<S)return -1;
	for(int i=S;i<=T;i++)DP[i]=INF;
	DP[S]=0;
	for(int i=S;i<=T;i++)
	{
		if(DP[i]==INF)continue;
		for(int j=0;P[j]<i&&i+P[j]<=T;j++)if(i%P[j]==0)getmin(DP[i+P[j]],DP[i]+1);
	}
	return DP[T]==INF?-1:DP[T];
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
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j]!=0;j++);
		}while(P[i]%P[j]==0);
		if(P[i]>1000)break;
	}
//	for(int i=0;i<100;i++)printf("%d\n",P[i]);
	while(scanf("%d%d",&S,&T)==2&&(S||T))
	{
		assert(T>=1&&T<=1000&&S>=1&&S<=1000);
		static int kase=1;
		printf("Case %d: %d\n",kase++,Solve());
	}
	return 0;
}
