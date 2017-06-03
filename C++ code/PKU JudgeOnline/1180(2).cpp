#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Deq
{
	int s[10002],l,r;
	void clear(){l=10002,r=10001;}
	void push_front(const int v){s[--l]=v;}
	void pop_back(){r--;}
	void pop_front(){l++;}
	int front(const int idx){return s[l+idx];}
	int back(const int idx){return s[r-idx];}
	int size(){return r-l+1;}
}DEQ;
int N,S,T[10001],C[10001],TSUM[10001],CSUM[10001],DP[10002];
double GetA(const int i){return -TSUM[i];}
double GetB(const int i){return (double)TSUM[i]*CSUM[N]+DP[i+1];}
double GetX(const int i1,const int i2)
{//ax+b=Ax+B, (a-A)x=(B-b)
	return (GetB(i2)-GetB(i1))/(GetA(i1)-GetA(i2));
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		scanf("%d",&S);
		for(int i=1;i<=N;i++)scanf("%d%d",&T[i],&C[i]),TSUM[i]=TSUM[i-1]+T[i],CSUM[i]=CSUM[i-1]+C[i];
		DP[N+1]=0;
		DEQ.clear(),DEQ.push_front(N+1);
		for(int i=N;i>=1;i--)
		{
			while(DEQ.size()>=2&&GetX(i,DEQ.front(0))>=GetX(DEQ.front(0),DEQ.front(1)))DEQ.pop_front();
			DEQ.push_front(i);
			while(DEQ.size()>=2&&GetX(DEQ.back(1),DEQ.back(0))>=CSUM[i-1])DEQ.pop_back();
			const int j=DEQ.back(0);
			DP[i]=(S*CSUM[N]-S*CSUM[i-1]-TSUM[i-1]*CSUM[N]+TSUM[i-1]*CSUM[i-1])+(TSUM[j]*CSUM[N]+DP[j+1])-(TSUM[j]*CSUM[i-1]);
			//DP[i]=(S+TSUM[j]-TSUM[i-1])*(CSUM[N]-CSUM[i-1])+DP[j+1]
			//=S*CSUM[N]-S*CSUM[i-1]+TSUM[j]*CSUM[N]-TSUM[j]*CSUM[i-1]-TSUM[i-1]*CSUM[N]+TSUM[i-1]*CSUM[i-1]+DP[j+1]
			//=(S*CSUM[N]-S*CSUM[i-1]-TSUM[i-1]*CSUM[N]+TSUM[i-1]*CSUM[i-1])+(TSUM[j]*CSUM[N]+DP[j+1])-(TSUM[j]*CSUM[i-1])
			//a=-TSUM[j],b=TSUM[j]*CSUM[N]+DP[j+1],x=CSUM[i-1]
			//minimize ax+b
		}
		printf("%d\n",DP[1]);
	}
	return 0;
}
