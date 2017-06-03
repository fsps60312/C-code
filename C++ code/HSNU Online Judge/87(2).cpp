#include<cstdio>
#include<map>
#include<cassert>
#include<algorithm>
using namespace std;
int N,M,Q,S[20001];
struct Bit
{
	int s[20001],n;
	void clear(const int _n){n=_n;for(int i=1;i<=n;i++)s[i]=0;}
	int lowbit(const int i){return i&(-i);}
	void Add(int i){while(i<=n){s[i]++,i+=lowbit(i);}}
	int Query(int i){int ans=0;while(i){ans+=s[i],i-=lowbit(i);}return ans;}
}BIT;
struct Seg
{
	struct Node2D
	{
		Node2D *l,*r;
		int y,sum;
		Node2D(const int _y,const int _s):y(_y),sum(_s),l(NULL),r(NULL){}
	};
	struct Node1D
	{
		Node1D *l,*r;
		Node2D *n;
		Node1D():l(NULL),r(NULL),n(NULL){}
	}*ROOT=NULL;
	void Build(Node1D* &o,const int l,const int r)
	{
		o=new Node1D();
		if(l==r)return;
		int mid=(l+r)/2;
		Build(o->l,l,mid),Build(o->r,mid+1,r); 
	}
	void Build(){Build(ROOT,1,N);}
	int X,Y,V;
	void Delete(Node2D* &o)
	{
		if(!o)return;
		Delete(o->l),Delete(o->r);
		delete o;o=NULL;
	}
	void Maintain(Node2D* &o)
	{
		if(o->y==-1)
		{
			if(o->l&&o->r)o->sum=o->l->sum+o->r->sum;
			else if(o->l||o->r)
			{
				Node2D* &ch=o->l?o->l:o->r;
				if(ch->y!=-1)
				{
					o->y=ch->y,o->sum=ch->sum;
					Delete(ch);
				}
				else o->sum=ch->sum;
			}
			else{delete o;o=NULL;}
		}
		else if(o->sum==0){delete o;o=NULL;}
	}
	void ModifyLEAF(Node2D* &o,const int l,const int r)
	{
		if(!o){o=new Node2D(Y,V);return;}
		if(o->y!=-1)
		{
			if(o->y==Y)
			{
				o->sum+=V;
				Maintain(o);
//				if(V==-1&&o)printf("leaf(%d,%d),y=%d,sum=%d\n",l,r,o->y,o->sum);
				assert(V==1||!o);
				return;
			}
			else
			{
				const int mid=(l+r)/2;
				if(o->y<=mid)o->l=new Node2D(o->y,o->sum);
				else o->r=new Node2D(o->y,o->sum);
				o->y=-1;
			}
		}
		const int mid=(l+r)/2;
		if(Y<=mid)ModifyLEAF(o->l,l,mid);
		else ModifyLEAF(o->r,mid+1,r);
		Maintain(o);
	}
	const Node2D *Lch(const Node2D *o,const int l,const int r)
	{
		if(!o)return NULL;
		if(o->y!=-1)return o->y<=(l+r)/2?o:NULL;
		return o->l;
	}
	const Node2D *Rch(const Node2D *o,const int l,const int r)
	{
		if(!o)return NULL;
		if(o->y!=-1)return o->y>(l+r)/2?o:NULL;
		return o->r;
	}
	int Sum(const Node2D *o){return o?o->sum:0;}
//	void Print(const Node2D *o)
//	{
//		if(!o)return;
//		printf("{");
//		Print(o->l);
//		printf("(%d,%d)",o->y,o->sum);
//		Print(o->r);
//		printf("}");
//	}
	void Modify2D(Node2D* &o,const int l,const int r,const Node2D *loch,const Node2D *roch)
	{
		if(!o)o=new Node2D(-1,0);
		if(!loch&&!roch){delete o;o=NULL;return;}
		else if(loch&&roch)
		{
			if(loch->y==roch->y&&loch->y!=-1)
			{
				o->y=loch->y,o->sum=loch->sum+roch->sum;
				Delete(o->l),Delete(o->r);
				return;
			}
		}
		else if(loch)
		{
			if(loch->y!=-1)
			{
				o->y=loch->y,o->sum=loch->sum;
				Delete(o->l),Delete(o->r);
				return;
			}
		}
		else
		{
			if(roch->y!=-1)
			{
				o->y=roch->y,o->sum=roch->sum;
				Delete(o->l),Delete(o->r);
				return;
			}
		}
		if(o->y!=-1)
		{
			const int mid=(l+r)/2;
			if(o->y<=mid)o->l=new Node2D(o->y,o->sum);
			else o->r=new Node2D(o->y,o->sum);
			o->y=-1;
		}
		const int mid=(l+r)/2;
		if(Y<=mid)Modify2D(o->l,l,mid,Lch(loch,l,r),Lch(roch,l,r));
		else Modify2D(o->r,mid+1,r,Rch(loch,l,r),Rch(roch,l,r));
		Maintain(o);
//		if(o->sum!=Sum(loch)+Sum(roch))
//		{
//			printf("o: ");Print(o);puts("");
//			printf("loch: ");Print(loch);puts("");
//			printf("roch: ");Print(roch);puts("");
//			printf("(%d,%d,%d)(%d,%d)\n",o->sum,Sum(loch),Sum(roch),l,r);
//			printf("l(%d,%d)r(%d,%d)\n",o->l->y,o->l->sum,o->r->y,o->r->sum);
//			printf("loch(%d,%d)roch(%d,%d)\n",loch->y,loch->sum,roch->y,roch->sum);
//		}
		assert(o->sum==Sum(loch)+Sum(roch));
	}
	void Modify1D(Node1D* &o,const int l,const int r)
	{
		if(l==r)ModifyLEAF(o->n,1,M);
		else
		{
			const int mid=(l+r)/2;
			if(X<=mid)Modify1D(o->l,l,mid);
			else Modify1D(o->r,mid+1,r);
			Modify2D(o->n,1,M,o->l->n,o->r->n);
		}
	}
	int X1,X2,Y1,Y2;
	void Query2D(const Node2D *o,const int l,const int r,int &ans)
	{
		if(!o)return;
		if(o->y!=-1)
		{
			if(Y1<=o->y&&o->y<=Y2)ans+=o->sum;
			return;
		}
		if(r<Y1||l>Y2)return;
		if(Y1<=l&&r<=Y2){ans+=o->sum;return;}
		const int mid=(l+r)/2;
		Query2D(o->l,l,mid,ans);
		Query2D(o->r,mid+1,r,ans);
	}
	void Query1D(const Node1D *o,const int l,const int r,int &ans)
	{
		if(r<X1||l>X2)return;
		if(X1<=l&&r<=X2){Query2D(o->n,1,M,ans);return;}
		const int mid=(l+r)/2;
		Query1D(o->l,l,mid,ans);
		Query1D(o->r,mid+1,r,ans);
	}
	void Add(const int x,const int y)
	{
		X=x,Y=y,V=1;
		assert(X>=1&&X<=N&&Y>=1&&Y<=M);
//		printf("Add(%d,%d)\n",X,Y);
		Modify1D(ROOT,1,N);
	}
	void Remove(const int x,const int y){X=x,Y=y,V=-1;Modify1D(ROOT,1,N);}
	int Query(const int x1,const int x2,const int y1,const int y2)
	{
		if(x2<x1||y2<y1)return 0;
		X1=x1,X2=x2,Y1=y1,Y2=y2;
		int ans=0;
		Query1D(ROOT,1,N,ans);
		return ans;
	}
}SEG;
map<int,int>IDX;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)scanf("%d",&S[i]),IDX[S[i]]=0;
	int cnt=1;
	for(auto it=IDX.begin();it!=IDX.end();it++)it->second=cnt++;
	for(int i=1;i<=N;i++)S[i]=IDX[S[i]];
	BIT.clear(M=IDX.size());
	int now=0;
	for(int i=1;i<=N;i++)
	{
		BIT.Add(S[i]);
		now+=i-BIT.Query(S[i]);
	}
	printf("%d\n",now);
	SEG.Build();
	for(int i=1;i<=N;i++)
	{
		SEG.Add(i,S[i]);
//		for(int i=1;i<=N;i++)
//		{
//			for(int j=1;j<=M;j++)printf(" %d",SEG.Query(i,i,j,j));
//			puts("");
//		}
	}
	scanf("%d",&Q);
	while(Q--)
	{
		static int a,b;
		scanf("%d%d",&a,&b);
		if(a==b)continue;
		if(a>b)swap(a,b);
		int bup=SEG.Query(a+1,b-1,S[b]+1,M);
		int bdown=SEG.Query(a+1,b-1,1,S[b]-1);
		int aup=SEG.Query(a+1,b-1,S[a]+1,M);
		int adown=SEG.Query(a+1,b-1,1,S[a]-1);
//		printf("(%d,%d)\n",a,b);
//		printf("a(%d,%d)b(%d,%d)\n",aup,adown,bup,bdown);
		now-=bup,now+=bdown;
		now-=adown,now+=aup;
		if(S[a]<S[b])now++;
		else if(S[a]>S[b])now--;
//		for(int i=1;i<=N;i++)
//		{
//			for(int j=1;j<=M;j++)printf(" %d",SEG.Query(i,i,j,j));
//			puts("");
//		}
		printf("%d\n",now);
		SEG.Remove(a,S[a]),SEG.Remove(b,S[b]);
		swap(S[a],S[b]);
		SEG.Add(a,S[a]),SEG.Add(b,S[b]);
	}
	return 0;
}
