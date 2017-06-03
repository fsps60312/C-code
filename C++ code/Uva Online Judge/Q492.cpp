#include<cstdio>
#include<cstdlib>
char S;
bool isvowel(char a)
{
	switch(a)
	{
		case'a':
		case'A':
		case'e':
		case'E':
		case'i':
		case'I':
		case'o':
		case'O':
		case'u':
		case'U':
			return true;
		default:
			return false;
	}
}
bool isletter(char a)
{
	return (a>='a'&&a<='z')||(a>='A'&&a<='Z');
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%c",&S)==1)
	{
		if(!isletter(S)) printf("%c",S);
		else
		{
			if(isvowel(S))
			{
				do
				{
					printf("%c",S);
				}while(scanf("%c",&S)==1&&isletter(S));
				printf("ay%c",S);
			}
			else
			{
				char c=S;
				while(scanf("%c",&S)==1&&isletter(S))
				{
					printf("%c",S);
				}
				printf("%cay%c",c,S);
			}
		}
	}
	return 0;
}
