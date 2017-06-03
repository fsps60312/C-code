#include<cstdio>
#include<vector>
//#include<cassert>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
struct Line
{
	int h,e1,e2;
	Line(){}
	Line(const int _h,const int _e1,const int _e2):h(_h),e1(_e1),e2(_e2){}
};
int N;
vector<Line>LH,LV;
bool CUT[201][201][4];
bool VIS[201][201];
map<int,int>XIDX,YIDX;
void ReIndex()
{
	XIDX.clear(),YIDX.clear();
	for(const Line &l:LH)YIDX[l.h]=XIDX[l.e1]=XIDX[l.e2]=-1;
	for(const Line &l:LV)XIDX[l.h]=YIDX[l.e1]=YIDX[l.e2]=-1;
	int cnt=1;
	for(auto &it:XIDX)it.second=cnt++;
	cnt=1;
	for(auto &it:YIDX)it.second=cnt++;
	for(Line &l:LH)l.h=YIDX[l.h],l.e1=XIDX[l.e1],l.e2=XIDX[l.e2];
	for(Line &l:LV)l.h=XIDX[l.h],l.e1=YIDX[l.e1],l.e2=YIDX[l.e2];
	for(int i=0;i<=(int)YIDX.size();i++)for(int j=0;j<=(int)XIDX.size();j++)
	{
		VIS[i][j]=false;
		for(int k=0;k<4;k++)CUT[i][j][k]=false;
	}
	for(int i=0;i<=(int)XIDX.size();i++)CUT[0][i][0]=CUT[(int)YIDX.size()][i][2]=true;
	for(int i=0;i<=(int)YIDX.size();i++)CUT[i][0][3]=CUT[i][(int)XIDX.size()][1]=true;
	for(Line &l:LH)for(int i=l.e1;i<l.e2;i++)CUT[l.h][i][0]=CUT[l.h-1][i][2]=true;
	for(Line &l:LV)for(int i=l.e1;i<l.e2;i++)CUT[i][l.h][3]=CUT[i][l.h-1][1]=true;
}
void Bfs(const int sy,const int sx,const bool type)
{
	queue<int>qy,qx;
	qy.push(sy),qx.push(sx);
	while(!qy.empty())
	{
		const int y=qy.front(),x=qx.front();
		qy.pop(),qx.pop();
		if(VIS[y][x])continue;
		VIS[y][x]=true;
		if(!CUT[y][x][0]||type)qy.push(y-1),qx.push(x);
		if(!CUT[y][x][1]||type)qy.push(y),qx.push(x+1);
		if(!CUT[y][x][2]||type)qy.push(y+1),qx.push(x);
		if(!CUT[y][x][3]||type)qy.push(y),qx.push(x-1);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		assert(scanf("%d",&N)==1);
		if(N==0)break;
		LH.clear(),LV.clear();
		for(int i=0,x1,x2,y1,y2;i<N;i++)
		{
			assert(scanf("%d%d%d%d",&x1,&y1,&x2,&y2)==4);
			if(x1==x2)
			{
				if(y1>y2)swap(y1,y2);
				if(y1==y2)continue;
				assert(y1<y2);
				LV.push_back(Line(x1,y1,y2));
			}
			else if(y1==y2)
			{
				if(x1>x2)swap(x1,x2);
				if(x1==x2)continue;
				assert(x1<x2);
				LH.push_back(Line(y1,x1,x2));
			}
			else assert(0);
		}
		ReIndex();
		int ans=0;
		Bfs(0,0,false);
		for(int i=0;i<=(int)YIDX.size();i++)for(int j=0;j<=(int)XIDX.size();j++)if(!VIS[i][j])Bfs(i,j,true),ans++;
		printf("%d\n",ans);
	}
	assert(scanf("%d",&N)!=1);
	return 0;
}
