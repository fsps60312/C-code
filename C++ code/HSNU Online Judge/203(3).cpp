#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N,L,SUM[100001],DP[100000],H[100000];
LL W(const int &l,const int &r){return SUM[r+1]-SUM[l];}
struct Deq
{
	int s[100001],l,r;
	int Sz()const{return r-l+1;}
	void Clear(){l=0,r=-1;}
	void PushBack(const int &v){s[++r]=v;}
	void PopBack(){r--;}
	void PopFront(){l++;}
	int &Front(const int &i=0){return s[l+i];}
	int &Back(const int &i=0){return s[r+i];}
}DEQ;
multiset<LL>S;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld",&N,&L)==2)
	{
		SUM[0]=0;
		for(int i=0;i<N;i++)
		{
			static LL w;
			scanf("%lld%lld",&H[i],&w);
			SUM[i+1]=SUM[i]+w;
		}
		DP[0]=H[0];
		S.clear();
		DEQ.Clear();
		DEQ.PushBack(0);
		for(int i=1;i<N;i++)
		{
			while(DEQ.Sz()>=2&&H[i]<H[DEQ.Back()])
			{
				assert(S.find(DP[DEQ.Back(-1)]+H[DEQ.Back()])!=S.end());
				S.erase(S.find(DP[DEQ.Back(-1)]+H[DEQ.Back()]));
				DEQ.PopBack();
			}
			DEQ.PushBack(i);
			while(W(DEQ.Front(),i)>L)
			{
				printf("W(%d,%d)=%lld,L=%lld\n",DEQ.Front(),i,W(DEQ.Front(),i),L);
				assert(DEQ.Sz()>=2&&S.find(DP[DEQ.Front()]+H[DEQ.Front(1)])!=S.end());
				S.erase(S.find(DP[DEQ.Front()]+H[DEQ.Front(1)]));
				if(++DEQ.Front()==DEQ.Front(1))DEQ.PopFront();
			}
			assert(DEQ.Back()==i);
			S.insert(DP[DEQ.Back(-1)]+H[i]);
			for(LL i:S)printf(" %d",i);puts("");
			DP[i]=*S.begin();
			printf("DP[%d]=%d\n",i,DP[i]);
		}
		printf("%lld\n",DP[N-1]);
	}
	return 0;
}
