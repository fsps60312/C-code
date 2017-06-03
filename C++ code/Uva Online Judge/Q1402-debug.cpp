#include<iostream>
 #include<cstdio>
 #include<algorithm>
 #include<cstring>
 #include<cmath>
 #include<queue>
 #include<stack>
 #include<vector>
 using namespace std;
 const int inf=1E9;
 struct node
 {
     node *ch[2];
     node *pre,*mini;
     int s,v,flip,o;
friend bool  operator < (node &a,node &b)
{
return a.v<b.v || (a.v==b.v && a.o<b.o);
}
     void maintain()
     {
         s=1;
mini=this;
         if(ch[0]) s+=ch[0]->s,mini=*(ch[0]->mini)<*mini?ch[0]->mini:mini;
         if(ch[1]) s+=ch[1]->s,mini=*(ch[1]->mini)<*mini?ch[1]->mini:mini;
     }
     void pushdown()
     {
         if(flip)
         {
             flip=0;
             if(ch[0])
             {
                 swap(ch[0]->ch[0],ch[0]->ch[1]);
                 ch[0]->flip=!ch[0]->flip;
             }
             if(ch[1])
             {
                 swap(ch[1]->ch[0],ch[1]->ch[1]);
                 ch[1]->flip=!ch[1]->flip;
             }
         }
     }
     node(int val,int order)
     {
         v=val;
o=order;
         s=1;
         flip=0;
         pre=ch[0]=ch[1]=0;
mini=this;
     }
 };
 node *root=NULL;
 void rotate(node *x,int c)
 {
     node *y=x->pre;
     y->pushdown();x->pushdown();
     y->ch[!c]=x->ch[c];
     if(x->ch[c]!=NULL) x->ch[c]->pre=y;
     x->pre=y->pre;
     if(y->pre!=NULL)
     {
         if(y->pre->ch[0]==y)
             y->pre->ch[0]=x;
         else
             y->pre->ch[1]=x;
     }
     x->ch[c]=y;
     y->pre=x;
     y->maintain();
     x->maintain();
 }
 void splay(node* x,node* f) {
     x->pushdown();
     while(x->pre!=f){
         if(x->pre->pre==f){
             rotate(x,x->pre->ch[0]==x);
         }
         else{
             node *y=x->pre,*z=y->pre;
             bool c=(z->ch[0]==y);
             y->pushdown();
             x->pushdown();
             if(y->ch[c]==x){
                 rotate(x,!c);
                 rotate(x,c);
             }
             else{
                 rotate(y,c);
                 rotate(x,c);
             }
         }
     }
     x->maintain();
     if(f==0) root=x;
 }
 void select(int k,node *f)
 {
     int temp;
     node *t=root;
     while(1)
     {
         t->pushdown();
         temp=0;
         if(t->ch[0])
             temp=t->ch[0]->s;
         if(k==temp+1)break;
         if(k<=temp)
             t=t->ch[0];
         else k-=temp+1,t=t->ch[1];
     }
     splay(t,f);
 }
 int getmin(node *f)
 {
f->pushdown();
if(f==f->mini) return (f->ch[0]?f->ch[0]->s:0)+1;
if(f->ch[0] && f->mini==f->ch[0]->mini) return getmin(f->ch[0]);
if(f->ch[1] && f->mini==f->ch[1]->mini) return (f->ch[0]?f->ch[0]->s:0)+1+getmin(f->ch[1]);
 }
 int val[110000],n;
 node *build(int l,int r)
 {
int m=(l+r)>>1;
node *rt=new node(val[m],m),*lson=NULL,*rson=NULL;
if(l==r) 
{
if(l==1)
{
rt->ch[0]=new node(inf,0);
rt->ch[0]->pre=rt;
rt->maintain();
}
if(l==n)
{
rt->ch[1]=new node(inf,n+1);
rt->ch[1]->pre=rt;
rt->maintain();
}
return rt;
}
if(r-l>1)
{
lson=build(l,m-1);
rson=build(m+1,r);
lson->pre=rson->pre=rt;
rt->ch[0]=lson;
rt->ch[1]=rson;
}
else 
{
if(l==1)
{
rt->ch[0]=new node(inf,0);
rt->ch[0]->pre=rt;
rt->maintain();
}
rson=build(m+1,r);
rson->pre=rt;
rt->ch[1]=rson;
}
rt->maintain();
return rt;
 }
 void del(node *&rt)
 {
if(rt->ch[0]) del(rt->ch[0]);
if(rt->ch[1]) del(rt->ch[1]);
delete rt;
rt=NULL;
 }
 int main()
 {
	//freopen("in.txt","r",stdin);
	//freopen("New.txt","w",stdout);
while(cin>>n && n)
{
for(int i=1;i<=n;i++)
scanf("%d",&val[i]);
root=build(1,n);
for(int i=1;i<n;i++)
{
select(i,NULL);
root->maintain();
select(i+1,root);
root->maintain();
int pos=getmin(root->ch[1])+root->s-root->ch[1]->s;
printf("%d ",pos-1);
select(pos,root);
select(pos+1,root);
root->ch[1]->ch[0]->flip^=1;
swap(root->ch[1]->ch[0]->ch[0],root->ch[1]->ch[0]->ch[1]);
}
printf("%d\n",n);
del(root);
}
 } 
