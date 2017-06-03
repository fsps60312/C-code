#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
int N,M,S[3000000];
vector<int>RIDX;
struct Bst
{
	struct Node
	{
		Node *l,*r;
		int tag,mn;
		Node():l(NULL),r(NULL),tag(0),mn(0){}
	}*ROOT=NULL;
	void Build(Node* &o,const int l,const int r)
	{
		o=new Node();
		if(l==r)return;
		const int mid=(l+r)>>1;
		Build(o->l,l,mid),Build(o->r,mid+1,r);
	}
	void Build(){Build(ROOT,0,M-2);}
	void PutDown(Node* &o)
	{
		if(o->tag==0)return;
		int &v=o->tag;
		o->l->tag+=v,o->l->mn+=v;
		o->r->tag+=v,o->r->mn+=v;
		v=0;
	}
	void Maintain(Node* &o){o->mn=min(o->l->mn,o->r->mn);}
	void Modify(Node* &o,const int l,const int r,const int bl,const int br,const int v)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){o->tag+=v,o->mn+=v;return;}
		PutDown(o);
		const int mid=(l+r)>>1;
		Modify(o->l,l,mid,bl,br,v),Modify(o->r,mid+1,r,bl,br,v);
		Maintain(o);
	}
	void Modify(const int bl,const int br,const int v){Modify(ROOT,0,M-2,bl,br,v);}
	void SetZero(Node* &o,const int l,const int r)
	{
		if(l==r)
		{
			if(o->mn>0)o->tag--,o->mn--;
			return;
		}
		PutDown(o);
		const int mid=(l+r)>>1;
		if(o->r->mn>0)o->r->tag--,o->r->mn--,SetZero(o->l,l,mid);
		else SetZero(o->r,mid+1,r);
		Maintain(o);
	}
	void SetZero(){SetZero(ROOT,0,M-2);}
	bool Output(Node* &o,const int l,const int r,LL &ans)
	{
		if(l==r)
		{
			const LL &v=(LL)(o->mn)*(LL)(RIDX[r+1]-RIDX[r]);
			if(v<0LL){ans+=v;return false;}
			else return true;
		}
		PutDown(o);
		const int mid=(l+r)>>1;
		if(Output(o->l,l,mid,ans))return true;
		if(Output(o->r,mid+1,r,ans))return true;
		return false;
	}
	void Solve(LL &ans){Output(ROOT,0,M-2,ans);}
}BST;
LL SUM;
void GetInt(int &ans)
{
	ans=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')ans=ans*10+(c-'0'),c=getchar();
}
int main()
{
//	freopen("in.txt","r",stdin);
	GetInt(N);
	RIDX.push_back(0);
	for(int i=0;i<N;i++)GetInt(S[i]),RIDX.push_back(S[i]);
	sort(RIDX.begin(),RIDX.end());
	RIDX.resize(unique(RIDX.begin(),RIDX.end())-RIDX.begin());
	M=RIDX.size();
	SUM=0LL;
	for(int i=0;i<N;i++)SUM+=S[i],S[i]=(lower_bound(RIDX.begin(),RIDX.end(),S[i])-RIDX.begin());
	BST.Build();
	for(int i=0;i<N;i++)
	{
		const int idx=S[i];
		BST.Modify(0,idx-1,-1);
		BST.Modify(idx,M-2,1);
		BST.SetZero();
	}
	BST.Solve(SUM);
	printf("%lld\n",SUM);
	return 0;
}
