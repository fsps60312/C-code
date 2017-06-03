#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Point
{
	LL x,y;
	Point(){}
	Point(const LL _x,const LL _y):x(_x),y(_y){}
};
bool GetPointList(int &n,vector<Point>&s)
{
	s.clear();
	if(scanf("%d",&n)!=1)return false;
	if(n==0)return false;
	for(int i=0,x,y;i<n;i++)scanf("%d%d",&x,&y),y*=-1,s.push_back(Point(x,y));
	return true;
}
struct Vector
{
	static int default_type;
	LL x,y;
	int type;
	Vector(){}
	Vector(const LL _x,const LL _y):x(_x),y(_y),type(Vector::default_type){}
};
int Vector::default_type;
Vector operator-(const Point &a,const Point &b){return Vector(a.x-b.x,a.y-b.y);}
int Quadrant(const Vector &a)
{
	if(a.x>0&&a.y>=0)return 1;
	if(a.x<=0&&a.y>0)return 2;
	if(a.x<0&&a.y<=0)return 3;
	if(a.x>=0&&a.y<0)return 4;
	assert(0);return -1;
}
LL Cross(const Vector &a,const Vector &b){return a.y*b.x-b.y*a.x;}
bool CmpAngle(const Vector &a,const Vector &b)
{
	if(Quadrant(a)!=Quadrant(b))return Quadrant(a)<Quadrant(b);
//	const int q=Quadrant(a);
//	if(q==1||q==3)return a.y*b.x<b.y*a.x;//a.y/a.x<b.y/b.x
//	else return a.x*b.y>b.x*a.y;//-a.x/a.y<-b.x/b.y
	return Cross(a,b)<0;//a.y*b.x<b.y*a.x;
}
struct Counter
{
	LL fsum,isum,lsum,ans;
	Counter(){fsum=isum=lsum=ans=0;}
	void push_flag()
	{
		++fsum;
		lsum+=isum;
//		puts("push_flag");
	}
	void pop_flag()
	{
		--fsum;
//		puts("pop_flag");
	}
	void push_item()
	{
		ans+=lsum;
		++isum;
//		puts("push_item");
	}
	void pop_item()
	{
		lsum-=fsum;
		--isum;
//		puts("pop_item");
	}
};
int N,M,T;
vector<Point>DRONE,FORT,TOWER;
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("ambitious.in","r",stdin);
	freopen("ambitious.out","w",stdout);
	while(GetPointList(N,DRONE))
	{
		assert(GetPointList(M,FORT)&&GetPointList(T,TOWER));
		LL ans=0;
		for(const Point fort:FORT)
		{
			vector<Vector>s;
			Vector::default_type=0;
			for(const Point &p:TOWER)s.push_back(p-fort);
			Vector::default_type=1;
			for(const Point &p:DRONE)s.push_back(p-fort);
			sort(s.begin(),s.end(),[](Vector a,Vector b)->bool{return CmpAngle(a,b);});
			for(int i=0;i<T+N;i++)s.push_back(s[i]);
			Counter cnt;
			int l=0,r=-1;
			while(r+1<T+N&&Cross(Vector(1,0),s[r+1])<=0)
			{
				++r;
				s[r].type==0?cnt.push_item():cnt.push_flag();
			}
//			printf("r=%d\n",r);
			for(;r+1<(T+N)*2&&(r+1<(T+N)||Cross(Vector(1,0),s[r+1])<=0);)
			{
				++r;
				for(;Cross(s[l],s[r])>0;)
				{
					s[l].type==0?cnt.pop_item():cnt.pop_flag();
					++l;
				}
//				printf(">l=%d,r=%d\n",l,r);
				s[r].type==0?cnt.push_item():cnt.push_flag();
			}
//			printf("l=%d,r=%d\n",l,r);
			ans+=cnt.ans;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
