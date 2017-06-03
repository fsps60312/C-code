#include<cstdio>
#include<stack>
using namespace std;
int N,S[1000000];
struct Deq
{
	int h[1000000],cnt[1000000],sz,r;
	void clear(){sz=0,r=-1;}
	int size(){return sz;}
	bool empty(){return size()==0;}
	int back(){return h[r];}
	void push_back(const int &v)
	{
		if(!empty()&&v==back())cnt[r]++;
		else h[++r]=v,cnt[r]=1;
		sz++;
	}
	void pop_back(){sz-=cnt[r--];}
	int Get(const int &v)
	{
		if(r<0)return 0;
		if(h[r]>v)return sz-1;
		else if(r<1)return 0;
		else return sz-cnt[r]-1;
	}
}DEQ;
int main()
{
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		DEQ.clear();
		DEQ.push_back(S[0]);
		long long ans=0LL;
		for(int i=1;i<N;i++)
		{
//			int ta=ans;
			ans+=DEQ.size();
			while(!DEQ.empty()&&DEQ.back()<S[i])DEQ.pop_back();
			ans-=DEQ.Get(S[i]);
//			printf("%d\n",ans-ta);
			DEQ.push_back(S[i]);
		}
		DEQ.clear();
		DEQ.push_back(S[N-1]);
		for(int i=N-2;i>=0;i--)
		{
//			int ta=ans;
			ans+=DEQ.size();
			while(!DEQ.empty()&&DEQ.back()<S[i])DEQ.pop_back();
			ans-=DEQ.Get(S[i]);
//			printf("%d\n",ans-ta);
			DEQ.push_back(S[i]);
		}
		printf("%lld\n",ans);
		break;
	}
	return 0;
}
