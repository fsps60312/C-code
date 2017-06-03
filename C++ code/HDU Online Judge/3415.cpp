#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
struct Deq
{
	int s[200001],l,r;
	void clear(){l=0,r=-1;}
	void push_back(const int v){s[++r]=v;}
	void pop_back(){r--;}
	void pop_front(){l++;}
	int size()const{return r-l+1;}
	int front()const{return s[l];}
	int back()const{return s[r];}
	bool empty()const{return r<l;}
}DEQ;
int N,K,S[200001],SUM[200001];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		for(int i=1;i<=N;i++)scanf("%d",&S[i]);
		for(int i=1;i<=N;i++)S[N+i]=S[i];
		for(int i=1;i<=N*2;i++)SUM[i]=SUM[i-1]+S[i];
		int ans_sum=-INF,ans_l=-1,ans_r=-1;
		DEQ.clear(),DEQ.push_back(0);
		for(int i=1;i<=N*2;i++)
		{
			while(DEQ.front()<i-K)DEQ.pop_front();
			assert(!DEQ.empty());
			const int sum=SUM[i]-SUM[DEQ.front()];
			if(sum>ans_sum||(sum==ans_sum&&DEQ.front()<ans_l))ans_sum=sum,ans_l=DEQ.front(),ans_r=i;
			while(!DEQ.empty()&&SUM[i]<=SUM[DEQ.back()])DEQ.pop_back();
			DEQ.push_back(i);
		}
		assert(ans_sum!=-INF&&ans_l<N);
		printf("%d %d %d\n",ans_sum,ans_l+1,(ans_r-1)%N+1);
	}
	return 0;
}
