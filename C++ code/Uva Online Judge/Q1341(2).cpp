#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
const int INF=2147483647;
int N;
int AllSame(const int digit)
{
	assert(digit>=1&&digit<=9);
	static int vis[65536];
	for(int i=0;i<N;i++)vis[i]=false;
	for(int u=digit%N,len=1;!vis[u];u=(u*10+digit)%N,len++)
	{
		vis[u]=true;
		if(u==0)return len;
	}
	return INF;
}
struct State
{
	vector<int>n;
	int a,b,mod;
	State(){}
	State(const int _a,const int _b,const vector<int>&_n,const int _add):a(_a),b(_b)
	{
		n.clear();
		mod=0;
		for(int i=0;i<_n.size();i++)n.push_back(_n[i]),mod=(mod*10+n[i])%N;
		n.push_back(_add),mod=(mod*10+_add)%N;
		assert(n[0]!=0);
	}
	bool operator<(const State &s)const
	{
		if(n.size()!=s.n.size())return n.size()>s.n.size();
		for(int i=0;i<n.size();i++)if(n[i]!=s.n[i])return n[i]>s.n[i];
		return false;
	}
};
bool VIS[10][10][65536];
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		int dans=-1,len=INF;
		for(int d=1;d<=9;d++)
		{
			int tl=AllSame(d);
			if(tl<len)len=tl,dans=d;
		}
		if(dans!=-1)
		{
			for(int i=0;i<len;i++)putchar('0'+dans);
			puts("");
		}
		else
		{
			priority_queue<State>pq;
			for(char i=0;i<=9;i++)
			{
				for(char j=i+1;j<=9;j++)
				{
					for(int k=0;k<N;k++)VIS[i][j][k]=false;
					const static vector<int>tmp;
					if(i!=0)pq.push(State(i,j,tmp,i));
					pq.push(State(i,j,tmp,j));
				}
			}
			bool found=false;
			while(!pq.empty())
			{
				const State s=pq.top();pq.pop();
				if(VIS[s.a][s.b][s.mod])continue;
				if(s.mod==0)
				{
					for(int i=0;i<s.n.size();i++)putchar('0'+s.n[i]);puts("");
					found=true;
					break;
				}
				VIS[s.a][s.b][s.mod]=true;
				pq.push(State(s.a,s.b,s.n,s.a));
				pq.push(State(s.a,s.b,s.n,s.b));
			}
			assert(found);
		}
	}
	return 0;
}
