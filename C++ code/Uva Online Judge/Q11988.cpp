#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
char S[100002];
struct nodetype
{
	int f,sum;
	char c;
	nodetype *ch[2];
	nodetype(char c):c(c)
	{
		f=rand();
		sum=1;
		ch[0]=ch[1]=NULL;
	}
	void maintain()
	{
		sum=1;
		if(ch[0]!=NULL)sum+=ch[0]->sum;
		if(ch[1]!=NULL)sum+=ch[1]->sum;
	}
};
void rotate(nodetype* &o,int d)
{
	nodetype *k=o->ch[d^1];
	o->ch[d^1]=k->ch[d];
	k->ch[d]=o;
	o->maintain(),k->maintain();
	o=k;
}
void push_back(nodetype* &o,char c)
{
	if(o==NULL)
	{
		o=new nodetype(c);
		return;
	}
	push_back(o->ch[1],c);
	o->maintain();
	if(o->f<o->ch[1]->f)rotate(o,0);
}
void removetree(nodetype* &o)
{
	if(o==NULL)return;
	removetree(o->ch[0]);
	removetree(o->ch[1]);
	delete o;
	o=NULL;
}
void sink(nodetype* &o)
{
	int d;
	if(o->ch[0]!=NULL&&o->ch[1]!=NULL)
	{
		d=o->ch[0]->f>o->ch[1]->f?0:1;
	}
	else
	{
		if(o->ch[0]!=NULL)d=0;
		else if(o->ch[1]!=NULL)d=1;
		else return;
	}
	if(o->f>=o->ch[d]->f)return;
	rotate(o,d^1);
	sink(o->ch[d^1]);
}
void splayfront(nodetype* &o)
{
	if(o->ch[0]==NULL)return;
	splayfront(o->ch[0]);
	rotate(o,1);
}
void splayback(nodetype* &o)
{
	if(o->ch[1]==NULL)return;
	splayback(o->ch[1]);
	rotate(o,0);
}
nodetype *Ans,*Tmp;
void putfront()
{
	if(Tmp==NULL)return;
	if(Ans==NULL)Ans=Tmp;
	else
	{
		splayfront(Ans);
		Ans->ch[0]=Tmp;
		Ans->maintain();
		sink(Ans);
	}
	Tmp=NULL;
}
void putback()
{
	if(Tmp==NULL)return;
	if(Ans==NULL)Ans=Tmp;
	else
	{
		splayback(Ans);
		Ans->ch[1]=Tmp;
		Ans->maintain();
		sink(Ans);
	}
	Tmp=NULL;
}
void dfsprint(nodetype* &o)
{
	if(o==NULL)return;
	dfsprint(o->ch[0]);
	printf("%c",o->c);
	dfsprint(o->ch[1]);
}
int main()
{
	//freopen("in.txt","r",stdin);
	srand(time(NULL));
	while(fgets(S,100002,stdin))
	{
		removetree(Ans);
		removetree(Tmp);
		int i=0;
		char t;
		while(S[i]!='\n')
		{
			if(S[i]=='['||S[i]==']'){t=S[i++];break;}
			push_back(Ans,S[i]);
			i++;
		}
		while(S[i]!='\n')
		{
			if(S[i]=='['||S[i]==']')
			{
				if(t=='[')putfront();
				else putback();
				t=S[i];
			}
			else push_back(Tmp,S[i]);
			i++;
		}
		if(t=='[')putfront();
		else putback();
		dfsprint(Ans);printf("\n");
	}
	return 0;
}
