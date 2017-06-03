#include<cstdio>
#include<cassert>
#include<cmath>
//#include<algorithm>
using namespace std;
typedef long long LL;
const int INF=2147483647;
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
LL Pow(LL a,LL p)
{
	LL ans=1;
	for(;p;p>>=1)
	{
		if(p&1)ans*=a;
		a*=a;
	}
	return ans;
}
LL A,B,ANS1,ANS2;
bool Solve(const int x)
{
	LL n=pow(B,1.0/x)+0.5;
//	printf("x=%d,A=%d,B=%d,n=%d\n",x,A,B,n);
	if(Pow(n,x)!=B||Pow((n+1),x)!=A)return false;
	ANS1=0;
	for(int i=0;i<x;i++)ANS1+=Pow(n,i);
	ANS2=0;
	for(int i=0;i<=x;i++)ANS2+=Pow(n+1,x-i)*Pow(n,i);
	return true;
}
int main()
{
//	freopen("inb.txt","r",stdin);
	while(scanf("%lld%lld",&A,&B)==2)//A=(N+1)^X,B=N^X
	{
		if(A==0&&B==0)break;
		if(A==1&&B==1)
		{
			ANS1=0,ANS2=1;
			goto found_index;
		}
		for(int p=32;p>=1;p--)
		{
			if(Solve(p))goto found_index;
		}
		assert(0);
		found_index:;
		printf("%lld %lld\n",ANS1,ANS2);
	}
	return 0;
}
