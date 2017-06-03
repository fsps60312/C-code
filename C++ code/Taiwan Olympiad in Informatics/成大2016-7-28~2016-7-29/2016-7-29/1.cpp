#include<cstdio>
#include<cassert>
#include<deque>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
const int INF=2147483647;
int N,L,A[500000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&L)==2)
	{
		if(N==0&&L==0)break;
		assert(N>=2);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		deque<int>deq;deq.push_back(0);
		int ans=-INF;
		for(int i=1;i<N;i++)
		{
			while(!deq.empty()&&deq.front()<i-L)deq.pop_front();
			getmax(ans,A[i]-A[deq.front()]);
			while(!deq.empty()&&A[deq.back()]>=A[i])deq.pop_back();
			deq.push_back(i);
		}
		printf("%d\n",ans);
	}
	return 0;
}
