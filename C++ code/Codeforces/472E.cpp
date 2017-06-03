#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int R,C,GRID[32][32],TARGET[32][32],CUR;
int VIS[32][32],KASE;
vector<int>ANS;
bool Valid()
{
	static int cnt[901];
	for(int i=1;i<=900;i++)cnt[i]=0;
	for(int i=1;i<=R;i++)for(int j=1;j<=C;j++)cnt[GRID[i][j]]++;
	for(int i=1;i<=R;i++)for(int j=1;j<=C;j++)cnt[TARGET[i][j]]--;
	for(int i=1;i<=900;i++)if(cnt[i]!=0)return false;
	return true;
}
int Point(const int r,const int c){return r*(C+2)+c;}
void Extract(const int loc,int &r,int &c){r=loc/(C+2),c=loc%(C+2);}
int Get(const int s[32][32],const int loc){static int r,c;Extract(loc,r,c);return s[r][c];}
int Select(const int color)
{
	for(int i=1;i<=R;i++)for(int j=C;j>=1;j--)if(VIS[i][j]<KASE&&Point(i,j)!=CUR&&GRID[i][j]==color)return Point(i,j);
	assert(0);return -1;
}
void MoveCUR(const int loc)
{
	static int r1,c1,r2,c2;
	Extract(CUR,r1,c1),Extract(loc,r2,c2);
//	printf("CUR:(%d,%d)=>(%d,%d)\n",r1,c1,r2,c2);
	assert(max(abs(r1-r2),abs(c1-c2))==1);
	swap(GRID[r1][c1],GRID[r2][c2]);
	ANS.push_back(loc),CUR=loc;
}
//void PrintLoc(const int loc){int r,c;Extract(loc,r,c),printf("(%d,%d)\n",r,c);}
void GetPath(const int source,const int target,vector<int>&path)
{
//	puts("source:"),PrintLoc(source),puts("target:"),PrintLoc(target);
	static int pre[32][32];
	queue<int>q;q.push(source),q.push(source);
	bool found=false;
	while(!q.empty())
	{
		static int r,c;
		Extract(q.front(),r,c),q.pop();
		const int pre_loc=q.front();q.pop();
		if(VIS[r][c]>=KASE)continue;
		assert(1<=r&&r<=R&&1<=c&&c<=C);
		VIS[r][c]=KASE;
		pre[r][c]=pre_loc;
		if(Point(r,c)==target){found=true;break;}
		static int d[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
		for(int i=0;i<8;i++)q.push(Point(r+d[i][0],c+d[i][1])),q.push(Point(r,c));
	}
	assert(found);
	path.clear();
	for(int cur=target;cur!=source;cur=Get(pre,cur))path.push_back(cur);
	path.push_back(source);
	for(int l=0,r=(int)path.size()-1;l<r;l++,r--)swap(path[l],path[r]);
	KASE++;
}
void MoveCUR(const int target,const int banned)
{
	if(CUR==target)return;
	if(true){int r,c;Extract(banned,r,c);VIS[r][c]=KASE;}
	vector<int>path;
	GetPath(CUR,target,path);
	for(int i=1;i<(int)path.size();i++)MoveCUR(path[i]);
}
void MoveBeedOneStep(const int source,const int target)
{
	MoveCUR(target,source);
	MoveCUR(source);
}
void MoveBeed(const vector<int>&path)
{
	for(int i=1;i<(int)path.size();i++)MoveBeedOneStep(path[i-1],path[i]);
}
bool SameAsTARGET()
{
	for(int r=1;r<=R;r++)for(int c=1;c<=C;c++)if(GRID[r][c]!=TARGET[r][c])return false;
	return true;
}
bool Solve()
{
	assert(R>=C);
	if(!Valid())return false;
	ANS.clear();
	if(C==1)
	{
		static int grid_backup[32];
		for(int r=1;r<=R;r++)grid_backup[r]=GRID[r][1];
		for(int i=1;i<=R;i++)for(int j=1;j<=R;j++)if(i!=j)
		{
			ANS.clear(),ANS.push_back(CUR=Point(i,1));
			if(j<i)
			{
				for(int k=i-1;k>=j;k--)MoveCUR(Point(k,1));
			}
			else
			{
				for(int k=i+1;k<=j;k++)MoveCUR(Point(k,1));
			}
			if(SameAsTARGET())return true;
			for(int k=1;k<=R;k++)GRID[k][1]=grid_backup[k];
		}
		return false;
	}
	ANS.push_back(CUR=Select(TARGET[R][C]));
	for(int sum=2;sum<R+C;sum++)
	{
		vector<int>rs,cs;
		for(int r=1;r<sum&&r<=R;r++)
		{
			const int c=sum-r;
			if(c>C)continue;
			rs.push_back(r),cs.push_back(c);
		}
		for(int l=1,r=(int)rs.size()-1;l<r;l++,r--)swap(rs[l],rs[r]),swap(cs[l],cs[r]);
		for(int i=0;i<(int)rs.size();i++)
		{
			const int r=rs[i],c=cs[i];
			if(Point(r,c)!=CUR&&GRID[r][c]==TARGET[r][c])goto do_continue;
			static vector<int>path;
			GetPath(Select(TARGET[r][c]),Point(r,c),path);
			MoveBeed(path);
			do_continue:;
			assert(GRID[r][c]==TARGET[r][c]);
			VIS[r][c]=INF;
//			for(int i=1;i<=R;i++)
//			{
//				for(int j=1;j<=C;j++)printf("%d",GRID[i][j]);puts("");
//			}puts("");
		}
	}
	return true;
}
int main()
{
//	freopen("inn.txt","r",stdin);
	while(scanf("%d%d",&R,&C)==2)
	{
		for(int i=1;i<=R;i++)for(int j=1;j<=C;j++)scanf("%d",&GRID[i][j]);
		for(int i=1;i<=R;i++)for(int j=1;j<=C;j++)scanf("%d",&TARGET[i][j]);
		bool flipped=false;
		if(R<C)
		{
			const int n=max(R,C);
			for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)swap(GRID[i][j],GRID[j][i]),swap(TARGET[i][j],TARGET[j][i]);
			swap(R,C);
			flipped=true;
		}
		for(int i=0;i<=R+1;i++)for(int j=0;j<=C+1;j++)VIS[i][j]=0;
		for(int i=0;i<=R+1;i++)VIS[i][0]=VIS[i][C+1]=INF;
		for(int i=0;i<=C+1;i++)VIS[0][i]=VIS[R+1][i]=INF;
		KASE=1;
		if(Solve())
		{
			printf("%d\n",(int)ANS.size()-1);
			for(const int loc:ANS)
			{
				static int r,c;Extract(loc,r,c);
				if(flipped)swap(r,c);
				printf("%d %d\n",r,c);
			}
		}
		else puts("-1");
	}
	return 0;
}
