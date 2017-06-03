#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=500000LL*500000LL+1LL;
struct Deq
{
	int s[500001],l,r;
	void clear(){l=0,r=-1;}
	void push_back(const int v){s[++r]=v;}
	void pop_back(){r--;}
	void pop_front(){l++;}
	int back(const int i)const{return s[r-i];}
	int front(const int i)const{return s[l+i];}
	int size()const{return r-l+1;}
	bool empty()const{return r<l;}
//	void Print()const{for(int i=l;i<=r;i++)printf("%d ",s[i]);puts("");}
}DEQ;
int N,K,S[500001];
LL SUM[500001],DP[500002];
LL GetA(const int i){return -S[i+1];}
LL GetB(const int i){return (LL)S[i+1]*i+DP[i]-SUM[i];}
double GetX(const int i1,const int i2){assert(GetA(i1)!=GetA(i2));return (double)(GetB(i1)-GetB(i2))/(GetA(i2)-GetA(i1));}
bool NeedPopBack(const int i)
{
	if(DEQ.empty())return false;
	else if(GetA(DEQ.back(0))==GetA(i))return GetB(i)<=GetB(DEQ.back(0));
	else if(DEQ.size()==1)return false;
	else return GetX(DEQ.back(0),i)<=GetX(DEQ.back(1),DEQ.back(0));
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		S[0]=SUM[0]=0LL;
		for(int i=1;i<=N;i++)scanf("%d",&S[i]);
		for(int i=1;i<=N;i++)SUM[i]=SUM[i-1]+S[i];
		//DP[i]=min(DP[k]+(SUM[i]-SUM[k])-S[k+1]*(i-k))
		//=DP[k]+SUM[i]-SUM[k]-S[k+1]*i+S[k+1]*k
		//=-S[k+1]*i+S[k+1]*k+DP[k]-SUM[k]+SUM[i]
		DP[0]=0LL;
		DEQ.clear(),DEQ.push_back(0);
		for(int i=1;i<=N;i++)
		{
			while(DEQ.size()>=2&&DEQ.front(1)<=i-K)DEQ.pop_front();
			if(DEQ.empty()||DEQ.front(0)>i-K)DP[i]=INF;
			else
			{
				const int k=DEQ.front(0);
				DP[i]=GetA(k)*i+GetB(k)+SUM[i];
			}
			while(NeedPopBack(i))DEQ.pop_back();
			if(DEQ.empty()||GetA(DEQ.back(0))!=GetA(i))DEQ.push_back(i);
//			DEQ.Print();
		}
		printf("%I64d\n",DP[N]);
	}
	return 0;
}
