#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define debug(x,...) {}//printf(x,##__VA_ARGS__)
#define termin(x,...) {while(1)printf(x,##__VA_ARGS__);;}
int max(int a,int b){return a>b?a:b;}
struct Node
{
	int v,y,h,d;
	Node *ch[2],*l,*r,*ldown,*rdown;
	Node(int v,int y):v(v),y(y),h(1),l(NULL),r(NULL),ldown(NULL),rdown(NULL),d(0){ch[0]=ch[1]=NULL;}
	void SetNeighbor(Node *nl,Node *nr)
	{
		l=nl,r=nr;
		if(l)l->r=this;
		if(r)r->l=this;
		if(l||r)
		{
			if((l&&r)&&l->y==r->y)termin("y must be different\n");
			if(l&&(!r||l->y>r->y))d=-1,y=l->y+2,l->rdown=this;
			else d=1,y=r->y+2,r->ldown=this;
		}
	}
}*ROOT;
int H(Node *o){return o?o->h:0;}
void Maintain(Node* &o){o->h=1+max(H(o->ch[0]),H(o->ch[1]));}
void Rotate(Node* &o,int chup)
{
	Node *ro=o;
	o=o->ch[chup];
	ro->ch[chup]=o->ch[chup^1];
	o->ch[chup^1]=ro;
	Maintain(ro);
	Maintain(o);
}
void Rotate(Node* &o)
{
	int h0=H(o->ch[0]),h1=H(o->ch[1]);
	if(h0-h1>=2)Rotate(o,0);
	else if(h1-h0>=2)Rotate(o,1);
}
void Insert(Node* &o,int v,Node *fa)
{
	if(!o)
	{
		if(!fa){o=new Node(v,1);return;}
		o=new Node(v,fa->y+2);
		if(v<fa->v)o->SetNeighbor(fa->l,fa);
		else o->SetNeighbor(fa,fa->r);
		return;
	}
	if(v<o->v)Insert(o->ch[0],v,o);
	else Insert(o->ch[1],v,o);
	Maintain(o);
	Rotate(o);
}
Node *Find(Node *o,int v)
{
	if(o->v==v)return o;
	return Find(o->ch[v>o->v],v);
}
int T,N,M;
char ANS[200][202];
struct Point{int o,v;};
vector<Point>INPUT;
bool cmpv(Point a,Point b){return a.v<b.v;}
bool cmpo(Point a,Point b){return a.o<b.o;}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		ROOT=NULL;
		scanf("%d",&N);
		printf("Case #%d:\n",kase++);
		INPUT.clear();
		for(int i=0,a;i<N;i++)
		{
			scanf("%d",&a);
			INPUT.push_back((Point){i,a});
		}
		sort(INPUT.begin(),INPUT.end(),cmpv);
		for(int i=0;i<N;i++)INPUT[i].v=i+1;
		sort(INPUT.begin(),INPUT.end(),cmpo);
		for(int i=0;i<N;i++)
		{
			Insert(ROOT,INPUT[i].v,NULL);
		}
		scanf("%d",&M);
		int r,c,R,C;
		while(M--)
		{
			scanf("%d%d%d%d",&r,&c,&R,&C);
			for(int i=0;i<C;i++)
			{
				for(int j=0;j<R+2;j++)
				{
					ANS[i][j]=' ';
				}
			}
			if(c>N)continue;
			Node *o=Find(ROOT,c),*now=o;
			for(int i=0;now&&i<C;i++,now=now->r)
			{
				int y=now->y;
				if(y<r||y>=r+R+2)continue;
				ANS[i][y-r]='o';
			}
			now=o;
			for(int i=0;now&&i<C;i++,now=now->r)
			{
				int y=now->y;
				if(y<r||y>=r+R+2)continue;
				y-=r;y--;
				if(now->d==0||y<0)continue;
				ANS[i][y]='|';y--;
				if(y<0)continue;
				ANS[i][y]='+';
				for(int x=i+now->d;x>=0&&x<C&&ANS[x][y]!='o';x+=now->d)ANS[x][y]='-';
			}
			now=o;
			for(int i=0;now&&i<C;i++,now=now->r)
			{
				int y=now->y;
				if(y<r||y>=r+R)continue;
				y-=r;
				if(now->ldown)for(int x=i-1;x>=0&&ANS[x][y]==' ';x--)ANS[x][y]='-';
				if(now->rdown)for(int x=i+1;x<C&&ANS[x][y]==' ';x++)ANS[x][y]='-';
			}
			for(int i=0;i<R;i++)
			{
				bool blank=true;
				for(int j=0;j<C;j++)if(ANS[j][i]!=' '){debug("find %d=%d\n",j,ANS[j][i]);blank=false;break;}
				if(blank)continue;
				for(int j=0;j<C;j++)printf("%c",ANS[j][i]);puts("");
			}
			puts("");
		}
	}
	return 0;
}
