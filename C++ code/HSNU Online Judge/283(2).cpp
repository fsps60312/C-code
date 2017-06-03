#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
int N,M,K;
char GRID[2001][2001];
int ANS[1000][1000];
bool Check()
{
	int cnt=0,sum=0;
	for(int r=0;r<2*N-1;r++)
	{
		for(int c=(r%2==0?1:0);c<2*M-1;c+=2)
		{
			const char v=GRID[r][c];
			sum++;
			if(r%2==0&&(ANS[r/2][c/2]==ANS[r/2][c/2+1])==(v=='E'))cnt++;
			if(r%2==1&&(ANS[r/2][c/2]==ANS[r/2+1][c/2])==(v=='E'))cnt++;
		}
	}
	return cnt>=sum*3/4;
}
bool Solve()
{
	assert(K>=1);
	if(K==1)
	{
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)ANS[i][j]=0;
		return Check();
	}
	bool flipped=false;
	if(N>M)
	{
		flipped=true;
		for(int i=0;i<2*N-1;i++)for(int j=i+1;j<2*max(N,M)-1;j++)swap(GRID[i][j],GRID[j][i]);
		swap(N,M);
	}
	for(int r=0;r<N;r++)
	{
		int pre=ANS[r][0]=0;
		for(int c=1;c<M;c++)ANS[r][c]=(GRID[r*2][c*2-1]=='E'?pre:(pre^=1));
	}
	for(int r=1;r<N;r++)
	{
		int cnt=0;
		for(int c=0;c<M;c++)if((ANS[r-1][c]==ANS[r][c])==(GRID[r*2-1][c*2]=='E'))cnt++;
		if(cnt*2<M)for(int c=0;c<M;c++)ANS[r][c]^=1;
	}
	assert(Check());
	if(flipped)
	{
		for(int i=0;i<N;i++)for(int j=i+1;j<max(N,M);j++)swap(ANS[i][j],ANS[j][i]);
		swap(N,M);
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&M,&K);
	for(int i=0;i<2*N-1;i++)
	{
		for(int j=(i%2==0?1:0);j<2*M-1;j+=2)
		{
			char &c=GRID[i][j]=getchar();
			while(c!='N'&&c!='E')c=getchar();
		}
	}
	if(Solve())
	{
		puts("YES");
		for(int r=0;r<N;r++)
		{
			for(int c=0;c<M;c++)
			{
				if(c)putchar(' ');
				printf("%d",ANS[r][c]+1);
			}
			puts("");
		}
	}
	else puts("NO");
	return 0;
}
