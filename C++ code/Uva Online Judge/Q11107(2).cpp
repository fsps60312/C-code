#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
const int MAXN=200000;
char S[MAXN];
int n,L,sa[MAXN],t1[MAXN],t2[MAXN],t3[MAXN],idx[MAXN],rank[MAXN],height[MAXN];
vector<int> Ans;
void getsa()
{
	int i,*x=t1,*y=t2,*c=t3,m='z'+100;
	for(i=0;i<m;i++)c[i]=0;
	for(i=0;i<L;i++)c[x[i]=S[i]+99]++;
	for(i=1;i<m;i++)c[i]+=c[i-1];
	for(i=L-1;i>=0;i--)sa[--c[x[i]]]=i;
	for(int k=1;k<=L;k<<=1)
	{
		int p=0;
		for(i=L-k;i<L;i++)y[p++]=i;
		for(i=0;i<L;i++)if(sa[i]>=k)y[p++]=sa[i]-k;//sort second value
		for(i=0;i<m;i++)c[i]=0;
		for(i=0;i<L;i++)c[x[i]]++;
		for(i=1;i<m;i++)c[i]+=c[i-1];
		for(i=L-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
		p=1,y[sa[0]]=0;
		for(i=1;i<L;i++)
		{
			y[sa[i]]=x[sa[i]]==x[sa[i-1]]&&x[sa[i]+k]==x[sa[i-1]+k]?p-1:p++;
		}
		if(p==L)break;
		m=p;
		int *tt1=x;x=y,y=tt1;
	}
}
void getheight()
{
	int i,k=0;
	for(i=0;i<L;i++)rank[sa[i]]=i;
	for(i=0;i<L;i++)
	{
		//k=0;
		if(k)k--;
		if(!rank[i])continue;
		int j=sa[rank[i]-1];
		while(S[i+k]==S[j+k])k++;
		height[rank[i]]=k;
	}
}
bool isans(int hv)
{
	int *x=t1;Ans.clear();
	for(int i=0;i<n;i++)x[i]=0;
	for(int i=1,ans=0,j=1;i<L;i++,j++,ans=0)
	{
		while(i<L&&height[i]>=hv)
		{
			//if(idx[sa[i]]==-1||idx[sa[i-1]]==-1){printf("i=%d,%d>=%d,sa[i-1]=%d,sa[i]=%d, error!\n",i,height[i],hv,sa[i-1],sa[i]);i++;continue;}
			if(x[idx[sa[i]]]!=j)x[idx[sa[i]]]=j,ans++;
			if(x[idx[sa[i-1]]]!=j)x[idx[sa[i-1]]]=j,ans++;
			i++;
		}
		if(ans>n/2)
		{
			Ans.push_back(sa[i-1]);
		}
	}
	return Ans.size()>0;
}
int getans()//something went wrong here
{
	int r=1,l=L-1;
	while(r<l)
	{
		int mid=(r+l)/2;
		if(isans(mid))r=mid+1;
		else l=mid;
	}
	if(r-1)isans(r-1);
	return r-1;
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=0;
	while(scanf("%d",&n)==1&&n)
	{
		if(kase++)printf("\n");
		if(n==1)
		{
			scanf("%s",S);
			printf("%s\n",S);
			continue;
		}
		L=0;
		for(int i=0;i<n;i++)
		{
			scanf("%s",S+L);
			while(S[L])idx[L++]=i;
			idx[L]=-1;
			S[L++]='a'-1-i;
			S[L]=0;
		}
		getsa();
		/*for(int i=0;i<L;i++)t1[i]=0;
		for(int i=0;i<L;i++)
		{
			if(t1[sa[i]])printf("error!\n");
			t1[sa[i]]++;
		}*/
		//printf("sa:");for(int i=0;i<L;i++)printf(" %d",sa[i]);printf("\n");
		getheight();
		/*for(int i=0;i<L;i++)
		{
			if(idx[i]==-1)
			{
				//printf("height:%d %d\n",height[rank[i]],height[rank[i]+1]);
			}
		}*/
		/*for(int i=0;i<L;i++)t1[i]=0;
		for(int i=0;i<L;i++)
		{
			if(t1[rank[i]])printf("error!\n");
			t1[rank[i]]++;
		}*/
		//printf("he:");for(int i=0;i<L;i++)printf(" %d",height[i]);printf("\n");
		int ans=getans();//printf("ans=%d\n",ans);
		if(Ans.size())
		{
			for(int i=0;i<Ans.size();i++)
			{
				//printf("%d\n",Ans[i]);
				for(int j=0;j<ans;j++)
				{
					printf("%c",S[Ans[i]+j]);
				}
				printf("\n");
			}
		}
		else printf("?\n");
	}
	return 0;
}
