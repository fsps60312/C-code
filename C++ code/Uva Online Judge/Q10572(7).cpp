#include<cstdio>
#include<set>
#include<cassert>
#include<map>
#include<vector> 
using namespace std;
//typedef long long LL;
int R,C;
char GRID[8][8];
struct State
{
	int data[8];
	int left;
	const State *fa;
	State(const State *_fa):fa(_fa)
	{
		if(fa)
		{
			left=fa->left;
			for(int i=0;i<C;i++)data[i]=fa->data[i];
		}
		else
		{
			left=0;
			for(int i=0;i<C;i++)data[i]=0;
		}
	}
	bool operator<(const State &s)const
	{
		if(left!=s.left)return left<s.left;
		for(int i=0;i<C;i++)if(data[i]!=s.data[i])return data[i]<s.data[i];
		return false;
	}
	bool TryMove(State &t,const int row,const int col,const int color)const;
	bool ColorSame(const int col,const int color,const int value)const;
	void Replace(const int sou,const int tar){for(int i=0;i<C;i++)if(data[i]==sou)data[i]=tar;}
	void ReIndex()
	{
		map<int,int>idx[2];
		int cnt[2]={0,0};
		for(int i=0;i<C;i++)
		{
			auto &ctn=idx[data[i]&1];
			if(ctn.find(data[i])==ctn.end())ctn[data[i]]=((cnt[data[i]&1]++)<<1)|(data[i]&1);
		}
		for(int i=0;i<C;i++)
		{
			const auto it=idx[data[i]&1].find(data[i]);
			assert(it!=idx[data[i]&1].end());
			assert((data[i]&1)==((it->second)&1));
			data[i]=it->second;
		}
	}
	void AddColor(State &t,const int col,const int color,bool allow_disappear)const
	{
		t=State(this);
		t.left=(data[col]&1);
		if(color==(data[col]&1))
		{
			t.data[col]=data[col];
			if(col&&color==(data[col-1]&1))
			{
				assert(color!=left);
				assert(allow_disappear||data[col-1]!=data[col]);
				t.Replace(data[col-1],data[col]);
				t.ReIndex();
			}
			return;
		}
		else
		{
			if(col&&color==(data[col-1]&1))t.data[col]=data[col-1];
			else t.data[col]=(20<<1)|color;
			int result=-1;
			for(int i=0;i<C;i++)if(i!=col&&data[i]==data[col]){result=i;break;}
			if(result==-1)assert(allow_disappear);
			t.ReIndex();
		}
	}
	bool ContainOnlyZeroOne()
	{
		for(int i=0;i<C;i++)if(data[i]!=0&&data[i]!=1)return false;
		return true;
	}
//	void Print()const{printf("(left=%d,data=",left);for(int i=0;i<C;i++)printf("%d",data[i]);puts(")");}
};
struct CmpState{bool operator()(const State *a,const State *b)const{return (*a)<(*b);};};
map<State*,int,CmpState>DP[65];
void AddDP(map<State*,int,CmpState>&dp,State *s,const int value)
{
	auto it=dp.find(s);
	if(it!=dp.end())it->second+=value;
	else dp[s]=value;
}
vector<State>POOL;
State *New(const State &s){assert(s.left==0||s.left==1);const int sz=POOL.size();assert(sz<10000000);POOL.push_back(s);return &POOL[sz];}
bool State::ColorSame(const int col,const int color,const int value)const
{
	assert(value>=1LL);
	for(int i=col;i<C;i++)
	{
		if((data[i]&1)==(color^1)&&data[i]!=(color^1))return false;
		if((color==1&&GRID[R-1][i]=='o')||(color==0&&GRID[R-1][i]=='#'))return false;
	}
	for(int i=col+1;i<C;i++)if(color==(data[i-1]&1)&&color==(data[i]&1))return false;
	State *pre=(State*)this;
	for(int i=col;i<C;i++)
	{
		State *nxt=New(State(pre));
		pre->AddColor(*nxt,i,color,true); 
		pre=nxt;
	}
	AddDP(DP[R*C],pre,value);
	return true;
} 
bool State::TryMove(State &t,const int row,const int col,const int color)const
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
		if((data[0]&1)==color){AddColor(t,0,color,false);return true;}
		bool found=false;
		for(int i=1;i<C;i++)if(data[i]==data[0]){found=true;break;}
		if(!found)
		{
			if(row<R-1)return false;
			assert(row==R-1);
			ColorSame(0,color,DP[row*C+col][(State*)this]);
			return false;
		}
		else{AddColor(t,0,color,false);return true;}
	}
	if(color==(data[col]&1))
	{
		if(color==(data[col-1]&1)&&left==color)return false;
		assert(data[col-1]!=data[col]);
		AddColor(t,col,color,false);
		return true;
	}
	else
	{
		bool found=false;
		for(int i=0;i<C;i++)if(i!=col&&data[i]==data[col]){found=true;break;}
		if(!found)
		{
			if(row<R-1)return false;
			assert(row==R-1);
			ColorSame(col,color,DP[row*C+col][(State*)this]);
			return false;
		}
		else{AddColor(t,col,color,false);return true;}
	}
}
void Print(const State *s,vector<int>&ans)
{
	if(!s->fa)return;
	Print(s->fa,ans);
	ans.push_back(s->data[ans.size()%C]&1);
}
void Print(const State *s,const int len)
{
	vector<int>ans;
	Print(s,ans);
	assert((int)ans.size()==len);
	for(int i=0;i<(int)ans.size();i++)
	{
		if(i&&i%C==0)puts("");
		putchar(ans[i]==0?'o':'#');
	}
	puts("");
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
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
		AddDP(DP[0],New(State(NULL)),1LL);
		for(int row=0,col=0,i=0;;i++)
		{
			for(const auto &it:DP[i])
			{
				const State *state=it.first;
				static State target=State(NULL);
				if(GRID[row][col]!='#'&&state->TryMove(target,row,col,0))AddDP(DP[i+1],New(target),it.second);
				if(GRID[row][col]!='o'&&state->TryMove(target,row,col,1))AddDP(DP[i+1],New(target),it.second);
			}
			if(++col==C)col=0,row++;
			if(row==R)break;
		}
		int ans=0;
		State *result=NULL;
		for(const auto &it:DP[R*C])if(it.first->ContainOnlyZeroOne())
		{
			result=it.first;
			ans+=it.second;
		}
		if(result==NULL)puts("0");
		else
		{
			printf("%d\n",ans);
			Print(result,R*C);
		}
		puts("");
//		printf("%d\n",POOL.size());
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
