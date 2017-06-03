#include<cstdio>
#include<cassert>
using namespace std;
bool Digit(const char a){return a>='0'&&a<='9';}
bool Lower(const char a){return a>='a'&&a<='z';}
bool Upper(const char a){return a>='A'&&a<='Z';}
int G;
int main()
{
	for(;;)
	{
		assert(scanf("%d",&G)==1);
		if(G==0)break;
		static char tmp[101];
		assert(scanf("%s",tmp)==1);
		int n=-1;while(tmp[++n]);
		assert(n%G==0);
		const int gap=n/G;
		for(int i=0;i<G;i++)
		{
			for(int j=gap-1;j>=0;j--)putchar(tmp[i*gap+j]);
		}
		puts("");
	}
	return 0;
}
