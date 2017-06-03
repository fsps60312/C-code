#include<cstdio>
#include<cassert>
#include<deque>
#include<cmath>
using namespace std;
#define double long double
typedef long long LL;
int N;
LL K,S[100001],DP[100001];
double GetX(const int a,const int b)
{
	const double d=(S[b]-S[a]);
	//DP[a]+(d+x)^3==DP[b]+x^3
	//DP[a]+d^3+3*d^2*x+3*d*x^2+x^3==DP[b]+x^3
	//DP[a]+d^3+3*d^2*x+3*d*x^2==DP[b]
	//(3*d)x^2+(3*d^2)x+(DP[a]-DP[b]+d^3)==0
	//x=(-3*d^2+sqrt(9*d^4-12*d*(DP[a]-DP[b]+d^3)))/(6*d)
	return S[b]+(-3*d*d+sqrt(9*d*d*d*d-12*d*((DP[a]-DP[b])+d*d*d)))/(6*d);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount=0;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%lld",&N,&K);
		S[0]=0;
		for(int i=1;i<=N;i++)
		{
			scanf("%lld",&S[i]);
			if(S[i]==0)
			{
				--i,--N;
				continue;
			}
			S[i]+=S[i-1];
		}
		DP[0]=0;
		deque<int>deq;
		deq.push_back(0);
		for(int i=1;i<=N;i++)
		{
			while(deq.size()>=2&&GetX(deq[0],deq[1])<=S[i])/*printf("f (%d,%d) %.10f<%lld\n",deq[0],deq[1],GetX(deq[0],deq[1]),S[i]),*/deq.pop_front();
			const LL l=S[i]-S[deq.front()];
			DP[i]=DP[deq.front()]+K+l*l*l;
//			printf("dp[%d]=%lld\n",i,DP[i]);
			while(deq.size()>=2&&GetX(deq[deq.size()-2],deq.back())>=GetX(deq.back(),i))deq.pop_back();//,puts("b");
			deq.push_back(i);
		}
		printf("%lld\n",DP[N]);
	}
	return 0;
}
