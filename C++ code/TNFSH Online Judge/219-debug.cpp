#include<bits/stdc++.h>
using namespace std;
struct node{
	node *l,*r;
	int s;
	bool rev;
	char c;
	node(char d):l(0),r(0),s(1),rev(0),c(d){}
	node(node &p):l(p.l),r(p.r),s(p.s),rev(p.rev),c(p.c){}
	inline void up(){
		s=1+(l?l->s:0)+(r?r->s:0);
	}
	inline void down(){
		if(!rev)return;
		swap(l,r);
		if(l){
			l=new node(*l);
			l->rev^=1;
		}
		if(r){
			r=new node(*r);
			r->rev^=1;
		}
		rev=0;
	}
};
inline int ran(){
	static int x=20150211;
	return x=(x*0xdefaced+1)&INT_MAX;
}
node *merge(node *a,node *b){
	if(!a||!b)return a?a:b;
	if(ran()%(a->s+b->s)<a->s){
		a=new node(*a);
		a->down();
		a->r=merge(a->r,b);
		a->up();
		return a;
	}else{
		b=new node(*b);
		b->down();
		b->l=merge(a,b->l);
		b->up();
		return b;
	}
}
int size(node *o){return o?o->s:0;}
void split(node *o,node *&a,node *&b,int k){
	if(!o)a=b=0;
	else{
		o=new node(*o);
		o->down();
		if(k<=size(o->l)){
			b=o;
			split(o->l,a,b->l,k);
		}else{
			a=o;
			split(o->r,a->r,b,k-size(o->l)-1);
		}
		o->up();
	}
}
void dfs(node *p,bool rev){
	if(!p)return;
	rev^=p->rev;
	if(rev){
		dfs(p->r,rev);
		putchar(p->c);
		dfs(p->l,rev);
	}else{
		dfs(p->l,rev);
		putchar(p->c);
		dfs(p->r,rev);
	}
}
node *build(char *s,int l,int r){
	int mid=(l+r)>>1;
	node *p=new node(s[mid]);
	if(l<=mid-1)p->l=build(s,l,mid-1);
	if(mid+1<=r)p->r=build(s,mid+1,r);
	p->up();
	return p;
}
int t,n,m;
int e,l,r;
char s[50005];
node *root,*a,*b,*c,*d;
int main(){
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%s",&n,&m,s);
		root=build(s,0,n-1);
		while(m--){
			scanf("%d%d%d",&e,&l,&r);
			split(root,a,b,l-1);
			split(b,c,d,r-l+1);
			if(e==1){
				dfs(c,0);puts("");
			}else if(e==2){
				root=merge(a,merge(c,b));
			}else{
				c->rev^=1;
				root=merge(a,merge(c,d));
			}
		}
	}
	return 0;
}
