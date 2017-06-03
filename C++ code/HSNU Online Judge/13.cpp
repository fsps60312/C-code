#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N;
struct Seg
{
	int x,y1,y2;
	bool i;
	Seg(){}
	Seg(int x,int y1,int y2,int i):x(x),y1(y1),y2(y2),i(i){}
	bool operator<(const Seg &s)const{return x!=s.x?x<s.x:i<s.i;}
};
vector<Seg>SEG;
struct Bst
{
	int cover[80000],v[80000];
	void Build(int id,int l,int r)
	{
		cover[id]=v[id]=0;
		if(l==r)return;
		int mid=(l+r)/2;
		Build(id*2,l,mid);
		Build(id*2+1,mid+1,r);
	}
	void Add(int id,int l,int r,int L,int R,int d)
	{
		if(l>R||r<L)return;
		if(L<=l&&r<=R){cover[id]+=d;v[id]+=d*(r-l+1);return;}
		int mid=(l+r)/2;
		Add(id*2,l,mid,L,R);
		Add(id*2+1,mid+1,r,L,R);
		v[id]=v[id*2]+v[id*2+1];
	}
	void Query(int id,int l,int r,int &x,int &y)
	{
		
	}
}BST;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		int l=INF,r=-INF;
		for(int i=0;i<N;i++)
		{
			static int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			SEG.push_back(Seg(x1,y1,y2,1));
			SEG.push_back(Seg(x2,y1,y2,-1)); 
			r=min(r,y1),l=max(l,y2);
		}
		sort(SEG.begin(),SEG.end());
		BST.Build(1,l,r);
		int ans=0;
		for(int i=0;i<SEG.size();)
		{
			if(i)
			int x=SEG[i].x;
			while(SEG[i].x==x)
			{
				BST.Add(1,l,r,SEG[i].y1,SEG[i].y2,SEG[i].i);
				i++;
			}
		}
	}
	return 0;
}
