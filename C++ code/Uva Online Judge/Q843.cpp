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
	void clear(){LINE.clear();TRANS.clear();}
	void push(const string &s){LINE.push_back(s),TRANS.push_back(map<char,char>());}
	bool Valid(const string &source,const string &target,map<char,char>&trans)
	{
		for(int i=0;i<(int)source.size();i++)
		{
			const char a=source[i],b=target[i];
			const auto it=trans.find(a);
			if(it==trans.end())trans[a]=b;
			else if((it->second)!=b)return false;
		}
		return true;
	}
	bool Dfs(const int dep)
	{
		if(dep==(int)LINE.size())return true;
		const string &line=LINE[dep];
		const map<char,char>&backup=(dep?TRANS[dep-1]:map<char,char>());
		for(const string &word:DICT[line.size()])
		{
			TRANS[dep]=backup;
			if(Valid(line,word,TRANS[dep])&&Dfs(dep+1))return true;
		}
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
