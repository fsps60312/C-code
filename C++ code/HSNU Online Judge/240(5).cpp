#include<cstdio>
#include<set>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
#include<cassert>
using namespace std;
const char emptychar=' ';
struct State
{
	char *up;
	vector<char>down;
	int n;
	vector<int>remain;
	State(){}
	State(const int len):n(len),up(new char[len]){for(int i=0;i<n;i++)up[i]=emptychar;}
	bool operator<(const State &s)const
	{
		for(int i=0;i<n;i++)if(up[i]!=s.up[i])return up[i]<s.up[i];
		return down<s.down;
	}
};
map<State,bool>DP;
vector<string>STR;
bool Win(const State &state)
{
	goto codelinetostart;
	returntrue:;return DP[state]=true;
	returnfalse:;return DP[state]=false;
	codelinetostart:;
	const auto it=DP.find(state);
	if(it!=DP.end())
	{
		assert(state.remain==it->first.remain);
		return it->second;
	}
	assert(!state.remain.empty());
	const int n=state.n;
	if(state.down.size()>n)goto returntrue;
	State nxt[26][8];
	bool valid[26][8],charuse[26];
	int up_cnt=0;
	for(int i=0;i<26;i++)charuse[i]=false;
	for(int i=0;i<n;i++)if(state.up[i]!=emptychar)charuse[state.up[i]-'A']=true,up_cnt++;
	if(up_cnt==n)goto returnfalse;
	for(int i=0;i<state.down.size();i++)charuse[state.down[i]-'A']=true;
	for(int c=0;c<26;c++)for(int i=0;i<=n;i++)
	{
		if(charuse[c])valid[c][i]=false;
		else if(i==n)valid[c][i]=true;
		else if(state.up[i]==emptychar)valid[c][i]=true;
		else valid[c][i]=false;
	}
	for(int c=0;c<26;c++)for(int i=0;i<=n;i++)if(valid[c][i])
	{
		State &s=nxt[c][i]=State(n);
		for(int j=0;j<n;j++)s.up[j]=state.up[j];
		s.down=state.down;
		if(i<n)assert(s.up[i]==emptychar),s.up[i]='A'+c;
		else s.down.push_back('A'+c),sort(s.down.begin(),s.down.end());
	}
	for(const auto idx:state.remain)
	{
		const string &str=STR[idx];
		static bool vis[26];
		for(int i=0;i<26;i++)vis[i]=false;
		assert(str.size()==n);
		for(int i=0;i<n;i++)
		{
			if(valid[str[i]-'A'][i])nxt[str[i]-'A'][i].remain.push_back(idx);
			vis[str[i]-'A']=true;
			assert(!charuse[str[i]-'A']);
		}
		for(int i=0;i<26;i++)if(!vis[i]&&valid[i][n])nxt[i][n].remain.push_back(idx);
	}
	for(int c=0;c<26;c++)if(!charuse[c])
	{
		bool result=false;
		int cnt=0;
		for(int i=0;i<=n;i++)if(valid[c][i])
		{
			cnt++;
			if(!nxt[c][i].remain.empty()&&Win(nxt[c][i])){result=true;break;}
		}
		assert(cnt);
		if(!result)goto returnfalse;
	}
	goto returntrue;
}
int T,N;
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		STR.clear();
		State s[8];
		for(int i=1;i<=7;i++)s[i]=State(i);
		for(int i=0;i<N;i++)
		{
			static char tmp[8];
			scanf("%s",tmp);
			STR.push_back(tmp);
			s[STR[i].size()].remain.push_back(i);
		}
		bool ans=false;
		for(int i=1;i<=7;i++){DP.clear();if(!s[i].remain.empty()&&Win(s[i])){ans=true;break;}}
		puts(ans?"Yes":"No");
	}
	return 0;
}
