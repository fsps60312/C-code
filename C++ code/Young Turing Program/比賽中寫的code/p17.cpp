//{{{
#include <bits/stdc++.h>
using namespace std;
//types
typedef long long ll;
typedef pair<int,int> pii;
//input
bool SR(int &_x){return scanf("%d",&_x)==1;}bool SR(ll &_x){return scanf("%lld",&_x)==1;}
bool SR(double &_x){return scanf("%lf",&_x)==1;}bool SR(char *_s){return scanf("%s",_s)==1;}
bool RI(){return true;}
template<typename I,typename... T>bool RI(I &_x,T&... _tail){return SR(_x) && RI(_tail...);}
//output
void SP(const int _x){printf("%d",_x);}void SP(const ll _x){printf("%lld",_x);}
void SP(const double _x){printf("%.16lf",_x);}void SP(const char *s){printf("%s",s);}
void PL(){puts("");}
template<typename I,typename... T>void PL(const I _x,const T... _tail)
{SP(_x);if(sizeof...(_tail)) putchar(' ');PL(_tail...);}
//macro
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
#define REP(i,n) for(int i=0;i<int(n);i++)
#define REP1(i,a,b) for(int i=(a);i<=int(b);i++)
#define pb push_back
#define mkp make_pair
#define F first
#define S second
//debug
#ifdef darry140
template<typename I>
void _DOING(const char *_s,I&& _x){cerr<<_s<<"="<<_x<<endl;}//without ','
template<typename I,typename... T>
void _DOING(const char *_s,I&& _x,T&&... _tail)//with ','
{
    int _c=0;
    static const char _bra[]="({[";
    static const char _ket[]=")}]";
    while(*_s!=',' || _c!=0)//eg. mkp(a,b)
    {
        if(strchr(_bra,*_s)) _c++;
        if(strchr(_ket,*_s)) _c--;
        cerr<<*_s++;
    }
    cerr<<"="<<_x<<", ";
    _DOING(_s+1,_tail...);
}
#define debug(...) do{\
    fprintf(stderr,"%s:%d - ",__PRETTY_FUNCTION__,__LINE__);\
    _DOING(#__VA_ARGS__,__VA_ARGS__);\
}while(0)
template<typename It>
ostream& _OUTC(ostream &_s,It _b,It _e)//container
{
    _s<<"{";
    for(auto _it=_b;_it!=_e;_it++) _s<<(_it==_b?"":" ")<<*_it;
    _s<<"}";
    return _s;
}
template<typename A,typename B>
ostream& operator <<(ostream&_s, const pair<A,B> &_p){return _s<<"("<<_p.F<<","<<_p.S<<")";}
template<typename A,typename B>
ostream& operator <<(ostream&_s, const map<A,B> &_c){return _OUTC(_s,ALL(_c));}
template<typename T>
ostream& operator <<(ostream&_s, const set<T> &_c){return _OUTC(_s,ALL(_c));}
template<typename T>
ostream& operator <<(ostream&_s, const vector<T> &_c){return _OUTC(_s,ALL(_c));}
#else
#define debug(...)
#endif
//}}}
struct Q
{
	ll up,dn;
	Q():up(0),dn(1){}
	Q(const ll &x):up(x),dn(1){}
	Q(const ll &a,const ll &b):up(a),dn(b){
		ll g=__gcd(abs(a),abs(b));
		up/=g;dn/=g;
		if(dn<0) up*=-1,dn*=-1;
	}
	Q operator +(const Q &i) const
	{
		return Q(up*i.dn + dn*i.up,dn*i.dn);
	}
	Q operator -(const Q &i) const
	{
		return Q(up*i.dn - dn*i.up,dn*i.dn);
	}
	Q operator *(const Q &i) const
	{
		return Q(up*i.up,dn*i.dn);
	}
	Q operator /(const Q &i) const
	{
		return Q(up*i.dn,dn*i.up);
	}
};
const int maxn=10;
int n;
vector<Q> a[maxn];
void read()
{
	RI(n);
	REP(i,n) a[i].resize(n+1);
	REP(i,n) REP(j,n+1)
	{
		int x;RI(x);
		a[i][j]=x;
	}
}
void build()
{
	int h=0;
	REP(i,n)
	{
		REP1(j,h+1,n-1) if(a[j][i].up)
			a[j].swap(a[h]);
		if(a[h][i].up==0) continue;
		REP1(j,h+1,n-1)
		{
			Q fac=a[j][i]/a[h][i];
			REP(k,n+1) a[j][k]=a[j][k]-a[h][k]*fac;
		}
		h++;
	}
}
bool isna()
{
	REP(i,n)
	{
		bool cur=1;
		REP(j,n) cur&=(a[i][j].up==0);
		cur&=(a[i].back().up!=0);
		if(cur) return 1;
	}
	return 0;
}
bool isinf()
{
	REP(i,n)
	{
		bool cur=1;
		REP(j,n) cur&=(a[i][j].up==0);
		cur&=(a[i].back().up==0);
		if(cur) return 1;
	}
	return 0;
}
void sol()
{
	if(isna()) PL("NA");
	else if(isinf()) PL("INF");
	else
	{
		for(int i=n-1;i>=0;i--) REP(j,i)
		{
			Q fac=a[j][i]/a[i][i];
			REP(k,n+1) a[j][k]=a[j][k]-a[i][k]*fac;
		}
		REP(i,n)
		{
			Q x=a[i].back()/a[i][i];
			if(x.dn!=1) printf("%lld/%lld%c",x.up,x.dn," \n"[i==n-1]);
			else printf("%lld%c",x.up," \n"[i==n-1]);
		}
	}
}
int main()
{
	read();
	build();
	sol();
    return 0;
}




































/*End Of File*/


