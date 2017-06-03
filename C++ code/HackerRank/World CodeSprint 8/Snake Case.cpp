#include<cstdio>
#include<cassert>
using namespace std;
int main()
{
	char s[101];
	scanf("%s",s);
	int ans=1;
	for(int i=0;s[i];i++)if(s[i]=='_')++ans;
	printf("%d\n",ans);
	return 0;
}
