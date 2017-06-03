#include<cstdio>
#include<cstdlib>
struct Treap
{
	int val,pri,sz;
	Treap *l,*r;
	Treap(int _val):val(_val),sz(1),pri(rand()),l(NULL),r(NULL){}
};
void show(Treap *t)
{
	if(!t)return;
	show(t->l);
	printf(" %d",t->val);
	show(t->r);
}
int sz(Treap *t){return t?t->sz:0;}
void pull(Treap* &t){t->sz=sz(t->l)+1+sz(t->r);}
Treap *merge(Treap *a,Treap *b)
{
	if(!a||!b)return a?a:b;
	if(a->pri>b->pri)
	{
		a->r=merge(a->r,b);
		pull(a);
		return a;
	}
	else
	{
		b->l=merge(a,b->l);
		pull(b);
		return b;
	}
}
int rank(Treap *t){return t?sz(t->l)+1:0;}
void split(Treap *t,int _r,Treap* &a,Treap* &b)
{
	if(!t){a=b=NULL;return;}
	int r=rank(t);
	if(r<=_r)
	{
		a=t;
		split(t->r,_r-r,a->r,b);
		pull(a);
	}
	else
	{
		b=t;
		split(t->l,_r,a,b->l);
		pull(b);
	}
}
Treap *insert(Treap* t,int r,int val)
{
	Treap *a,*b;
	//printf("a\n");
	split(t,r,a,b);
	//printf("r=%d\na:",r);show(a);
	//printf("\nb:");show(b);printf("\n");
	//printf("b\n");
	return merge(merge(a,new Treap(val)),b);
}
Treap *remove(Treap* t,int r)
{
	Treap *a,*b,*c;
	split(t,r,b,c);
	split(b,r-1,a,b);
	return merge(a,c);
}
int N,K,M;
int main()
{
	srand(2853);
	Treap *rt;
	while(scanf("%d%d%d",&N,&K,&M)==3&&(N||K||M))
	{
		M--;
		rt=NULL;
		for(int i=0;i<N;i++)rt=insert(rt,sz(rt),i);
		while(N>1)
		{
			if(N!=sz(rt))printf("->%d %d\n",N,sz(rt));
			//show(rt);printf("\n");
			//printf("M=%d\n",M+1);
			rt=remove(rt,M+1);
			//show(rt);printf("\n");
			N--;
			M+=K-1;
			M%=N;
		}
		printf("%d\n",rt->val+1);
	}
	return 0;
}
