#include<cstdio>
#include<set>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
#include<cassert>
using namespace std;
const char emptychar=' ';
int T,N;
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
	auto it=DP.find(state);
	if(it!=DP.end())return it->second;
	const int n=state.n;
//	printf("up:");for(int i=0;i<n;i++)printf("%c",state.up[i]);puts("");
//	printf("down:");for(int i=0;i<state.down.size();i++)printf("%c",state.down[i]);puts("");
//	printf("remain:");for(int i=0;i<state.remain.size();i++)printf(" %s",STR[state.remain[i]].c_str());puts("");
//	freopen("out.txt","a",stdout);
//	if(state.remain.empty())goto returnfalse;
	assert(!state.remain.empty());
	State nxt[26][8];
	bool valid[26][8],charuse[26];
	int up_cnt;
	if(state.down.size()>n)goto returntrue;
	up_cnt=0;
	for(int i=0;i<26;i++)charuse[i]=false;
	for(int i=0;i<n;i++)if(state.up[i]!=emptychar)charuse[state.up[i]-'A']=true,up_cnt++;
	if(up_cnt==n)goto returnfalse;
	for(int i=0;i<state.down.size();i++)charuse[state.down[i]-'A']=true;
	static bool charusebackup[26];for(int i=0;i<26;i++)charusebackup[i]=charuse[i]; 
	for(int c=0;c<26;c++)for(int i=0;i<=n;i++)
	{
		if(charuse[c])valid[c][i]=false;
		else if(i==n)valid[c][i]=true;
		else if(state.up[i]==emptychar)valid[c][i]=true;
		else valid[c][i]=false;
	}
//	static bool validbackup[26][8];for(int c=0;c<26;c++)for(int i=0;i<=n;i++)validbackup[c][i]=valid[c][i];
	for(int c=0;c<26;c++)for(int i=0;i<=n;i++)if(valid[c][i])
	{
		State &s=nxt[c][i]=State(n);
		for(int j=0;j<n;j++)s.up[j]=state.up[j];
		s.down=state.down;
		if(i<n)assert(s.up[i]==emptychar),s.up[i]='A'+c;
		else s.down.push_back('A'+c),sort(s.down.begin(),s.down.end());
	}
//	puts("");
//	printf("up:");for(int i=0;i<n;i++)printf("%c",state.up[i]);puts("");
//	printf("down:");for(int i=0;i<state.down.size();i++)printf("%c",state.down[i]);puts("");
//	printf("remain:");for(int i=0;i<state.remain.size();i++)printf(" %s",STR[state.remain[i]].c_str());puts("");
	for(const auto idx:state.remain)
	{
		const string &str=STR[idx];
		bool vis[26];
		for(int i=0;i<26;i++)vis[i]=false;
		for(int i=0;i<n;i++)
		{
			if(valid[str[i]-'A'][i])nxt[str[i]-'A'][i].remain.push_back(idx);
			vis[str[i]-'A']=true;
		}
		for(int i=0;i<26;i++)if(!vis[i]&&valid[i][n])nxt[i][n].remain.push_back(idx);//,printf(" %c(%s)",'A'+i,str.c_str());puts("");
	}
	for(int c=0;c<26;c++)if(!charuse[c])
	{
		bool result=false;
		int cnt=0;
		for(int i=0;i<=n;i++)if(valid[c][i]&&!nxt[c][i].remain.empty())
		{
			if(Win(nxt[c][i])){result=true;break;}
			cnt++;
		}
//		if(cnt==0)continue;
		assert(cnt);
//		if(!result)
//		{
//			printf("lose when choose %c(%d results)\n",'A'+c,cnt);
//			for(int i=0;i<26;i++)printf("%d",charuse[i]);puts("");
//			for(int i=0;i<26;i++)
//			{
//				for(int j=0;j<=n;j++)printf("%d",valid[i][j]);puts("");
//			}
//		}
		if(!result)goto returnfalse;
	}
	goto returntrue;
	
	returntrue:;
//	printf("Win %d:\n",n);
//	printf("up:");for(int i=0;i<n;i++)printf("%c",state.up[i]);puts("");
//	printf("down:");for(int i=0;i<state.down.size();i++)printf("%c",state.down[i]);puts("");
//	printf("remain:");for(int i=0;i<state.remain.size();i++)printf(" %s",STR[state.remain[i]].c_str());puts("");
//	puts("");
	return DP[state]=true;
	
	returnfalse:;
//	printf("Lose %d:\n",n);
//	printf("up:");for(int i=0;i<n;i++)printf("%c",state.up[i]);puts("");
//	printf("down:");for(int i=0;i<state.down.size();i++)printf("%c",state.down[i]);puts("");
//	printf("remain:");for(int i=0;i<state.remain.size();i++)printf(" %s",STR[state.remain[i]].c_str());puts("");
//	puts("");
	return DP[state]=false;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
//	set<int>a,b;
//	for(int i=0;i<=1000000;i++)a.insert(i),b.insert(1000000-i);
//	printf("%d %d %d %d %d %d\n",a>b,a<b,a>=b,a<=b,a==b,a!=b);
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
