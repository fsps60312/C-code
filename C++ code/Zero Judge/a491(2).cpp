#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
int T,R,C;
struct Cargo
{
	LL cnt;
	int loc;
	Cargo(){}
	Cargo(LL c,int l):cnt(c),loc(l){}
};
vector<Cargo>X,Y;
inline void GetLL(LL &v)
{
	const int zero='0',nine='9';
	int c=getchar();
	while(c<zero||c>nine)c=getchar();
	v=0LL;
	while(c>=zero&&c<=nine)v*=10LL,v+=(c-zero),c=getchar();
}
inline void GetInt(int &v)
{
	const int zero='0',nine='9';
	int c=getchar();
	while(c<zero||c>nine)c=getchar();
	v=0;
	while(c>=zero&&c<=nine)v*=10,v+=(c-zero),c=getchar();
}
LL GRID[2000][2000];
int main()
{
//	freopen("in.txt","r",stdin);
	GetInt(T);
	while(T--)
	{
		GetInt(R),GetInt(C);
		X.clear(),Y.clear();
		LL sum=0LL;
		for(int i=0;i<R;i++)
		{
			LL ts=0LL;
			for(int j=0;j<C;j++)
			{
				LL &v=GRID[i][j];
				GetLL(v);
				if(v==0LL)continue;
				sum+=v;
				ts+=v;
			}
			Y.push_back(Cargo(ts,i));
		}
		for(int j=0;j<C;j++)
		{
			LL ts=0LL;
			for(int i=0;i<R;i++)ts+=GRID[i][j];
			X.push_back(Cargo(ts,j));
		}
		LL ans=0LL;
		int yans,xans;
		LL now=0LL;
		for(int i=0;i<Y.size();i++)
		{
			now+=Y[i].cnt;
			if(now>=(sum+1LL)>>1)
			{
				yans=Y[i].loc;
				for(int j=0;j<Y.size();j++)ans+=(LL)abs(Y[j].loc-yans)*Y[j].cnt;
				break;
			}
		}
		now=0LL;
		for(int i=0;i<X.size();i++)
		{
			now+=X[i].cnt;
			if(now>=(sum+1LL)>>1)
			{
				xans=X[i].loc;
				for(int j=0;j<X.size();j++)ans+=(LL)abs(X[j].loc-xans)*X[j].cnt;
				break;
			}
		}
		printf("%lld %lld\n%lld\n",yans+1LL,xans+1LL,ans*100LL);
	}
	return 0;
}
