#include<cstdio>
#include<set>
#include<cassert>
#include<map>
#include<algorithm>
using namespace std;
int N;
char GRID[4][20001];
struct State
{
	int data[4],down;
	bool operator<(const State &s)const{for(int i=0;i<4;i++)if(data[i]!=s.data[i])return data[i]<s.data[i];return down<s.down;}
	void Replace(const int sou,const int tar){for(int i=0;i<4;i++)if(data[i]==sou)data[i]=tar;if(down==sou)down=tar;}
	void ReIndex()
	{
		map<int,int>idx;
		for(int i=0,cnt=0;i<4;i++){const int v=data[i];if(v>=0&&idx.find(v)==idx.end())idx[v]=cnt++;}
		for(int i=0;i<4;i++)if(data[i]>=0)data[i]=idx[data[i]];
	}
	bool TryMove(State &t,const int row,const bool up,const bool right,const bool down,const bool left)const
	{
		int type=-3;
		t=(*this);
		if(left&&up)
		{
			const int a=(row>0?down:-2),b=data[row];
			if(a==-1&&b==-1)type=-1;
			else if(a==-2&&b==-2)type=100;
			else if(a>=0&&b>=0)t.Replace(a,b),type=b;
			else if((a==-1&&b==-2)||(b==-1&&a==-2))type=-1;
			else if((a==-1&&b>=0)||(b==-1&&a>=0))t.Replace(max(a,b),-1),type=-1;
			else assert((a==-2&&b>=0)||(b==-2&&a>=0)),type=max(a,b);
		}
		else if(!left&&!up)type=100;
		else if(left&&!up)type=(data[row]==-2?100:data[row]);
		else assert(!left&&up),type=(row>0?(down==-2?100:down):100);
		assert(type!=-3);
		t.data[row]=(right?type:-2);
		t.down=(down?type:-2);
		bool found=(t.down==-1);
		for(int i=0;i<4&&!found;i++)if(t.data[i]==-1)found=true;
		if(!found)return false;
		t.ReIndex();
		return true;
	}
};
set<State>DP[2];
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d",&N)==1);
		for(int i=0;i<4;i++)assert(scanf("%s",GRID[i])==1);
		State source;
		for(int i=0;i<4;i++)source.data[i]=-1;
		source.down=0;
		assert(DP[0].empty()&&DP[1].empty());
		DP[0].insert(source);
		int d=0;
		for(int row=0,col=0;col<N;d^=1)
		{
			for(const State &s:DP[d])
			{
				static State t;
				switch(GRID[row][col])
				{
					case'X':
						if(s.TryMove(t,row,false,false,false,false))DP[d^1].insert(t);
						break;
					case'A':
						if(s.TryMove(t,row,false,true,false,true))DP[d^1].insert(t);
						if(s.TryMove(t,row,true,false,true,false))DP[d^1].insert(t);
						break;
					case'B':
						if(s.TryMove(t,row,true,false,false,true))DP[d^1].insert(t);
						if(s.TryMove(t,row,false,false,true,true))DP[d^1].insert(t);
						if(s.TryMove(t,row,false,true,true,false))DP[d^1].insert(t);
						if(s.TryMove(t,row,true,true,false,false))DP[d^1].insert(t);
						break;
					default:assert(0);break;
				}
			}
			DP[d].clear();
			if(++row==4)row=0,col++;
		}
		puts(DP[d].empty()?"Don't Try.":"Try.");
		DP[d].clear();
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
/*
4
3
BAA
AXB
BAB
AXA
3
BAA
AXB
BXB
AXA
3
BXA
AXB
BAB
AXA
3
BXA
AXB
BXB
AXA
*/
