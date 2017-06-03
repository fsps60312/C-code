#include<cstdio>
#include<cstdlib>
char S[1000001];
int fail[1000001],n;
bool period[1000001];
void getfail()
{
	fail[0]=fail[1]=0;
	for(int i=1;i<n;i++)
	{
		int j=fail[i];
		while(j&&S[j]!=S[i])j=fail[j];
		fail[i+1]=S[i]==S[j]?j+1:0;
	}
}
int main()
{
	int kase=1;
	while(scanf("%d",&n)==1&&n)
	{
		scanf("%s",S);
		getfail();
		//for(int i=0;i<=n;i++)printf(" %d",fail[i]);printf("\n");
		printf("Test case #%d\n",kase++);
		for(int i=2;i<=n;i++)
		{
			int j=i-fail[i];
			if(i%j==0&&i/j>=2)
			{
				printf("%d %d\n",i,i/j);
			}
		}
		printf("\n");
	}
	return 0;
}
