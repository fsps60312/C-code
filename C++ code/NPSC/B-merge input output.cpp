#include<cstdio>
#include<cassert>
using namespace std;
int main()
{
	freopen("in.txt","w",stdout);
	for(int i=0;i<=99;i++)
	{
		static char filename[1000];
		sprintf(filename,"%d.in",i);
		freopen(filename,"r",stdin);
		for(char c;scanf("%c",&c)==1;)putchar(c);
	}
	for(int i=30;i<=59;i++)
	{
		static char filename[1000];
		sprintf(filename,"n-small-%d-%d.in",i/10,i%10);
		freopen(filename,"r",stdin);
		for(char c;scanf("%c",&c)==1;)putchar(c);
	}
	freopen("new.txt","w",stdout);
	for(int i=0;i<=99;i++)
	{
		static char filename[1000];
		sprintf(filename,"%d.ans",i);
		freopen(filename,"r",stdin);
		for(char c;scanf("%c",&c)==1;)putchar(c);
	}
	for(int i=30;i<=59;i++)
	{
		static char filename[1000];
		sprintf(filename,"n-small-%d-%d.ans",i/10,i%10);
		freopen(filename,"r",stdin);
		for(char c;scanf("%c",&c)==1;)putchar(c);
	}
	return 0;
}
