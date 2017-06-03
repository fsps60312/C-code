#include<cstdio>
#include<cassert>
#define int long long
using namespace std;
const int INF=2147483647;
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
int N,S[400000];
main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		int mn=INF;
		for(int i=0;i<N;i++)getmin(mn,S[N+i]=S[i]);
		int ans=N*mn;
		for(int i=0,last=-1;i<N*2;i++)
		{
			if(S[i]==mn)last=i;
			getmax(ans,N*mn+(i-last));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
