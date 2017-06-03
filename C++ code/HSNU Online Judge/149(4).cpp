#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
int N,M,S[3000000];
struct Bst
{
	struct Node
	{
		Node *l,*r;
		int tag,mn;
		Node():l(NULL),r(NULL),tag(0),mn(0){}
	}*ROOT=new Node();
	void PutDown(Node* &o)
	{
		if(!o->l)o->l=new Node();
		if(!o->r)o->r=new Node();
		int &v=o->tag;
		if(v==0)return;
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
	void Output(Node* &o,const int l,const int r,int *ans)
	{
		if(l==r){ans[r]=o->mn;return;}
		PutDown(o);
		const int mid=(l+r)>>1;
		Output(o->l,l,mid,ans),Output(o->r,mid+1,r,ans);
	}
	void Output(int *ans){Output(ROOT,0,M-2,ans);}
}BST;
map<int,int>IDX;
vector<int>RIDX;
typedef long long LL;
LL Solve()
{
	int *slopes=new int[2999999];
	BST.Output(slopes);
	LL y=0LL;
	for(int i=0;i<N;i++)y+=S[i];
	for(int i=0;i<M-1;i++)
	{
		const LL &v=(LL)slopes[i]*(LL)(RIDX[i+1]-RIDX[i]);
		if(v<0LL)y+=v;
		else return y;
	}
	return y;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	IDX[0]=-1;
	for(int i=0;i<N;i++)scanf("%d",&S[i]),IDX[S[i]]=-1;
	if(true)
	{
		int cnt=0;
		for(auto &it:IDX)it.second=cnt++,RIDX.push_back(it.first);
	}
	M=IDX.size();
	for(int i=0;i<N;i++)
	{
		const int idx=IDX[S[i]];
		BST.Modify(0,idx-1,-1);
		BST.Modify(idx,M-2,1);
		BST.SetZero();
	}
	IDX.clear();
	map<int,int>().swap(IDX);
	printf("%lld\n",Solve());
	return 0;
}
