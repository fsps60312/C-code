#include<cstdio>
bool vis[101];
char s1[101],s2[101];
bool mark(char a)
{
	for(int i=0;s2[i];i++)
	{
		if(vis[i]||s2[i]!=a)continue;
		vis[i]=1;
		return true;
	}
	return false;
}
bool fitans()
{
	for(int i=0;s1[i];i++)vis[i]=0;
	for(int i=0;s1[i];i++)if(!mark(s1[i]))return false;
	return true;
}
bool isans()
{
	for(int i=0;i<26;i++)
	{
		for(int i=0;s1[i];i++)
		{
			s1[i]++;
			if(s1[i]>'Z')s1[i]-=26;
		}
		if(fitans())return true;
	}
	return false;
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
