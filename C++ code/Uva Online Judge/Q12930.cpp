#include<cstdio>
char A[201],B[201];
int solve()
{
	int a=0,b=0;
	while(A[a]!='.')a++;
	while(B[b]!='.')b++;
	if(a!=b)return a<b?-1:1;
	for(int i=0;i<a;i++)if(A[i]!=B[i])return A[i]<B[i]?-1:1;
	for(int i=a+1;A[i]||B[i];i++)
	{
		if(!A[i])A[i]='0',A[i+1]=0;
		if(!B[i])B[i]='0',B[i+1]=0;
		if(A[i]!=B[i])return A[i]<B[i]?-1:1;
	}
	return 0;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s%s",A,B)==2)
	{
		int ans=solve();
		static int kase=1;
		printf("Case %d: ",kase++);
		if(ans==1)puts("Bigger");
		else if(ans==-1)puts("Smaller");
		else puts("Same");
	}
	return 0;
}
