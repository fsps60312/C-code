#include<cstdio>
#include<cstdlib>
#include<string>
#include<set>
#include<vector>
using namespace std;
char INPUT1[50],INPUT2[250];
bool islower(char &a){return a>='a'&&a<='z';}
int IN[26],USED[26],VIS[26];
vector<int> LINK[26];
set<string> TANS;
vector<char*> LINE;
vector<int> IDX;
char TSTR[21];
void dfs(int u,int dep)
{
	TSTR[dep]='a'+u;
	if(!LINK[u].size())
	{
		char tmp[dep+2];
		for(int i=0;i<=dep;i++)tmp[i]=TSTR[i];
		tmp[dep+1]=0;
		LINE.push_back(tmp);
		printf("->  %s\n",LINE[0]);
		IDX.push_back(0);
	}
	for(int i=0;i<LINK[u].size();i++)dfs(LINK[u][i],dep+1);
}
int TSUM;
void enumerate(set<string> &ans)
{
	int isend=1;
	for(int i=0;i<IDX.size();i++)
	{
		if(LINE[i][IDX[i]])
		{
			TSTR[TSUM++]=LINE[i][IDX[i]];
			IDX[i]++;
			isend=0;
			enumerate(ans);
			TSUM--;
			IDX[i]--;
		}
	}
	if(isend)ans.insert(TSTR);
}
int main()
{
	while(fgets(INPUT1,50,stdin)&&fgets(INPUT2,250,stdin))
	{
		for(int i=0;i<26;i++)
		{
			USED[i]=IN[i]=USED[i]=0;
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
		LINE.clear();
		IDX.clear();
		for(int i=0;i<26;i++)
		{
			if(!USED[i]||IN[i])continue;
			dfs(i,0);
		}
		for(int i=0;i<LINE.size();i++)printf("LINE[%d]=%s\n",i,LINE[i]);
		set<string> ans;
		TSUM=0;
		enumerate(ans);
		for(set<string>::iterator it=ans.begin();it!=ans.end();it++)
		{
			printf("%s\n",(*it).c_str());
		}
	}
	return 0;
}
