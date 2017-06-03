#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int T,N;
vector<LL>X,Y;
struct Node
{
	vector<Node*>ch;
	int v;
	Node(){}
	Node(int v):v(v){}
	bool cmp(const Node* &a,const Node* &b){return a->v<b->v;}
	void GetV()
	{
		static int sz,i,j,idx;sz=ch.size();
		for(i=0;i<sz;i++)
		{
			idx=i;
			for(int j=i+1;j<sz;j++)
			{
				if(ch[j]->v<ch[idx]->v)idx=j;
			}
			if(idx!=i)swap(ch[i],ch[idx]);
		}
		v=ch[sz/2]->v;
	}
};
void Build(Node* &o,vector<LL>&s,int l,int r)
{
	o=new Node();
	if(r-l+1<=5)
	{
		for(int i=l;i<=r;i++)o->ch.push_back(new Node(s[i]));
		o->GetV();
		return;
	}
	for(int p=1,li=l,ri;p<=5;p++)
	{
		ri=l+(r-l)*p/5;
		Node *ch=NULL;
		Build(ch,s,li,ri);
		o->ch.push_back(ch);
		li=ri+1;
	}
	o->GetV();
}
LL Select(vector<LL>&s)
{
	if(s.size()<=5){sort(s.begin(),s.end());return s[s.size()/2];}
	Node *root=NULL;
	Build(root,s,0,s.size()-1);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		X.clear(),Y.clear();
		for(int i=0;i<N;i++)
		{
			static LL x,y;
			scanf("%lld%lld",&x,&y);
			X.push_back(x),Y.push_back(y);
		}
		int x=Select(X),y=Select(Y);
		LL ans=0LL;
		for(int i=0;i<N;i++)ans+=abs(x-X[i])+abs(y-Y[i]);
		printf("%lld\n",ans);
	}
	return 0;
}
