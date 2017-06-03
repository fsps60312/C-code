#include<cstdio>
#include<cstdlib>
#include<string>
#include<set>
#include<vector>
using namespace std;
char INPUT1[50],INPUT2[250];
bool islower(char &a){return a>='a'&&a<='z';}
int FREE[26],IN[26],OUT[26],USED[26];
vector<int> LINK[26];
set<string> TANS;
char TSTR[21];
void merge(const char *s1,const char *s2,int i1,int i2)
{
	if(!s1[i1]&&!s2[i2])
	{
		TSTR[i1+i2]=0;
		TANS.insert(TSTR);
		return;
	}
	if(s1[i1])
	{
		TSTR[i1+i2]=s1[i1];
		merge(s1,s2,i1+1,i2);
	}
	if(s2[i2])
	{
		TSTR[i1+i2]=s2[i2];
		merge(s1,s2,i1,i2+1);
	}
}
set<string> merge(set<string> a,set<string> b)
{
	TANS.clear();
	for(set<string>::iterator it1=a.begin();it1!=a.end();it1++)
	{
		for(set<string>::iterator it2=b.begin();it2!=b.end();it2++)
		{
			merge((*it1).c_str(),(*it2).c_str(),0,0);
		}
	}
	return TANS;
}
set<string> dfs(int u)
{
	set<string> ans;
	if(!OUT[u])
	{
		char tans[2]={'a'+u,0};
		ans.insert(tans);
		return ans;
	}
	set<string> tans=dfs(LINK[u][0]);
	for(int i=1;i<LINK[u].size();i++)
		tans=merge(tans,dfs(LINK[u][i]));
	for(set<string>::iterator it=tans.begin();it!=tans.end();it++)
	{
		ans.insert(((char)('a'+u))+(*it));
	}
	return ans;
}
int main()
{
	while(fgets(INPUT1,50,stdin)&&fgets(INPUT2,250,stdin))
	{
		for(int i=0;i<26;i++)
		{
			FREE[i]=IN[i]=OUT[i]=USED[i]=0;
			LINK[i].clear();
		}
		for(int i=0;INPUT1[i];i++)
			if(islower(INPUT1[i]))
				FREE[INPUT1[i]-'a']=1;
		for(int i=0;INPUT2[i];i++)
		{
			if(islower(INPUT2[i]))
			{
				FREE[INPUT2[i]-'a']=0;
				int ti=i+1;
				while(!islower(INPUT2[++ti]));
				int a=INPUT2[i]-'a',b=INPUT2[ti]-'a';
				USED[a]=USED[b]=1;
				LINK[a].push_back(b);
				OUT[a]++,IN[b]++;
				i=ti+1;
			}
		}
		set<string> ans;
		for(int i=0;i<26;i++)
		{
			if(IN[i]||!USED[i])continue;
			set<string> dfset=dfs(i);
			for(set<string>::iterator it=dfset.begin();it!=dfset.end();it++)ans.insert(*it);
		}
		for(set<string>::iterator it=ans.begin();it!=ans.end();it++)
		{
			printf("%s\n",(*it).c_str());
		}
	}
	return 0;
}
