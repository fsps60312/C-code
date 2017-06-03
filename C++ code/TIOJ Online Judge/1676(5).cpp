#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
struct Deq
{
	int S[500001],L,R;
	void Clear(){L=0,R=-1;}
	void PushBack(const int v){S[++R]=v;}
	void PopBack(){--R;}
	void PopFront(){++L;}
	int Front(const int i)const{return S[L+i];}
	int Back(const int i)const{return S[R-i];}
	int Size()const{return R-L+1;}
}DEQ;
int N,K;
LL S[500000],SUM[500001],DP[500001];
LL GetA(const int i){return 2LL*i;}
LL GetB(const int i){return DP[i]-(LL)i*i;}
double GetX(const int i1,const int i2){return (double)(GetB(i1)-GetB(i2))/(GetA(i2)-GetA(i1));}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		SUM[N]=0LL;
		for(int i=N-1;i>=0;i--)SUM[i]=SUM[i+1]+S[i];
		//DP[i]=max(SUM[i]+DP[j]-(j-i)^2)
		//=SUM[i]+DP[j]-j^2-i^2+2ij
		//=2j(i)+(DP[j]-j^2)+(SUM[i]-i^2)
		DEQ.Clear();
		DEQ.PushBack(N);
		DP[N]=0LL;
		for(int i=N-1;i>=0;i--)
		{
			while(DEQ.Front(0)>i+K)DEQ.PopFront();
			while(DEQ.Size()>=2&&GetX(DEQ.Front(0),DEQ.Front(1))>=i)DEQ.PopFront();
			DP[i]=GetA(DEQ.Front(0))*i+GetB(DEQ.Front(0))+(SUM[i]-(LL)i*i);
			while(DEQ.Size()>=2&&GetX(DEQ.Back(1),DEQ.Back(0))<=GetX(DEQ.Back(0),i))DEQ.PopBack();
			DEQ.PushBack(i);
		}
		printf("%lld\n",DP[0]-SUM[0]);
	}
	return 0;
}
