#include<cstdio>
#include<set>
#include<vector>
#include<cassert>
using namespace std;
struct State
{
	vector<bool>now;
	int cnt;
	void clear(const int n){now.resize(n);for(int i=0;i<n;i++)now[i]=false;cnt=0;}
	void Add(const int station){if(now[station])return;now[station]=true;cnt++;}
	bool operator<(const State &st)const
	{
		for(int i=0;i<(int)now.size();i++)if(now[i]!=st.now[i])return now[i];
		return false;
	}
}S[10000001];
set<State>VIS;
int TRANS[3][1000];
int N;
bool Win(const int dep)
{
//	if(dep==1000)return true;
	const auto it=VIS.find(S[dep]);
	if(it!=VIS.end())return false;
	VIS.insert(S[dep]);
//	printf("dep=%d,cnt=%d\n",dep,S[dep].cnt);
	if(S[dep].cnt==1)return true;
	for(int i=0;i<3;i++)
	{
		bool win=true;
		State t;t.clear(N);
		for(int k=0;k<N;k++)if(S[dep].now[k])t.Add(TRANS[i][k]);
		if(t.cnt==1)return true;
		if(t.cnt==S[dep].cnt)return false;
		for(int j=0;j<3;j++)
		{
			S[dep+1].clear(N);
			for(int k=0;k<N;k++)if(t.now[k])S[dep+1].Add(TRANS[j][k]);
			assert(S[dep+1].cnt<=S[dep].cnt);
//			if(S[dep+1].cnt==S[dep].cnt){win=false;break;}
			if(!Win(dep+1)){win=false;break;}
		}
		if(win)return true;
	}
	return false;
}
int main()
{
//	freopen("A.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		VIS.clear();
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<N;j++)scanf("%d",&TRANS[i][j]),TRANS[i][j]--,assert(TRANS[i][j]>=0&&TRANS[i][j]<N);
		}
		S[0].now.resize(N);
		for(int i=0;i<N;i++)S[0].now[i]=true;
		S[0].cnt=N;
		puts(Win(0)?"Yes":"No");
	}
}
