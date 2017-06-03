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
	vector<map<char,char> >TRANS;
	vector<set<char> >USED;
	void clear(){LINE.clear();TRANS.clear(),USED.clear();}
	void push(const string &s){LINE.push_back(s),TRANS.push_back(map<char,char>()),USED.push_back(set<char>());}
	bool Valid(const string &source,const string &target,map<char,char>&trans,set<char>&used)
	{
		assert(source.size()==target.size());
		for(int i=0;i<(int)source.size();i++)
		{
			const char a=source[i],b=target[i];
			const auto it=trans.find(a);
			if(it==trans.end())
			{
				if(used.find(b)!=used.end())return false;
				used.insert(b);
				trans[a]=b;
			}
			else if((it->second)!=b)return false;
		}
		return true;
	}
	bool Dfs(const int dep)
	{
		if(dep==(int)LINE.size())return true;
		const string &line=LINE[dep];
		const map<char,char>&backup=(dep?TRANS[dep-1]:map<char,char>());
		const set<char>&preused=(dep?USED[dep-1]:set<char>());
		for(const string &word:DICT[line.size()])if(Valid(line,word,TRANS[dep]=backup,USED[dep]=preused)&&Dfs(dep+1))return true;
		return false;
	}
	bool Solve(map<char,char>&ans)
	{
		sort(LINE.begin(),LINE.end(),CmpWordLength);
		if(LINE.empty())return true;
		if(!Dfs(0))return false;
		ans=TRANS[(int)LINE.size()-1];
		return true;
	}
}SOLVER;
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
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
		int n=-1;
		while(tmp[++n])
		{
			if(tmp[n]=='\n'){tmp[n]='\0';break;}
			else assert(IsLower(tmp[n])||tmp[n]==' ');
		}
		vector<string>ans;
		for(int i=0;i<n;i++)if(IsLower(tmp[i]))
		{
			string s="";
			while(IsLower(tmp[i]))s.push_back(tmp[i++]);
			ans.push_back(s);
			SOLVER.push(s);
		}
		map<char,char>result;
		if(SOLVER.Solve(result))
		{
			bool printed=false;
			for(const auto &s:ans)
			{
				if(printed)putchar(' ');
				else printed=true;
				string check="";
				for(const char c:s)
				{
					const auto it=result.find(c);
					assert(it!=result.end());
					putchar(it->second);
					check.push_back(it->second);
				}
				assert(DICT[check.size()].find(check)!=DICT[check.size()].end());
			}
			puts("");
		}
		else
		{
			bool printed=false;
			for(const auto &s:ans)
			{
				if(printed)putchar(' ');
				else printed=true;
				for(int i=0;i<(int)s.size();i++)putchar('*');
			}
			puts("");
		}
	}
	return 0;
}
