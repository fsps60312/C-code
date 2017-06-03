//still confussed
#include<cstdio>
int T,A,B;
bool IsPrime(const int n)
{
	for(int i=2;i*i<=n;i++)if(n%i==0)return false;
	return true;
}
bool Solve()
{
	if(A==0)return true;
	return !IsPrime(A*A+2*B*B);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&A,&B);
		puts(Solve()?"No":"Yes");
	}
	return 0;
}
