#include<cstdio>
#include<cstdlib>
int n,pos,neg;
struct pairtype
{
	int x;
	int y;
	int tris;
	int index;
	double dx;
	double dy;
};
pairtype S[1200],tmp[1200],P[1200],N[1200];
int findP(double a)//dx
{
	int Min=0,Max=pos+1,mid;
	do
	{
		mid=(Min+Max)/2;
		if(P[mid].dx<a) Min=mid;
		else Max=mid;
	}while(Max-Min>1);
	return P[Min].dx>a?Min:Max;
}
int findN(double a)
{
	int Min=0,Max=neg+1,mid;
	do
	{
		mid=(Min+Max)/2;
		if(N[mid].dx<a) Min=mid;
		else Max=mid;
	}while(Max-Min>1);
	return N[Min].dx>a?Min:Max;
}
double sqrt(double a)
{
	double b=0,c=a,d;
	do
	{
		d=(b+c)/2;
		if(d*d>a) c=d;
		else b=d;
	}while(c-b>1e-10);
	return (b+c)/2;
}
void makevector(int a)
{
	double b,c,d;
	for(int i=0;i<n;i++)
	{
		if(i!=a)
		{
			b=S[i].x-S[a].x;
			c=S[i].y-S[a].y;
			d=sqrt(b*b+c*c);
			S[i].dx=b/d;
			S[i].dy=c/d;
		}
	}
}
void rangedx(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	rangedx(a,mid);
	rangedx(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&S[c].dx<S[d].dx))
		{
			tmp[i]=S[c++];
		}
		else
		{
			tmp[i]=S[d++];
		}
	}
	for(int i=a;i<=b;i++) S[i]=tmp[i];
}
void rangeindex(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	rangeindex(a,mid);
	rangeindex(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&S[c].index<S[d].index))
		{
			tmp[i]=S[c++];
		}
		else
		{
			tmp[i]=S[d++];
		}
	}
	for(int i=a;i<=b;i++) S[i]=tmp[i];
}
int main()
{
	int T=1;
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(scanf("%d",&n)==1&&n)
	{
		for(int i=0;i<n;i++)
		{
			scanf("%d%d",&S[i].x,&S[i].y);
			S[i].index=i;
			S[i].tris=0;
		}
		double ans=0;
		for(int i=0;i<n;i++)
		{
			makevector(i);
			//for(int j=0;j<n;j++) printf(",%.3lf %.3lf",S[j].dx,S[j].dy);printf("\n");
			rangedx(0,n-1);
			//for(int j=0;j<n;j++) printf(",%.3lf %.3lf",S[j].dx,S[j].dy);printf("\n");
			pos=-1,neg=-1;
			for(int j=0;j<n;j++)
			{
				if(S[j].index==i) continue;
				if(S[j].dy>0)
				{
					S[j].tris=++pos;
					P[pos]=S[j];
				}
				else
				{
					S[j].tris=++neg;
					N[neg]=S[j];
				}
			}
			for(int j=0,k;j<n;j++)
			{
				if(S[j].index==i) continue;
				if(S[j].dy>0)//+-++---+-+-++-+--
				{
					k=findN(-S[j].dx);
					//if(dx<0) find N[j].dx>-dx
					//if(dx>0) find N[j].dx>-dx
					//printf(",%d %d",k,neg+1);
					ans+=k*(neg-k+1);
				}
				else
				{
					k=findP(-S[j].dx);
					//if(dx<0) find P[j].dx>-dx
					//if(dx>0) find P[j].dx>-dx
					//printf(",%d %d",k,pos+1);
					ans+=k*(pos-k+1);
				}
			}
			rangeindex(0,n-1);
			//printf("\n%.0lf\n",ans);
		}
		ans/=n*(n-1)/2*(n-2)/3;
		printf("City %d: %.2lf\n",T++,ans);//C(n,3)
	}
	return 0;
}
