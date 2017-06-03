#include<cstdio>
#define LL long long
void termin(char *c){puts(c);int a[9];for(int i=0;;i++)a[i]=9;}
int A,M,B,N,S;
LL MAT[20][21],C[21][21];
LL abs(LL &a){return a>=0?a:-a;}
void initMAT()
{
	for(int i=0;i<S;i++)for(int j=0;j<=S;j++)MAT[i][j]=0LL;
	for(int d=S;d>=0;d--)//degree
	{
		for(int a=0;a<=d;a++)//pow of A 
		{
			//C(d,a)*A^a*B^(d-a)
			LL c=1LL;
			LL r=1LL;
			for(int i=0;i<a/M;i++)r*=A;
			for(int i=0;i<(d-a)/N;i++)r*=B;
			if(d<S)MAT[a%M*N+(d-a)%N][d]+=r*C[d][a];//A^(a/M)*B^(b/N)
			else
			{
				MAT[a%M*N+(d-a)%N][S]-=r*C[d][a];
//				printf("%d\n",r*C[d][a]);
			}
		}
	}
}
void Exchange(int r1,int r2)
{
	LL v;
	for(int i=0;i<=S;i++)v=MAT[r1][i],MAT[r1][i]=MAT[r2][i],MAT[r2][i]=v;
}
void MulBy(int r1,LL ratio){for(int i=0;i<=S;i++)MAT[r1][i]*=ratio;}
void DivBy(int r1,LL ratio)
{
	for(int i=0;i<=S;i++)
	{
		if(MAT[r1][i]%ratio){termin("not divisable\n");}
		MAT[r1][i]/=ratio;
	}
}
void Kill(int r1,int r2){for(int i=0;i<=S;i++)MAT[r1][i]-=MAT[r2][i];}
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
void Carry(int r1)
{
	LL g=-1LL;
	for(int i=0;i<=S;i++)
	{
		if(!MAT[r1][i])continue;
		if(g==-1LL)g=abs(MAT[r1][i]);
		else g=gcd(g,abs(MAT[r1][i]));
	}
	if(g==-1LL)return;
	for(int i=0;i<=S;i++)MAT[r1][i]/=g;
}
void showMAT(char *msg)
{
	puts(msg);
	for(int i=0;i<S;i++)
	{
		printf("A^%d*B^%d:",i/N,i%N);
		for(int j=0;j<=S;j++)printf(" %lld",MAT[i][j]);
		puts("");
	}
}
void solve()
{
	for(int i=0;i<S;i++)
	{
//		printf("i=%d\n",i);
		int j;for(j=i;j<S;j++)if(MAT[j][i])break;
		if(j==S)termin("j==N");
		Exchange(i,j);
		if(MAT[i][i]<0LL)MulBy(i,-1LL);
		for(int k=0;k<S;k++)
		{
			if(k==i||!MAT[k][i])continue;
			if(MAT[k][i]<0LL)MulBy(k,-1LL);
//		showMAT("aaa");
			LL g=gcd(MAT[i][i],MAT[k][i]);
			LL g1=MAT[k][i]/g,g2=MAT[i][i]/g;
//			if(g1<=0LL||g2<=0LL)printf("<=0LL\n");
			MulBy(i,g1);
			MulBy(k,g2);
			Kill(k,i);
//puts("a");
			Carry(k),Carry(i);
//puts("b");
		}
	}
	for(int i=0;i<S;i++)
	{
		if(MAT[i][S]%MAT[i][i])termin("not divisable");
		MAT[i][S]/=MAT[i][i];
	}
//showMAT("bbb");
}
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	for(int i=0;i<=20;i++)
	{
		C[i][0]=C[i][i]=1LL;
		for(int j=1;j<i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	while(scanf("%d%d%d%d",&A,&M,&B,&N)==4&&(A||M||B||N))
	{
		S=M*N;
		initMAT();
//		showMAT("0");
		solve();
		printf("1");
		for(int i=S-1;i>=0;i--)printf(" %lld",MAT[i][S]);
		puts("");
	}
	return 0;
}
