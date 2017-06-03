#include<cstdio>
#include<queue>
using namespace std;
#define min(x,y) (x<y?x:y)
const int INF=2147483647;
int Z,N,F[1000000],C[1000000],MX[1000000],KASE=0;
struct Loc
{
	int h,idx;
	Loc(){}
	Loc(const int &h,const int &i):h(h),idx(i){}
	bool operator<(const Loc &l)const{return h>l.h;}
};
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&Z);
	while(Z--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&F[i]);
		for(int i=0;i<N;i++)scanf("%d",&C[i]);
		priority_queue<Loc>pq;
		for(int i=0;i<N;i++)MX[i]=INF,pq.push(Loc(C[i],i));
		while(!pq.empty())
		{
			Loc loc=pq.top();pq.pop();
			if(MX[loc.idx]<=loc.h)continue;
			MX[loc.idx]=loc.h;
			int l=loc.idx-1,r=loc.idx+1;
			for(;l>=0&&F[l]<=loc.h&&MX[l]>loc.h;l--)MX[l]=loc.h;
			for(;l>=0&&F[l]>=F[l+1];l--)MX[l]=F[l];
			for(;r<N&&F[r]<=loc.h&&MX[r]>loc.h;r++)MX[r]=loc.h;
			for(;r<N&&F[r-1]<=F[r];r++)MX[r]=F[r];
		}
		for(int i=0;i<N;i++)printf(" %d",MX[i]);puts("");
		int ans=0;
		for(int i=0;i<N;i++)ans+=MX[i]-F[i];
		printf("%d\n",ans);
	}
	return 0;
}
