#include<cstdio>
#include<cassert>
//#include<algorithm>
using namespace std;
const int INF=2147483647;
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
int N,M,A[20],B[20];
int main()
{
//	freopen("inb.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		int sum=0;
		for(int i=0;i<N;i++)scanf("%d%d",&A[i],&B[i]),sum+=A[i];
		int ans=-1;
		for(int s=0;s<(1<<N);s++)
		{
			int a=0,b=0;
			for(int i=0;i<N;i++)if(s&(1<<i))a+=A[i],b+=B[i];
			if(b<=M)getmax(ans,a);
		}
		if(ans*2<sum)ans=-1;
		printf("%d\n",ans);
	}
	return 0;
}
