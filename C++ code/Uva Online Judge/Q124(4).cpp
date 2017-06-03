#include<cstdio>
#include<cstdlib>
#include<string>
#include<set>
#include<vector>
using namespace std;
char INPUT1[50],INPUT2[250];
bool islower(char &a){return a>='a'&&a<='z';}
int IN[26],USED[26];
vector<int> LINK[26];
set<string> ANS;
char TSTR[21];
void dfs(int u,int dep)
{
	TSTR[dep]='a'+u;
	int prein=IN[u],isend=1;
	IN[u]=-1;
	for(int i=0;i<LINK[u].size();i++)IN[LINK[u][i]]--;
	for(int i=0;i<26;i++)
	{
		if(USED[i]&&!IN[i])
		{
			isend=0;
			dfs(i,dep+1);
		}
	}
	for(int i=0;i<LINK[u].size();i++)IN[LINK[u][i]]++;
	IN[u]=prein;
	if(isend)
	{
		TSTR[dep+1]=0;
		ANS.insert(TSTR);
	}
}
int main()
{
	int kase=0;
	while(fgets(INPUT1,50,stdin)&&fgets(INPUT2,250,stdin))
	{
		if(kase++)printf("\n");
		for(int i=0;i<26;i++)
		{
			USED[i]=IN[i]=0;
			LINK[i].clear();
		}
		for(int i=0;INPUT1[i];i++)
			if(islower(INPUT1[i]))
				USED[INPUT1[i]-'a']=1;
		for(int i=0;INPUT2[i];i++)
		{
			if(islower(INPUT2[i]))
			{
				int ti=i+1;
				while(!islower(INPUT2[++ti]));
				int a=INPUT2[i]-'a',b=INPUT2[ti]-'a';
				LINK[a].push_back(b);
				IN[b]++;
				i=ti+1;
			}
		}
		ANS.clear();
		for(int i=0;i<26;i++)
		{
			if(!USED[i]||IN[i])continue;
			dfs(i,0);
		}
		for(set<string>::iterator it=ANS.begin();it!=ANS.end();it++)
		{
			printf("%s\n",(*it).c_str());
		}
	}
	return 0;
}
