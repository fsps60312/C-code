#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
int R,C;
double GRID[6][5],ANS[6][5];
struct State
{
	int data[5];//-2: stone, -1: path from source
	bool operator<(const State &s)const{for(int i=0;i<C;i++)if(data[i]!=s.data[i])return data[i]<s.data[i];return false;}
	void Replace(const int sou,const int tar){for(int i=0;i<C;i++)if(data[i]==sou)data[i]=tar;}
	void ReIndex()
	{
		map<int,int>idx;
		int cnt=0;
		for(int i=0;i<C;i++)if(data[i]>=0&&idx.find(data[i])==idx.end())idx[data[i]]=cnt++;
		for(int i=0;i<C;i++)if(data[i]>=0)data[i]=idx[data[i]];
	}
	bool TryMove(State &target,const int col,const bool stone)const
	{
		if(stone)
		{
			if(data[col]==-1)
			{
				bool found=false;
				for(int i=0;i<C;i++)if(i!=col&&data[i]==-1){found=true;break;}
				if(!found)return false;
			}
			target=(*this);
			target.data[col]=-2;
			target.ReIndex();
			return true;
		}
		else if(col==0)
		{
			target=(*this);
			if(target.data[col]==-2)target.data[col]=100,target.ReIndex();
			return true;
		}
		else
		{
			const int c1=data[col-1],c2=data[col];
			target=(*this);
			if(c1==-1&&c2==-1)return true;
			else if(c1==-2&&c2==-2)target.data[col]=100;
			else if(c1>=0&&c2>=0)target.Replace(c2,c1);
			else if((c1==-1&&c2==-2)||(c2==-1&&c1==-2))target.data[col]=-1;
			else if((c1==-1&&c2>=0)||(c2==-1&&c1>=0))target.Replace(max(c1,c2),-1);
			else assert((c1==-2&&c2>=0)||(c2==-2&&c1>=0)),target.data[col]=max(c1,c2);
			target.ReIndex();
			return true;
		}
	}
	void Print()const{for(int i=0;i<C;i++)printf(" %d",data[i]);}
};
struct Info
{
	double protion,success;
	Info(){}
	Info(const double _pr):protion(_pr),success(0.0){}
};
map<State,Info>DP[31];
void Add(const int dep,const State &s,const double value)
{
	auto it=DP[dep].find(s);
	if(it==DP[dep].end())DP[dep][s]=Info(value);
	else (it->second).protion+=value;
}
void Dfs(const int row,const int col,const int dep)
{
	if(row==R)
	{
		for(auto &it:DP[dep])
		{
			const State &s=it.first;
			if(s.data[C-1]==-1)it.second.success=1.0;//,printf("%.4f: ",it.second.protion),s.Print(),puts("");
			else it.second.success=0.0;
		}
		return;
	}
	const double &grid=GRID[row][col];
	for(const auto &it:DP[dep])
	{
		const State &s=it.first;
		static State t;
		if(grid>0.0&&s.TryMove(t,col,true))Add(dep+1,t,it.second.protion*grid);
		if(grid<1.0&&s.TryMove(t,col,false))Add(dep+1,t,it.second.protion*(1.0-grid));
	}
	int nxtr=row,nxtc=col+1;
	if(nxtc==C)nxtc=0,nxtr++;
	Dfs(nxtr,nxtc,dep+1);
	ANS[row][col]=0.0;
	double sum=0.0;
	for(auto &elem:DP[dep])
	{
		const State &s=elem.first;
		double &sus=elem.second.success;
		static State t;
		if(grid>0.0&&s.TryMove(t,col,true))
		{
			const auto it=DP[dep+1].find(t);
			assert(it!=DP[dep+1].end());
			const double &ta=grid*(it->second).success;
			sus+=ta;
			ANS[row][col]+=elem.second.protion*ta;
			sum+=elem.second.protion*ta;
		}
		if(grid<1.0&&s.TryMove(t,col,false))
		{
			const auto it=DP[dep+1].find(t);
			assert(it!=DP[dep+1].end());
			const double &ta=(1.0-grid)*(it->second).success;
			sus+=ta;
			sum+=elem.second.protion*ta;
		}
	}
	ANS[row][col]/=sum;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d",&C,&R)==2);
		for(int i=0;i<C;i++)for(int j=0;j<R;j++)assert(scanf("%lf",&GRID[j][i])==1);
		for(int i=0;i<=R*C;i++)DP[i].clear();
		State source;
		for(int i=0;i<C;i++)source.data[i]=-2;
		source.data[0]=-1;
		Add(0,source,1.0);
		Dfs(0,0,0);
		static int kase=0;
		if(kase++)puts("");
		for(int i=0;i<C;i++)
		{
			for(int j=0;j<R;j++)
			{
				if(j)putchar(' ');
				printf("%.6f",ANS[j][i]);
			}
			puts("");
		}
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
