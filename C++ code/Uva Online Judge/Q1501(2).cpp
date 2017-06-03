#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
const int INF=2147483647;
int R,C;
char GRID[8][9];
struct State
{
	int data[9];
	bool appear;
	void Replace(const int sou,const int tar){for(int i=0;i<=C;i++)if(data[i]==sou)data[i]=tar;}
	void ReIndex()
	{
		map<int,int>idx;
		for(int i=0,cnt=0;i<=C;i++)if(data[i]!=-2&&idx.find(data[i])==idx.end())idx[data[i]]=cnt++;
		for(int i=0;i<=C;i++)if(data[i]!=-2)data[i]=idx[data[i]];
	}
	bool TryYes(State &t,int &value,const int col)const
	{
		if(appear)
		{
			bool found=false;
			for(int i=0;i<C;i++)if(data[i]!=-2){found=true;break;}
			if(!found)return false;
		}
		t=(*this),t.appear=true,t.data[C]=(col+1==C?-2:data[col]),value=0;
		if(col==0)
		{
			assert(data[C]==-2);
			if(data[col]==-2)t.data[col]=100,value++;
			value++;
		}
		else
		{
			if(data[col-1]==-2&&data[col]==-2)
			{
				if(data[C]>=0)return false;
				t.data[col]=100,value+=2;
			}
			else if(data[col-1]==-2&&data[col]>=0)value++;
			else if(data[col-1]>=0&&data[col]==-2)t.data[col]=data[col-1],value++;
			else
			{
				assert(data[col-1]>=0&&data[col]>=0);
				if(data[col-1]==data[col])
				{
					if(data[C]==-2)return false;//form a cycle
					assert(data[C]==data[col]);
				}
				else assert(data[C]==-2),t.Replace(data[col],data[col-1]);
			}
		}
		t.ReIndex();
		if(col+1==C)value++;
		return true;
	}
	bool CanCover(const int col)const
	{
		bool found=false,another=false;
		for(int i=0;i<C;i++)if(i!=col)found|=(data[i]==data[col]),another|=(data[i]!=data[col]&&data[i]>=0);
		if(another&&!found)return false;
		return true;
	}
	bool TryNo(State &t,int &value,const int col)const
	{
		t=(*this),t.data[C]=(col+1==C?-2:data[col]),value=0;
		if(col==0)
		{
			assert(data[C]==-2);
			if(data[col]>=0){if(!CanCover(col))return false;value++;}
			t.data[col]=-2;
		}
		else
		{
			if(data[col-1]==-2&&data[col]==-2);
			else if(data[col-1]==-2&&data[col]>=0)
			{
				if(!CanCover(col))return false;
				t.data[col]=-2,value++;
			}
			else if(data[col-1]>=0&&data[col]==-2)value++;
			else
			{
				assert(data[col-1]>=0&&data[col]>=0);
				if(data[C]==-2)return false;
				else assert(data[C]==data[col]);
				t.data[col]=-2,value+=2;
			}
		}
		t.ReIndex();
		return true;
	}
	bool operator<(const State &s)const{for(int i=0;i<=C;i++)if(data[i]!=s.data[i])return data[i]<s.data[i];return appear<s.appear;}
};
map<State,int>DP[2];
void Update(const int d,const State &s,const int value)
{
	auto it=DP[d].find(s);
	if(it==DP[d].end())DP[d][s]=value;
	else if(value<(it->second))it->second=value;
}
int IsAns(const State &s)
{
	int ans=0;
	for(int i=0;i<C;i++)
	{
		if(s.data[i]==-2)continue;
		if(s.data[i]==0){ans++;continue;}
		assert(s.data[i]>0);
		return -1;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d",&R,&C)==2);
		for(int i=0;i<R;i++)assert(scanf("%s",GRID[i])==1);
		int d=0;
		assert(DP[0].empty()&&DP[1].empty());
		State state0;
		for(int i=0;i<=C;i++)state0.data[i]=-2;
		state0.appear=false;
		Update(0,state0,0);
		for(int row=0,col=0;row<R;d^=1)
		{
			const char type=GRID[row][col];
			assert(type=='o'||type=='.'||type=='x');
			for(const auto &it:DP[d])
			{
				const State &s=it.first;
				static State t;
				static int value;
				if(type!='x'&&s.TryYes(t,value,col))Update(d^1,t,(it.second)+value);
				if(type!='o'&&s.TryNo(t,value,col))Update(d^1,t,(it.second)+value);
			}
			DP[d].clear();
			if(++col==C)col=0,row++;
		}
		int ans=INF;
		for(const auto &it:DP[d])
		{
			const int ta=IsAns(it.first);
			if(ta!=-1&&(it.second+ta)<ans)ans=it.second+ta;
		}
		DP[d].clear();
		static int kase=1;
		printf("Case #%d: %d\n",kase++,ans==INF?-1:ans);
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
