#include<cstdio>
int N;
char S[500000];
int FAIL[500001];
void GetFAIL(const int len)
{
	FAIL[0]=FAIL[1]=0;
	for(int i=1;i<len;i++)
	{
		int f=FAIL[i];
		while(f&&S[f]!=S[i])f=FAIL[f];
		FAIL[i+1]=(S[f]==S[i]?++f:0);
	}
}
bool Solve(const int len)
{
	GetFAIL(len);
	int pre=-1,u=0;
	for(int i=0;i<N;i++)
	{
		if(u==len)u=FAIL[len];
		while(u&&S[u]!=S[i])u=FAIL[u];
		if(S[u]==S[i])u++;
//		printf("len=%d,i=%d,u=%d\n",len,i,u);
		if(u==len)
		{
			if(i-pre>len)return false;
			pre=i;
		}
	}
//	printf("u=%d\n",u);
	return N-pre<=len&&u==len;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%s",S);
	N=-1;while(S[++N]);
//	int l=1,r=N;
//	while(l<r)
//	{
//		const int mid=(l+r)/2;
//		if(Solve(mid))r=mid;
//		else l=mid+1;
//	}
	int r=1;
	while(!Solve(r))r++;
	printf("%d\n",r);
	return 0;
}
