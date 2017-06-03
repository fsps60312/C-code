#include<cstdio>
#include<cstdlib>
#include<vector>
#include<ctime>
#include<queue>
using namespace std;
int N,M;
struct sidetype
{
	int x,y;
	bool deleted;
};
int mrand()
{
	int ans=rand(),t=10;while(t--)ans+=rand(),ans*=rand();return ans;
}
int Max;
struct vertextype
{
	int f,v,head,index,o,sum,depth;
	vertextype* ch[2];
	vertextype* mom;
	void init(int a)
	{
		head=index=a;
		ch[0]=ch[1]=mom=NULL;
		f=mrand();
		sum=1;
		depth=1;
	}
	bool cmp(int a)
	{
		//if(a==v)return -1;
		return a>v?0:1;
	}
	//bool operator<(vertextype a){return f<a.f;}
	//bool operator>(vertextype a){return f>a.f;}
	void maintain()
	{
		sum=1;
		if(ch[0]!=NULL)sum+=ch[0]->sum;
		if(ch[1]!=NULL)sum+=ch[1]->sum;
		depth=1;
		if(mom!=NULL)depth=mom->depth+1;
	}
	void rotate(int d)//0:left,1:right
	{
		//printf("s rotate\n");
		if(ch[d^1]==NULL)return;
		if(mom!=NULL)mom->ch[o]=ch[d^1];
		ch[d^1]->o=o;
		ch[d^1]->mom=mom;
		mom=ch[d^1];
		o=d;
		vertextype *a=ch[d^1];
		ch[d^1]=ch[d^1]->ch[d];
		if(ch[d^1]!=NULL)ch[d^1]->o=d^1,ch[d^1]->mom=this;
		a->ch[d]=this;
		maintain();
		a->maintain();
		//printf("f rotate\n");
	}
	void rotateup()
	{
		while(mom!=NULL&&mom->f<f)
		{
			mom->rotate(o^1);
		}
	}
	void insert(vertextype* a)
	{
		vertextype* m=this;
		bool changed=false;
		if(a->ch[0]!=NULL)
		{
			m->insert(a->ch[0]);
			a->ch[0]=NULL;
			while(m->mom!=NULL)m=m->mom;
			changed=true;
		}
		if(a->ch[1]!=NULL)
		{
			m->insert(a->ch[1]);
			a->ch[1]=NULL;
			while(m->mom!=NULL)m=m->mom;
			changed=true;
		}
		if(changed)
		{
			m->insert(a);
			return;
		}
		int d=cmp(a->v);
		if(ch[d]==NULL)
		{
			ch[d]=a;
			ch[d]->sum=1;
			ch[d]->depth=depth+1;
			if(depth+1>Max)Max=depth+1;
			ch[d]->o=d;
			ch[d]->mom=this;
			maintain();
			ch[d]->rotateup();
			return;
		}
		else ch[d]->insert(a);
		maintain();
	}
	int askrank(int r)
	{
		int tr=ch[0]!=NULL?ch[0]->sum+1:1;
		if(r==tr)return v;
		else if(r<tr)
		{
			if(ch[0]==NULL)return 0;
			return ch[0]->askrank(r);
		}
		else
		{
			if(ch[1]==NULL)return 0;
			return ch[1]->askrank(r-tr);
		}
	}
	void deletevertex(vertextype *a)
	{
		//int t=1;
		while(a->ch[0]!=NULL||a->ch[1]!=NULL)
		{
			if(a->ch[0]==NULL)a->rotate(0);
			else if(a->ch[1]==NULL)a->rotate(1);
			else a->rotate(a->ch[0]->f>a->ch[1]->f?1:0);
			//printf("%d",t++);
		}
		if(a->mom!=NULL)a->mom->ch[o]=NULL;
	}
	void changevalue(int a)
	{
		//printf("a");
		deletevertex(this);
		v=a;
		vertextype *m=mom;
		//printf("b");
		if(m==NULL)return;
		//printf("c");
		m->maintain();
		while(m->mom!=NULL){m=m->mom;m->maintain();}
		//printf("d");
		m->insert(this);
		//printf("e");
	}
};
struct querytype
{
	char type;
	int x,y;
};
vertextype vertex[20001];
sidetype side[60001];
vector<querytype> query;
int findhead(int a)
{
	if(vertex[a].head==a)return a;
	return vertex[a].head=findhead(vertex[a].head);
}
void shownodes()
{
			for(int j=1;j<=N;j++)
			{
				vertextype *c=&vertex[j];
				printf("%d:%d %d %d %d sum=%d\n",j,c->mom==NULL?0:c->mom->index,c->ch[0]==NULL?0:c->ch[0]->index,c->ch[1]==NULL?0:c->ch[1]->index,c->v,c->sum);
			}
}
int main()
{
	//freopen("in.txt","r",stdin);
	srand(time(NULL));
	int kase=1;
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		for(int i=1;i<=N;i++)
		{
			scanf("%d",&vertex[i].v);
			vertex[i].init(i);
		}
		for(int i=1;i<=M;i++)
		{
			scanf("%d%d",&side[i].x,&side[i].y);
			side[i].deleted=false;
		}
		querytype tquery;query.clear();
		while(scanf("%c",&tquery.type)==1&&tquery.type!='E')
		{
			bool ok=true;
			switch(tquery.type)
			{
				case'D':
				{
					scanf("%d",&tquery.x);
					side[tquery.x].deleted=true;
				}break;
				case'C':
				{
					scanf("%d",&tquery.x);
					tquery.y=vertex[tquery.x].v;
					scanf("%d",&vertex[tquery.x].v);
				}break;
				case'Q':
				{
					scanf("%d%d",&tquery.x,&tquery.y);
				}break;
				default:ok=false;break;
			}
			if(ok)query.push_back(tquery);
		}
		if(!query.size())continue;
		Max=0;
		for(int i=1;i<=M;i++)
		{
			//if(i%100==0){printf("M=%d,Max=%d\n",i,Max);Max=0;}
			if(side[i].deleted)continue;
			if(findhead(side[i].x)==findhead(side[i].y))continue;
			//printf("a");
			//printf("join: %d %d\n",findhead(side[i].x),findhead(side[i].y));shownodes();
			vertextype *m1=&vertex[findhead(side[i].x)],*m2=&vertex[findhead(side[i].y)];
			while(m1->mom!=NULL)m1=m1->mom;
			while(m2->mom!=NULL)m2=m2->mom;
			m1->insert(m2);
			//printf("b");
			vertex[findhead(side[i].x)].head=findhead(side[i].y);
			//if(i%100==0)printf("%d\n",i);
		}
		double ans=0;
		int tans=0;
		for(int i=query.size()-1;i>=0;i--)
		{
			//if(i%1000==0)	printf("i=%d\n",i);
			//printf("%d\t",i);
			//printf("Q:%c %d %d\n",query[i].type,query[i].x,query[i].y);shownodes();
			switch(query[i].type)
			{
				case'Q':
				{
					vertextype *a=&vertex[query[i].x];
					while(a->mom!=NULL)a=a->mom;
					int b=a->askrank(query[i].y);
					//printf("askrank(%d)=%d\n",query[i].y,b);
					ans+=b;
					tans++;
				}break;
				case'D':
				{
					int a=query[i].x;
					if(!side[a].deleted||findhead(side[a].x)==findhead(side[a].y))break;
					side[a].deleted=false;
					vertextype *m1=&vertex[findhead(side[a].x)],*m2=&vertex[findhead(side[a].y)];
					while(m1->mom!=NULL)m1=m1->mom;
					while(m2->mom!=NULL)m2=m2->mom;
					m1->insert(m2);
					vertex[findhead(side[a].x)].head=findhead(side[a].y);
				}break;
				case'C':
				{
					vertex[query[i].x].changevalue(query[i].y);
				}break;
			}
		}
		printf("Case %d: %.6lf\n",kase++,ans/tans);
	}
	return 0;
}
