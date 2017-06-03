#include<cstdio>
#include<set>
#include<cassert>
using namespace std;
int R,C;
char GRID[8][8];
struct State
{
	int data[8];
	int left;
	State *fa;
	State(const State *_fa):fa(_fa)
	{
		if(fa)
		{
			left=fa->left;
			for(int i=0;i<C;i++)data[i]=fa->data[i];
		}
	}
	bool operator<(const State &s)const{for(int i=0;i<C;i++)if(data[i]!=s.data[i])return data[i]<s.data[i];return false;}
	bool TryMove(const State &s,State &t,const int row,const int col,const int color);
	void AddColor(State &t,const int col,const int color,bool allow_disappear)const
	{
		t=State(this);
		t.left=(data[col]&1);
		if(color==(data[col]&1))
		{
			t.data[col]=data[col];
			if(col&&color==(data[col-1]&1)){assert(color!=left);if(data[col-1]!=data[col])
			{
				assert(data[col-1]+2==data[col]);
				for(int i=col;i<C;i++)if(color==(data[i]&1)&&data[i]>data[col-1])t.data[i]-=2;
			}}
		}
		else
		{
			if(color==(data[col-1]&1))t.data[col]=data[col-1];
			else
			{
				int id=0;
				for(int i=0;i<col;i++)if((data[i]&1)==color&&(data[i]>>1)==id)id++;
				t.data[col]=(id<<1)|color;
				for(int i=col+1;i<C;i++)if((data[i]&1)==color&&(data[i]>>1)>=id)data[i]+=2;
			}
			int result=-1;
			for(int i=0;i<C;i++)if(i!=col&&data[i]==data[col]){result=i;break;}
			if(result==-1)
			{
				assert(allow_disappear);
				for(int i=col+1;i<C;i++)if((data[i]&1)==(data[col]&1)&&data[i]>data[col])t.data[i]-=2;
			}
			else if(result<col)return;
			else
			{
				assert(result>col);
				assert(0&&"Not Implement");
			}
		}
	}
};
struct CmpState{bool operator()(const State *a,const State *b)const{return (*a)<(*b);};};
set<State*,CmpState>DP[65];
vectro<State>POOL;
State *New(const State &s){const int sz=POOL.size();assert(sz<10000000);POOL.push_back(s);return &POOL[sz];}
bool State::TryMove(const State &s,State &t,const int row,const int col,const int color)
{
	if(row==0)
	{
		int id=0;
		for(int i=0;i<col;i++)if((data[i]&1)==color&&(data[i]>>1)==id)id++;
		if(col&&(data[col-1]&1)==color)id--;
		t=State(this);
		t.data[col]=(id<<1)|color;
		return true;
	}
	if(col==0)
	{
		if((data[0]&1)==color){t=State(this);t->left=(data[0]&1);return true;}
		bool found=false;
		for(int i=1;i<C;i++)if(data[i]==data[0]){found=true;break;}
		if(!found)
		{
			if(row<R-1)return false;
			for(int i=1;i<C;i++)if(color==(data[i-1]&1)&&color==(data[i]&1))return false;
			assert(row==R-1);
			State *pre=this;
			for(int i=0;i<C;i++)
			{
				State *nxt=New(State(pre));
				nxt->left=(nxt->data[i]&1);
				nxt->data[i]=color;
				DP[row*C+i+1].insert(nxt);
				pre=nxt;
			}
			return false;
		}
		t=State(this);
		t.left=(data[0]&1);
		t.data[0]=color;
		for(int i=1;i<C;i++)
		{
			if((t.data[i]&1)==(data[0]&1))t.data[i]-=2;
			else t.data[i]+=2;
		}
		return true;
	}
	assert(data[col-1]!=data[col]);
	if(color==(data[col]&1))
	{
		if(color==(data[col-1]&1))
		{
			if(left==color)return false;
			else
			{
				t=State(this);
				t->left=color;
				if(data[col-1]!=data[col])
				{
					assert(data[col-1]+2==data[col]);
					for(int i=col;i<C;i++)t.data[i]-=2;
				}
				return true;
			}
		}
		else{t=State(this);t->left=color;return true;}
	}
	else
	{
		bool found=false;
		for(int i=0;i<C;i++)if(i!=col&&data[i]==data[col]){found=true;break;}
		if(!found)
	}
}
int main()
{
	POOL.reserve(10000000);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d",&R,&C)==2);
		for(int i=0;i<R;i++)for(int j=0;j<C;j++)
		{
			char &c=GRID[i][j];
			for(;;)
			{
				assert(scanf("%c",&c)==1);
				if(c=='#'||c=='o'||c=='.')break;
			}
		}
		for(int i=0;i<=R*C;i++)DP[i].clear();
		POOL.clear();
		DP[0].insert(New(State(NULL)));
		for(int row=0,col=0,i=0;DP[R*C].empty();col++,i++)
		{
			for(const auto &state:DP[i])
			{
				static State target;
				if(GRID[row][col]!='#'&&TryMove(state,target,row,col,0))DP[i+1].insert(New(target));
				if(GRID[row][col]!='o'&&TryMove(state,target,row,col,1))DP[i+1].insert(New(target));
			}
			if(col==C)col=0,row++;
			if(row==R)break;
		}
	}
	return 0;
}
