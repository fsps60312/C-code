#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
using namespace std;
vector<int> TO[26];
int TIME[26],USED[26],IN[26],VIS[26];
bool isletter(char a){return a>='A'&&a<='Z';}
bool isempty(char *a)
{
	for(int i=0;a[i];i++)
	{
		if(a[i]>='0'&&a[i]<='9')return false;
		if(a[i]>='A'&&a[i]<='Z')return false;
	}
	return true;
}
char firstletter(char *a)
{
	for(int i=0;;i++)
	{
		if(a[i]>='A'&&a[i]<='Z')return a[i];
	}
}
void init()
{
	char tstr[100],str1[2],str2[27];
	for(int i=0;i<26;i++)
	{
		TO[i].clear();
		VIS[i]=USED[i]=IN[i]=0;
	}
	while(fgets(tstr,100,stdin))
	{
		if(isempty(tstr))break;
		sscanf(tstr,"%s",str1);
		int a=firstletter(str1)-'A';
		int innum=sscanf(tstr,"%s%d%s",str1,&TIME[a],str2);
		//printf("%d\tTIME[%c]=%d\n",innum,firstletter(str1),TIME[a]);
		USED[a]=1;
		if(innum==3)
		{
			for(int i=0;str2[i];i++)
			{
				if(!isletter(str2[i]))continue;
				int b=str2[i]-'A';
				TO[b].push_back(a);
				IN[a]++;
			}
		}
	}
}
#define min(x,y) (x)<(y)?(x):(y)
#define max(x,y) (x)>(y)?(x):(y)
int DP[26];
int dfs(int u)
{
	if(VIS[u])return DP[u];
	int &ans=DP[u];
	ans=0;
	for(int i=0;i<TO[u].size();i++)
	{
		ans=max(ans,dfs(TO[u][i]));
	}
	ans+=TIME[u];
	VIS[u]=1;
	return ans;
}
int T;
int main()
{
	//freopen("in.txt","r",stdin);
	char tstr[100];
	fgets(tstr,100,stdin);
	sscanf(tstr,"%d",&T);
	fgets(tstr,100,stdin);
	int kase=0;
	while(T--)
	{
		if(kase++)printf("\n");
		init();
		int ans=0;
		for(int i=0;i<26;i++)
		{
			if(!USED[i]||IN[i])continue;
			ans=max(ans,dfs(i));
		}
		printf("%d\n",ans);
	}
	return 0;
}
