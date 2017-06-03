#include<cstdio>
#include<cstdlib>
#include<ctime>
#define min(x,y) (x)<(y)?(x):(y)
#define LL long long
using namespace std;
struct Treap
{
    LL sz,pri,v,sma;
    LL addv,rev;
    Treap *lch,*rch;
    Treap(LL v):v(v),sma(v),lch(NULL),rch(NULL),pri(rand()),sz(1),addv(0),rev(0){}
};
LL sz(Treap* &a){return a?a->sz:0;}
LL rank(Treap* &a){return 1+sz(a->lch);}
LL sma(Treap* &a){return a?a->sma+a->addv:2147483647;}
void putup(Treap* &a)
{
    a->sz=sz(a->lch)+1+sz(a->rch);
    a->sma=min(min(sma(a->lch),a->v),sma(a->rch));
}
void putdown(Treap* &a)
{
    if(a->addv)
    {
        LL &addv=a->addv;
        a->v+=addv;
        if(a->lch)a->lch->addv+=addv;
        if(a->rch)a->rch->addv+=addv;
        addv=0;
    }
    if(a->rev)
    {
        Treap *b=a->lch;
        a->lch=a->rch;
        a->rch=b;
        if(a->lch)a->lch->rev^=1;
        if(a->rch)a->rch->rev^=1;
        a->rev=0;
    }
    putup(a);
}
void show(Treap* &a)
{
	if(!a)return;
	putdown(a);
	show(a->lch);
	printf(" %lld",a->v);
	show(a->rch);
}
Treap *merge(Treap *a,Treap *b)
{
    if(!a||!b)return a?a:b;
    if(a->pri>b->pri)
    {
        putdown(a);
        a->rch=merge(a->rch,b);
        putup(a);
        return a;
    }
    else
    {
        putdown(b);
        b->lch=merge(a,b->lch);
        putup(b);
        return b;
    }
}
void split(Treap *t,LL r,Treap* &a,Treap* &b)
{
    if(!t){a=b=NULL;return;}
    putdown(t);
    if(r>=rank(t))
    {
        a=t;
        putdown(a);
        split(t->rch,r-rank(t),a->rch,b);
        putup(a);
    }
    else
    {
        b=t;
        putdown(b);
        split(t->lch,r,a,b->lch);
        putup(b);
    }
}
void insert(Treap* &t,LL r,LL v)
{
    Treap *a,*b;
    //printf("origin:");show(t);printf("\n");
    split(t,r,a,b);
    //printf("split%lld:\na:",r);
    //show(a);printf("\nb:");show(b);printf("\n");
    t=merge(merge(a,new Treap(v)),b);
}
void remove(Treap* &t,LL r)
{
    Treap *a,*b,*c;
    split(t,r,b,c);
    split(b,r-1,a,b);
    t=merge(a,c);
}
void add(Treap* &t,LL l,LL r,LL v)
{
    Treap *a,*b,*c;
    split(t,r,b,c);
    split(b,l-1,a,b);
    b->addv+=v;
    t=merge(merge(a,b),c);
}
LL mod(LL a,LL b){return (a%b+b)%b;}
void cycle(Treap* &t,LL l,LL r,LL d)
{
    d=mod(d,r-l+1);
    Treap *ta,*tb,*tc,*td;
    split(t,r,tc,td);
    split(tc,r-d,tb,tc);
    split(tb,l-1,ta,tb);
    t=merge(merge(ta,tc),merge(tb,td));
}
    Treap *rt=NULL;
void reverse(Treap* &t,LL l,LL r)
{
    Treap *a,*b,*c;
    split(t,r,b,c);
    split(b,l-1,a,b);
    //if(b==NULL)printf("rt==%lld\n",sz(rt));
    b->rev^=1;
    t=merge(merge(a,b),c);
}
LL asksma(Treap* &t,LL l,LL r)
{
    Treap *a,*b,*c;
    //printf("origin:");show(t);printf("\n");
    split(t,r,b,c);
    split(b,l-1,a,b);
    //printf("split%lld:\na:",r);
    //show(a);printf("\nb:");show(b);printf("\nc:");show(c);printf("\n");
    //putdown(b),putup(b);
    LL ans=sma(b);
    t=merge(merge(a,b),c);
    return ans;
}
int main()
{
	srand(time(NULL));
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
    LL n;
	while(scanf("%lld",&n)==1)
	{
	    while(n--)
	    {
	        LL a;scanf("%lld",&a);
	        insert(rt,sz(rt),a);
	    }
	    //show(rt);printf("\n");
	    scanf("%lld",&n);
	    char tstr[8];
	    while(n--)
	    {
	        scanf("%s",tstr);
	        //printf("%s\n",tstr);
	        switch(tstr[0])
	        {
	            case'A':
	            {
	                LL l,r,v;scanf("%lld%lld%lld",&l,&r,&v);
	                add(rt,l,r,v);
	            }break;
	            case'I':
	            {
	            	LL pre=sz(rt);
	                LL r,v;scanf("%lld%lld",&r,&v);
	                insert(rt,r,v);
	                if(sz(rt)!=pre+1)
	                {
	                	show(rt);printf("\n");
	                	printf("error insert%lldto%lld %lld->%lld\n",v,r,pre,sz(rt));
	                	return 0;
					}
	            }break;
	            case'D':
	            {
	            	LL pre=sz(rt);
	                LL r;scanf("%lld",&r);
	                remove(rt,r);
	                if(sz(rt)!=pre-1)
	                {
	                	show(rt);printf("\n");
	                	printf("error delete%lld %lld->%lld\n",r,pre,sz(rt));
	                	return 0;
					}
	            }break;
	            case'M':
	            {
	                LL l,r;scanf("%lld%lld",&l,&r);
	                printf("%lld\n",asksma(rt,l,r));
	            }break;
	            default:
	            {
	                if(tstr[3]=='E')
	                {
	                    LL l,r;scanf("%lld%lld",&l,&r);
	                    reverse(rt,l,r);
	                }
	                else
	                {
	                    LL l,r,d;scanf("%lld%lld%lld",&l,&r,&d);
	                    cycle(rt,l,r,d);
	                }
	            }break;
	        }
	        //show(rt);printf("\n");
	    }
	}
    return 0;
}
