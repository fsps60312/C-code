#include<cstdio>
#include<string>
#include<vector>
#include<set>
#include<queue>
using namespace std;
int T,N;
struct State
{
	char *up;
	int len;
	vector<int>idx,down;
	State(){}
	State(const int _l):len(_l),up(new char[_l]){}
	bool operator<(const State &s)const
	{
		for(int i=0;i<len;i++)if(up[i]!=s.up[i])return up[i]<s.up[i];
		return down<s.down;
	}
};
set<State>VIS;
vector<string>VOCA[8];
bool CanNotGuessOut(const int len)
{
	queue<State>q;
	State source=State(len);
	for(int i=0;i<len;i++)source.up[i]='\0';
	for(int i=0;i<VOCA[len].size();i++)source.idx.push_back(i);
	q.push(source),VIS.insert(0);
	while(!q.empty())
	{
		State state=q.front();q.pop();
		for(int i=0;i<state.idx.size();i++)
		{
			const string str=VOCA[len][state.idx[i]];
			for(int j=0;j<len;j++)
			{
				if(state.up[j]!='\0')continue;
				
			}
		}
	}
	return true;
}
bool Solve()
{
	for(int i=1;i<=7;i++)if(CanNotGuessOut(i))return true;
	return false;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			static char tmp[8];
			scanf("%s",tmp);
			string s=tmp;
			VOCA[s.size()].push_back(s);
		}
		puts(Solve()?"Yes":"No");
	}
	return 0;
}
