#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
struct Deq
{
	int S[1000001],L,R;
	void Clear(){L=0,R=-1;}
	void PushBack(const int v){S[++R]=v;}
	void PopBack(){R--;}
	void PopFront(){L++;}
	int Front(const int i){return S[L+i];}
	int Back(const int i){return S[R-i];}
	int Size(){return R-L+1;}
}DEQ;
struct Factory
{
	LL X,P,C;
}F[1000001];
int N;
LL DP[1000001],PROD[1000001],COST[1000001];
LL GetA(const int i){return -PROD[i];}
LL GetB(const int i){return DP[i]-COST[i]+PROD[i]*F[N].X;}
double GetX(const int i1,const int i2){return (double)(GetB(i1)-GetB(i2))/(GetA(i2)-GetA(i1));}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)scanf("%lld%lld%lld",&F[i].X,&F[i].P,&F[i].C);
	PROD[0]=COST[0]=0LL;
	for(int i=1;i<=N;i++)
	{
		PROD[i]=PROD[i-1]+F[i].P;
		COST[i]=COST[i-1]+F[i].P*(F[N].X-F[i].X);
	}
	DP[0]=0LL;
	DEQ.Clear();
	DEQ.PushBack(0);
	for(int i=1;i<=N;i++)
	{
		DP[i]=INF;
		//DP[i] = DP[j]+(COST[i]-COST[j])-(PROD[i]-PROD[j])*(F[N].X-F[i].X)
		//DP[j]+COST[i]-COST[j]-PROD[i]*X[N]+PROD[i]*X[i]+PROD[j]*X[N]-PROD[j]*X[i]
		//-PROD[j]*X[i]+DP[j]-COST[j]+PROD[j]*X[N]+COST[i]-PROD[i]*X[N]+PROD[i]*X[i]
		//A=-PROD[j],B=DP[j]-COST[j]+PROD[j]*X[N]
		while(DEQ.Size()>=2&&GetX(DEQ.Front(0),DEQ.Front(1))<=F[i].X)DEQ.PopFront();
		DP[i]=GetA(DEQ.Front(0))*F[i].X+GetB(DEQ.Front(0))+COST[i]-PROD[i]*F[N].X+PROD[i]*F[i].X+F[i].C;
		while(DEQ.Size()>=2&&GetX(DEQ.Back(1),DEQ.Back(0))>=GetX(DEQ.Back(0),i))DEQ.PopBack();
		DEQ.PushBack(i);
	}
	printf("%lld\n",DP[N]);
	return 0;
}
