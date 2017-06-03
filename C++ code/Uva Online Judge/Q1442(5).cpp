#include<cstdio>
#include<queue>
using namespace std;
#define min(x,y) (x<y?x:y)
const int INF=2147483647;
int Z,N,F[1000000],C[1000000],MX[1000000],KASE=0;
struct Loc
{
	int h,idx,d;
	Loc(){}
	Loc(const int &h,const int &i,const int &d):h(h),idx(i),d(d){}
	bool operator<(const Loc &l)const{return h>l.h;}
};
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&Z);
	while(Z--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&F[i]);
		for(int i=0;i<N;i++)scanf("%d",&C[i]);
		priority_queue<Loc>pq;
		for(int i=0;i<N;i++)MX[i]=INF,pq.push(Loc(C[i],i,-1)),pq.push(Loc(C[i],i,1));
		while(!pq.empty())
		{
			Loc loc=pq.top();pq.pop();
			if(MX[loc.idx]>loc.h)MX[loc.idx]=loc.h;
			int i=loc.idx+loc.d;
			for(;i>=0&&i<N&&F[i]<=loc.h&&MX[i]>loc.h;i+=loc.d)MX[i]=loc.h;
			if(MX[i]<=loc.h)continue;
			for(;i>=0&&i<N&&F[i]>=F[i-loc.d];i+=loc.d)MX[i]=F[i];
			if(i<0||i>=N)continue;
			i-=loc.d;
			pq.push(Loc(F[i],i,loc.d));
		}
//		for(int i=0;i<N;i++)printf(" %d",MX[i]);puts("");
		int ans=0;
		for(int i=0;i<N;i++)ans+=MX[i]-F[i];
		printf("%d\n",ans);
	}
	return 0;
}
