#include<cstdio>
#include<cstdlib>
#include<queue>
#include<ctime>
#include<string>
#define max(x,y) (x)>(y)?(x):(y)
#define min(x,y) (x)<(y)?(x):(y)
#define LL long long
using namespace std;
struct Pair
{
	LL x,y;
	bool operator<(Pair a)const{if(x!=a.x)return x>a.x;return y>a.y;}
};
Pair newpair(LL x,LL y){Pair ans;ans.x=x,ans.y=y;return ans;}
LL N,B;
priority_queue<Pair> TERMIN;
struct Node
{
	LL f,pos,len,lfree,rfree,mfree,lpos,rpos;
	Node *ch[2];
	Node(LL pos,LL len,LL totalfree):pos(pos),len(len)
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
string shownode(Node *o)
{
	char a[1000];
	sprintf(a,"pos=%lld,len=%lld,lfree=%lld,rfree=%lld,mfree=%lld,lpos=%lld,rpos=%lld\n"
	,o->pos,o->len,o->lfree,o->rfree,o->mfree,o->lpos,o->rpos);
	string tts=a;
	return tts;
}
Node *RT=NULL;
string showall(Node *o,LL dep)
{
	string ans;
	if(o==NULL)return ans;
	for(LL i=0;i<dep;i++)ans+="  ";
	//for(LL i=0;i<dep;i++)printf("  ");
	ans+=shownode(o);
	ans+=showall(o->ch[0],dep+1);
	ans+=showall(o->ch[1],dep+1);
	if(dep==0)printf("%s\n",ans.c_str());
	return ans;
}
LL SETLF,SETRF;
void setfree(Node* &o,LL d)
{
	if(o==NULL||(d==0&&SETRF==-1)||(d==1&&SETLF==-1))return;
	setfree(o->ch[d],d);
	if(d==0&&SETLF!=-1)o->lfree=SETLF,SETLF=-1;
	if(d==1&&SETRF!=-1)o->rfree=SETRF,SETRF=-1;
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
void rotate(Node* &o,LL d)
{
	Node *k=o->ch[d^1];
	o->ch[d^1]=k->ch[d];
	k->ch[d]=o;
	o->maintain(),k->maintain();
	o=k;
}
LL insert(Node* &o,LL len,LL pos,LL freegap)
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
	LL d=-1,ans=-1;
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
	else if(o->ch[0]==NULL&&o->lfree>=len)ans=insert(o->ch[d=0],len,o->pos-o->lfree,o->lfree);
	else if(o->ch[0]!=NULL&&o->ch[0]->mfree>=len)ans=insert(o->ch[d=0],len,0,0);
	else if(o->ch[1]==NULL&&o->rfree>=len)ans=insert(o->ch[d=1],len,o->pos+o->len,o->rfree);
	else if(o->ch[1]!=NULL&&o->ch[1]->mfree>=len)ans=insert(o->ch[d=1],len,0,0);
	if(ans==-1)return -1;
	if(d==-1)printf("d==-1,error\n");
	if(d==0&&SETLF!=-1)o->lfree=SETLF,SETLF=-1;
	if(d==1&&SETRF!=-1)o->rfree=SETRF,SETRF=-1;
	o->maintain();
	if(o->f<o->ch[d]->f)rotate(o,d^1);
	return ans;
}
void remove(Node* &o,LL p)
{
	LL d;
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
			setfree(o,d^1);
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
struct Input{LL T,M,P,i;};
queue<Input> WAIT;
int main()
{
	freopen("inn.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	srand(time(NULL));
	//int kase=1;
	while(scanf("%lld%lld",&N,&B)==2)
	{
		while(!TERMIN.empty())TERMIN.pop();
		while(!WAIT.empty())WAIT.pop();
		removetree(RT);
		Input I;
		LL waited=0,endtime=0,processn=1;
		while(scanf("%lld%lld%lld",&I.T,&I.M,&I.P)==3&&(I.T||I.M||I.P))
		{
			I.i=processn++;
			LL pos;
			while(!TERMIN.empty())
			{
				printf("enter termin...\n");
				Pair tt;
				do
				{
					tt=TERMIN.top();
					if(tt.x>I.T)break;
					printf("terminate (%lld,%lld)\n",tt.x,tt.y);
					endtime=tt.x;
				printf("before remove:\n");showall(RT,0);
					remove(RT,tt.y);
				printf("after remove:\n");showall(RT,0);
					TERMIN.pop();
				}while(!TERMIN.empty()&&TERMIN.top().x==tt.x);
				if(tt.x>I.T)break;
				while(!WAIT.empty())
				{
					Input ti=WAIT.front();
					ti.T=tt.x;
					SETLF=SETRF=-1;
					string backup=showall(RT,0);
			printf("before insert:I=(%lld,%lld,%lld)\n",ti.T,ti.M,ti.P);showall(RT,0);
					pos=insert(RT,ti.M,0,N);
			printf("after insert:\n");showall(RT,0);
			printf("pos=%lld\n",pos);
					if(pos<-1)
					{
						printf("%s\n%s\n",backup.c_str(),showall(RT,0).c_str());
						printf("error\n");
						return 0;
					}
					if(pos!=-1)
					{
						if(ti.P)TERMIN.push(newpair(ti.T+ti.P,pos));
						else remove(RT,pos);
						if(B)
						{
							printf("%lld %lld %lld\n",ti.T,ti.i,pos);
						}
					}
					else break;
					WAIT.pop();
				}
			}
			SETLF=SETRF=-1;
			printf("before insert:I=(%lld,%lld,%lld)\n",I.T,I.M,I.P);showall(RT,0);
			pos=insert(RT,I.M,0,N);
			printf("after insert:\n");showall(RT,0);
			printf("pos=%lld\n",pos);
			if(pos!=-1)
			{
				if(I.P)TERMIN.push(newpair(I.T+I.P,pos));
				else remove(RT,pos);
				if(B)
				{
					printf("%lld %lld %lld\n",I.T,I.i,pos);
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
				printf("WAIT=(%lld,%lld,%lld)\n",ti.T,ti.M,ti.P);
				LL pos=insert(RT,ti.M,0,N);
				if(pos!=-1)
				{
					if(ti.P)TERMIN.push(newpair(ti.T+ti.P,pos));
					else remove(RT,pos);
					if(B)
					{
						printf("%lld %lld %lld\n",ti.T,ti.i,pos);
					}
				}
				else break;
				WAIT.pop();
			}
		}
		printf("%lld\n%lld\n\n",endtime,waited);
	}
	return 0;
}
