#include"interactive/118.h"
#include<cstdio>
#include<cassert>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
int N;
int Guess(const int l,const int r,const int v)
{
	if(l==r)return r;
	const int mid=(l+r)/2;
	static int tmp[101];
	for(int i=1;i<=N;i++)tmp[i]=0;
	for(int i=l;i<=mid;i++)tmp[i]=v;
	const int result=Answer(tmp);
	assert(result==0||result==1);
	if(result==0)return Guess(mid+1,r,v);
	else return Guess(l,mid,v);
}
int main()
{
	N=Init();
	static int ans[101];
	for(int v=1;v<=N;v++)ans[Guess(1,N,v)]=v;
	Answer(ans);
	assert(0);
	return 0;
}
