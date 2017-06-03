#include<cstdio>
#include<cassert>
#include<queue>
#include<algorithm>
//#include"Q1321-DiceBuilder.cpp"
using namespace std;
typedef long long LL;
struct DiceState
{
	LL top,type;
	DiceState(){}
	DiceState(const LL _to,const LL _ty):top(_to),type(_ty){}
}MOVE[24][4];
struct DiceBuilder
{
	struct Dice
	{
		LL top,front,right,left,back,bottom;
		Dice():top(0),front(1),right(2),left(3),back(4),bottom(5){}
		Dice(const LL _to,const LL _fr,const LL _ri,const LL _le,const LL _ba,const LL _bo):top(_to),front(_fr),right(_ri),left(_le),back(_ba),bottom(_bo){}
		Dice Move(const LL direction)
		{
			LL tmp;
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
	LL dice_idx[6][6];
	void BuildMOVE()
	{
		static bool vis[4][24];
		for(LL i=0;i<4;i++)for(LL j=0;j<24;j++)vis[i][j]=false;
		for(LL i=0;i<24;i++)
		{
			Dice now,nxt;
			now=dice_type[i];
			for(LL d=0;d<4;d++)
			{
				switch(d)
				{
					case 0:nxt=now.Up();break;
					case 1:nxt=now.Right();break;
					case 2:nxt=now.Down();break;
					case 3:nxt=now.Left();break;
					default:assert(0);break;
				}
				const LL type=dice_idx[nxt.top][nxt.front];
				MOVE[i][d]=DiceState(nxt.top,type);
				assert(type!=-1);
				assert(vis[d][type]==false);
				vis[d][type]=true;
			}
		}
	}
	void Build()
	{
		for(LL i=0;i<36;i++)dice_idx[i/6][i%6]=-1;
		Dice *d=dice_type;
		d[0]=Dice();
		d[4]=d[0].Up();
		d[8]=d[0].Up().Up();
		d[12]=d[0].Down();
		d[16]=d[0].Left().Up();
		d[20]=d[0].Right().Up();
		for(LL i=0;i<=20;i+=4)for(LL j=1;j<=3;j++)d[i+j]=d[i+j-1].Left();
//		for(LL i=0;i<24;i++)printf("(%lld,%lld)\n",d[i].top,d[i].front);
		for(LL i=0;i<24;i++)
		{
			LL &idx=dice_idx[d[i].top][d[i].front];
			assert(idx==-1),idx=i;
		}
		BuildMOVE();
	}
}DICEBUILDER;
const LL INF=9223372036854775807LL;
const LL MAXDIS=1;
bool getmin(LL &a,const LL &b){if(b<a){a=b;return true};return false;}
LL COST[6];
LL X1,Y1,X2,Y2;
struct Matrix
{
	LL s[96][96];
	Matrix(){}
	Matrix operator*(const Matrix &a)const
	{
		Matrix ans=Matrix();
		for(LL i=0;i<96;i++)for(LL j=0;j<96;j++)
		{
			LL &v=ans.s[i][j]=INF;
			for(LL k=0;k<96;k++)if(s[i][k]!=INF&&a.s[k][j]!=INF)getmin(v,s[i][k]+a.s[k][j]);
		}
		return ans;
	}
	bool Update(const Matrix &a)
	{
		bool ans=false;
		for(int i=0;i<96;i++)for(int j=0;j<96;j++)ans|=getmin(s[i][j],a.s[i][j]);
		return ans;
	}
}M,I;
Matrix Pow(Matrix a,LL p)
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
		LL y,x,type;
		LL cost;
		Pq(){}
		Pq(const LL _y,const LL _x,const LL _t,const LL &_c):y(_y),x(_x),type(_t),cost(_c){}
		bool operator<(const Pq &p)const{return cost>p.cost;}
	};
	void Build(const LL sy,const LL st)
	{
		for(LL y=0;y<4;y++)for(LL x=0;x<=MAXDIS*2;x++)for(LL t=0;t<24;t++)DP[y][x][t]=INF;
		priority_queue<Pq>pq;
		pq.push(Pq(sy,MAXDIS,st,0LL));
		while(!pq.empty())
		{
			const Pq p=pq.top();pq.pop();
			if(DP[p.y][p.x][p.type]!=INF)continue;
			DP[p.y][p.x][p.type]=p.cost;
			static LL d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
			for(LL i=0;i<4;i++)
			{
				const LL nxty=p.y+d[i][0],nxtx=p.x+d[i][1];
				if(nxty>=0&&nxty<4&&nxtx>=0&&nxtx<=MAXDIS*2)
				{
					const DiceState &move=MOVE[p.type][i];
					if(DP[nxty][nxtx][move.type]==INF)pq.push(Pq(nxty,nxtx,move.type,p.cost+COST[move.top]));
				}
			}
		}
	}
	Matrix R[32],L[32];
	void Build()
	{
		for(LL sy=0;sy<4;sy++)for(LL stype=0;stype<24;stype++)
		{
			Build(sy,stype);
			for(LL y=0;y<4;y++)for(LL type=0;type<24;type++)
			{
				R[0].s[sy*24+stype][y*24+type]=DP[y][MAXDIS+1][type];
				I   .s[sy*24+stype][y*24+type]=DP[y][MAXDIS  ][type];
				L[0].s[sy*24+stype][y*24+type]=DP[y][MAXDIS-1][type];
			}
		}
		for(int d=1;d<32;d++)
		{
			L[d]=L[d-1]*L[d-1];
			R[d]=R[d-1]*R[d-1];
			
		}
		M=R[0];
	}
}MATRIXBUILDER;
LL Solve()
{
	if(X1==X2)
	{
		MATRIXBUILDER.Build(Y1,0);
		LL ans=INF;
		for(LL i=0;i<24;i++)getmin(ans,MATRIXBUILDER.DP[Y2][MAXDIS][i]);
		return ans;
	}
	if(X1>X2)swap(X1,X2),swap(Y1,Y2);
	MATRIXBUILDER.Build();
//	for(LL i=0;i<96;i++)for(LL j=0;j<96;j++)printf("(%lld,%lld)(%lld,%lld): %lld\n",i/24,i%24,j/24,j%24,M.s[i][j]);
	assert(X1<X2);
	Matrix result=Pow(M,X2-X1);
//	for(LL i=0;i<96;i++)for(LL j=0;j<96;j++)printf("(%lld,%lld)(%lld,%lld): %lld\n",i/24,i%24,j/24,j%24,result.s[i][j]);
	LL ans=INF;
	for(LL i=0;i<24;i++)getmin(ans,result.s[Y1*24+0][Y2*24+i]);
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	DICEBUILDER.Build();
	static LL casecount;assert(scanf("%lld",&casecount)==1);
	while(casecount--)
	{
		for(LL i=0;i<6;i++)assert(scanf("%lld",&COST[i])==1&&COST[i]>0LL);
		assert(scanf("%lld%lld%lld%lld",&X1,&Y1,&X2,&Y2)==4);
		Y1--,Y2--;
		assert(Y1>=0&&Y1<4&&Y2>=0&&Y2<4);
		static LL kase=1;
		if(kase++>1)puts("");
		printf("%lld\n",Solve());
	}
	assert(scanf("%lld",&casecount)!=1);
	return 0;
}
