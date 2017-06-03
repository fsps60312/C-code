#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
void BuildSa(const char *str,const int n,int *sa)
{
	static int tmp[3][100000];
	int k=256,*x=tmp[0],*y=tmp[1],*c=tmp[2];
	for(int i=0;i<k;i++)c[i]=0;
	for(int i=0;i<n;i++)c[x[i]=str[i]]++;
	for(int i=1;i<k;i++)c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
	for(int move=1;move<n;move<<=1)
	{
		int t=0;
		for(int i=n-move;i<n;i++)y[t++]=i;
		for(int i=0;i<n;i++)if(sa[i]>=move)y[t++]=sa[i]-move;
		for(int i=0;i<k;i++)c[i]=0;
		for(int i=0;i<n;i++)c[x[i]]++;
		for(int i=1;i<k;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		k=0,x[sa[0]]=k++;
		for(int i=1;i<n;i++)
		{
			if(y[sa[i-1]]!=y[sa[i]])x[sa[i]]=k++;
			else if((sa[i-1]+move<n)!=(sa[i]+move<n))x[sa[i]]=k++;
			else assert(sa[i-1]+move<n&&sa[i]+move<n),x[sa[i]]=(y[sa[i-1]+move]==y[sa[i]+move]?k-1:k++);
		}
		if(k==n)break;
	}
}
void BuildHeight(const char *str,const int n,const int *sa,int *rank,int *height)
{
	for(int i=0;i<n;i++)rank[sa[i]]=i;
	for(int i=0,ans=0;i<n;i++)
	{
		if(ans)ans--;
		if(rank[i]==0){height[0]=0;continue;}
		const int j=sa[rank[i]-1];
		while(str[i+ans]==str[j+ans])ans++;
		height[rank[i]]=ans;
	}
}
int N,K,SA[100000],RANK[100000],HEIGHT[100000];
char S[100001];
int main()
{
//	BuildSa("aabaaaab",8,SA);
//	BuildHeight("aabaaaab",8,SA,RANK,HEIGHT);
//	for(int i=0;i<8;i++)printf("%d ",SA[i]);puts("");
//	for(int i=0;i<8;i++)printf("%d ",HEIGHT[i]);puts("");
//	freopen("in.txt","r",stdin);
	while(scanf("%d%s",&K,S)==2)
	{
		N=-1;while(S[++N]);
		BuildSa(S,N,SA);
		BuildHeight(S,N,SA,RANK,HEIGHT);
		int ans=0;
		for(int i=1;i<N;i++)if(HEIGHT[i]>=K)
		{
			vector<int>locs;
			locs.push_back(SA[i-1]);
			while(i<N&&HEIGHT[i]>=K)locs.push_back(SA[i++]);
			sort(locs.begin(),locs.end());
			for(int l=0,r=0;;l++)
			{
				while(r<(int)locs.size()&&locs[r]<locs[l]+K)r++;
				if(r==(int)locs.size())break;
				if(locs[l]+K==locs[r])ans++;
			}
			vector<int>().swap(locs);
		}
		printf("%d\n",ans);
	}
	return 0;
}
