#include<cstdio>
//#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void assert(bool valid){if(valid)return;int a=0,b=0;a/=b;}
struct Node
{
	Node *ch[2];
	int sum;
	Node(const int _sum):sum(_sum){ch[0]=ch[1]=NULL;}
}*ST[100001];
Node *Build(const int l,const int r)
{
	Node *ans=new Node(0);
	if(l<r)
	{
		const int mid=(l+r)/2;
		ans->ch[0]=Build(l,mid),ans->ch[1]=Build(mid+1,r);
	}
	return ans;
}
Node *Add(Node *o,const int l,const int r,const int loc)
{
	Node *ans=new Node((o->sum)+1);
	if(l<r)
	{
		const int mid=(l+r)/2;
		if(loc<=mid)ans->ch[0]=Add(o->ch[0],l,mid,loc),ans->ch[1]=o->ch[1];
		else ans->ch[0]=o->ch[0],ans->ch[1]=Add(o->ch[1],mid+1,r,loc);
	}
	return ans;
}
int Query(Node *lo,Node *ro,const int l,const int r,const int rank)
{
	if(l==r)return r;
	const int mid=(l+r)/2,ch0dif=(ro->ch[0]->sum)-(lo->ch[0]->sum);
	assert(ch0dif>=0);
	if(ch0dif>=rank)return Query(lo->ch[0],ro->ch[0],l,mid,rank);
	else return Query(lo->ch[1],ro->ch[1],mid+1,r,rank-ch0dif);
}
int N,M,S[100001];
vector<int>V;
int main()
{
//	freopen("in.txt","r",stdin);
	int querycount;
	while(scanf("%d%d",&N,&querycount)==2)
	{
		V.clear();
		for(int i=1;i<=N;i++)scanf("%d",&S[i]),V.push_back(S[i]);
		sort(V.begin(),V.end()),V.resize(M=unique(V.begin(),V.end())-V.begin());
		for(int i=1;i<=N;i++)S[i]=lower_bound(V.begin(),V.end(),S[i])-V.begin();
		ST[0]=Build(0,M-1);
		for(int i=1;i<=N;i++)ST[i]=Add(ST[i-1],0,M-1,S[i]);
		for(int l,r,k;querycount--;)
		{
			scanf("%d%d%d",&l,&r,&k);
			printf("%d\n",V[Query(ST[l-1],ST[r],0,M-1,k)]);
		}
		break;
	}
	return 0;
}
