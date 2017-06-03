#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,K;
char S[100001];
bool Solve()
{
	static bool changed[100000];
	for(int i=0;i<N;i++)changed[i]=false;
	for(int l=0,r=N-1;l<r;l++,r--)if(S[l]!=S[r])
	{
		char c=max(S[l],S[r]);
		S[l]=S[r]=c;
		changed[l]=true;
		if(K==0)return false;
		--K;
	}
	for(int l=0,r=N-1;l<=r;l++,r--)if(S[l]<'9')
	{
		if(changed[l]||l==r)
		{
			if(K>=1)--K,S[l]=S[r]='9';
		}
		else
		{
			if(K>=2)K-=2,S[l]=S[r]='9';
		}
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		scanf("%s",S);
		if(!Solve())puts("-1");
		else printf("%s\n",S);
	}
	return 0;
}
