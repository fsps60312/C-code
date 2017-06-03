#include<cstdio>
#include<set>
#include<cassert>
#include<queue>
#include<vector>
using namespace std;
const int INF=2147483647;
int *GetNumberAround(const int d)
{
	if(0<=d&&d<=4)return new int[3]{d+5,(d+4)%5,(d+1)%5};
	else if(5<=d&&d<=9)return new int[3]{d-5,d==9?d+1:d+6,d+5};
	else if(10<=d&&d<=14)return new int[3]{d+5,d==10?d-1:d-6,d-5};
	else if(15<=d&&d<=19)return new int[3]{d-5,d==19?15:d+1,d==15?19:d-1};
	return NULL;
}
struct State
{
	int x,y,down,side;
	State(){}
	State(const int _x,const int _y,const int _down,const int _side):x(_x),y(_y),down(_down),side(_side){}
	int NumberOf(const bool is_clockwise)const
	{
		int *tmp=GetNumberAround(down);
		assert(tmp!=NULL);
		int ans=-1;
		for(int i=0;i<3;i++)if(side==tmp[i])ans=(!is_clockwise?tmp[(i+1)%3]:tmp[(i+2)%3]);
		delete[]tmp;
		assert(ans!=-1);
		return ans;
	}
	State ToLeft()const
	{
		State ans=(*this);
		ans.x--;
		const bool is_up=((x&1)==(y&1));
		ans.down=NumberOf(!is_up);
		ans.side=down;
		ans.side=ans.NumberOf(is_up);
		return ans;
	}
	State ToRight()const
	{
		State ans=(*this);
		ans.x++;
		const bool is_up=((x&1)==(y&1));
		ans.down=NumberOf(is_up);
		ans.side=down;
		ans.side=ans.NumberOf(!is_up);
		return ans;
	}
	State ToSide()const
	{
		State ans=(*this);
		swap(ans.down,ans.side);
		if((x&1)==(y&1))ans.y++;
		else ans.y--;
		return ans;
	}
	bool operator<(const State &s)const
	{
		if(x!=s.x)return x<s.x;
		if(y!=s.y)return y<s.y;
		if(down!=s.down)return down<s.down;
		return side<s.side;
	}
	void Print(){printf("(x=%d,y=%d,down=%d,side=%d)\n",x,y,down,side);}
};
State InitialState(){return State(0,0,0,5);}
vector<set<State> >DP;
void MoveBall(const State &nxt,const int idx){DP[idx].insert(nxt);}
void Initialize()
{
	DP.clear();
	DP.push_back(set<State>());
	DP[0].insert(InitialState());
}
void Expand()
{
	const int idx=DP.size();
	DP.push_back(set<State>());
	for(const State &s:DP[idx-1])
	{
		DP[idx].insert(s.ToSide());
		DP[idx].insert(s.ToLeft());
		DP[idx].insert(s.ToRight());
	}
}
int main()
{
	Initialize();
	int x,y,z;
	while(scanf("%d%d%d",&x,&y,&z)==3)
	{
		State s[3];
		int *tmp=GetNumberAround(z);
		for(int i=0;i<3;i++)s[i].x=x,s[i].y=y,s[i].down=z,s[i].side=tmp[i];
		delete[]tmp;
		int ans=0;
		for(;;ans++)
		{
			if((int)DP.size()==ans)Expand();
			bool found=false;
			for(int i=0;i<3;i++)if(DP[ans].find(s[i])!=DP[ans].end()){found=true;break;}
			if(found)break;
		}
		printf("%d\n",ans);
	}
	return 0;
}
