#include<cstdio>
#include<map>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Line
{
	int y,x1,x2,v;
	Line(){}
	Line(const int _y,const int _x1,const int _x2,const int _v):y(_y),x1(_x1),x2(_x2),v(_v){}
	bool operator<(const Line &l)const{return y<l.y;}
};
vector<Line>LINE;
vector<int>X; 
void ReIndex()
{
	map<int,int>idx;
	for(const auto &s:LINE)idx[s.x1]=idx[s.x2]=-1;
	int cnt=0;
	X.clear();
	for(auto &it:idx)it.second=cnt++,X.push_back(it.first);
	for(auto &s:LINE)s.x1=idx[s.x1],s.x2=idx[s.x2];
}
int LAYER[4*60000],REACH[4*60000][11];
int T,N,K;
void Build(const int id,const int l,const int r)
{
	for(int i=0;i<=K;i++)REACH[id][i]=0;
	REACH[id][0]=X[r+1]-X[l];
	LAYER[id]=0;
	if(l==r)return;
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
}
void Rebuild(const int id)
{
	for(int i=0;i<=K;i++)REACH[id][i]=0;
	for(int i=0;i<=K;i++)
	{
		const int j=min(i+LAYER[id],K);
		REACH[id][j]+=REACH[id*2][i]+REACH[id*2+1][i];
	}
}
void Add(const int id,const int l,const int r,const int lb,const int rb,const int v)
{
	if(r<lb||rb<l)return;
	if(lb<=l&&r<=rb)
	{
		if(!v)return;
		LAYER[id]+=v;
		assert(LAYER[id]>=0);
		if(l==r)
		{
			for(int i=0;i<=K;i++)REACH[id][i]=0;
			REACH[id][min(LAYER[id],K)]=X[r+1]-X[l];
		}
		else Rebuild(id);
		return;
	}
	const int mid=(l+r)/2;
	Add(id*2,l,mid,lb,rb,v),Add(id*2+1,mid+1,r,lb,rb,v);
	Rebuild(id);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&K);
		LINE.clear();
		for(int i=0,x1,x2,y1,y2;i<N;i++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2),assert(x1<=x2&&y1<=y2);
			LINE.push_back(Line(y1,x1,x2+1,1)),LINE.push_back(Line(y2+1,x1,x2+1,-1));
		}
		ReIndex();
		sort(LINE.begin(),LINE.end());
		assert(X.size()>=2);
		Build(1,0,X.size()-2);
		LL prey=-1LL;
		LL ans=0LL;
		for(int i=0;;)
		{
			const int y=LINE[i].y;
//			printf("%d*%d\n",REACH[1][K],(y-prey));
			ans+=REACH[1][K]*(y-prey);
			while(i<LINE.size()&&LINE[i].y==y)
			{
				const Line &l=LINE[i++];
				Add(1,0,X.size()-2,l.x1,l.x2-1,l.v);
//				printf("(%d,%d):%d\n",l.x1,l.x2,l.v);
			}
			if(i==LINE.size())break;
			prey=y;
		}
		static int kase=1;
		printf("Case %d: %lld\n",kase++,ans);
	}
	return 0;
}
