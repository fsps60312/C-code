#include<cstdio>
#include<cstdlib>
char S[1001];
int state[1000][1000],n;
int Max(int a,int b)
{
	return a>b?a:b;
}
void showans(int a,int b)
{
	for(char i='a';i<='z';i++)
	{
		int j,k;
		for(j=a;S[j]!=i&&j<=b;j++);
		if(j==b+1) continue;
		for(k=b;S[k]!=i;k--);
		if(state[j][k]==state[a][b])
		{
			printf("%c",i);
			if(state[j][k]>2) showans(j+1,k-1);
			if(state[j][k]>=2) printf("%c",i);
			return;
		}
	}
	return;
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%s",S)==1)
	{
		n=-1;
		while(S[++n]);
		for(int i=0;i<n;i++)
		{
			state[i][i]=1;
		}
		for(int i=1;i<n;i++)
		{
			if(S[i-1]==S[i])
			{
				state[i-1][i]=2;
			}
			else state[i-1][i]=1;
		}
		for(int i=2;i<n;i++)
		{
			for(int j=0;j+i<n;j++)
			{
				if(S[j]==S[j+i])
				{
					state[j][j+i]=state[j+1][j+i-1]+2;
				}
				else state[j][j+i]=Max(state[j+1][j+i],state[j][j+i-1]);
			}
		}
		//printf("%d ",state[0][n-1]);
		showans(0,n-1);
		printf("\n");
	}
	return 0;
}
