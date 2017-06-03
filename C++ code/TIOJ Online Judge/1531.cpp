#include<cstdio>
#include<cassert>
using namespace std;
int BuildFail(const char *str,int *fail)
{
	fail[0]=fail[1]=0;
	for(int i=1;;i++)
	{
		if(!str[i])return i;
		int &f=fail[i+1]=fail[i];
		while(f&&str[f]!=str[i])f=fail[f];
		if(str[f]==str[i])f++;
	}
}
int K,N,FAIL[5000001];
char S[5000001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%s",&K,S)==2)
	{
		N=BuildFail(S,FAIL);
		int ans=0;
		for(int len=N/K;len>0;len--)
		{
			const int v=len*K-FAIL[len*K];
			if(len%v==0){ans=len;break;}
		}
		printf("%d\n",ans);
	}
	return 0;
}
