#include<cstdio>
#include<cassert>
using namespace std;
void BuildFail(const char *str,int *fail)
{
	fail[0]=fail[1]=0;
	for(int i=1;str[i];i++)
	{
		int &f=fail[i+1]=fail[i];
		while(f&&str[f]!=str[i])f=fail[f];
		if(str[f]==str[i])f++;
	}
}
int N,FAIL[500001];
char S[500001];
bool Solve(const int max_len)
{
	int u=0;
	for(int i=0,last=-1;i<N;i++)
	{
		if(u==max_len)last=i,u=FAIL[u],printf("find");
		while(u&&S[u]!=S[i])u=FAIL[u];
		if(S[u]==S[i])u++;
		if(last<i-u)return false;
	}
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%s",S);
	N=-1;while(S[++N]);
	BuildFail(S,FAIL);
	for(int i=0;i<=N;i++)printf("%d ",FAIL[i]);puts("");
	int l=1,r=N;
	while(l<r)
	{
		const int mid=(l+r)/2;
		printf("(%d,%d,%d)\n",l,mid,r);
		if(!Solve(mid))l=mid+1;
		else r=mid;
	}
	printf("%d\n",r);
	return 0;
}
