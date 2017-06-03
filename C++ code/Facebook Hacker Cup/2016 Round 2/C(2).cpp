#include<cstdio>
#include<cassert>
#include<stack>
#include<algorithm>
#define int long long
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int INF=2147483647,MOD=1000000007;
void getmax(double &a,const double &b){if(b>a)a=b;}
struct Ladder
{
	int x,h;
	bool operator<(const Ladder &l)const{return x<l.x;}
}L[200001];
int N,SUM[200001],CNT[200001],ANS[200001];
main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcount;scanf(1,"%lld",&testcount);
	while(testcount--)
	{
		scanf(1,"%lld",&N);
		for(int i=1;i<=N;i++)scanf(2,"%lld%lld",&L[i].x,&L[i].h);
		sort(L+1,L+N+1);
		for(int i=1;i<=N;i++)CNT[i]=SUM[i]=ANS[i]=0;
		stack<int>stk;
		L[0].h=INF,stk.push(0);
		int ans=0;
		for(int i=1;i<=N;i++)
		{
			while(L[stk.top()].h<L[i].h)stk.pop();
			if(L[stk.top()].h>L[i].h)stk.push(i);
			else
			{
				CNT[i]=CNT[stk.top()]+1;
				SUM[i]=(SUM[stk.top()]+2*CNT[i]*(L[i].x-L[stk.top()].x))%MOD;
				ANS[i]=(ANS[stk.top()]+(L[i].x-L[stk.top()].x)*(SUM[stk.top()]+CNT[i]*(L[i].x-L[stk.top()].x)))%MOD;
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
