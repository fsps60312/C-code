#include<cstdio>
#include<cassert>
using namespace std;
char S[1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s",S)==1&&S[0]!='#')
	{
		int ans=1;
		for(int i=1,now=1;S[i];i++)
		{
			if(S[i]==S[i-1]+1)++now;
			else now=1;
			if(now>ans)ans=now;
		}
		printf("%d\n",ans);
	}
	return 0;
}
