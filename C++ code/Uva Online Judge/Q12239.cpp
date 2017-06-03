#include<cstdio>
#include<cassert>
#include<set>
#include<algorithm>
using namespace std;
int N,B,S[90];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&B)==2&&(N||B))
	{
		for(int i=0;i<B;i++)scanf("%d",&S[i]);
		set<int>tmp;
		for(int i=0;i<B;i++)for(int j=0;j<B;j++)tmp.insert(abs(S[i]-S[j]));
		puts((int)tmp.size()==N+1?"Y":"N");
	}
	return 0;
}
