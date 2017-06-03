#include<cstdio>
#include<cassert>
#include<queue>
#include<vector>
#include<algorithm>
#include"Q1321-DiceBuilder.cpp"
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
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
	LL DP[4][481][24];
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
		for(int y=0;y<4;y++)for(int x=0;x<=480;x++)for(int t=0;t<24;t++)DP[y][x][t]=INF;
		priority_queue<Pq>pq;
		pq.push(Pq(sy,240,st,0LL));
		while(!pq.empty())
		{
			const Pq p=pq.top();pq.pop();
			if(DP[p.y][p.x][p.type]!=INF)continue;
			DP[p.y][p.x][p.type]=p.cost;
			static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
			for(int i=0;i<4;i++)
			{
				const int nxty=p.y+d[i][0],nxtx=p.x+d[i][1];
				if(nxty>=0&&nxty<4&&nxtx>=0&&nxtx<=480)
				{
					const DiceState &move=MOVE[p.type][i];
					pq.push(Pq(nxty,nxtx,move.type,p.cost+COST[move.top]));
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
				M.s[sy*24+stype][y*24+type]=DP[y][241][type];
				I.s[sy*24+stype][y*24+type]=DP[y][240][type];
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
		for(int i=0;i<24;i++)getmin(ans,MATRIXBUILDER.DP[Y2][240][i]);
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
		printf("%lld\n",Solve());
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
