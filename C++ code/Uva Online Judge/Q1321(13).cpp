#include<cstdio>
#include<cassert>
#include<queue>
#include<vector>
#include<algorithm>
//#include"Q1321-DiceBuilder.cpp"
using namespace std;
struct DiceState
{
	int top,type;
	DiceState(){}
	DiceState(const int _to,const int _ty):top(_to),type(_ty){}
}MOVE[24][4];
struct DiceBuilder
{
	struct Dice
	{
		int top,front,right,left,back,bottom;
		Dice():top(0),front(1),right(2),left(3),back(4),bottom(5){}
		Dice(const int _to,const int _fr,const int _ri,const int _le,const int _ba,const int _bo):top(_to),front(_fr),right(_ri),left(_le),back(_ba),bottom(_bo){}
		Dice Move(const int direction)
		{
			int tmp;
			switch(direction)
			{
				case 0:tmp=top,top=front,front=bottom,bottom=back,back=tmp;break;
				case 1:tmp=top,top=left,left=bottom,bottom=right,right=tmp;break;
				case 2:tmp=top,top=back,back=bottom,bottom=front,front=tmp;break;
				case 3:tmp=top,top=right,right=bottom,bottom=left,left=tmp;break;
				default:assert(0);break;
			}
			return (*this);
		}
		Dice Up()const{Dice ans=(*this);return ans.Move(0);}
		Dice Right()const{Dice ans=(*this);return ans.Move(1);}
		Dice Down()const{Dice ans=(*this);return ans.Move(2);}
		Dice Left()const{Dice ans=(*this);return ans.Move(3);}
	};
	Dice dice_type[24];
	int dice_idx[6][6];
	void BuildMOVE()
	{
		static bool vis[4][24];
		for(int i=0;i<4;i++)for(int j=0;j<24;j++)vis[i][j]=false;
		for(int i=0;i<24;i++)
		{
			Dice now,nxt;
			now=dice_type[i];
			for(int d=0;d<4;d++)
			{
				switch(d)
				{
					case 0:nxt=now.Up();break;
					case 1:nxt=now.Right();break;
					case 2:nxt=now.Down();break;
					case 3:nxt=now.Left();break;
					default:assert(0);break;
				}
				const int type=dice_idx[nxt.top][nxt.front];
				MOVE[i][d]=DiceState(nxt.top,type);
				assert(type!=-1);
				assert(vis[d][type]==false);
				vis[d][type]=true;
			}
		}
	}
	void Build()
	{
		for(int i=0;i<36;i++)dice_idx[i/6][i%6]=-1;
		Dice *d=dice_type;
		d[0]=Dice();
		d[4]=d[0].Up();
		d[8]=d[0].Up().Up();
		d[12]=d[0].Down();
		d[16]=d[0].Left().Up();
		d[20]=d[0].Right().Up();
		for(int i=0;i<=20;i+=4)for(int j=1;j<=3;j++)d[i+j]=d[i+j-1].Left();
//		for(int i=0;i<24;i++)printf("(%d,%d)\n",d[i].top,d[i].front);
		for(int i=0;i<24;i++)
		{
			int &idx=dice_idx[d[i].top][d[i].front];
			assert(idx==-1),idx=i;
		}
		BuildMOVE();
	}
}DICEBUILDER;
typedef long long LL;
const LL INF=9223372036854775807LL;
const int MAXDIS=120;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
LL COST[6];
int X1,Y1,X2,Y2;
struct Matrix
{
	LL s[96][96];
	Matrix(){}
	Matrix operator*(const Matrix &a)const
	{
		Matrix ans=Matrix();
		for(int i=0;i<96;i++)for(int j=0;j<96;j++)
		{
			LL &v=ans.s[i][j]=INF;
			for(int k=0;k<96;k++)if(s[i][k]!=INF&&a.s[k][j]!=INF)getmin(v,s[i][k]+a.s[k][j]);
		}
		return ans;
	}
}M,I;
Matrix Pow(Matrix a,int p)
{
	Matrix ans=I;
	while(p)
	{
		if(p&1)ans=ans*a;
		a=a*a;
		p>>=1;
	}
	return ans;
}
struct MatrixBuilder
{
	LL DP[4][MAXDIS*2+1][24];
	struct Pq
	{
		int y,x,type;
		LL cost;
		Pq(){}
		Pq(const int _y,const int _x,const int _t,const LL &_c):y(_y),x(_x),type(_t),cost(_c){}
		bool operator<(const Pq &p)const{return cost>p.cost;}
	};
	void Build(const int sy,const int st)
	{
		for(int y=0;y<4;y++)for(int x=0;x<=MAXDIS*2;x++)for(int t=0;t<24;t++)DP[y][x][t]=INF;
		priority_queue<Pq>pq;
		pq.push(Pq(sy,MAXDIS,st,0LL));
		while(!pq.empty())
		{
			const Pq p=pq.top();pq.pop();
			if(DP[p.y][p.x][p.type]!=INF)continue;
			DP[p.y][p.x][p.type]=p.cost;
			static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
			for(int i=0;i<4;i++)
			{
				const int nxty=p.y+d[i][0],nxtx=p.x+d[i][1];
				if(nxty>=0&&nxty<4&&nxtx>=0&&nxtx<=MAXDIS*2)
				{
					const DiceState &move=MOVE[p.type][i];
					if(DP[nxty][nxtx][move.type]==INF)pq.push(Pq(nxty,nxtx,move.type,p.cost+COST[move.top]));
				}
			}
		}
	}
	void Build()
	{
		for(int sy=0;sy<4;sy++)for(int stype=0;stype<24;stype++)
		{
			Build(sy,stype);
			for(int y=0;y<4;y++)for(int type=0;type<24;type++)
			{
				M.s[sy*24+stype][y*24+type]=DP[y][MAXDIS+1][type];
				I.s[sy*24+stype][y*24+type]=DP[y][MAXDIS][type];
			}
		}
	}
}MATRIXBUILDER;
LL Solve()
{
	if(X1==X2)
	{
		MATRIXBUILDER.Build(Y1,0);
		LL ans=INF;
		for(int i=0;i<24;i++)getmin(ans,MATRIXBUILDER.DP[Y2][MAXDIS][i]);
		return ans;
	}
	if(X1>X2)swap(X1,X2),swap(Y1,Y2);
	MATRIXBUILDER.Build();
//	for(int i=0;i<96;i++)for(int j=0;j<96;j++)printf("(%d,%d)(%d,%d): %lld\n",i/24,i%24,j/24,j%24,M.s[i][j]);
	assert(X1<X2);
	Matrix result=Pow(M,X2-X1);
//	for(int i=0;i<96;i++)for(int j=0;j<96;j++)printf("(%d,%d)(%d,%d): %lld\n",i/24,i%24,j/24,j%24,result.s[i][j]);
	LL ans=INF;
	for(int i=0;i<24;i++)getmin(ans,result.s[Y1*24+0][Y2*24+i]);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	DICEBUILDER.Build();
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		for(int i=0;i<6;i++)assert(scanf("%lld",&COST[i])==1&&COST[i]>0LL);
		assert(scanf("%d%d%d%d",&X1,&Y1,&X2,&Y2)==4);
		Y1--,Y2--;
		assert(Y1>=0&&Y1<4&&Y2>=0&&Y2<4);
		static int kase=1;
		if(kase++>1)puts("");
		printf("%lld\n",Solve());
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
