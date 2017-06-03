#include<cstdio>
//#include<cassert>
using namespace std;
void assert(bool valid){if(valid)return;while(1)printf("E");}
int N,M,U,SEQ[300001];
struct Node
{
	Node *ch[2];
	int sz,v;
	Node(int _v):sz(1),v(_v){ch[0]=ch[1]=NULL;}
}*V[300001];
struct Bit
{
	int Sz(Node* &o){return o?o->sz:0;}
	void Maintain(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
	void Rotate(Node* &o,int chup)
	{
		Node *u=o;
		o=o->ch[chup];
		u->ch[chup]=o->ch[chup^1];
		o->ch[chup^1]=u;
		Maintain(u);
		Maintain(o);
	}
	void Rotate(Node* &o)
	{
		if(Sz(o->ch[0])>Sz(o->ch[1])&&o->ch[0])Rotate(o,0);
		else if(Sz(o->ch[1])>Sz(o->ch[0])&&o->ch[1])Rotate(o,1);
	}
	void Add(Node* &o,int v)
	{
		if(!o){o=new Node(v);return;}
		if(v<o->v)Add(o->ch[0],v);
		else Add(o->ch[1],v);
		Maintain(o);
		Rotate(o);
	}
	void Remove(Node* &o)
	{
		if(o->ch[0]&&o->ch[1])
		{
			int chup=(Sz(o->ch[0])>Sz(o->ch[1])?0:1);
			Rotate(o,chup);
			Remove(o->ch[chup^1]);
			Maintain(o);
		}
		else if(o->ch[0])o=o->ch[0];
		else o=o->ch[1];
	}
	void Remove(Node* &o,int v)
	{
		assert(o);
		if(v==o->v){Remove(o);return;}
		else if(v<o->v)Remove(o->ch[0],v);
		else Remove(o->ch[1],v);
		Maintain(o);
		Rotate(o);
	}
	int Query(Node* &o,int v)
	{
		if(!o)return 0;
		if(v==o->v)return Sz(o->ch[0])+1;
		else if(v<o->v)return Query(o->ch[0],v);
		else return Sz(o->ch[0])+1+Query(o->ch[1],v);
	}
	void Clear()
	{
		for(int i=1;i<=N;i++)V[i]=NULL;
	}
	int lowbit(int i){return i&(-i);}
	void Add(int i,int v)
	{
		while(i<=N)
		{
			int sz=Sz(V[i]);
			Add(V[i],v);
			assert(Sz(V[i])==sz+1);
			i+=lowbit(i);
		}
	}
	int Query(int i,int v)
	{
		int ans=0;
		while(i)
		{
			ans+=Query(V[i],v);
			i-=lowbit(i);
		}
		return ans;
	}
	void Remove(int i,int v)
	{
		while(i<=N)
		{
			int sz=Sz(V[i]);
			Remove(V[i],v);
			assert(Sz(V[i])==sz-1);
			i+=lowbit(i);
		}
	}
}BIT;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&U)==3)
	{
		BIT.Clear();
		for(int i=1;i<=N;i++)
		{
			scanf("%d",&SEQ[i]);
//			puts("adding");
			BIT.Add(i,SEQ[i]);
//			puts("added");
		}
		for(int i=1;i<=M;i++)
		{
			static int l,r,v,p,k;
			scanf("%d%d%d%d",&l,&r,&v,&p);
			k=BIT.Query(r,v-1)-BIT.Query(l-1,v-1);
//			puts("removing");
			BIT.Remove(p,SEQ[p]);
//			puts("removed");
			SEQ[p]=(long long)U*k/(r-l+1);
//			puts("adding");
			BIT.Add(p,SEQ[p]);
//			puts("added");
		}
		for(int i=1;i<=N;i++)
		{
			printf("%d\n",SEQ[i]);
		}
	}
	return 0;
}
