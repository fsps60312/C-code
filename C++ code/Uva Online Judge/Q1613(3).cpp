#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
void getmax(int &a,int b){if(b>a)a=b;}
int N,M,K,DEG[9999],ANS[9999];
vector<int>TO[9999];
vector<int>ORDER;
struct Node
{
	Node *ch[2];
	int c,sz;
	Node(int c):c(c),sz(1),ch{NULL,NULL}{}
}*C[9999];
int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+(o->c?1:0)+Sz(o->ch[1]);
}
void Insert(Node* &o,int c,int l,int r)
{
	if(!o){o=new Node(c);return;}
	if(l==r)return;
	if(o->c)
	{
		if(o->c==c)return;
		int cr=o->c;
		o->c=0;
		Insert(o,cr,l,r);
		Insert(o,c,l,r);
	}
	else
	{
		int mid=(l+r)/2;
		if(c<=mid)Insert(o->ch[0],c,l,mid);
		else Insert(o->ch[1],c,mid+1,r);
		Maintain(o);
	}
}
int Query(Node* &o,int l,int r)
{
	if(!o)return r;
	if(o->c)return o->c==r?r-1:r;
	int mid=(l+r)/2;
	if(Sz(o->ch[1])<r-mid)return Query(o->ch[1],mid+1,r);
	else return Query(o->ch[0],l,mid);
}
void Dfs(int u)
{
	if(DEG[u]==-1)return;
	DEG[u]=-1;
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		Dfs(j);
	}
	ORDER.push_back(u);
}
void DecideOrder()
{
	ORDER.clear();
	Dfs(0);
}
void solve()
{
	DecideOrder();
	assert(ORDER.size()==N);
	for(int ti=N-1;ti>=0;ti--)
	{
		int &i=ORDER[ti];
		ANS[i]=Query(C[i],1,K);
		for(int j=0;j<TO[i].size();j++)
		{
			int &k=TO[i][j];
			Insert(C[k],ANS[i],1,K);
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		static int kase=0;
		if(kase++)puts("");
		for(int i=0;i<N;i++)
		{
			TO[i].clear();
			DEG[i]=0;
			C[i]=NULL;
		}
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			a--,b--;
			TO[a].push_back(b);
			TO[b].push_back(a);
			DEG[a]++,DEG[b]++;
		}
		K=0;
		for(int i=0;i<N;i++)getmax(K,DEG[i]);
		if(K%2==0)K++;
		printf("%d\n",K);
		solve();
		for(int i=0;i<N;i++)printf("%d\n",ANS[i]);
	}
	return 0;
}
