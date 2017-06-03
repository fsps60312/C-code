#include<cstdio>
#include<cassert>
using namespace std;
int DP[201][201][201];
int N;
int GetDP(const int a,const int b,const int c)
{
	int &ans=DP[a][b][c];
	if(ans)return ans;
	if(a>=2)ans|=GetDP(a-1,b,c);
	if(b>=2)ans|=GetDP(a,b-1,c);
	if(c>=2)ans|=GetDP(a,b,c-1);
	if(a&&b)ans|=GetDP(a-1,b-1,c+1);
	if(a&&c)ans|=GetDP(a-1,b+1,c-1);
	if(b&&c)ans|=GetDP(a+1,b-1,c-1);
	return ans;
}
char LETTER[3]={'B','G','R'};
int ID[256];
int main()
{
	for(int i=0;i<3;i++)ID[LETTER[i]]=i;
//	freopen("in.txt","r",stdin);
	for(int i=0;i<200;i++)for(int j=0;j<200;j++)for(int k=0;k<200;k++)DP[i][j][k]=0;
	DP[1][0][0]=1<<0;
	DP[0][1][0]=1<<1;
	DP[0][0][1]=1<<2;
	while(scanf("%d",&N)==1)
	{
		static char str[201];
		scanf("%s",str);
		int cnt[3]={0,0,0};
		for(int i=0;i<N;i++)cnt[ID[str[i]]]++;
		const int ans=GetDP(cnt[0],cnt[1],cnt[2]);
		for(int i=0;i<3;i++)if(ans&(1<<i))putchar(LETTER[i]);puts("");
	}
	return 0;
}
