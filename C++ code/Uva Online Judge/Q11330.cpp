#include<cstdio>
#include<cstdlib>
struct pairtype
{
	int x,y;
};
pairtype S[10000],tmp[10000];
int T,n,index[10000];
void rangeSx(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	rangeSx(a,mid);
	rangeSx(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&S[c].x<S[d].x)) tmp[i]=S[c++];
		else tmp[i]=S[d++];
	}
	for(int i=a;i<=b;i++) S[i]=tmp[i];
}
void rangeSy(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	rangeSy(a,mid);
	rangeSy(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&S[c].y<S[d].y)) tmp[i]=S[c++];
		else tmp[i]=S[d++];
	}
	for(int i=a;i<=b;i++) S[i]=tmp[i];
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%d%d",&S[i].x,&S[i].y);
		}
		rangeSy(0,n-1);
		for(int i=0;i<n;i++) S[i].y=i;
		rangeSx(0,n-1);
		for(int i=0;i<n;i++)
		{
			S[i].x=i;
			index[S[i].y]=i;
		}
		int ans=0;
		for(int i=0;i<n;i++)
		{
			if(S[i].y!=S[i].x)
			{
				int j=index[S[i].x];
				int k=S[j].y;
				S[j].y=S[i].y;
				S[i].y=k;
				index[S[i].y]=i;
				index[S[j].y]=j;
				ans++;
		//for(int j=0;j<n;j++) printf("%d %d\n",S[j].x,S[j].y);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
