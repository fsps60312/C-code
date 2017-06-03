#include<cstdio>
#include<algorithm>
using namespace std; 
bool c1[26],c2[26];
char s1[101],s2[101];
bool isans()
{
	for(int i=0;i<26;i++)c1[i]=c2[i]=0;
	for(int i=0;s1[i];i++)c1[s1[i]-'A']++,c2[s2[i]-'A']++;
	sort(c1,c1+26);
	sort(c2,c2+26);
	for(int i=0;i<26;i++)
	{
		if(c1[i]!=c2[i])return false;
	}
	return true;
}
int main()
{
	while(scanf("%s%s",s1,s2)==2)
	{
		if(isans())printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
