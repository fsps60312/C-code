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
vector<Seg>SEG[2];
struct Bst
{
	int cover[80000],lb[80000],mb[80000],rb[80000];
	void Build(int id,int l,int r)
	{
		cover[id]=lb[id]=mb[id]=rb[id]=0;
//		printf("(%d,%d)\n",l,r);
		if(l==r)return;
		int mid=(l+r)/2;
		Build(id*2,l,mid);
		Build(id*2+1,mid+1,r);
	}
	void Add(int id,int l,int r,int L,int R,int d)
	{
		if(l>=R||r<L)return;
//		printf("%d %d\n",l,r);
		if(L<=l&&r<R)
		{
			cover[id]+=d;
			if(cover[id])
			{
				mb[id]=0;
				lb[id]=rb[id]=1;
			}
			else
			{
				mb[id]=l==r?0:abs(rb[id*2]-lb[id*2+1])+mb[id*2]+mb[id*2+1];
				lb[id]=lb[id*2],rb[id]=rb[id*2+1];
			}
			return;
		}
		int mid=(l+r)/2;
		Add(id*2,l,mid,L,R,d);
		Add(id*2+1,mid+1,r,L,R,d);
		if(!cover[id])
		{
			mb[id]=abs(rb[id*2]-lb[id*2+1])+mb[id*2]+mb[id*2+1];
			lb[id]=lb[id*2],rb[id]=rb[id*2+1];
		}
		else lb[id]=rb[id]=1,mb[id]=0;
	}
	int Query(){return lb[1]+mb[1]+rb[1];}
}BST;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		int l[2]={INF,INF},r[2]={-INF,-INF};
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
			l[0]=min(l[0],y1),r[0]=max(r[0],y2);
			l[1]=min(l[1],x1),r[1]=max(r[1],x2);
		}
		int ans=0;
		for(int k=0;k<2;k++)
		{
			printf("k=%d\n",k);
			sort(SEG[k].begin(),SEG[k].end());
			BST.Build(1,l[k],r[k]);
			for(int i=0;i<SEG[k].size();)
			{
				if(i)
				{
					int q=BST.Query();
					ans+=(SEG[k][i].x-SEG[k][i-1].x)*q;
					printf("q=%d,seg=%d,ans=%d\n",q,SEG[k][i].x-SEG[k][i-1].x,ans);
				}
				int x=SEG[k][i].x;
				while(SEG[k][i].x==x)
				{
					BST.Add(1,l[k],r[k],SEG[k][i].y1,SEG[k][i].y2,SEG[k][i].i);
					i++;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
