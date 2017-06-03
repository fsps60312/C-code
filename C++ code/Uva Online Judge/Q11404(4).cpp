#include<stdio.h>
#include<assert.h>
#include<algorithm>
using namespace std;
const int INF=2147483647;
char S[1001];
int N,DP[1000][1000],L[26][1000],R[26][1000];
inline void getmax(int &a,const int b){if(b>a)a=b;}
void PrintAns(const int l,const int r)
{
//	printf("(%d,%d)\n",l,r);
	for(int c=0;c<26;c++)if(R[c][l]!=INF&&L[c][r]>=R[c][l])
	{
		if(DP[l][r]==2)
		{
			if(L[c][r]==R[c][l])continue;
			putchar('a'+c),putchar('a'+c);return;
		}
		if(DP[l][r]==1){putchar('a'+c);return;}
		if(DP[R[c][l]][L[c][r]]==DP[l][r])
		{
			putchar('a'+c);
			PrintAns(R[c][l]+1,L[c][r]-1);
			putchar('a'+c);
			return;
		}
	}
	assert(0);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s",&S)==1)
	{
		N=-1;while(S[++N]);
		for(int i=0;i<N;i++)DP[i][i]=1;
		for(int i=0;i+1<N;i++)DP[i][i+1]=(S[i]==S[i+1]?2:1);
		for(int gap=2;gap<N;gap++)
		{
			for(int i=0;i+gap<N;i++)
			{
				if(S[i]==S[i+gap])DP[i][i+gap]=DP[i+1][i+gap-1]+2;
				else DP[i][i+gap]=max(DP[i+1][i+gap],DP[i][i+gap-1]);
			}
		}
		for(int c=0;c<26;c++)
		{
			int l=-INF;
			for(int i=0;i<N;i++)
			{
				if(S[i]=='a'+c)l=i;
				L[c][i]=l;
			}
			int r=INF;
			for(int i=N-1;i>=0;i--)
			{
				if(S[i]=='a'+c)r=i;
				R[c][i]=r;
			}
		}
//		printf("len=%d\n",DP[0][N-1]);
		PrintAns(0,N-1);puts("");
	}
}
