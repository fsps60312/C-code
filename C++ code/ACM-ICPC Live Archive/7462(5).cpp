#include<cstdio>
const int INF=2147483647;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
char S[10000000];
int main()
{
	assert(fgets(S,INF,stdin));
	int testcount;
	assert(sscanf(S,"%d",&testcount)==1);
	return 0;
}
