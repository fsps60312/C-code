#include<cstdio>
char S[1001];
bool Solve()
{
	int n=-1;while(S[++n]);
	for(int i=0;i<n/2;i++)if(S[i]!=S[n-1-i])return false;
	return true;
}
int main()
{
	while(gets(S))
	{
		puts(!Solve()?"no":"yes");
	}
	return 0;
}
