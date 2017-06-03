#include<cstdio>
int Abs(const int a){return a>=0?a:-a;}
int N,M;
char A[25],B[25];
int Solve()
{
	int a=0,b=0;
	for(int i=0;i<N;i++)a+=(A[i]=='o'),b+=(B[i]=='o');
	if(a!=b)return -1;
	int ans=0;
	for(int i=0,j=-1;i<N;i++)if(A[i]=='o')
	{
		while(B[++j]!='o');
		ans+=Abs(i-j);
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	scanf("%s",A);
	while(M--)scanf("%s",B),printf("%d\n",Solve());
	return 0;
}
