#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
int R,C;
char GRID[20][10];
bool GetBit(const int s,const int i){return (s&(1<<i))>0;}
void SetBit(int &s,const int i,const bool value)
{
	if(value)s|=1<<i;
	else s&=~(1<<i);
}
struct State
{
	int data[10],river;
	void Replace(const int sou,const int tar){for(int i=0;i<=C;i++)if(data[i]==sou)data[i]=tar;}
	void ReIndex()
	{
//		printf("before:"),Print();
		map<int,int>idx;
		for(int i=0,cnt=0;i<=C;i++)if(data[i]>=0&&idx.find(data[i])==idx.end())idx[data[i]]=cnt++;
		for(int i=0;i<=C;i++)if(data[i]>=0)data[i]=idx[data[i]];
//		printf("after :"),Print();
	}
	bool TryYes(State &t,const int col,const int up,const int right,const int down,const int left)const
	{
		if(col==0)assert(data[C]==-2&&!GetBit(river,C));
		if((col==0&&left)||(col+1==C&&right))return false;
		if((left!=(data[C]!=-2))||(up!=(data[col]!=-2)))return false;
		if(GetBit(river,C)&&(GetBit(river,col-1)==GetBit(river,col)))return false;
		if((!up&&GetBit(river,col))||(!left&&(col?GetBit(river,col-1):false)))return false;
		int type=-3;
		t=(*this);
		if(up&&left)
		{
			const int a=data[col],b=data[C];
			assert(a!=-2&&b!=-2);
			if(a==b)return false;
			t.Replace(max(a,b),type=min(a,b));
		}
		else if(up&&!left)assert((type=data[col])!=-2);
		else if(!up&&left)assert((type=data[C])!=-2);
		else assert(!up&&!left),type=100;
//		printf("type=%d\n",type);
		assert(type!=-3);
		t.data[col]=(down?type:-2);
		t.data[C]=(right?type:-2);
		SetBit(t.river,C,col+1==C?false:GetBit(river,col));
		SetBit(t.river,col,true);
		t.ReIndex();
		return true;
	}
	bool TryNo(State &t,const int col)const
	{
		if(col==0)assert(data[C]==-2&&!GetBit(river,C));
		if(data[col]!=-2||data[C]!=-2)return false;
		if(col&&!GetBit(river,C)&&GetBit(river,col-1)&&GetBit(river,col))return false;
		t=(*this);
		SetBit(t.river,C,col+1==C?false:GetBit(river,col));
		SetBit(t.river,col,false);
		return true;
	}
	bool operator<(const State &s)const{for(int i=0;i<=C;i++)if(data[i]!=s.data[i])return data[i]<s.data[i];return river<s.river;}
	void Print()const
	{
		printf("(right=%d)",data[C]);
		for(int i=0;i<=C;i++)putchar(river&(1<<i)?'1':'0');
		putchar(':');
		for(int i=0;i<C;i++)printf(" %d",data[i]);puts("");
	}
}POOL[1000000];
int POOL_COUNTER;
struct CmpStatePointer{bool operator()(const State *a,const State *b)const{return (*a)<(*b);}};
State *New(const State &s){assert(POOL_COUNTER<1000000);return &(POOL[POOL_COUNTER++]=s);}
struct Info
{
	const State *pre;
	int cow;
	Info(){}
	Info(const State *_p,const int _c):pre(_p),cow(_c){}
};
map<State*,Info,CmpStatePointer>DP[181];
void Update(const int dep,State *s,const Info &info)
{
	auto it=DP[dep].find(s);
	if(it==DP[dep].end())DP[dep][s]=info;
	else if(info.cow>(it->second).cow)it->second=info;
}
void Track(const map<State*,Info,CmpStatePointer>::iterator &it,const int dep,vector<bool>&ans)
{
	assert(it->first);
	if(!dep)return;
	ans.push_back(GetBit(it->first->river,(dep-1)%C));
	Track(DP[dep-1].find((State*)(it->second).pre),dep-1,ans);
}
bool IsAns(const State &s)
{
	for(int i=0;i+1<C;i++)if(s.data[i]!=-2)return false;
	if(s.data[C-1]!=-1)return false;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		assert(scanf("%d%d",&R,&C)==2);
		if(R==0&&C==0)break;
		for(int i=0;i<R;i++)assert(scanf("%s",GRID[i])==1);
		for(int i=0;i<=R*C;i++)DP[i].clear();
		State state0=State();
		for(int i=0;i<=C;i++)state0.data[i]=-2;
		state0.data[0]=-1,state0.river=1;
		POOL_COUNTER=0;
		Update(0,New(state0),Info(NULL,0));
		for(int row=0,col=0,dep=0;row<R;dep++)
		{
			const bool placable=(GRID[row][col]=='.');
			if(!placable)assert(GRID[row][col]=='#');
			for(const auto &it:DP[dep])
			{
				const State &s=*(it.first);
//				printf("(%d,%d):",row,col),s.Print();
				static State t;
				if(s.TryNo(t,col))Update(dep+1,New(t),Info(it.first,it.second.cow));
				if(placable)
				{
					if(s.TryYes(t,col,true,false,true,false))Update(dep+1,New(t),Info(it.first,it.second.cow+1));
					if(s.TryYes(t,col,false,true,false,true))Update(dep+1,New(t),Info(it.first,it.second.cow+1));
					if(s.TryYes(t,col,true,true,false,false))Update(dep+1,New(t),Info(it.first,it.second.cow+1));
					if(s.TryYes(t,col,false,true,true,false))Update(dep+1,New(t),Info(it.first,it.second.cow+1));
					if(s.TryYes(t,col,false,false,true,true))Update(dep+1,New(t),Info(it.first,it.second.cow+1));
					if(s.TryYes(t,col,true,false,false,true))Update(dep+1,New(t),Info(it.first,it.second.cow+1));
				}
			}
			if(++col==C)col=0,row++;
		}
//		for(const auto &it:DP[R*C])(*it.first).Print();
		assert(!DP[R*C].empty());
		auto source=DP[R*C].end();
		for(auto it=DP[R*C].begin();it!=DP[R*C].end();it++)if(IsAns(*(it->first)))
		{
			if(source==DP[R*C].end()||(it->second).cow>(source->second).cow)source=it;
		}
		assert(source!=DP[R*C].end());
//		printf("len=%d\n",(source->second).cow);
		vector<bool>ans;
		Track(source,R*C,ans);
		assert((int)ans.size()==R*C);
		static int kase=1;printf("Case %d:\n",kase++);
		for(int i=R*C-1,col=0,row=0;i>=0;i--,col++)
		{
			if(col==C)col=0,row++,puts("");
			putchar(ans[i]?'C':GRID[row][col]);
		}
		puts(""),puts("");
	}
	return 0;
}
