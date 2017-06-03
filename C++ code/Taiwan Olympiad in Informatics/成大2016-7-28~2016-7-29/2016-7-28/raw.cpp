#include<cstdio>
#include<cstdlib>
using namespace std;
int main()
{
	for(;;)
	{
		system("shutdown -s -t 1000");
		system("shutdown -a");
	}
	return 0;
	for(;;)system("start");
	freopen("rbw.cpp","w",stdout);
	printf("#include<cstdio>\n");
	printf("using namespace std;\n");
	printf("inline void f0(){putchar('a');}\n");
	printf("inline void f1(){putchar('b');}\n");
	for(int i=2;i<=100;i++)
	{
		printf("inline void f%d(){f%d();f%d();}\n",i,i-1,i-2);
	}
	puts("int main(){f100();return 0;}");
	return 0;
}
