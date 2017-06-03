#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int n,L,idx[100101],sa[100101],t1[100101],t2[100101],t3[100101];
char S[100101];
void getsa()
{
	int *c=t3,*x=t1,*y=t2;
	int m=100101;
	for(int i=0;i<m;i++)c[i]=0;
	for(int i=0;i<L;i++)c[x[i]=S[i]-'a']++;
	for(int i=1;i<m;i++)c[i]+=c[i-1];
	for(int i=L-1;i>=0;i--)sa[--c[x[i]]]=i;
	for(int k=1;k<=L;k<<=1)
	{
		int p=0;
		for(int i=L-k;i<L;i++)y[p++]=i;
		for(int i=0;i<L;i++)if(sa[i]>=k)y[p++]=sa[i]-k;//sort second val
		for(int i=0;i<m;i++)c[i]=0;
		for(int i=0;i<L;i++)c[x[i]]++;
		for(int i=1;i<m;i++)c[i]+=c[i-1];
		for(int i=L-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];//sort by kth, then idx
		p=1,y[sa[0]]=0;
		for(int i=1;i<L;i++)
		{
			y[sa[i]]=x[sa[i]]==x[sa[i-1]]&&x[sa[i]+k]==x[sa[i-1]+k]?p-1:p++;//cal equal group
		}
		if(p>=L)break;
		m=p;
		int *tmp=x;x=y,y=tmp;
	}
}
int height[100101];
int rank[100101];
void getheight()
{
	//int *rank=t1;
	for(int i=0;i<L;i++)rank[sa[i]]=i;
	int k=0;
	for(int i=0;i<L;i++)
	{
		if(k)k--;
		if(rank[i]==0){height[i]=-1;continue;}
		int j=sa[rank[i]-1];
		if(j==i)printf("error!\n");
		while(S[j+k+1]&&S[i+k+1]&&S[j+k]==S[i+k])k++;
		height[rank[i]]=k;
	}
}
vector<int> Ans;
bool isans(int lcpl)
{
	int *x=t1;
	for(int i=0;i<n;i++)x[i]=0;
	Ans.clear();
	for(int i=1,j=1,ans=0;i<L;i++,j++,ans=0)
	{
		while(height[i]>=lcpl)
		{
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
int getans()
{
	int L=1,R=1000;
	while(L<R)
	{
		int mid=(L+R)/2;
		if(!isans(mid))R=mid;
		else L=mid+1;
	}
	isans(R-1);
	return R-1;
}
int main()
{
	freopen("in.txt","r",stdin);
	int kase=0;
	while(scanf("%d",&n)==1&&n)
	{
		if(kase++)printf("\n");
		L=0;
		for(int i=0;i<n;i++)
		{
			scanf("%s",S+L);
			while(S[L])idx[L++]=i;
			S[L]='z'+i+1;
			idx[L++]=-1;
			S[L]=0;
			//printf(" %d",L);
		}
		getsa();
		printf("sa:");for(int i=0;i<L;i++)printf(" %d",sa[i]);printf("\n");
		getheight();
		//for(int i=0;i<L;i++)printf(" %d",height[i]);printf("\n");
		//for(int i=0;i<L;i++)printf(" %d",idx[i]);printf("\n");
		int ans=getans();printf("ans=%d\n",ans);
		if(ans)
		{
			for(int i=0;i<Ans.size();i++)
			{
				for(int j=0;j<ans;j++)printf("%c",S[Ans[i]+j]);
				printf("\n");
			}
		} 
		else printf("?\n");
	}
	return 0;
}
/*
3
abcdefg
bcdefgh
cdefghi
3
xxx
yyy
zzz
0
*/
