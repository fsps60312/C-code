#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int INF=0x7fffffff;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
int N;
vector<pair<int,int> >S;
int DOWN_LEFT/*max(y)*/,UPON_LEFT/*min(x+y)*/,DOWN_RIGT/*max(x+y)*/,UPON_RIGT/*min(y)*/,LEFT/*min(x)*/,RIGT/*max(x)*/;
bool Check(const int x,const int y,const int n)
{
//	const int down_left=y+n,upon_left=x+y-n,down_rigt=x+y+n,upon_rigt=y-n,left=x-n,rigt=x+n;
	return DOWN_LEFT<y+n
		&& UPON_LEFT>x+y-n
		&& DOWN_RIGT<x+y+n
		&& UPON_RIGT>y-n
		&& LEFT>x-n
		&& RIGT<x+n; 
}
int AnchorDown()
{
	const int x=DOWN_RIGT-DOWN_LEFT,y=DOWN_LEFT;
	int l=1,r=100000;
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(Check(x,y-(mid-1),mid))r=mid;
		else l=mid+1;
	}
	return r;
}
int AnchorUpon()
{
	const int x=UPON_LEFT-UPON_RIGT,y=UPON_RIGT;
	int l=1,r=100000;
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(Check(x,y+(mid-1),mid))r=mid;
		else l=mid+1;
	}
	return r;
}
int AnchorDownLeft()
{
	const int x=LEFT,y=DOWN_LEFT;
	int l=1,r=100000;
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(Check(x+(mid-1),y-(mid-1),mid))r=mid;
		else l=mid+1;
	}
	return r;
}
int AnchorUponLeft()
{
	const int x=LEFT,y=UPON_LEFT-LEFT;
	int l=1,r=100000;
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(Check(x+(mid-1),y,mid))r=mid;
		else l=mid+1;
	}
	return r;
}
int AnchorDownRigt()
{
	const int x=RIGT,y=DOWN_RIGT-RIGT;
	int l=1,r=100000;
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(Check(x-(mid-1),y,mid))r=mid;
		else l=mid+1;
	}
	return r;
}
int AnchorUponRigt()
{
	const int x=RIGT,y=UPON_RIGT;
	int l=1,r=100000;
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(Check(x-(mid-1),y+(mid-1),mid))r=mid;
		else l=mid+1;
	}
	return r;
}
//int DOWN_LEFT/*max(y)*/,UPON_LEFT/*min(x+y)*/,DOWN_RIGT/*max(x+y)*/,UPON_RIGT/*min(y)*/,LEFT/*min(x)*/,RIGT/*max(x)*/;
static int D[9][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,-1}};
int AnchorLeftArrow()
{
	int n=RIGT-(UPON_LEFT-DOWN_LEFT);
	if(n%3!=0)n+=3;//return INF;
	n/=3,n++;
	const int x=(RIGT*2+(UPON_LEFT-DOWN_LEFT))/3,y=(DOWN_LEFT*2+(UPON_LEFT-RIGT))/3;
	for(int i=0;i<9;i++)if(Check(x+D[i][0],y+D[i][1],n))return n;
	return INF;
}
int AnchorRigtArrow()
{
	int n=(DOWN_RIGT-UPON_RIGT)-LEFT;
	if(n%3!=0)n+=3;//return INF;
	n/=3,n++;
	const int x=(LEFT*2+(DOWN_RIGT-UPON_RIGT))/3,y=(UPON_RIGT*2+(DOWN_RIGT-LEFT))/3;
	for(int i=0;i<9;i++)if(Check(x+D[i][0],y+D[i][1],n))return n;
	return INF;
}
long long GetArea(const int n)
{
	return 1LL+(0+6LL*(n-1LL))*n/2LL;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		S.clear();
		DOWN_LEFT=DOWN_RIGT=RIGT=-INF;
		UPON_LEFT=UPON_RIGT=LEFT=INF;
		for(int i=0,x,y;i<N;i++)
		{
			scanf("%d%d",&x,&y);
			S.push_back(make_pair(x,y));
			getmax(DOWN_LEFT,y);
			getmax(DOWN_RIGT,x+y);
			getmax(RIGT,x);
			getmin(UPON_LEFT,x+y);
			getmin(UPON_RIGT,y);
			getmin(LEFT,x);
		}
		static int kase=0;
//		printf("%d %d %d %d %d %d %d %d\n",AnchorDownLeft(),AnchorUponLeft(),AnchorDown(),AnchorDownRigt(),AnchorUponRigt(),AnchorUpon(),AnchorLeftArrow(),AnchorRigtArrow());
		printf("Case %d: %lld\n",++kase,GetArea(min(min(min(AnchorDownLeft(),AnchorUponLeft()),min(AnchorDown(),AnchorLeftArrow())),min(min(AnchorDownRigt(),AnchorUponRigt()),min(AnchorUpon(),AnchorRigtArrow())))));
//		if(kase==154)
//		{
//			printf("%d\n",N);
//			for(auto p:S)printf("%d %d\n",p.first,p.second);
//			break;
//		}
	}
	return 0;
}
