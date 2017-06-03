#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int N,M;
struct Coin
{
	int c,x;
	bool operator<(const Coin &a)const{return c<a.c;}
}C[101];
int Solve()
{
	if(C[0].c>1)return -1;
	int now=0,ans=0;
	C[N].c=INF;
	for(int i=0;now<M&&i<N;i++)
	{
		now+=C[i].c*C[i].x;
		int goal=min(C[i+1].c-1,M);
		if(now>=goal)continue;
		int cnt=(goal+C[i].c-1-now)/C[i].c;
		now+=C[i].c*cnt;
		C[i].x+=cnt;
		ans+=cnt;
	}
	return ans;
}
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d%d",&C[i].c,&C[i].x);
	}
	scanf("%d",&M);
	sort(C,C+N);
	int ans=Solve();
	printf("%d\n",ans);
	return 0;
}
