#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
const int INF=2147483647;
//void assert(bool valid){return;if(valid)return;for(int i=0;i<100000000;i++)putchar('E');exit(0);}
int R,C,MOD;
char GRID[399][20];
struct State
{
	int data[8];
	State(){for(int i=0;i<C;i++)data[i]=i;}
	void ReIndex()
	{
		map<int,int>idx;
		int cnt=0;
		for(int i=0;i<C;i++)if(idx.find(data[i])==idx.end())idx[data[i]]=cnt++;
		for(int i=0;i<C;i++)data[i]=idx[data[i]];
	}
	void Replace(const int source,const int target){for(int i=0;i<C;i++)if(data[i]==source)data[i]=target;}
	bool TryMove(State &t,const int row,const int col,const bool stickleft,const bool stickup)const
	{
		if(row==0&&stickup)return false;
		if(col==0&&stickleft)return false;
		if(!stickleft&&col&&GRID[row*2][col*2-1]=='-')return false;
		if(!stickup&&row&&GRID[row*2-1][col*2]=='|')return false;
		if(stickleft&&stickup&&data[col-1]==data[col])return false;
		if(!stickup&&row)
		{
			bool found=false;
			for(int i=0;i<C;i++)if(i!=col&&data[i]==data[col]){found=true;break;}
			if(!found)return false;
		}
		t=(*this);
		if(!stickleft&&!stickup)t.data[col]=-1;
		else if(stickleft&&stickup)t.Replace(data[col],data[col-1]);
		else if(stickleft&&!stickup)t.data[col]=data[col-1];
		else assert(!stickleft&&stickup);
		t.ReIndex();
		return true;
	}
	void Print(){for(int i=0;i<C;i++)printf(" %d",data[i]);puts("");}
	bool operator<(const State &s)const{for(int i=0;i<C;i++)if(data[i]!=s.data[i])return data[i]<s.data[i];return false;}
};
map<State,int>DP[2];
void Add(const int d,const State &s,const int value)
{
	auto it=DP[d].find(s);
	if(it==DP[d].end())(DP[d][s]=value)%=MOD;
	else ((it->second)+=value)%=MOD;
}
int Solve()
{
	assert(DP[0].empty()&&DP[1].empty());
	Add(0,State(),1);
	int d=0;
	for(int row=0,col=0;row<R;d^=1)
	{
		assert(DP[d^1].empty());
//		printf("(%d,%d):sz=%d\n",row,col,DP[d].size());
		for(const auto &it:DP[d])
		{
			const State &s=it.first;
			for(int a=0;a<=1;a++)for(int b=0;b<=1;b++)
			{
				static State target;
				if(s.TryMove(target,row,col,(bool)a,(bool)b))Add(d^1,target,it.second);
			}
		}
		DP[d].clear();
		if(++col==C)col=0,row++;//,printf("row=%d\n",row);
	}
	int ans=-1;
	for(const auto &it:DP[d])
	{
		const State &s=it.first;
		bool all0=true;
		for(int i=0;i<C;i++)if(s.data[i]!=0){all0=false;break;}
		if(all0){ans=it.second;break;}
	}
	DP[d].clear();
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static char tmp[1000000];
	static int casecount;assert(fgets(tmp,INF,stdin)&&sscanf(tmp,"%d",&casecount)==1);
	while(casecount--)
	{
		assert(fgets(tmp,INF,stdin)&&sscanf(tmp,"%d%d%d",&R,&C,&MOD)==3);
		for(int i=0;i<R*2-1;i++)assert(fgets(GRID[i],INF,stdin));
		const int ans=Solve();
		if(ans==-1)puts("Impossible");
		else printf("%d\n",ans);
	}
	return 0;
}
