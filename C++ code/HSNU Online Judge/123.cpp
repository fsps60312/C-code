#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
typedef long long LL;
int N;
struct State
{
	int data[8];
	void Replace(const int sou,const int tar){for(int i=0;i<=N;i++)if(data[i]==sou)data[i]=tar;}
	void ReIndex()
	{
		map<int,int>idx;
		for(int i=0,cnt=0;i<=N;i++)if(data[i]!=-1&&idx.find(data[i])==idx.end())idx[data[i]]=cnt++;
		for(int i=0;i<=N;i++)if(data[i]!=-1)data[i]=idx[data[i]];
	}
	bool TryMove(State &t,const int col,const bool up,const int right,const bool down,const bool left)const
	{
		if((col!=0&&data[N]!=-1)!=left)return false;
		if((data[col]!=-1)!=up)return false;
		if(col+1==N&&right)return false;
		int type=-3;
		t=(*this);
		if(col==0)assert(data[N]==-1),type=(data[col]==-1?100:data[col]);
		else
		{
			if(data[col]==-1&&data[N]==-1)type=100;
			else if(data[col]==-1&&data[N]!=-1)type=data[N];
			else if(data[col]!=-1&&data[N]==-1)type=data[col];
			else
			{
				if(data[col]==data[N])return false;
				t.Replace(data[col],type=data[N]);
			}
		}
		assert(type!=-3);
		t.data[col]=(down?type:-1);
		t.data[N]=(right?type:-1);
		t.ReIndex();
		return true;
	}
	bool operator<(const State &s)const{for(int i=0;i<=N;i++)if(data[i]!=s.data[i])return data[i]<s.data[i];return false;}
};
map<State,LL>DP[2];
void Update(const int d,const State &s,const LL value)
{
	auto it=DP[d].find(s);
	if(it==DP[d].end())DP[d][s]=value;
	else it->second+=value;
}
bool IsAns(const State &s)
{
	assert(s.data[N]==-1);
	for(int i=1;i<N;i++)if(s.data[i]!=-1)return false;
	return s.data[0]==0;
}
int main()
{
	assert(scanf("%d",&N)==1);
	DP[0].clear(),DP[1].clear();
	State state0;
	for(int i=0;i<=N;i++)state0.data[i]=-1;
	state0.data[0]=0;
	Update(0,state0,1LL);
	int d=0;
	for(int row=0,col=0;row<N;d^=1)
	{
		for(const auto &it:DP[d])
		{
			const State &s=it.first;
			const LL &val=it.second;
			static State t;
			if(s.TryMove(t,col,true,false,true,false))Update(d^1,t,val);
			if(s.TryMove(t,col,false,true,false,true))Update(d^1,t,val);
			if(s.TryMove(t,col,true,true,false,false))Update(d^1,t,val);
			if(s.TryMove(t,col,false,true,true,false))Update(d^1,t,val);
			if(s.TryMove(t,col,false,false,true,true))Update(d^1,t,val);
			if(s.TryMove(t,col,true,false,false,true))Update(d^1,t,val);
		}
		DP[d].clear();
		if(++col==N)col=0,row++;
	}
	LL ans=0LL;
	for(const auto &it:DP[d])if(IsAns(it.first))ans+=it.second;
	DP[d].clear();
	printf("%lld\n",ans);
	return 0;
}
