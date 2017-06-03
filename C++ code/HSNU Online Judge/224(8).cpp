#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
void SetBit(int &s,const int i,const int v){if(v)s|=1<<i;else s&=~(1<<i);}
int GetBit(const int s,const int i){return (s&(1<<i))>>i;}
struct BorderLineSolver
{
	int data[30][30],type;
	void Clear(){for(int i=0;i<30;i++)for(int j=0;j<30;j++)data[i][j]=-2;}
	void Print()
	{
		printf("R=%d,C=%d,type=%d\n",R,C,type);
		for(int i=0;i<R;i++)
		{
			for(int j=0;j<C;j++)printf("%3d",data[i][j]);
			puts("");
		}
	}
	bool Try(const int s,const int row,const int col,const int color,int &t,int &score)
	{
		if(!(-1<=data[row][col]&&data[row][col]<=1))printf("(%d,%d)error=%d\n",row,col,data[row][col]);
		assert(-1<=data[row][col]&&data[row][col]<=1);
		if(data[row][col]==1-color*2)return false;
		t=s;
		SetBit(t,col,color),score=0;
		if(row==0)return true;
		else if((row&1)==type)
		{
			if(col-1>=0&&GetBit(s,col-1)!=color)score++;
			if(col+1<C&&GetBit(s,col+1)!=color)score++;
		}
		else
		{
			assert(col>=1);
			SetBit(t,0,0);
			if(GetBit(s,col-1)!=color)score++;
			if(col+1<C&&GetBit(s,col+1)!=color)score++;
		}
		if(col)SetBit(t,col-1,0);
		return true;
	}
	int R,C;
	map<int,int>DP[2];
	void Update(const int d,const int s,const int v)
	{
		auto it=DP[d].find(s);
		if(it==DP[d].end())DP[d][s]=v;
		else getmax(it->second,v);
	}
	int Solve()
	{
		assert(type==0||type==1);
		DP[0].clear(),DP[1].clear();
		int d=0;
		Update(d,0,0);
		for(int row=0,col=type;;col+=2,d^=1)
		{
			while(row<R&&col>=C)row++,col=(row&1?type^1:type);
			if(row==R)break;
//			printf("row=%d,col=%d\n",row,col);
			for(const auto &it:DP[d])
			{
				static int t,score;
				if(Try(it.first,row,col,0,t,score))Update(d^1,t,(it.second)+score);
				if(Try(it.first,row,col,1,t,score))Update(d^1,t,(it.second)+score);
			}
			DP[d].clear();
		}
		int ans=0;
		for(const auto it:DP[d])getmax(ans,it.second);
//		printf("ans=%d\n",ans);
		return ans;
	}
}SOLVER;
int N,M,A,B,GRID[30][30];
bool VIS[30][30];
int Fill(int *s,const int r,const int c)
{
	int cnt=c/B;
	for(int i=c;i<M;i+=2*B,cnt+=2)
	{
		if(r==-1)s[cnt]=(cnt&1);
		else s[cnt]=GRID[r][i],VIS[r][i]=true;
	}
	return cnt-1;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d%d%d%d",&N,&M,&A,&B);
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)scanf("%d",&GRID[i][j]),VIS[i][j]=false;
		int ans=0;
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)if(!VIS[i][j])
		{
			SOLVER.Clear();
			int &sr=SOLVER.R=0,&sc=SOLVER.C=0;
			SOLVER.type=j/B;
			for(int r=i;r<N;r+=A,sr++)
			{
				if(sr%2==0)getmax(sc,Fill(SOLVER.data[sr],r,j));
				else getmax(sc,Fill(SOLVER.data[sr],r,(j+B)%(2*B)));
			}
//			SOLVER.Print();
			ans+=SOLVER.Solve();
		}
		printf("%d\n",ans);
	}
	return 0;
}
