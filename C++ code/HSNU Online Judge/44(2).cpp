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
	if(l==r)return ans=N&1?Pair(S[l],0):Pair(0,S[l]);
	Pair a=Get(l+1,r),b=Get(l,r-1);
	int i=(r-l+1+N)&1;
	a.v[i]+=S[l],b.v[i]+=S[r];
	if(a.v[i]>b.v[i])return ans=a;
	else return ans=b;
}
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	for(int i=0;i<N;i++)for(int j=i;j<N;j++)DP[i][j]=Pair(-1,-1);
	Pair ans=Get(0,N-1);
	printf("%d %d\n",ans.v[0],ans.v[1]);
	return 0;
}
