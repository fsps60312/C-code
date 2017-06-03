#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
struct Seg
{
	int x,y1,y2,i;
	Seg(){}
	Seg(int x,int y1,int y2,int i):x(x),y1(y1),y2(y2),i(i){}
	bool operator<(const Seg &s)const{return x!=s.x?x<s.x:i<s.i;}
};
vector<Seg>SEG[2];
struct Bst
{
	int cover[80000],v[80000];
	bool le[80000],re[80000];
	void Build(int id,int l,int r)
	{
		cover[id]=v[id]=0;
		le[id]=re[id]=false;
		if(l==r)return;
		int mid=(l+r)/2;
		Build(id*2,l,mid);
		Build(id*2+1,mid+1,r);
	}
	void Add(int id,int l,int r,int L,int R,int d)
	{
		if(l>R||r<L)return;
		if(L<=l&&r<=R)
		{
			cover[id]+=d;
			if(cover[id])
			{
				v[id]=2;
				le[id]=re[id]=true;
			}
			else if(l<r)
			{
				v[id]=v[id*2]+v[id*2+1];
				le[id]=le[id*2],re[id]=re[id*2+1];
				if(le[id*2+1]&&re[id*2])v[id]-=2;
			}
			else
			{
				v[id]=0;
				le[id]=re[id]=false;
			}
			return;
		}
		int mid=(l+r)/2;
		Add(id*2,l,mid,L,R,d);
		Add(id*2+1,mid+1,r,L,R,d);
		if(!cover[id])
		{
			v[id]=v[id*2]+v[id*2+1];
			le[id]=le[id*2],re[id]=re[id*2+1];
			if(le[id*2+1]&&re[id*2])v[id]-=2;
		}
		else
		{
			v[id]=2;
			le[id]=re[id]=true;
		}
	}
	int Query(){return v[1];}
}BST;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		SEG[0].clear(),SEG[1].clear();
		for(int i=0;i<N;i++)
		{
			static int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			x1+=10000,x2+=10000,y1+=10000,y2+=10000;
			SEG[0].push_back(Seg(x1,y1,y2,1));
			SEG[0].push_back(Seg(x2,y1,y2,-1));
			SEG[1].push_back(Seg(y1,x1,x2,1));
			SEG[1].push_back(Seg(y2,x1,x2,-1));
		}
		int ans=0;
		for(int k=0;k<2;k++)
		{
			sort(SEG[k].begin(),SEG[k].end());
			BST.Build(1,0,19999);
			for(int i=0;i<SEG[k].size();)
			{
				if(i)
				{
					int q=BST.Query();
					int dis=SEG[k][i].x-SEG[k][i-1].x;
					ans+=q*dis;
//					printf("ans=%d\n",ans);
				}
				int x=SEG[k][i].x;
				while(SEG[k][i].x==x)
				{
					BST.Add(1,0,19999,SEG[k][i].y1,SEG[k][i].y2-1,SEG[k][i].i);
					i++;
				}
			} 
		}
		printf("%d\n",ans);
	}
}
