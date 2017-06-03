#include<cstdio>
#include<map>
#include<string>
#include<vector>
using namespace std;
void termin(char *msg){puts(msg);int a[9];for(int i=0;;i--)a[i]=9,puts(msg);}
int N,M,K,MAT[300][301];
char D1[4],D2[4];
map<string,int>DAYS;
void Exchange(int r1,int r2){for(int i=0,v;i<=N;i++)v=MAT[r1][i],MAT[r1][i]=MAT[r2][i],MAT[r2][i]=v;}
void exgcd(int a,int b,int &x,int &y)
{
	if(b)
	{
		exgcd(b,a%b,y,x);
		y-=a/b*x;
	}
	else x=1,y=0;
}
int inv(int a)
{
	if(!a)termin("a==0");
	int x,y;
	exgcd(a,7,x,y);
	return (x%7+7)%7;
}
void showMAT(char *msg)
{
	puts(msg);
	for(int i=0;i<M;i++)
	{
		for(int j=0;j<=N;j++)printf(" %d",MAT[i][j]);
		puts("");
	}
}
int solve()
{
//	if(M<N)return -1;
	int i1=0,i2=0;
	for(;i1<M&&i2<N;)
	{
//		showMAT("i");
		int j;for(j=i1;j<M;j++)if(MAT[j][i2])break;
		if(j==M){i2++;continue;}
		if(j!=i1)Exchange(i1,j);
		for(j=0;j<M;j++)
		{
			if(j==i1||!MAT[j][i2])continue;
			int ratio=inv(MAT[i1][i2])*MAT[j][i2]%7;
			for(int k=0;k<=N;k++)MAT[j][k]=((MAT[j][k]-MAT[i1][k]*ratio)%7+7)%7;
			if(MAT[j][i2])termin("not cleared");
		}
		i1++;
	}
	for(int j=i1;j<M;j++)if(MAT[j][N])return -1;
	if(i1<N)return 1;
	return 0;
}
int main()
{
//	freopen("in.txt","r",stdin);
	DAYS["SUN"]=0;
	DAYS["MON"]=1;
	DAYS["TUE"]=2;
	DAYS["WED"]=3;
	DAYS["THU"]=4;
	DAYS["FRI"]=5;
	DAYS["SAT"]=6;
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		for(int i=0;i<M;i++)
		{
			scanf("%d%s%s",&K,D1,D2);
			MAT[i][N]=((DAYS[D2]-DAYS[D1]+1)%7+7)%7;
			for(int j=0;j<N;j++)MAT[i][j]=0;
			for(int j=0,t;j<K;j++)
			{
				scanf("%d",&t);
				MAT[i][--t]++;
				MAT[i][t]%=7;
			}
		}
//		showMAT("a");
		int result=solve();
//		showMAT("b");
		if(result)printf(result==1?"Multiple solutions.\n":"Inconsistent data.\n");
		else
		{
			for(int i=0,v;i<N;i++)
			{
				if(i)printf(" ");
				v=MAT[i][N]*inv(MAT[i][i])%7;
				if(v<3)v+=7;
				printf("%d",v);
			}
			puts("");
		}
	}
	return 0;
}
