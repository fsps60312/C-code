#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
using namespace std;
vector<int> TO[26],FROM[26];
int TIME[26],VIS[26],USED[26];
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
	fgets(tstr,100,stdin);
	for(int i=0;i<26;i++)
	{
		TO[i].clear();
		FROM[i].clear();
		VIS[i]=USED[i]=0;
	}
	while(fgets(tstr,100,stdin))
	{
		if(isempty(tstr))break;
		sscanf(tstr,"%s",str1);
		int innum=sscanf(tstr,"%s%d%s",str1,&TIME[firstletter(str1)-'A'],str2);
		int a=firstletter(str1)-'A';
		//printf("%d\tTIME[%c]=%d\n",innum,firstletter(str1),TIME[a]);
		USED[a]=1;
		if(innum==3)
		{
			for(int i=0;str2[i];i++)
			{
				if(!isletter(str2[i]))continue;
				int b=str2[i]-'A';
				FROM[a].push_back(b);
				TO[b].push_back(a);
			}
		}
	}
}
struct Pair{int x,y;};
#define min(x,y) (x)<(y)?(x):(y)
#define max(x,y) (x)>(y)?(x):(y)
Pair DP[26];
Pair dfs(int u,int val)
{
	if(VIS[u])return (Pair){DP[u].x+val,DP[u].y+val};
	DP[u]=(Pair){-TIME[u],0};
	int &low=DP[u].x,&up=DP[u].y;
	printf("%c:%d\n",'A'+u,val);
	VIS[u]=true;
	for(int i=0;i<TO[u].size();i++)
	{
		int j=TO[u][i];
		Pair tp=dfs(j,val+TIME[u]);
		low=min(low,tp.x-val);
		up=max(up,tp.y-val);
	}
	for(int i=0;i<FROM[u].size();i++)
	{
		int j=FROM[u][i];
		Pair tp=dfs(j,val-TIME[j]);
		low=min(low,tp.x-val);
		up=max(up,tp.y-val);
	}
	printf("DP[%d]=(%d,%d)\n",u,DP[u].x,DP[u].y);
	return (Pair){low+val,up+val};
}
int T;
int main()
{
	freopen("in.txt","r",stdin);
	char tstr[100];
	fgets(tstr,100,stdin);
	sscanf(tstr,"%d",&T);
	int kase=0;
	while(T--)
	{
		if(kase++)printf("\n");
		init();
		int ans=0;
		for(int i=0;i<26;i++)
		{
			if(!USED[i]||VIS[i])continue;
			Pair tp=dfs(i,0);
			ans=max(ans,tp.y-tp.x);
		}
		printf("%d\n",ans);
	}
	return 0;
}
