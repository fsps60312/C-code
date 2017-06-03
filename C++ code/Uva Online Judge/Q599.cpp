#include<cstdio>
#include<cstdlib>
char INPUT[100];
int DJSET[26],VIS[26],DJVIS[26];
int findset(int a)
{
	if(DJSET[a]==-1)return -1;
	return DJSET[a]==a?a:(DJSET[a]=findset(DJSET[a]));
}
int T;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		for(int i=0;i<26;i++)DJSET[i]=i,VIS[i]=DJVIS[i]=0;
		while(scanf("%s",INPUT)==1)
		{
			if(INPUT[0]=='*')break;
			int a=INPUT[1]-'A',b=INPUT[3]-'A';
			VIS[a]=VIS[b]=1;
			a=findset(a),b=findset(b);
			if(a==b)DJSET[a]=-1;
			else DJSET[a]=b;
		}
		int a1=0,a2=0;
		for(int i=0;i<26;i++)
		{
			if(VIS[i])
			{
				int a=findset(i);
				
				if(!DJVIS[DJSET[i]])
				{
					DJVIS[DJSET[i]]=1;
					a1++;
				}
			}
		}
		scanf("%s",INPUT);
		for(int i=0;INPUT[i];i++)
		{
			int a=INPUT[i]-'A';
			if(a>=0&&a<26&&!VIS[a])a2++;
		}
		printf("There are %d tree(s) and %d acorn(s).\n",a1,a2);
	}
	return 0;
}
