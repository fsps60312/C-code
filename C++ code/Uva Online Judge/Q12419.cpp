#include<cstdio>
#include<cstdlib>
#include<queue>
#include<ctime>
#define max(x,y) (x)>(y)?(x):(y)
#define min(x,y) (x)<(y)?(x):(y)
using namespace std;
struct Pair
{
	int x,y;
	bool operator<(Pair a)const{if(x!=a.x)return x>a.x;return y>a.y;}
};
Pair newpair(int x,int y){Pair ans;ans.x=x,ans.y=y;return ans;}
int N,B;
priority_queue<Pair> TERMIN;
struct Node
{
	int f,pos,len,lfree,rfree,mfree,lpos,rpos;
	Node *ch[2];
	Node(int pos,int len,int totalfree):pos(pos),len(len)
	{
		lfree=0;
		lpos=pos,rpos=lpos+len;
		rfree=mfree=totalfree-len;
		f=rand();
		ch[0]=ch[1]=NULL;
	}
	void maintain()
	{
		lpos=pos,rpos=lpos+len;
		mfree=max(lfree,rfree);
		if(ch[0]!=NULL)mfree=max(mfree,ch[0]->mfree),lpos=ch[0]->lpos;
		if(ch[1]!=NULL)mfree=max(mfree,ch[1]->mfree),rpos=ch[1]->rpos;
	}
};
void shownode(Node *o)
{
	printf("pos=%d,len=%d,lfree=%d,rfree=%d,mfree=%d,lpos=%d,rpos=%d\n"
	,o->pos,o->len,o->lfree,o->rfree,o->mfree,o->lpos,o->rpos);
}
Node *RT=NULL;
void showall(Node *o,int dep)
{
	if(o==NULL)return;
	for(int i=0;i<dep;i++)printf("  ");shownode(o);
	showall(o->ch[0],dep+1);
	showall(o->ch[1],dep+1);
}
int SETLF,SETRF;
void setfree(Node* &o,int d)
{
	if(o==NULL||(d==0&&SETRF==-1)||(d==1&&SETLF==-1))return;
	setfree(o->ch[d],d);
	if(d==0&&SETRF!=-1)o->rfree=SETRF,SETRF=-1;
	if(d==1&&SETLF!=-1)o->lfree=SETLF,SETLF=-1;
	o->maintain();
}
void removetree(Node* &o)
{
	if(o==NULL)return;
	removetree(o->ch[0]);
	removetree(o->ch[1]);
	delete o;
	o=NULL;
}
void rotate(Node* &o,int d)
{
	Node *k=o->ch[d^1];
	o->ch[d^1]=k->ch[d];
	k->ch[d]=o;
	o->maintain(),k->maintain();
	o=k;
}
int insert(Node* &o,int len,int pos,int freegap)
{
	if(o==NULL)
	{
		o=new Node(pos,len,freegap);
		SETLF=o->rfree;
		SETRF=o->lfree;
		//shownode(o);
		return pos;
	}
	if(o->mfree<len)return -1;
	int d=-1,ans=-1;
	if(o->ch[0]==NULL&&o->ch[1]==NULL)
	{
		if(o->lfree>=len)
		{
			ans=insert(o->ch[d=0],len,o->pos-o->lfree,o->lfree);
		}
		else if(o->rfree>=len)
		{
			ans=insert(o->ch[d=1],len,o->pos+o->len,o->rfree);
		}
		else printf("no free gap larger error\n");
	}
	else if(o->lfree>=len||(o->ch[0]!=NULL&&o->ch[0]->mfree>=len))ans=insert(o->ch[d=0],len,o->pos-o->lfree,o->lfree);
	else if(o->rfree>=len||(o->ch[1]!=NULL&&o->ch[1]->mfree>=len))ans=insert(o->ch[d=1],len,o->pos+o->len,o->rfree);
	if(d==-1)printf("d==-1,error\n");
	if(d==0&&SETLF!=-1)o->lfree=SETLF,SETLF=-1;
	if(d==1&&SETRF!=-1)o->rfree=SETRF,SETRF=-1;
	o->maintain();
	if(o->f<o->ch[d]->f)rotate(o,d^1);
	return ans;
}
void remove(Node* &o,int p)
{
	int d;
	if(o->pos!=p)
	{
		d=p<o->pos?0:1;
		remove(o->ch[d],p);
		o->maintain();
	}
	else
	{
		if(o->ch[0]!=NULL&&o->ch[1]!=NULL)
		{
			d=o->ch[0]->f>o->ch[1]->f?1:0;
			rotate(o,d);
			remove(o->ch[d],p);
			o->maintain();
		}
		else
		{
			SETLF=SETRF=o->lfree+o->len+o->rfree;
			Node *k=o;
			if(o->ch[0]!=NULL)o=o->ch[d=0];
			else o=o->ch[d=1];
			delete k;
			//printf("a\n");
			setfree(o,d);
			//printf("b\n");
			if(o!=NULL)setfree(o->ch[d],d^1);
			//printf("c\n");
			return;
		}
	}
	if(d==0&&SETLF!=-1)
	{
		o->lfree=SETLF;
		SETLF=-1;
		o->maintain();
	}
	if(d==1&&SETRF!=-1)
	{
		o->rfree=SETRF;
		SETRF=-1;
		o->maintain();
	}
}
struct Input{int T,M,P,i;};
queue<Input> WAIT;
int main()
{
	freopen("in.txt","r",stdin);
	srand(time(NULL));
	while(scanf("%d%d",&N,&B)==2)
	{
		while(!TERMIN.empty())TERMIN.pop();
		while(!WAIT.empty())WAIT.pop();
		removetree(RT);
		Input I;
		int waited=0,endtime=0,processn=1;
		while(scanf("%d%d%d",&I.T,&I.M,&I.P)==3&&(I.T||I.M||I.P))
		{
			I.i=processn++;
			int pos;
			while(!TERMIN.empty())
			{
				//printf("enter termin...\n");
				Pair tt;
				do
				{
					tt=TERMIN.top();
					if(tt.x>I.T)break;
					//printf("terminate (%d,%d)\n",tt.x,tt.y);
					endtime=tt.x;
				//printf("before remove:\n");showall(RT,0);
					remove(RT,tt.y);
				//printf("after remove:\n");showall(RT,0);
					TERMIN.pop();
				}while(!TERMIN.empty()&&TERMIN.top().x==tt.x);
				if(tt.x>I.T)break;
				while(!WAIT.empty())
				{
					Input ti=WAIT.front();
					ti.T=tt.x;
					SETLF=SETRF=-1;
			//printf("before insert:I=(%d,%d,%d)\n",ti.T,ti.M,ti.P);//showall(RT,0);
					pos=insert(RT,ti.M,0,N);
			//printf("after insert:\n");showall(RT,0);
			//printf("pos=%d\n",pos);
					if(pos!=-1)
					{
						if(ti.P)TERMIN.push(newpair(ti.T+ti.P,pos));
						else remove(RT,pos);
						if(B)
						{
							printf("%d %d %d\n",ti.T,ti.i,pos);
						}
					}
					else break;
					WAIT.pop();
				}
			}
			SETLF=SETRF=-1;
			//printf("before insert:I=(%d,%d,%d)\n",I.T,I.M,I.P);//showall(RT,0);
			pos=insert(RT,I.M,0,N);
			//printf("after insert:\n");showall(RT,0);
			//printf("pos=%d\n",pos);
			if(pos!=-1)
			{
				if(I.P)TERMIN.push(newpair(I.T+I.P,pos));
				else remove(RT,pos);
				if(B)
				{
					printf("%d %d %d\n",I.T,I.i,pos);
				}
			}
			else
			{
				WAIT.push(I);
				waited++;
			}
		}
		while(!TERMIN.empty())
		{
			Pair tt;
			do
			{
				tt=TERMIN.top();
				endtime=tt.x;
				remove(RT,tt.y);
				TERMIN.pop();
			}while(!TERMIN.empty()&&TERMIN.top().x==tt.x);
			while(!WAIT.empty())
			{
				Input ti=WAIT.front();
				ti.T=tt.x;
				SETLF=SETRF=-1;
				//printf("WAIT=(%d,%d,%d)\n",ti.T,ti.M,ti.P);
				int pos=insert(RT,ti.M,0,N);
				if(pos!=-1)
				{
					if(ti.P)TERMIN.push(newpair(ti.T+ti.P,pos));
					else remove(RT,pos);
					if(B)
					{
						printf("%d %d %d\n",ti.T,ti.i,pos);
					}
				}
				else break;
				WAIT.pop();
			}
		}
		printf("%d\n%d\n\n",endtime,waited);
	}
	return 0;
}
