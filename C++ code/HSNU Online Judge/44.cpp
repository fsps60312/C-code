#include<bits/stdc++.h>
using namespace std;
int N,S[1000];
struct Pair
{
	int v[2];
	Pair(){}
	Pair(int a,int b):v{a,b}{}
}DP[1000][1000];
Pair Get(int l,int r)
{
	Pair &ans=DP[l][r];
	if(ans.v[0]!=-1)return ans;
	if(l==r)return ans=Pair(0,S[l]);
	Pair a=Get(l+1,r),b=Get(l,r-1);
	int i=(r-l+1)&1;
	a.v[i]+=S[l],b.v[i]+=S[r];
	if(a.v[i]>b.v[i])return ans=a;
	else return ans=b;
}
int main()
{
	Pair p=Pair(1,2);
	assert(p.v[0]==1&&p.v[1]==2);
	Pair t=p;
	t.v[0]+=100,t.v[1]+=100;
	assert(p.v[0]==1&&p.v[1]==2);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d",&S[i]);
		assert(S[i]>=0);
	}
	for(int i=0;i<N;i++)for(int j=i;j<N;j++)DP[i][j]=Pair(-1,-1);
	Pair ans=Get(0,N-1);
//	assert(!(N&1));
//	assert(ans.v[0]>=ans.v[1]);
	printf("%d %d\n",ans.v[0],ans.v[1]);
	return 0;
}
