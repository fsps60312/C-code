#include<cstdio>
#include<cstdlib>
#include<ctime>
#define min(x,y) (x)<(y)?(x):(y)
using namespace std;
struct Treap
{
    int sz,pri,v,sma;
    int addv,rev;
    Treap *lch,*rch;
    Treap(int v):v(v),sma(v),lch(NULL),rch(NULL),pri(rand()),sz(1),addv(0),rev(0){}
};
void show(Treap* &a)
{
	if(!a)return;
	show(a->lch);
	printf(" %d",a->v);
	show(a->rch);
}
int sz(Treap* &a){return a?a->sz:0;}
int rank(Treap* &a){return 1+sz(a->lch);}
int sma(Treap* &a){return a?a->sma:2147483647;}
void putup(Treap* &a)
{
    a->sz=sz(a->lch)+1+sz(a->rch);
    a->sma=min(min(sma(a->lch),a->v),sma(a->rch));
}
void putdown(Treap* &a)
{
    if(a->addv)
    {
        int &addv=a->addv;
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
        a->rev=0;
    }
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
void split(Treap *t,int r,Treap* &a,Treap* &b)
{
    if(!t){a=b=NULL;return;}
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
void insert(Treap* &t,int r,int v)
{
    Treap *a,*b;
    //printf("origin:");show(t);printf("\n");
    split(t,r,a,b);
    //printf("split%d:\na:",r);
    //show(a);printf("\nb:");show(b);printf("\n");
    t=merge(merge(a,new Treap(v)),b);
}
void remove(Treap* &t,int r)
{
    Treap *a,*b,*c;
    split(t,r,b,c);
    split(b,r-1,a,b);
    t=merge(a,c);
}
void add(Treap* &t,int l,int r,int v)
{
    Treap *a,*b,*c;
    split(t,r,b,c);
    split(b,l-1,a,b);
    b->addv+=v;
    t=merge(merge(a,b),c);
}
void cycle(Treap* &t,int l,int r,int d)
{
    d%=(r-l+1);
    Treap *ta,*tb,*tc,*td;
    split(t,r,tc,td);
    split(tc,r-d,tb,tc);
    split(tb,l-1,ta,tb);
    t=merge(merge(ta,tc),merge(tb,td));
}
void reverse(Treap* &t,int l,int r)
{
    Treap *a,*b,*c;
    split(t,r,b,c);
    split(b,l-1,a,b);
    b->rev=1;
    t=merge(merge(a,b),c);
}
int asksma(Treap* &t,int l,int r)
{
    Treap *a,*b,*c;
    //printf("origin:");show(t);printf("\n");
    split(t,r,b,c);
    split(b,l-1,a,b);
    //printf("split%d:\na:",r);
    //show(a);printf("\nb:");show(b);printf("\nc:");show(c);printf("\n");
    int ans=b->sma;
    t=merge(merge(a,b),c);
    return ans;
}
int main()
{
    Treap *rt=NULL;
    int n;scanf("%d",&n);
    while(n--)
    {
        int a;scanf("%d",&a);
        insert(rt,sz(rt),a);
    }
    //show(rt);printf("\n");
    scanf("%d",&n);
    char tstr[8];
    while(n--)
    {
        scanf("%s",tstr);
        switch(tstr[0])
        {
            case'A':
            {
                int l,r,v;scanf("%d%d%d",&l,&r,&v);
                add(rt,l,r,v);
            }break;
            case'I':
            {
                int r,v;scanf("%d%d",&r,&v);
                insert(rt,r,v);
            }break;
            case'D':
            {
                int r;scanf("%d",&r);
                remove(rt,r);
            }break;
            case'M':
            {
                int l,r;scanf("%d%d",&l,&r);
                printf("%d\n",asksma(rt,l,r));
            }break;
            default:
            {
                if(tstr[3]=='E')
                {
                    int l,r;scanf("%d%d",&l,&r);
                    reverse(rt,l,r);
                }
                else
                {
                    int l,r,d;scanf("%d%d%d",&l,&r,&d);
                    cycle(rt,l,r,d);
                }
            }break;
        }
        //show(rt);printf("\n");
    }
    return 0;
}
