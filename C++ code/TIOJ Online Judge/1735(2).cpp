#include<cstdio>
#include<cassert>
using namespace std;
int K,N;
char S[100001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%s",&K,S)==2)
	{
		N=-1;while(S[++N]);
		int ans=0;
		for(int i=0,matched=0;i+K<N;i++)
		{
			if(S[i]==S[i+K])matched++;
			else matched=0;
			if(matched>=K)ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
