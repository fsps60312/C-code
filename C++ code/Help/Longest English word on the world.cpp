#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int MAX_N=1000000;
void BuildSA(const int N,const char *S,int *SA)
{
	static int tmp[3][MAX_N];
	int *x=tmp[0],*y=tmp[1],*c=tmp[2];
	int k=256;
	for(int i=0;i<k;i++)c[i]=0;
	for(int i=0;i<N;i++)++c[x[i]=S[i]];
	for(int i=1;i<k;i++)c[i]+=c[i-1];
	for(int i=N-1;i>=0;i--)SA[--c[x[i]]]=i;
	for(int move=1;move<N;move<<=1)
	{
		int p=0;
		for(int i=N-move;i<N;i++)y[p++]=i;
		for(int i=0;i<N;i++)if(SA[i]>=move)y[p++]=SA[i]-move;
		for(int i=0;i<k;i++)c[i]=0;
		for(int i=0;i<N;i++)++c[x[i]];
		for(int i=1;i<k;i++)c[i]+=c[i-1];
		for(int i=N-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];
		swap(x,y);
		k=0;x[SA[0]]=k++;
		for(int i=1;i<N;i++)
		{
			if(y[SA[i]]!=y[SA[i-1]]||(SA[i]+move<N)!=(SA[i-1]+move<N))x[SA[i]]=k++;
			else assert(SA[i]+move<N&&SA[i-1]+move<N),x[SA[i]]=(y[SA[i]+move]==y[SA[i-1]+move]?k-1:k++);
		}
		if(k==N)break;
	}
}
int N,SA[MAX_N];
char S[MAX_N];
int main()
{
	freopen("titin.txt","r",stdin);
//	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	scanf("%s",S);
	N=-1;while(S[++N]);
	BuildSA(N,S,SA);
//	for(int i=0;i<N;i++)printf("%d ",SA[i]);puts("");
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<100;j++)if(SA[i]+j<N)putchar(S[SA[i]+j]);
		puts("");
	}
}
