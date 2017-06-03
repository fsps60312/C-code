#include<cstdio>
#define termin(x,...) {for(;;)printf(x,##__VA_ARGS__);}
int T,P,N,MAT[70][71];
char S[71];
void initMAT()
{
	for(int i=0,k=1;i<N;i++,k++)
	{
		MAT[i][N]=S[i]=='*'?0:S[i]-'a'+1;
		for(int j=0,p=1;j<N;j++,p*=k,p%=P)
		{
			MAT[i][j]=p;
		}
	}
}
void exgcd(int a,int b,int &x,int &y)
{
	if(b)
	{
		exgcd(b,a%b,y,x);
		//(a-a/b*b)x+by==g
		y-=a/b*x;
	}
	else
	{
		if(a!=1)termin("exgcd a==%d\n",a);
		x=1,y=0;
	}
}
int mod(int a){return (a%P+P)%P;}
int inv(int a)
{
	int x,y;
	exgcd(a,P,x,y);
	return mod(x);
}
void Swap(int r1,int r2){for(int i=0,v;i<=N;i++)v=MAT[r1][i],MAT[r1][i]=MAT[r2][i],MAT[r2][i]=v;}
void mul(int r1,int v){for(int i=0;i<=N;i++)MAT[r1][i]*=v,MAT[r1][i]%=P;}
void sub(int r1,int r2){for(int i=0;i<=N;i++)MAT[r1][i]=mod(MAT[r1][i]-MAT[r2][i]);}
void solve()
{
	for(int i=0;i<N;i++)
	{
		int j;for(j=i;j<N;j++)if(MAT[j][i])break;
		if(j==N)termin("can't find >0: %d\n",i);
		if(j!=i)Swap(i,j);
		for(j=0;j<N;j++)
		{
			if(j==i||!MAT[j][i])continue;
			mul(j,MAT[i][i]*inv(MAT[j][i])%P);
			sub(j,i);
		}
	}
	for(int i=0;i<N;i++)
	{
		MAT[i][N]*=inv(MAT[i][i]);
		MAT[i][N]%=P;
	}
}
int main()
{
//	printf("%d %d\n",'*','a');return 0;//42 97
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%s",&P,S);
		N=-1;while(S[++N]);
		initMAT();
		solve();
		for(int i=0;i<N;i++)
		{
			if(i)printf(" ");
			printf("%d",MAT[i][N]);
		}
		puts("");
	}
	return 0;
}
