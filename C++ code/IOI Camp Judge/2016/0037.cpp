#include<cstdio>
#include<cassert>
#include<algorithm> 
using namespace std;
const int INF=1000000000;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
struct Node2D
{
	Node2D *ch[2];
	int mn,mx;
	Node2D(const int _v):ch{NULL,NULL},mn(_v),mx(_v){}
};
struct Node1D
{
	Node1D *ch[2];
	Node2D *ch2d;
	Node1D():ch{NULL,NULL},ch2d(NULL){}
}*ADD=NULL,*SUB=NULL;
void Delete(Node2D* &o)
{
	if(!o)return;
	for(int i=0;i<2;i++)Delete(o->ch[i]);
	delete o;o=NULL;
}
void Delete(Node1D* &o)
{
	if(!o)return;
	for(int i=0;i<2;i++)Delete(o->ch[i]);
	Delete(o->ch2d);
	delete o;o=NULL;
}
void Build(Node1D* &o,const int l,const int r)
{
	o=new Node1D();
	if(l==r)return;
	const int mid=(l+r)/2;
	Build(o->ch[0],l,mid),Build(o->ch[1],mid+1,r);
}
int Mn(Node2D* &o){return o?o->mn:INF;}
int Mx(Node2D* &o){return o?o->mx:-INF;}
void Maintain(Node2D* &o)
{
	o->mn=min(Mn(o->ch[0]),Mn(o->ch[1]));
	o->mx=max(Mx(o->ch[0]),Mx(o->ch[1]));
}
void ModifyLeaf(Node2D* &o,const int l,const int r,const int y,const int val)
{
//	printf("(%d,%d)(y=%d,val=%d)\n",l,r,y,val);
	if(!o)o=new Node2D(val);
	if(l==r)return;
	const int mid=(l+r)/2;
	if(y<=mid)ModifyLeaf(o->ch[0],l,mid,y,val);
	else ModifyLeaf(o->ch[1],mid+1,r,y,val);
	Maintain(o);
}
Node2D *Ch(Node2D* &o,const int d){return o?o->ch[d]:NULL;}
void Modify2D(Node2D* &o,Node2D *lo,Node2D *ro,const int l,const int r,const int y)
{
	if(!lo&&!ro)return;
	if(!o)o=new Node2D(0);
	o->mn=min(Mn(lo),Mn(ro));
	o->mx=max(Mx(lo),Mx(ro));
	const int mid=(l+r)/2;
	if(y<=mid)Modify2D(o->ch[0],Ch(lo,0),Ch(ro,0),l,mid,y);
	else Modify2D(o->ch[1],Ch(lo,1),Ch(ro,1),mid+1,r,y);
}
void Modify1D(Node1D* &o,const int l,const int r,const int x,const int y,const int val)
{
//	printf("(%d,%d)(x=%d,y=%d,val=%d)\n",l,r,x,y,val);
	assert(o);
	if(l<r)
	{
		const int mid=(l+r)/2;
		if(x<=mid)Modify1D(o->ch[0],l,mid,x,y,val);
		else Modify1D(o->ch[1],mid+1,r,x,y,val);
	}
	if(l==r)ModifyLeaf(o->ch2d,1,1000000,y,val);
	else Modify2D(o->ch2d,o->ch[0]->ch2d,o->ch[1]->ch2d,1,1000000,y);
}
void Query2D(Node2D* &o,const int l,const int r,const int y1,const int y2,int &mn,int &mx)
{
	if(!o||r<y1||y2<l)return;
	if(y1<=l&&r<=y2){getmin(mn,o->mn),getmax(mx,o->mx);return;}
	const int mid=(l+r)/2;
	Query2D(o->ch[0],l,mid,y1,y2,mn,mx),Query2D(o->ch[1],mid+1,r,y1,y2,mn,mx);
}
void Query1D(Node1D* &o,const int l,const int r,const int x1,const int x2,const int y1,const int y2,int &mn,int &mx)
{
	assert(o);
	if(r<x1||x2<l)return;
	if(x1<=l&&r<=x2){Query2D(o->ch2d,1,1000000,y1,y2,mn,mx);return;}
	const int mid=(l+r)/2;
	Query1D(o->ch[0],l,mid,x1,x2,y1,y2,mn,mx),Query1D(o->ch[1],mid+1,r,x1,x2,y1,y2,mn,mx);
}
int QueryMax(Node1D* &o,const int x1,const int x2,const int y1,const int y2)
{
	int mn=INF,mx=-INF;
	Query1D(o,1,1000000,x1,x2,y1,y2,mn,mx);
	return mx;
}
int QueryMin(Node1D* &o,const int x1,const int x2,const int y1,const int y2)
{
	int mn=INF,mx=-INF;
	Query1D(o,1,1000000,x1,x2,y1,y2,mn,mx);
	return mn;
}
int N;
int Solve(const int x,const int y)
{
	int ans=INF;
	getmin(ans,(x+y)-QueryMax(ADD,1,x,1,y));
	getmin(ans,QueryMin(ADD,x,1000000,y,1000000)-(x+y));
	getmin(ans,(x-y)-QueryMax(SUB,1,x,y,1000000));
	getmin(ans,QueryMin(SUB,x,1000000,1,y)-(x-y));
	assert(ans>=0);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	if(true)
	{
		vector<int>s;
		sort(s.begin(),s.end(),[](int a,int b)->bool{return a<b;});
	}
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		Delete(ADD),Delete(SUB);
		Build(ADD,1,1000000),Build(SUB,1,1000000);
		for(int i=0,type,x,y;i<N;i++)
		{
			scanf("%d%d%d",&type,&x,&y);
			if(type==0)Modify1D(ADD,1,1000000,x,y,x+y),Modify1D(SUB,1,1000000,x,y,x-y);
			else if(type==1)printf("%d\n",Solve(x,y));
		}
	}
	return 0;
}
