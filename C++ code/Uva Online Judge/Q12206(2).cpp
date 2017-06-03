#include<cstdio>
#include<cstdlib>
int n,m,sa[40001],t1[3][40001],rank[40001],height[40001];
char S[40001];
void getsa()
{
	int i,*x=t1[0],*y=t1[1],*c=t1[2];
	int l='z'+1;
	for(i=0;i<l;i++)c[i]=0;
	for(i=0;i<n;i++)c[x[i]=S[i]]++;
	for(i=1;i<l;i++)c[i]+=c[i-1];
	for(i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int p=0;
		for(i=n-k;i<n;i++)y[p++]=i;
		for(i=0;i<n;i++)if(sa[i]>=k)y[p++]=sa[i]-k;//sort second value
		for(i=0;i<l;i++)c[i]=0;
		for(i=0;i<n;i++)c[x[i]]++;
		for(i=1;i<l;i++)c[i]+=c[i-1];
		for(i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];//sort by first->second
		int *tmp=x;x=y,y=tmp;
		p=1,x[sa[0]]=0;
		for(i=1;i<n;i++)x[sa[i]]=y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]?p-1:p++;
		if(p>=n)break;
		l=p;
	}
}
void getheight()
{
	int i,k=0;
	for(i=0;i<n;i++)rank[sa[i]]=i;
	for(i=0;i<n;i++)
	{
		if(k)k--;
		if(!rank[i])continue;
		int j=sa[rank[i]-1];
		while(S[i+k]==S[j+k])k++;
		height[rank[i]]=k;
	}
}
int pos;
bool isans(int hv)
{
	int ans=1,tpos=sa[0];
	pos=-1;
	for(int i=1;i<n;i++)
	{
		if(height[i]>=hv)
		{
			ans++;
			if(sa[i]>tpos)tpos=sa[i];
			if(ans>=m&&tpos>pos)pos=tpos;
		}
		else ans=1,tpos=sa[i];
	}
	return pos>=0;
}
int getans()
{
	int l=1,r=n+1;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(isans(mid))l=mid+1;
		else r=mid;
	}
	if(r-1)isans(r-1);
	return r-1;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(scanf("%d",&m)==1&&m)
	{
		scanf("%s",S);
		n=-1;while(S[++n]);
		if(m==1){printf("%d 0\n",n);continue;}
		getsa();
		getheight();
		//printf("height:");for(int i=0;i<n;i++)printf(" %d",height[i]);printf("\n");
		int ans=getans();
		if(ans)printf("%d %d\n",ans,pos);
		else printf("none\n");
	}
	return 0;
}
