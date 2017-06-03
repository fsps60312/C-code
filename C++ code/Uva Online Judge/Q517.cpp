#include<cstdio>
int N,T;
char S[4][17],C[8][4];
void Transform(char* &a,char* &b,const int &r)
{
	for(int i=0;i<N;i++)
	{
		if(a[i]==C[r][0]&&a[(i+2)%N]==C[r][1]&&a[(i+3)%N]==C[r][2])b[(i+2)%N]=C[r][3];
		else b[(i+2)%N]=a[(i+2)%N];
	}
	char *c=a;a=b,b=c;
}
void Solve()
{
	char *a=S[0],*b=S[1];
	for(int i1=0,i2=0;;)
	{
		
	}
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		scanf("%s",S[0]);
		for(int i=0;i<N;i++)S[2][i]=S[0][i];
		for(int i=0;i<8;i++)for(int j=0;j<4;j++)
		{
			char &c=C[i][j];
			do{scanf("%c",&c);}while(c!='a'&&c!='b');
		}
		scanf("%d",&T);
		char *ans=Solve();
		printf("%c",ans[0]);
		for(int i=1;i<N;i++)printf(" %c",ans[i]);
		puts("");
	}
	return 0;
}
