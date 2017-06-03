#include<cstdio>
#include<cassert>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#define sscanf(x,...) assert(sscanf(__VA_ARGS__)==x)
#define fgets(x) fgets(x,INF,stdin)
using namespace std;
const int INF=2147483647;
bool IsLower(const char a){return a>='a'&&a<='z';}
int N;
map<int,set<string> >DICT;
bool CmpWordLength(const string &a,const string &b){return a.size()!=b.size()?a.size()>b.size():a<b;}
struct Solver
{
	vector<string>LINE;
	bool USED[26];
	char TRANS[26];
	void clear(){LINE.clear();for(int i=0;i<26;i++)USED[i]=false;}
	void push(const string &s){LINE.push_back(s);}
	bool Dfs(const int dep)
	{
		if(dep==26)return true;
		const char alpha='a'+dep;
		for(char &to=TRANS[dep]='a';to<='z';to++)if(!USED[to-'a'])
		{
			USED[to-'a']=true;
			for(const string &line:LINE)
			{
				for(int i=0;i<(int)line.size();i++)if(line[i]==alpha)
				{
					
				}
			}
			USED[to-'a']=false;
		}
		return false;
	}
	bool Solve()
	{
		sort(LINE.begin(),LINE.end(),CmpWordLength);
		if(LINE.empty())return true;
		if(!Dfs(0))return false;
		return true;
	}
}SOLVER;
int main()
{
//	freopen("in.txt","r",stdin);
	static char tmp[1000000];
	fgets(tmp),sscanf(1,tmp,"%d",&N);
	DICT.clear();
	for(int i=0;i<N;i++)
	{
		fgets(tmp);
		string word="";
		for(int j=0;IsLower(tmp[j]);word.push_back(tmp[j++]));
		assert(!word.empty());
		DICT[word.size()].insert(word);
	}
	while(fgets(tmp))
	{
		SOLVER.clear();
		static int n;
		for(n=-1;tmp[++n];)if(tmp[n]=='\n'){tmp[n]='\0';break;}
		for(int i=0;i<n;i++)if(IsLower(tmp[i]))
		{
			string s="";
			while(IsLower(tmp[i]))s.push_back(tmp[i++]);
			SOLVER.push(s);
		}
		map<char,char>result;
		if(SOLVER.Solve(result))
		{
			for(int i=0;i<n;i++)if(IsLower(tmp[i]))
			{
				const auto it=result.find(tmp[i]);
				assert(it!=result.end());
				tmp[i]=(it->second);
			}
		}
		else for(int i=0;i<n;i++)if(IsLower(tmp[i]))tmp[i]='*';
		puts(tmp);
	}
	return 0;
}
