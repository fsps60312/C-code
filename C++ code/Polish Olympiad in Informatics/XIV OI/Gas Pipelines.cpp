#include<cstdio>
#include<cassert>
#include<map>
#include<algorithm>
using namespace std;
struct Point
{
	int ID,X,Y;
};
bool operator<(const Point &a,const Point &b){return a.X<b.X;}
int N;
Point S[50000],T[50000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		long long ans=0;
		for(int i=0;i<N;i++)scanf("%d%d",&S[i].X,&S[i].Y),S[i].ID=i+1,ans-=S[i].X,ans+=S[i].Y;
		for(int i=0;i<N;i++)scanf("%d%d",&T[i].X,&T[i].Y),T[i].ID=i+1,ans+=T[i].X,ans-=T[i].Y;
		printf("%lld\n",ans);
		sort(S,S+N),sort(T,T+N);
		multimap<int,int>m;
		for(int i=N-1,j=N-1,x=100000;x>=0;x--)
		{
			for(;j!=-1&&T[j].X==x;--j)m.insert(make_pair(T[j].Y,j));
			for(;i!=-1&&S[i].X==x;--i)
			{
				multimap<int,int>::iterator it=m.upper_bound(S[i].Y);
				assert(it!=m.begin());
				--it;
				printf("%d %d\n",S[i].ID,T[it->second].ID);
				m.erase(it);
			}
		}
	}
	return 0;
}
