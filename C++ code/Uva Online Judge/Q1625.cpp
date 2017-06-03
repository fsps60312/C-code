#include<cstdio>
#include<cstdlib>
char S1[5001],S2[5001];
int N1,N2;
int CP1[26][2],CP2[26][2];
int ANS[5001][5001];
void getmax(int &a,int b){if(b>a)a=b;}
void getmin(int &a,int b){if(b<a)a=b;}
bool atrange(int n,int l,int r){return n>=l&&n<=r;}
int get_color(int i1,int i2)
{
	int ans=0;
	for(int c=0;c<26;c++)
	{
		if((i1>CP1[c][0]||i2>CP2[c][0])&&(i1<=CP1[c][1]||i2<=CP2[c][1]))ans++;
	}
	return ans;
}
int min(int a,int b){return a<b?a:b;}
int get_ans()
{
	ANS[0][0]=0;
	for(int i1=1;i1<=N1;i1++)ANS[i1][0]=ANS[i1-1][0]+get_color(i1,0);
	for(int i2=1;i2<=N2;i2++)ANS[0][i2]=ANS[0][i2-1]+get_color(0,i2);
	for(int i1=1;i1<=N1;i1++)
	{
		for(int i2=1;i2<=N2;i2++)
		{
			ANS[i1][i2]=min(ANS[i1-1][i2],ANS[i1][i2-1])+get_color(i1,i2);
		}
	}
	/*for(int i=0;i<=N1;i++)
	{
		for(int j=0;j<=N2;j++)
		{
			printf(" %2d %c",ANS[i][j],S2[j]);
		}
		printf("\n");
		if(i==N1)break;
		for(int j=0;j<=N2;j++)
		{
			printf("  %c  ",S1[i]);
		}
		printf("\n");
	}*/
	return ANS[N1][N2];
}
int T;
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%s",S1,S2);
		N1=N2=-1;
		for(int i=0;i<26;i++)
		{
			CP1[i][0]=CP2[i][0]=2147483646;
			CP1[i][1]=CP2[i][1]=-1;
		}
		while(S1[++N1])
		{
			getmax(CP1[S1[N1]-'A'][1],N1);
			getmin(CP1[S1[N1]-'A'][0],N1);
		}
		while(S2[++N2])
		{
			getmax(CP2[S2[N2]-'A'][1],N2);
			getmin(CP2[S2[N2]-'A'][0],N2);
		}
		/*for(int i=0;i<26;i++)
		{
			printf("%c:\t%d\t%d\t%d\t%d\n",'A'+i,CP1[i][0],CP1[i][1],CP2[i][0],CP2[i][1]);
		}*/
		printf("%d\n",get_ans());
	}
}
