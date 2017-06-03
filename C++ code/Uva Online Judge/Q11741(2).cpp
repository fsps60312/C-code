#include<cstdio>
#include<cassert>
#include<map>
#include<set>
using namespace std;
typedef long long LL;
const LL MOD=10000007;
void Add(LL &a,const LL &b){(a+=b)%=MOD;}
int R,C,N;
struct Matrix
{
	LL s[1<<4][1<<4];
	Matrix operator*(const Matrix &a)const
	{
		Matrix ans;
		for(int i=0;i<(1<<C);i++)for(int j=0;j<(1<<C);j++)
		{
			LL &v=ans.s[i][j]=0;
			for(int k=0;k<(1<<C);k++)Add(v,s[i][k]*a.s[k][j]);
		}
		return ans;
	}
}M;
Matrix Pow(Matrix a,int p)
{
	Matrix ans;
	for(int i=0;i<(1<<C);i++)for(int j=0;j<(1<<C);j++)ans.s[i][j]=(i==j?1LL:0LL);
	while(p)
	{
		if(p&1)ans=ans*a;
		a=a*a;
		p>>=1;
	}
	return ans;
}
LL DP[2][1<<4];
map<int,set<int> >UNUSABLE;
bool Usable(const int r,const int c)
{
	const auto it=UNUSABLE.find(r);
	if(it==UNUSABLE.end())return true;
	return (it->second).find(c)==(it->second).end();
}
int GetNxtRow(const int row)
{
	const auto it=UNUSABLE.lower_bound(row);
	if(it==UNUSABLE.end())return R;
	return it->first;
}
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
void BuildMatrix()
{
	for(int source=0;source<(1<<C);source++)
	{
		for(int i=0;i<(1<<C);i++)DP[0][i]=DP[1][i]=0LL;
		Add(DP[0][source],1LL);
		int d=0;
		for(int col=0;col<C;d^=1,col++)
		{
			for(int s=0;s<(1<<C);s++)if(DP[d][s])
			{
				const LL value=DP[d][s];
				if(s&(1<<col))Add(DP[d^1][s-(1<<col)],value);
				else
				{
					static int target;
					if(TryH(s,target,col))Add(DP[d^1][target],value);
					if(TryV(s,target,col))Add(DP[d^1][target],value);
				}
				DP[d][s]=0LL;
			}
		}
		for(int target=0;target<(1<<C);target++)M.s[source][target]=DP[d][target];
	}
}
LL Solve()
{
	BuildMatrix();
//	for(int i=0;i<(1<<C);i++)
//	{
//		for(int j=0;j<(1<<C);j++)printf(" %d",M.s[i][j]);
//		puts("");
//	}
	for(int i=0;i<(1<<C);i++)DP[0][i]=DP[1][i]=0LL;
	Add(DP[0][0],1LL);
	int d=0;
	for(int row=0,col=0;row<R;d^=1)
	{
		const bool usable=Usable(row,col);
//		printf("row=%d,col=%d\n",row,col);
		for(int s=0;s<(1<<C);s++)if(DP[d][s])
		{
			const LL value=DP[d][s];
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
			DP[d][s]=0LL;
		}
		if(++col==C)
		{
			col=0,row++;
			const int nxtr=GetNxtRow(row);
			if(nxtr>row)
			{
				d^=1;
				Matrix result=Pow(M,nxtr-row);
				for(int i=0;i<(1<<C);i++)if(DP[d][i])
				{
					const LL value=DP[d][i];
					for(int j=0;j<(1<<C);j++)Add(DP[d^1][j],result.s[i][j]*value);
					DP[d][i]=0LL;
				}
//				printf("row: %d -> %d\n",row,nxtr);
				row=nxtr;
			}
		}
	}
//	for(int i=0;i<(1<<C);i++)
//	{
//		for(int j=0;j<(1<<C);j++)printf(" %d",M.s[i][j]);
//		puts("");
//	}
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
		printf("Case %d: %lld\n",kase++,Solve());
	}
	return 0;
}
