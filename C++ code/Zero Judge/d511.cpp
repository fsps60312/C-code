#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	int s[3],ans=0;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<3;j++)scanf("%d",&s[j]);
		sort(s,s+3);
		if(s[0]+s[1]>s[2])ans++;
	}
	printf("%d\n",ans);
	return 0;
}
