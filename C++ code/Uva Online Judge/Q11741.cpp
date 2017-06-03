#include<cstdio>
#include<cassert>
#include<map>
#include<set>
using namespace std;
const int MOD=10000007;
int R,C,N;
int DP[2][1<<4];
map<int,set<int> >UNUSABLE;
bool Usable(const int r,const int c)
{
	const auto it=UNUSABLE.find(r);
	if(it==UNUSABLE.end())return true;
	return (it->second).find(c)==(it->second).end();
}
void Add(int &a,const int b){(a+=b)%=MOD;}
bool TryH(const int s,int &t,const int col)
{
	assert(!(s&(1<<col)));
	if(col+1>=C)return false;
	if(s&(1<<(col+1)))return false;
	t=s+(1<<(col+1));
	return true;
}
bool TryV(const int s,int &t,const int col)
{
	assert(!(s&(1<<col)));
	t=s+(1<<col);
	return true;
}
int Solve()
{
	for(int i=0;i<(1<<C);i++)DP[0][i]=DP[1][i]=0;
	Add(DP[0][0],1);
	int d=0;
//	printf("R=%d,C=%d\n",R,C);
	for(int row=0,col=0;row<R;d^=1)
	{
		const bool usable=Usable(row,col);
//		printf("row=%d,col=%d\n",row,col);
		for(int s=0;s<(1<<C);s++)if(DP[d][s])
		{
			const int value=DP[d][s];
//			printf("(%d,%d,%d):%d\n",row,col,s,value);
			if(!usable)
			{
				if(s&(1<<col))continue;
				Add(DP[d^1][s],value);
			}
			else
			{
				if(s&(1<<col))Add(DP[d^1][s-(1<<col)],value);
				else
				{
					static int target;
					if(TryH(s,target,col))Add(DP[d^1][target],value);
					if(TryV(s,target,col))Add(DP[d^1][target],value);
				}
			}
			DP[d][s]=0;
		}
		if(++col==C)col=0,row++;
	}
	return DP[d][0];
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		assert(scanf("%d%d%d",&C,&R,&N)==3);
		if(R==0&&C==0&&N==0)break;
		UNUSABLE.clear();
		for(int i=0,r,c;i<N;i++)assert(scanf("%d%d",&c,&r)==2),UNUSABLE[r].insert(c);
		static int kase=1;
		printf("Case %d: %d\n",kase++,Solve());
	}
	return 0;
}
