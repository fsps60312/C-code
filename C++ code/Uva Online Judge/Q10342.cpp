#include<cstdio>
#include<cstdlib>
int C,R;
struct Pair
{
	int x,y;
};
Pair MAT[100][100];
void setMAT(Pair &p,int dis)
{
	if(p.x==-1){p.x=dis;return;}
	else if(dis<p.x){p.y=p.x;p.x=dis;return;}
	else if(dis==p.x)return;
	if(p.y==-1){p.y=dis;return;}
	else if(dis<p.y)p.y=dis;
}
void setMAT(int i,int j,int dis)
{
	if(i>j)i^=j^=i^=j;
	setMAT(MAT[i][j],dis);
}
void setMAT(int i,int j,Pair p)
{
	if(p.x!=-1)setMAT(i,j,p.x);
	if(p.y!=-1)setMAT(i,j,p.y);
}
Pair getMAT(int i,int j)
{
	if(i>j)i^=j^=i^=j;
	return MAT[i][j];
}
Pair mergeMAT(Pair a,Pair b)
{
	Pair ans=(Pair){-1,-1};
	if(a.x!=-1)
	{
		if(b.x!=-1)setMAT(ans,a.x+b.x);
		if(b.y!=-1)setMAT(ans,a.x+b.y);
	}
	if(a.y!=-1)
	{
		if(b.x!=-1)setMAT(ans,a.y+b.x);
		if(b.y!=-1)setMAT(ans,a.y+b.y);
	}
	return ans;
}
void pre_cal()
{
	for(int k=0;k<C;k++)
	{
		for(int i=0;i<C;i++)
		{
			for(int j=i;j<C;j++)
			{
				setMAT(i,j,mergeMAT(getMAT(i,k),getMAT(k,j)));
			}
		} 
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int kase=1;
	while(scanf("%d%d",&C,&R)==2)
	{
		for(int i=0;i<C;i++){for(int j=i;j<C;j++)MAT[i][j]=(Pair){-1,-1};MAT[i][i].x=0;}
		while(R--)
		{
			int a,b,d;scanf("%d%d%d",&a,&b,&d);
			setMAT(a,b,d);
		}
		pre_cal();
		pre_cal();
		int q;scanf("%d",&q);
		printf("Set #%d\n",kase++);
		while(q--)
		{
			int a,b;scanf("%d%d",&a,&b);
			int ans=getMAT(a,b).y;
			if(ans==-1)printf("?\n");
			else printf("%d\n",ans);
		}
	}
	return 0;
}
