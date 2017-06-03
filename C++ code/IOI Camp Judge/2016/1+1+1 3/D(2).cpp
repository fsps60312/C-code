#include<cstdio>
#include<cassert>
#include<algorithm>
#include<set>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
void BuildSa(const char *str,const int n,int *sa)
{
	static int tmp[3][100000];
	int *x=tmp[0],*y=tmp[1],*c=tmp[2],p=128;
	for(int i=0;i<p;i++)c[i]=0;
	for(int i=0;i<n;i++)c[x[i]=str[i]]++;
	for(int i=1;i<p;i++)c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
	for(int move=1;move<n;move<<=1)
	{
		int tmp=0;
		for(int i=n-move;i<n;i++)y[tmp++]=i;
		for(int i=0;i<n;i++)if(sa[i]>=move)y[tmp++]=sa[i]-move;
		for(int i=0;i<p;i++)c[i]=0;
		for(int i=0;i<n;i++)c[x[i]]++;
		for(int i=1;i<p;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=0,x[sa[0]]=p++;
		for(int i=1;i<n;i++)
		{
			if(y[sa[i]]!=y[sa[i-1]])x[sa[i]]=p++;
			else if((sa[i]+move<n)!=(sa[i-1]+move<n))x[sa[i]]=p++;
			else assert(sa[i]+move<n&&sa[i-1]+move<n),x[sa[i]]=(y[sa[i]+move]==y[sa[i-1]+move]?p-1:p++);
		}
		if(p==n)break;
	}
}
void BuildHeight(const char *str,const int n,const int *sa,int *rank,int *height)
{
	for(int i=0;i<n;i++)rank[sa[i]]=i;
	for(int i=0,ans=0;i<n;i++)
	{
		if(ans)ans--;
		if(rank[i]==0)height[0]=0;
		else
		{
			const int j=sa[rank[i]-1];
			while(str[i+ans]==str[j+ans])ans++;
			height[rank[i]]=ans;
		}
	}
}
int N,SA[100000],RANK[100000],HEIGHT[100000];
char S[100001];
multiset<int>GAP,LOC;
void Insert(const int loc)
{
	auto it=LOC.upper_bound(loc);
	assert(it!=LOC.end()&&it!=LOC.begin());
	const int r=*it,l=*--it;
	it=GAP.find(r-l);
	assert(it!=GAP.end());
	GAP.erase(it);
	GAP.insert(r-loc),GAP.insert(loc-l);
	LOC.insert(loc);
}
int Solve()
{
	LOC.clear(),GAP.clear();
	LOC.insert(0),LOC.insert(N),GAP.insert(N);
	int ans=N+1;
	int l=RANK[0],r=RANK[0];
	for(int height=N;height>=0;height--)
	{
		while(l&&HEIGHT[l]>=height)Insert(SA[--l]);
		while(r+1<N&&HEIGHT[r+1]>=height)Insert(SA[++r]);
		auto it=GAP.end();it--;
		if(*it<=height)ans=height;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%s",&N,S);
		BuildSa(S,N,SA),BuildHeight(S,N,SA,RANK,HEIGHT);
		printf("%d\n",Solve());
	}
	return 0;
}
