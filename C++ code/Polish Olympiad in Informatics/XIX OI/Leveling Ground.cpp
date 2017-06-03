#include<cstdio>
#include<cassert>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=1e9;
struct Vector
{
	LL x,y;
	Vector(){}
	Vector(const LL _x,const LL _y):x(_x),y(_y){}
	Vector operator*(const LL v)const{return Vector(x*v,y*v);}
	Vector operator+(const Vector &v)const{return Vector(x+v.x,y+v.y);}
	Vector operator-(const Vector &v)const{return Vector(x-v.x,y-v.y);}
	LL Abs()const{return abs(x)+abs(y);}
};
struct Point
{
	LL x,y;
	Point(){}
	Point(const LL _x,const LL _y):x(_x),y(_y){}
	Vector operator-(const Point &p)const{return Vector(x-p.x,y-p.y);}
	void operator+=(const Vector &v){x+=v.x,y+=v.y;}
	bool Is(const Point &p)const{return x==p.x&&y==p.y;}
};
const Point O=Point(0,0);
struct Adjust
{
	Vector a,b;
	Adjust(){}
	Adjust(const Vector &_a,const Vector &_b):a(_a),b(_b){}
	LL Cost()const{return b.Abs()-a.Abs();}
	Adjust Move()const{return Adjust(b,b+(b-a));}
	bool operator<(const Adjust &v)const{return Cost()>v.Cost();}
};
void Exgcd(const LL a,const LL b,LL &g,Vector &ans)
{
	if(b==0){g=a,ans=Vector(1,0);return;}
	else
	{
		Vector tmp;
		Exgcd(b,a%b,g,tmp);
		ans=Vector(tmp.y,tmp.x);
		ans.y-=a/b*ans.x;
	}
}
int N;
LL A,B,G,S[100001];
Vector LINE,VECT;
LL Solve()
{
	Exgcd(A,B,G,LINE);
	for(int i=0;i<N;i++)
	{
		if(S[i]%G!=0)return -1;
		S[i]/=G;
	}
	S[N]=0;
	VECT=Vector(B/G,-A/G);
	Point now=O;
	LL ans=0LL;
	priority_queue<Adjust>to_add,to_sub;
	for(int i=0;i<=N;i++)
	{
		LL l=-INF,r=INF;
		const Vector &v=LINE*(S[i]-(i==0?0:S[i-1]));
		while(l+3<=r)
		{
			const LL bl=((l+INF)*2+(r+INF))/3-INF,br=((l+INF)+(r+INF)*2)/3-INF;
			if((v+VECT*bl).Abs()>(v+VECT*br).Abs())l=bl;
			else r=br;
		}
		Vector mn=v+VECT*l;
		for(LL t=l+1;t<=r;t++)if((v+VECT*t).Abs()<mn.Abs())mn=v+VECT*t;
		now+=mn,ans+=mn.Abs();
		to_add.push(Adjust(mn,mn+VECT)),to_sub.push(Adjust(mn,mn-VECT));
	}
	while(!now.Is(O))
	{
//		printf("now=(%lld,%lld)\n",now.x,now.y);
		priority_queue<Adjust>&pq=(((now-O)+VECT).Abs()<((now-O)-VECT).Abs()?to_add:to_sub);
		const Adjust p=pq.top();pq.pop();
		now+=p.b-p.a,ans+=p.Cost();
		pq.push(p.Move());
	}
	assert(ans%2==0);
	return ans/2;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%lld%lld",&N,&A,&B)==3)
	{
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		printf("%lld\n",Solve());
	}
	return 0;
}
