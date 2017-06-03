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
	int data[5];
	bool operator<(const State &s)const{for(int i=0;i<4;i++)if(data[i]!=s.data[i])return data[i]<s.data[i];return data[4]<s.data[4];}
	void Replace(const int sou,const int tar){for(int i=0;i<5;i++)if(data[i]==sou)data[i]=tar;}
	void ReIndex()
	{
		map<int,int>idx;
		for(int i=0,cnt=0;i<5;i++){const int v=data[i];if(v>=0&&idx.find(v)==idx.end())idx[v]=cnt++;}
		for(int i=0;i<5;i++)if(data[i]>=0)data[i]=idx[data[i]];
	}
	bool TryMove(State &t,const int row,const bool up,const bool right,const bool down,const bool left)const
	{
		if((up&&row==0)||(down&&row==3))return false;
		int type=-3;
		t=(*this);
		if(left&&up)
		{
			const int a=(row>0?data[4]:-2),b=data[row];
			if(a==-1&&b==-1)type=-1;
			else if(a==-2&&b==-2)type=100;
			else if(a>=0&&b>=0)t.Replace(a,b),type=b;
			else if((a==-1&&b==-2)||(b==-1&&a==-2))type=-1;
			else if((a==-1&&b>=0)||(b==-1&&a>=0))t.Replace(max(a,b),-1),type=-1;
			else assert((a==-2&&b>=0)||(b==-2&&a>=0)),type=max(a,b);
		}
		else if(!left&&!up)type=100;
		else if(left&&!up)type=(data[row]==-2?100:data[row]);
		else assert(!left&&up),type=(row>0?(data[4]==-2?100:data[4]):100);
		assert(type!=-3);
		t.data[row]=(right?type:-2);
		t.data[4]=(row==3?-2:(down?type:-2));
		bool found=false;
		for(int i=0;i<5&&!found;i++)if(t.data[i]==-1)found=true;
		if(!found)return false;
		t.ReIndex();
		return true;
	}
	void Print()const{for(int i=0;i<5;i++)printf(" %d",data[i]);puts("");}
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
		for(int i=0;i<5;i++)source.data[i]=-1;
		assert(DP[0].empty()&&DP[1].empty());
		DP[0].insert(source);
		int d=0;
		for(int row=0,col=0;col<N;d^=1)
		{
			for(const State &s:DP[d])
			{
//				printf("(%d,%d)",row,col),s.Print();
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
22
3
XXX
ABX
XBB
XXB
3
XXX
ABB
XBB
XXX
3
ABX
XBB
XXB
XXX
3
XXB
XBB
ABX
XXX
3
XXX
XBB
ABB
XXX
3
XXX
XXB
XBB
ABX
2
XX
XX
XX
AA
2
XX
XX
XX
AB
2
XX
XX
XX
BA
2
XX
XX
XX
BB
2
XX
XX
AA
XX
2
XX
XX
AB
XX
2
XX
XX
BA
XX
2
XX
XX
BB
XX
2
AA
XX
XX
XX
2
AB
XX
XX
XX
2
BA
XX
XX
XX
2
BB
XX
XX
XX
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
