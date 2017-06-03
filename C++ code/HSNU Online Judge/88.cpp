#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int N,M;
char LOLI[1000001];
int S[1000001],SUM[1000001];
int L[2000001],R[2000001];
int Sum(const int a,const int b){return SUM[b]-SUM[a-1];}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	scanf("%s",LOLI);
	SUM[0]=0;
	for(int i=1;i<=N;i++)
	{
		switch(LOLI[i-1])
		{
			case'T':S[i]=2;break;
			case'W':S[i]=1;break;
			default:assert(0);break;
		}
		SUM[i]=SUM[i-1]+S[i];
	}
	for(int i=0;i<=N*2;i++)L[i]=-1;
	int one=-1;
	for(int i=1;i<=N;i++)
	{
		if(one==-1&&S[i]==1)one=i;
		int len=Sum(1,i);
		L[len]=1,R[len]=i;
		if(one!=-1)
		{
			int len=Sum(one,i);
			L[len]=one,R[len]=i;
			if(len>1)
			{
				len--;
				L[len]=one+1,R[len]=i;
			}
		}
	}
	one=-1;
	for(int i=N;i>=1;i--)
	{
		if(one==-1&&S[i]==1)one=i;
		int len=Sum(i,N);
		L[len]=i,R[len]=N;
		if(one!=-1)
		{
			int len=Sum(i,one);
			L[len]=i,R[len]=one;
			if(len>1)
			{
				len--;
				L[len]=i,R[len]=one-1;
			}
		}
	}
	while(M--)
	{
		static int k;
		scanf("%d",&k);
		if(k>N*2||L[k]==-1)puts("NIE");
		else
		{
			assert(Sum(L[k],R[k])==k);
			printf("%d %d\n",L[k],R[k]);
		}
	}
	return 0;
}
