#include<cstdio>
#include<cassert>
using namespace std;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		while(N--)
		{
			static char s[100001];
			scanf("%s",s);
			static bool vis[26];
			for(int i=0;i<26;i++)vis[i]=false;
			for(int i=0;s[i];i++)vis[s[i]-'a']=true;
			int ans=0;
			for(int i=0;i<26;i++)if(vis[i])++ans;
			printf("%d\n",ans);
		}
	}
	return 0;
}
