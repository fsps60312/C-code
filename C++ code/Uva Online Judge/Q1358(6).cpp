#include<cstdio>
#include<cstdlib>
#define LL long long
int T,N,L,FAIL[13];
char S[13];
LL DP[13];
void buildfail()
{
	int u=0;
	FAIL[0]=FAIL[1]=0;
	for(int i=1;S[i];i++)
	{
		while(u&&S[i]!=S[u])u=FAIL[u];
		if(S[i]==S[u])u++;
		FAIL[i+1]=u;
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	scanf("%d",&T);
	int kase=0;
	while(T--)
	{
		scanf("%d%s",&N,S);
		if(kase)printf("\n");
		L=-1;while(S[++L]);
		buildfail();
		//DP[i]=DP[i-1]+f(i)
		//f(i)=1+sum((1/n)*(DP[i-1]-DP[fail(k)]+f(i)),k!=S[i-1])
		//f(i)=1+((1/n)*sum(DP[i-1]-DP[fail(k)],k!=S[i-1])+((n-1)/n)*f(i))
		//f(i)=n+sum(DP[i-1]-DP[fail(k)],k!=S[i-1])
		DP[0]=0;
		for(int i=1;i<=L;i++)
		{
			DP[i]=DP[i-1]+N;
			for(int c=0;c<N;c++)
			{
				char k='A'+c;
				if(S[i-1]==k)continue;
				int u=FAIL[i-1];
				while(u&&S[u]!=k)u=FAIL[u];
				if(S[u]==k)u++;
				DP[i]+=DP[i-1]-DP[u];
			}
			//printf(" %lld",DP[i]);
		}//printf("\n");
		printf("Case %d:\n%lld\n",++kase,DP[L]);
	}
	return 0;
}
