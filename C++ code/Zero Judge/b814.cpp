#include<cstdio>
#include<cassert>
using namespace std;
int N,T,SUM[100000];
char S[100001];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%s",S);
	N=-1;while(S[++N]);
	SUM[0]=0;
	for(int i=1;i<N;i++)
	{
		SUM[i]=SUM[i-1];
		if(S[i]==S[i-1])SUM[i]++;
	}
	scanf("%d",&T);
	for(int i=0,l,r;i<T;i++)
	{
		scanf("%d%d",&l,&r);
		r--;
		printf("%d\n",SUM[r]-SUM[l-1]);
	}
	return 0;
}
