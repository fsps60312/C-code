#include<cstdio>
#include<cstdlib>
struct pairtype
{
	int a;
	int b;
	int index;
	int tmp;
};
pairtype x[5001],y[5001],tmpx[5001],tmpy[5001];
int n;
bool cmp(pairtype a,pairtype b)
{
	if(a.a!=b.a) return a.a<b.a;
	return a.b<b.b;
}
void range(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	range(a,mid);
	range(mid+1,b);
	int cx=a,dx=mid+1,cy=a,dy=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(dx>b||(cx<=mid&&cmp(x[cx],x[dx])))
		{
			tmpx[i]=x[cx];
			cx++;
		}
		else
		{
			tmpx[i]=x[dx];
			dx++;
		}
		if(dy>b||(cy<=mid&&cmp(y[cy],y[dy])))
		{
			tmpy[i]=y[cy];
			cy++;
		}
		else
		{
			tmpy[i]=y[dy];
			dy++;
		}
	}
	for(int i=a;i<=b;i++)
	{
		x[i]=tmpx[i];
		y[i]=tmpy[i];
	}
}
void fillx(int a)
{
	int ans=a;
	for(int i=a+1;x[i].a<=a&&i<n;i++)
	{
		if(x[i].b<x[ans].b) ans=i;
	}
	pairtype c=x[a];
	x[a]=x[ans];
	x[ans]=c;
}
void filly(int a)
{
	int ans=a;
	for(int i=a+1;y[i].a<=a&&i<n;i++)
	{
		if(y[i].b<y[ans].b) ans=i;
	}
	pairtype c=y[a];
	y[a]=y[ans];
	y[ans]=c;
}
void rangeans(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	rangeans(a,mid);
	rangeans(mid+1,b);
	int cx=a,dx=mid+1,cy=a,dy=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(dx>b||(cx<=mid&&x[cx].index<x[dx].index))
		{
			tmpx[i]=x[cx];
			cx++;
		}
		else
		{
			tmpx[i]=x[dx];
			dx++;
		}
		if(dy>b||(cy<=mid&&y[cy].index<y[dy].index))
		{
			tmpy[i]=y[cy];
			cy++;
		}
		else
		{
			tmpy[i]=y[dy];
			dy++;
		}
	}
	for(int i=a;i<=b;i++)
	{
		x[i]=tmpx[i];
		y[i]=tmpy[i];
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&n)==1)
	{
		if(n==0) break;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d%d%d",&x[i].a,&y[i].a,&x[i].b,&y[i].b);
			x[i].index=y[i].index=i;
		}
		range(1,n);
		//for(int i=1;i<=n;i++) printf("%d %d %d %d\n",x[i].a,x[i].b,y[i].a,y[i].b);printf("\n");
		for(int i=1;i<=n;i++)
		{
			fillx(i);
			filly(i);
		//system("pause");
		}
		//for(int i=1;i<=n;i++) printf("%d %d %d %d\n",x[i].a,x[i].b,y[i].a,y[i].b);printf("\n");
		bool found=true;
		for(int i=1;i<=n;i++)
		{
			x[i].tmp=i;
			if(i<x[i].a||i>x[i].b)
			{
				found=false;
				break;
			}
			y[i].tmp=i;
			if(i<y[i].a||i>y[i].b)
			{
				found=false;
				break;
			}
		}
		if(!found) printf("IMPOSSIBLE\n");
		else
		{
			rangeans(1,n);
			for(int i=1;i<=n;i++) printf("%d %d\n",x[i].tmp,y[i].tmp);
		}
	}
	return 0;
}
