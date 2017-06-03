#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=4000000;
char S[100001],A[100001];
int N,F[100001];
void GetFail(const char *a,int *fail)
{
	fail[0]=fail[1]=0;
	for(int i=1,f;a[i];i++)
	{
		f=fail[i];
		while(f&&a[f]!=a[i])f=fail[f];
		fail[i+1]=(a[f]==a[i]?++f:0);
	}
//	for(int i=0;i==0||a[i-1];i++)printf(" %d",fail[i]);puts("");
}
int Query(const char *s,const char *a,const int *fail)
{
	int ans=0;
	for(int i=0,u=0;s[i];i++)
	{
		while(u&&a[u]!=s[i])u=fail[u];
		if(s[i]==a[u])u++;
		if(!a[u])ans++;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s%d",S,&N)==2)
	{
		for(int i=0;i<N;i++)
		{
			scanf("%s",A);
			GetFail(A,F);
			printf("%d\n",Query(S,A,F));
		}
	}
	return 0;
}
