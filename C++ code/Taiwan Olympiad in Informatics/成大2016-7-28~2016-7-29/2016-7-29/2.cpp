#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
void BuildFail(const int n,const int *str,int *fail)
{
	fail[0]=fail[1]=0;
	for(int i=1;i<n;i++)
	{
		int &f=fail[i+1]=fail[i];
		while(f&&str[f]!=str[i])f=fail[f];
		if(str[f]==str[i])++f;
	}
}
int N,M,A[100000],B[100000],FAIL[100001];
int Solve()
{
	int u=0,ans=0;
	for(int i=0;i<M;i++)
	{
		while(u&&B[i]!=A[u])u=FAIL[u];
		if(B[i]==A[u])++u;
		if(u==N)++ans,u=FAIL[u];
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<M;i++)scanf("%d",&B[i]);
		--N,--M;
		for(int i=0;i<N;i++)A[i]=A[i]-A[i+1];
		for(int i=0;i<M;i++)B[i]=B[i+1]-B[i];
		BuildFail(N,A,FAIL);
		printf("%d\n",Solve());
	}
	return 0;
}
