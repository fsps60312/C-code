#include<cstdio>
int main()
{
	char c=getchar();
	int ans=0;
	while(c>='0'&&c<='9')ans=(ans*10+(c-'0'))%8,c=getchar();
	printf("%d\n",ans);
	return 0;
}
