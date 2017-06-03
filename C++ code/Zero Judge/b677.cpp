#include<cstdio>
int N;
char S[100][101];
int main()
{
	scanf("%d",&N);
	for(int j=0;j<N;j++)
	{
		scanf("%s",&S[j]);
	}
	for(int j=N-1;j>=0;j--)
	{
		puts(S[j]);
	}
	return 0;
}
