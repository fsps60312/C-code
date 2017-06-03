#include<cstdio>
#include<cassert>
using namespace std;
int main()
{
//	freopen("in.txt","r",stdin);
	static char s[100001];
	while(scanf("%s",s)==1)
	{
		int ans=1;
		for(int i=0;s[i];i++)if('A'<=s[i]&&s[i]<='Z')++ans;
		printf("%d\n",ans);
	}
	return 0;
}
