#include<cstdio>
#include<map>
using namespace std;
int T,N,M,K,GRID[150][10],POW[10];
inline const int &D(const int &s,const int &i){return s/POW[i]%4;}
inline const bool &Move(const int &s,const int &r,const int &c,const int &w,const int &h,int &t)
{
	if(r+h>N||c+w>M)return false;
	static int i,j;
	for(i=0;i<w;i++)if(D(s,c+i)>0)return false;
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			if(GRID[r+i][c+j])return false;
		}
	}
	t=s;
	for(i=0;i<w;i++)t+=POW[c+i]*h;
	return true;
}
struct Node
{
	Node *ch[2];
	int s,v,sz;
	Node(const int &s,const int &v):s(s),v(v),sz(1),ch{NULL,NULL}{}
}*DP[150][10];
inline const int &Sz(Node* &o){return o?o->sz:0;}
inline void Maintain(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
void Delete(Node* &o)
{
	if(!o)return;
	Delete(o->ch[0]);
	Delete(o->ch[1]);
	delete o;
	o=NULL;
}
inline void Rotate(Node* &o,const int &cu)
{
	static Node *u;
	u=o;
	o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
const int &Query(Node* &o,const int &s)
{
	if(!o)return -1;
	if(s==o->s)return o->v;
	return Query(o->ch[s<o->s?0:1],s);
}
void Insert(Node* &o,const int &s,const int &v)
{
	if(!o){o=new Node(s,v);return;}
	Insert(o->ch[s<o->s?0:1],s,v);
	if(Sz(o->ch[s<o->s?0:1])>Sz(o->ch[s<o->s?1:0]))Rotate(o,s<o->s?0:1);
}
int ANS[150][10],TMP[150][10];
const int &Get(int r,int c,int &s)
{
	static int i,tmp;
	if(c==M)
	{
		c=0,r++;
		for(i=0;i<M;i++)if(D(s,i))s-=POW[i];
	}
	if(r==N)return 0;
	if((tmp=Query(DP[r][c],s))!=-1)return tmp;
	int &t=TMP[r][c]=s;
	int &ans=ANS[r][c]=Get(r,c+1,t);
	if(Move(s,r,c,2,3,t))ans=max(ans,1+Get(r,c+1,t));
	if(Move(s,r,c,3,2,t))ans=max(ans,1+Get(r,c+1,t));
	Insert(DP[r][c],s,ans);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int i,j;
	for(i=0;i<150;i++)for(j=0;j<10;j++)DP[i][j]=NULL;
	POW[0]=1;
	for(i=1;i<10;i++)POW[i]=POW[i-1]*4;
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d%d",&N,&M,&K);
			for(i=0;i<N;i++)
			{
				for(j=0;j<M;j++)
				{
					GRID[i][j]=0;
					Delete(DP[i][j]);
				}
			}
			for(i=0;i<K;i++)
			{
				static int x,y;
				scanf("%d%d",&x,&y);
				x--,y--;
				GRID[x][y]=1;
			}
			static int s;s=0;
			printf("%d\n",Get(0,0,s));
		}
	}
	return 0;
}
