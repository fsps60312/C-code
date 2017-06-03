#include<cstdio>
#include<cassert>
using namespace std;
template<class T>inline void getmin(T &a,const T &b){if(b<a)a=b;}
const int INF=2147483647;
int N,S[101],DP[102];
bool IsAlter(const int l,const int r,const int d)
{
	for(int i=l;i<=r;i++)if(!(S[i]&(1<<((i&1)^d))))return false;
	return true;
}
bool IsAlter(const int l,const int r)
{
	return IsAlter(l,r,0)||IsAlter(l,r,1);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)scanf("%d",&S[i]);
		for(int i=1;i<=N+1;i++)DP[i]=INF;
		DP[0]=0;
		for(int i=1;i<=N+1;i++)
		{
			for(int j=0;j<i;j++)if(IsAlter(j+1,i-1))getmin(DP[i],DP[j]+1);
//			printf("DP[%d]=%d\n",i,DP[i]);
		}
		printf("%d\n",DP[N+1]-1);
	}
	return 0;
}
