#include<cstdio>
int main()
{
	char c=getchar();
	while(c>='A'&&c<='Z')putchar(c<='M'?c+13:c-13),c=getchar();
	puts("");
	return 0;
}
