#include<cstdio>
#include<cassert>
#include<stack>
#define int long long
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int INF=2147483647,MOD=1000000007;
void getmax(double &a,const double &b){if(b>a)a=b;}
int N,X[200001],H[200001],SUM[200001],CNT[200001],ANS[200001];
main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int testcount;scanf(1,"%lld",&testcount);
	while(testcount--)
	{
		scanf(1,"%lld",&N);
		for(int i=1;i<=N;i++)scanf(2,"%lld%lld",&X[i],&H[i]);
		for(int i=1;i<=N;i++)CNT[i]=SUM[i]=ANS[i]=0;
		stack<int>stk;
		H[0]=INF,stk.push(0);
		int ans=0;
		for(int i=1;i<=N;i++)
		{
			while(H[stk.top()]<H[i])stk.pop();
			if(H[stk.top()]>H[i])stk.push(i);
			else
			{
				CNT[i]=CNT[stk.top()]+1;
				SUM[i]=(SUM[stk.top()]+2*CNT[i]*(X[i]-X[stk.top()]))%MOD;
				ANS[i]=(ANS[stk.top()]+(X[i]-X[stk.top()])*(SUM[stk.top()]+CNT[i]*(X[i]-X[stk.top()])))%MOD;
//				printf("%lld\n",SUM[stk.top()]+CNT[i]*(X[i]-X[stk.top()]));
				stk.pop();stk.push(i);
				(ans+=ANS[i])%=MOD;
			}
		}
		static int kase=1;
		printf("Case #%lld: %lld\n",kase++,ans);
	}
	return 0;
}
