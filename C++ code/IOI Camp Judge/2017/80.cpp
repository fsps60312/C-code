#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
struct Deq
{
	int S[30001];
	int L,R;
	void clear(){L=0,R=-1;}
	int size()const{return R-L+1;}
	bool empty()const{return size()==0;}
	int front()const{return S[L];}
	int back()const{return S[R];}
	void push_back(const int v){S[++R]=v;}
	void pop_back(){--R;}
	void pop_front(){++L;}
}DEQ;
int N,K,X;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&N,&K,&X);
		static LL dp[30001];
		for(int i=0;i<=X;i++)dp[i]=0;
		for(int i=0;i<N;i++)
		{
			int p,c;
			LL b;
			scanf("%d%lld%d",&p,&b,&c);
			assert(c>=K&&p<=X);
			if(c*p>X)c=X/p;
			if(c<K)continue;
			for(int start=0;start<p;start++)
			{
				DEQ.clear();
				for(int j=X-K*p-start;j+(c-K)*p>=0;j-=p)
				{
					if(j>=0)
					{
						while(!DEQ.empty()&&dp[DEQ.back()]<=dp[j]+b*((DEQ.back()-j)/p))DEQ.pop_back();
						DEQ.push_back(j);
					}
					while(!DEQ.empty()&&(DEQ.front()-j)/p>c-K)DEQ.pop_front();
					if(j+c*p<=X)
					{
						assert(!DEQ.empty());
						getmax(dp[j+c*p],dp[DEQ.front()]+b*(((j+c*p)-DEQ.front())/p));
					}
				}
			}
		}
		for(int i=1;i<=X;i++)/*printf("dp[%d]=%lld\n",i,dp[i]),*/getmax(dp[i],dp[i-1]);
		printf("%lld\n",dp[X]);
	}
	return 0;
}
