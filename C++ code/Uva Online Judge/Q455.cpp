#include<cstdio>
#include<cstdlib>
int T;
char S[100];
bool isans(int i)
{
	int j;
	for(j=0;S[j];j++)
	{
		if(S[j%i]!=S[j])
		{
			return false;
		}
	}
	if(j%i) return false;
	return true;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	gets(S);
	while(T--)
	{
		scanf("%s",S);
		for(int i=1;;i++)
		{
			if(isans(i))
			{
				printf("%d\n",i);
				if(T) printf("\n");
				break;
			}
		}
	}
	return 0;
}
