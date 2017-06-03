#include<cstdio>
#include<cassert>
using namespace std;
char S[501];
bool Solve()
{
	int mx=0;
	for(int i=0;S[i];i++)
	{
		if(S[i]-'a'==mx)++mx;
		if(S[i]-'a'>mx)return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s",S)==1)
	{
		puts(Solve()?"YES":"NO");
	}
	return 0;
}
