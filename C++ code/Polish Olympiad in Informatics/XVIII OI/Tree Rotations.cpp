#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Bit
{
	int S[1000001],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	void Add(int i,const int v){while(i<=N)S[i]+=v,i+=i&(-i);}
	int Query(int i)const{int ans=0;while(i)ans+=S[i],i-=i&(-i);return ans;}
}BIT;
struct Node
{
	Node *ch[2];
	int v;
	LL sz;
	Node(const int _v):v(_v),sz(v?1LL:0LL){ch[0]=ch[1]=NULL;}
};
Node *Build()
{
	int v;scanf("%d",&v);
	Node *ans=new Node(v);
	if(v==0)
	{
		ans->ch[0]=Build();
		ans->ch[1]=Build();
		ans->sz=ans->ch[0]->sz+ans->ch[1]->sz;
	}
	return ans;
}
LL ANS;
void Solve(Node *o,vector<int>&s)
{
	if(!o->ch[0]){s.push_back(o->v);BIT.Add(o->v,1);return;}
	if(o->ch[0]->sz>o->ch[1]->sz)swap(o->ch[0],o->ch[1]);
	const int l=s.size();
	Solve(o->ch[0],s);
	const int r=s.size();
	for(int i=l;i<r;i++)BIT.Add(s[i],-1);
	Solve(o->ch[1],s);
	LL ta=0LL;
	for(int i=l;i<r;i++)ta+=BIT.Query(s[i]);
	ANS+=min(ta,((o->ch[0]->sz)*(o->ch[1]->sz))-ta);
	for(int i=l;i<r;i++)BIT.Add(s[i],1);
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	BIT.Clear(N);
	Node *root=Build();
	vector<int>s;
	Solve(root,s);
	printf("%lld\n",ANS);
//	for(int i=0;i<(int)s.size();i++)printf(" %d",s[i]);puts("");
	assert((int)s.size()==N);
	return 0;
}
