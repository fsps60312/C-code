#include<cstdio>
#include<cstdlib>
long long T,A,B,C,R,ans;
long long dfs(long long a,long long b)
{
	if(b==0) return a;
	return dfs(b,a%b);
}
long long gcd(long long a,long long b)
{
	return a>b?dfs(a,b):dfs(b,a);
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%lld",&T);
	while(T--)
	{
		//LCM(A, B) = C
		//a*b==gcd(a,b)*c
		scanf("%lld%lld",&A,&C);
		if(C%A!=0) printf("NO SOLUTION\n");
		else
		{
			while(gcd(A,C/A)>1) A/=gcd(A,C/A);
			printf("%lld\n",C/A);
		}
	}
}
