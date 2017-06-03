#include<cstdio>
//#include<cassert>
#include<set>
#include<algorithm>
using namespace std;
void assert(bool valid){if(valid)return;for(int a=0,b=0;;)a/=b;}
typedef long long LL;
struct Deq
{
	int s[100001],l,r;
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
int N,S[100001];
LL M,SUM[100001],DP[100001];
multiset<LL>BEST;
void Erase(const LL &v)
{
	multiset<LL>::iterator it=BEST.find(v);
	assert(it!=BEST.end());
	BEST.erase(it);
}
void PopFront()
{
	if(DEQ.size()>=2)Erase(DP[DEQ.front(0)]+S[DEQ.front(1)]);
	DEQ.pop_front();
}
void PopBack()
{
	if(DEQ.size()>=2)Erase(DP[DEQ.back(1)]+S[DEQ.back(0)]);
	DEQ.pop_back();
}
void PushBack(const int i)
{
	DEQ.push_back(i);
	if(DEQ.size()>=2)BEST.insert(DP[DEQ.back(1)]+S[DEQ.back(0)]);
}
LL Solve()
{
	for(int i=1;i<=N;i++)if(S[i]>M)return -1LL;
	DEQ.clear(),DEQ.push_back(0),BEST.clear();
	DP[0]=S[0]=0;
	for(int i=1,l=0;i<=N;i++)
	{
		while(!DEQ.empty()&&S[i]>=S[DEQ.back(0)])PopBack();
		PushBack(i);
		while(!DEQ.empty()&&SUM[i]-SUM[DEQ.front(0)-1]>M)PopFront();
		while(SUM[i]-SUM[l]>M)l++;
		assert(!DEQ.empty());
		assert(l<i);
		DP[i]=DP[l]+S[DEQ.front(0)];
		if(!BEST.empty()&&*BEST.begin()<DP[i])DP[i]=*BEST.begin();
		assert(DP[i]>=DP[i-1]);
//		printf("DP[%d]=%lld\n",i,DP[i]);
//		DEQ.Print();
	}
	return DP[N];
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%lld",&N,&M)==2)
	{
		SUM[0]=0LL;
		for(int i=1;i<=N;i++)scanf("%d",&S[i]),SUM[i]=SUM[i-1]+S[i];
		printf("%lld\n",Solve());
	}
	return 0;
}
