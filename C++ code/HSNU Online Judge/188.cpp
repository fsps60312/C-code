#include<cstdio>
#include<map>
#include<cassert>
#include<queue>
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
map<State,int>DP;
void MoveBall(queue<State>&q,const State &nxt,const int costnow)
{
	if(DP.find(nxt)!=DP.end())return;
	DP[nxt]=costnow+1;
	if(costnow+1<100)q.push(nxt);
}
void Initialize()
{
	DP.clear();
	queue<State>q;
	const State source=InitialState();
	DP[source]=0;
	q.push(source);
	int costnow=0;
	while(!q.empty())
	{
		const State s=q.front();q.pop();
		const auto it=DP.find(s);
		if(it->second>costnow)costnow=it->second,printf("cost=%d, sz=%d\n",costnow,(int)DP.size());
		assert(it!=DP.end());
		MoveBall(q,s.ToSide(),it->second);
		MoveBall(q,s.ToLeft(),it->second);
		MoveBall(q,s.ToRight(),it->second);
	}
}
int main()
{
//	InitialState().Print();
//	InitialState().ToSide().Print();
//	InitialState().ToLeft().Print();
//	InitialState().ToRight().Print();return 0;
	Initialize();
	int x,y,z;
	while(scanf("%d%d%d",&x,&y,&z)==3)
	{
		State s;
		s.x=x,s.y=y,s.down=z;
		int *tmp=GetNumberAround(z);
		int ans=INF;
		for(int i=0;i<3;i++)
		{
			s.side=tmp[i];
			const auto it=DP.find(s);
			if(it==DP.end()){ans=INF;break;}
			if(it->second<ans)ans=it->second;
		}
//		assert(ans!=INF);
		printf("%d\n",ans);
	}
	return 0;
}
