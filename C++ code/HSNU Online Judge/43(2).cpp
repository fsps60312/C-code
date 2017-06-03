#include<bits/stdc++.h>
using namespace std;
struct Cow
{
	int h,a,c;
	bool operator<(const Cow &c)const{return a<c.a;}
}COW[400];
int N,MX;
bool DP[40001];
vector<int>V;
int main()
{
	scanf("%d",&N);
	MX=0;
	for(int i=0;i<N;i++)
	{
		Cow &c=COW[i];
		scanf("%d%d%d",&c.h,&c.a,&c.c);
		MX=max(MX,c.a);
	}
	sort(COW,COW+N);
	for(int i=0;i<=MX;i++)DP[i]=false;
	DP[0]=true;
	for(int i=0;i<N;i++)
	{
		Cow &c=COW[i];
		for(int j=0;j<c.c;j++)
		{
			for(int k=c.a;k-c.h>=0;k--)DP[k]|=DP[k-c.h];
		}
	}
	for(int i=MX;i>=0;i--)if(DP[i])
	{
		printf("%d\n",i);
		return 0;
	}
}
