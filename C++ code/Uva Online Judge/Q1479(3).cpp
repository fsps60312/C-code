#include<cstdio>
#include<cstdlib>
#include<vector>
#include<ctime>
#include<map>
using namespace std;
int N,M;
struct vertextype
{
	int v,f,sum,head;
	vertextype *ch[2];
	int cmp(int a){return a<v?0:1;}
	void maintain()
	{
		sum=1;
		if(ch[0]!=NULL)sum+=ch[0]->sum;
		if(ch[1]!=NULL)sum+=ch[1]->sum;
	}
}v[20000];
struct treaptype
{
	vertextype *root;
	void clear(){root=NULL;}
	void rotate(vertextype* &a,int d)
	{
		vertextype *b=a->ch[d^1];
		a->ch[d^1]=b->ch[d];
		b->ch[d]=a;
		a->maintain(),b->maintain();
		a=b;
	}
	void insert(vertextype* &a,vertextype *b)
	{
		//printf("now at %d(insert %d)\n",a->v,b->v);showvertexes();
		int d=a->cmp(b->v);
		if(a->ch[d]==NULL)
		{
			b->maintain();
			a->ch[d]=b;
		}
		else insert(a->ch[d],b);
		a->maintain();
		if(a->ch[d]->f>a->f)rotate(a,d^1);
		//printf("now at %d(insert %d)\n",a->v,b->v);showvertexes();
	}
	void insert(vertextype *b)
	{
		if(root==NULL)
		{
			b->maintain();
			root=b;
		}
		else insert(root,b);
	}
	void del(vertextype* &a)
	{
		if(a->ch[0]==NULL&&a->ch[1]==NULL)
		{
			a=NULL;
			return;
		}
		else
		{
			int d;
			if(a->ch[0]==NULL)rotate(a,d=0);
			else if(a->ch[1]==NULL)rotate(a,d=1);
			else rotate(a,d=(a->ch[0]->f>a->ch[1]->f?1:0));
			del(a->ch[d]);
			a->maintain();
		}
	}
	vertextype* &fin(vertextype* &a,int b)
	{
		//printf("a->v=%d\n",a->v);
		if(a->v==b)return a;
		int d=a->cmp(b);
		//printf("d=%d\n",d);
		return fin(a->ch[d],b);
	}
	vertextype* &fin(int b){return fin(root,b);}
	void del(int b){del(fin(b));}
	int qvbyrank(vertextype *a,int rank)
	{
		//printf(" %d:rank=%d\n",a->v,rank);
		int b=1;if(a->ch[1]!=NULL)b+=a->ch[1]->sum;
		if(rank==b)return a->v;
		if(rank<b)return a->ch[1]==NULL?0:qvbyrank(a->ch[1],rank);
		return a->ch[0]==NULL?0:qvbyrank(a->ch[0],rank-b);
	}
	int qvbyrank(int rank){return root==NULL?0:qvbyrank(root,rank);}
	void showvertexes(vertextype *a)
	{
		int debv=true;
		printf("%d:",a->v);
		if(a->ch[0]!=NULL&&(debv||a->ch[0]->v!=a->v))printf(" 0-%d",a->ch[0]->v);
		if(a->ch[1]!=NULL&&(debv||a->ch[1]->v!=a->v))printf(" 1-%d",a->ch[1]->v);
		printf("\n");
		if(a->ch[0]!=NULL&&(debv||a->ch[0]->v!=a->v))showvertexes(a->ch[0]);
		if(a->ch[1]!=NULL&&(debv||a->ch[1]->v!=a->v))showvertexes(a->ch[1]);
	}
	void showvertexes()
	{
		if(root!=NULL)showvertexes(root);
	}
	void dfsinsert(vertextype* &b)
	{
		//printf("dfs2:\n");showvertexes();//showallt();
		if(b->ch[0]!=NULL)dfsinsert(b->ch[0]);
		if(b->ch[1]!=NULL)dfsinsert(b->ch[1]);
		//b->ch[0]=b->ch[1]=NULL;
		//printf("dfs2-1:\n");showallt();
		insert(b);
		//printf("dfs2-2:\n");showallt();
		b=NULL;
	}
};
vector<treaptype> t;
struct sidetype
{
	int x,y;
	bool deleted;
}s[60000];
struct querytype
{
	char type;
	int x,y;
};
vector<querytype> q;
int fin(int a)
{
	if(v[a].head==a)return a;
	return v[a].head=fin(v[a].head);
}
map<int,int> m;
void showallt()
{
	for(int i=0;i<t.size();i++)
	{
		printf("t[%d]:\n",i);
		t[i].showvertexes();
	}
}
/*void dfsinsert(treaptype a,treaptype b)
{
	printf("dfs1:\n");
	a.showvertexes();printf("\n");
	b.showvertexes();printf("\n");
	if(b.root!=NULL)
	{
		dfsinsert(a,b.root);
		if(b.root!=NULL)a.root=b.root,b.root=NULL;
	}
}*/
int main()
{
	freopen("inn.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	srand(time(NULL));
	int kase=1;
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		for(int i=0;i<N;i++)
		{
			scanf("%d",&v[i].v);
			v[i].ch[0]=v[i].ch[1]=NULL;
			v[i].f=rand();
			v[i].head=i;
		}
		for(int i=0;i<M;i++)
		{
			scanf("%d%d",&s[i].x,&s[i].y);
			s[i].x--,s[i].y--;
			s[i].deleted=false;
		}
		//v[0].f=2,v[1].f=1,v[2].f=3;
		querytype tq;
		q.clear();
		while(scanf("%c",&tq.type)==1&&tq.type!='E')
		{
			switch(tq.type)
			{
				case'D':
				{
					scanf("%d",&tq.x);
					s[--tq.x].deleted=true;
					q.push_back(tq);
				}break;
				case'Q':
				{
					scanf("%d%d",&tq.x,&tq.y);
					tq.x--;
					q.push_back(tq);
				}break;
				case'C':
				{
					scanf("%d",&tq.x);
					tq.y=v[--tq.x].v;
					scanf("%d",&v[tq.x].v);
					q.push_back(tq);
				}break;
			}
		}
		for(int i=0;i<M;i++)
		{
			if(!s[i].deleted&&fin(s[i].x)!=fin(s[i].y))
			{
				v[fin(s[i].x)].head=fin(s[i].y);
			}
		}
		m.clear();
		t.clear();
		for(int i=0,j=0;i<N;i++)
		{
			if(m.find(fin(i))==m.end())
			{
				m[fin(i)]=j++;
				treaptype a;
				a.clear();
				t.push_back(a);
			}
			t[m[fin(i)]].insert(&v[i]);
			//showallt();
		}
		//printf("initial:\n");showallt();
		double ans1=0;
		int ans2=0;//printf("a\n");
		if(q.size())
		{
			for(int i=q.size()-1;i>=0;i--)
			{
				//printf("i=%d\n",i);
				switch(q[i].type)
				{
					case'D':
					{
						sidetype a=s[q[i].x];
						if(fin(a.x)==fin(a.y))break;
						int b1=m[fin(a.x)],b2=m[fin(a.y)];
						//printf("b1=%d, b2=%d\n",b1,b2);
						//printf("befins:\n");showallt();
						v[fin(a.y)].head=fin(a.x);
						if(t[b2].root!=NULL)t[b1].dfsinsert(t[b2].root);
						//printf("aftins:\n");showallt();
					}break;
					case'C':
					{
						int a=m[fin(q[i].x)];
						//printf("a\n");
						//t[a].showvertexes();
						//printf("bef:\n");showallt();
						t[a].del(v[q[i].x].v);
						//printf("b\n");
						v[q[i].x].v=q[i].y;
						t[a].insert(&v[q[i].x]);
						//printf("aft:\n");showallt();
					}break;
					case'Q':
					{
						int a=m[fin(q[i].x)];
						int b=t[a].qvbyrank(q[i].y);
						//showallt();printf("qrank:a=%d,b=%d\n",a,b);
						ans1+=b;
						ans2++;
					}
				}
			}
		}
		printf("Case %d: %.6lf\n",kase++,ans1/ans2);
	}
	return 0;
}
