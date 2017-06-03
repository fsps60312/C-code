#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
int K,M,M1,M2;
struct Node
{
	Node *ch[2];
	LL sz;
	int v;
	Node(int v):ch{NULL,NULL},sz(1LL),v(v){}
}*V[100001];
struct BIT
{
	void Clear(){for(int i=1;i<=M1;i++)V[i]=NULL;}
	int Lowbit(int i){return i&(-i);}
	LL Sz(Node* &o){return o?o->sz:0LL;}
	void Maintain(Node* &o){o->sz=Sz(o->ch[0])+1LL+Sz(o->ch[1]);}
	void Rotate(Node* &o,int cu)
	{
		Node *u=o;
		o=o->ch[cu];
		u->ch[cu]=o->ch[cu^1];
		o->ch[cu^1]=u;
		Maintain(u);
		Maintain(o);
	}
	void Rotate(Node* &o)
	{
		LL a=Sz(o->ch[0]),b=Sz(o->ch[1]);
		if(a>b&&o->ch[0])Rotate(o,0);
		else if(a<b&&o->ch[1])Rotate(o,1);
	}
	void Add(Node* &o,int v)
	{
		if(!o){o=new Node(v);return;}
		if(v<=o->v)Add(o->ch[0],v);
		else Add(o->ch[1],v);
		Maintain(o);
	}
	void Add(int i,int v)
	{
		while(i<=M1)
		{
			Add(V[i],v);
			i+=Lowbit(i);
		}
	}
	LL Query(Node* &o,int v,int up)
	{
		if(!o)return 0LL;
		if(v==o->v)return 1LL+Sz(o->ch[up]);
		else if(!(up^(v<o->v)))return Query(o->ch[up^1],v,up)+1LL+Sz(o->ch[up]);
		else return Query(o->ch[up],v,up);
	}
	LL Query(int i,int v,int up)
	{
		LL ans=0LL;
		while(i)
		{
			ans+=Query(V[i],v,up);
			i-=Lowbit(i);
		}
		return ans;
	}
}BIT;
struct Data
{
	int i,v,r;
	Data(){}
	Data(int i,int r):i(i),r(r){}
};
bool Cmpi(const Data &a,const Data &b){return a.i<b.i;}
bool Cmpr(const Data &a,const Data &b){return a.r<b.r;}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&K,&M)==2)
	{
		M1=M2=M;
		vector<Data>va,vb;
		for(int i=0,a;i<K;i++){scanf("%d",&a);va.push_back(Data(i,a));}
		for(int i=0,b;i<K;i++){scanf("%d",&b);vb.push_back(Data(i,b));}
		sort(va.begin(),va.end(),Cmpr);
		sort(vb.begin(),vb.end(),Cmpr);
		M1=M2=2;
		va[0].v=vb[0].v=1;
		for(int i=1;i<K;i++)
		{
			va[i].v=(va[i].r==va[i-1].r?M1-1:M1++);
			vb[i].v=(vb[i].r==vb[i-1].r?M2-1:M2++);
		}
		M1--,M2--;
		sort(va.begin(),va.end(),Cmpi);
		sort(vb.begin(),vb.end(),Cmpi);
		BIT.Clear();
		LL ans=0LL;
		for(int i=0;i<K;i++)
		{
			ans+=BIT.Query(va[i].v-1,vb[i].v+1,1);
			ans+=BIT.Query(M1,vb[i].v-1,0)-BIT.Query(va[i].v,vb[i].v-1,0);
			BIT.Add(va[i].v,vb[i].v);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
