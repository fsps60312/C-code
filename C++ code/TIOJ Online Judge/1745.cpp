#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
struct Deq
{
	int s[1000001],l,r;
	void clear(){l=0,r=-1;}
	void push_back(const int v){s[++r]=v;}
	void pop_back(){r--;}
	void pop_front(){l++;}
	int back(const int i)const{return s[r-i];}
	int front(const int i)const{return s[l+i];}
	int size()const{return r-l+1;}
	bool empty()const{return r<l;}
}DEQ;
int N;
LL SUM[1000001],A,B,C,DP[1000001];
LL GetA(const int k){return -2LL*A*SUM[k];}
LL GetB(const int k){return DP[k]+A*SUM[k]*SUM[k]-B*SUM[k];}
double GetX(const int i1,const int i2){return (double)(GetB(i1)-GetB(i2))/(GetA(i2)-GetA(i1));} 
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		scanf("%lld%lld%lld",&A,&B,&C);
		SUM[0]=0LL;
		for(int i=1;i<=N;i++)scanf("%lld",&SUM[i]),SUM[i]+=SUM[i-1];
		//DP[i]=min(DP[k]+A(SUM[i]-SUM[k])^2+B(SUM[i]-SUM[k])+C)
		//=DP[k]+A*SUM[i]*SUM[i]-2A*SUM[i]*SUM[k]+A*SUM[k]*SUM[k]+B*SUM[i]-B*SUM[k]+C
		//=-2A*SUM[k]*SUM[i]+DP[k]+A*SUM[k]*SUM[k]-B*SUM[k]+B*SUM[i]+A*SUM[i]*SUM[i]+C
		DEQ.clear(),DEQ.push_back(0);
		DP[0]=0LL;
		for(int i=1;i<=N;i++)
		{
			while(DEQ.size()>=2&&GetX(DEQ.front(0),DEQ.front(1))<=SUM[i])DEQ.pop_front();
			const int k=DEQ.front(0);
			DP[i]=GetA(k)*SUM[i]+GetB(k)+B*SUM[i]+A*SUM[i]*SUM[i]+C;
			while(DEQ.size()>=2&&GetX(DEQ.back(0),i)<=GetX(DEQ.back(1),DEQ.back(0)))DEQ.pop_back();
			DEQ.push_back(i);
		}
		printf("%lld\n",DP[N]);
	}
	return 0;
}
