#include<cstdio>
#include<set>
#include<cassert>
#include<queue>
#include<vector>
using namespace std;
const int INF=2147483647;
const int BOUND=110;
void getmin(int &a,const int b){if(b<a)a=b;}
int *GetNumberAround(const int d)
{
	if(0<=d&&d<=4)return new int[3]{d+5,(d+4)%5,(d+1)%5};
	else if(5<=d&&d<=9)return new int[3]{d-5,d==9?d+1:d+6,d+5};
	else if(10<=d&&d<=14)return new int[3]{d+5,d==10?d-1:d-6,d-5};
	else if(15<=d&&d<=19)return new int[3]{d-5,d==19?15:d+1,d==15?19:d-1};
	return NULL;
}
int GetSideIdx(const int down,const int side)
{
	int *tmp=GetNumberAround(down),ans=-1;
	for(int i=0;i<3;i++)if(tmp[i]==side){ans=i;break;}
	delete[]tmp;
	assert(ans!=-1);
	return ans;
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
};
int DIST[BOUND*2+1][BOUND*2+1][19][3];
bool Valid(const State &s){return -BOUND<=s.x&&s.x<=BOUND&&-BOUND<=s.y&&s.y<=BOUND;}
int &GetDist(const State &s){return DIST[s.x+BOUND][s.y+BOUND][s.down][GetSideIdx(s.down,s.side)];}
void TryMove(queue<State>&q,const State &nxt,const int distnow)
{
	if(!Valid(nxt))return;
	int &dist=GetDist(nxt);
	if(dist!=INF)return;
	dist=distnow+1;
	q.push(nxt);
}
void Initialize()
{
	for(int i=0;i<=BOUND*2;i++)for(int j=0;j<BOUND*2+1;j++)for(int k=0;k<19;k++)for(int l=0;l<3;l++)DIST[i][j][k][l]=INF;
	queue<State>q;
	const State source=State(0,0,0,5);
	GetDist(source)=0,q.push(source);
	while(!q.empty())
	{
		const State s=q.front();q.pop();
		const int distnow=GetDist(s);
		TryMove(q,s.ToSide(),distnow);
		TryMove(q,s.ToLeft(),distnow);
		TryMove(q,s.ToRight(),distnow);
	}
}
int main()
{
	Initialize();
	int x,y,z;
	while(scanf("%d%d%d",&x,&y,&z)==3)
	{
		int ans=INF;
		for(int i=0;i<3;i++)getmin(ans,DIST[x+BOUND][y+BOUND][z][i]);
		printf("%d\n",ans);
	}
	return 0;
}
