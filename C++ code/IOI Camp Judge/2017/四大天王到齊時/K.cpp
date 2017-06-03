#include<cstdio>
#include<cassert>
using namespace std;
bool Solve(const int m,const int n)
{
	for(int i=2;i*i<=m;i++)if(m%i==0)
	{
		if(Solve(n,m/i))return false;
		else return true;
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int T;scanf("%d",&T);
	while(T--)
	{
		int N,M;
		scanf("%d%d",&N,&M);
		const bool a=Solve(M,N)/*cut M*/,b=Solve(N,M);
		if(!a&&!b)puts("FL");
		else if(a&&!b)puts("V");
		else if(!a&&b)puts("H");
		else assert(0);
	}
	return 0;
}
