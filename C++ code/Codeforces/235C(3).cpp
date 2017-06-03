#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
#include<queue>
using namespace std;
const int MAXN=1000001+1000000*2;
struct SegmentsManager
{
	int DATA[MAXN],SIZE[MAXN],N;
	void Clear(const int _N){N=_N;for(int i=0;i<N;i++)DATA[i]=i,SIZE[i]=0;}
	int Find(const int a){return DATA[a]==a?a:(DATA[a]=Find(DATA[a]));}
	bool Merge(int l,int r)
	{
		assert(l<r);
		if((l=Find(l))==(r=Find(r)))return false;
		DATA[r]=l;
		SIZE[l]+=SIZE[r],SIZE[r]=0;
		return true;
	}
}SEG_MGR;
void BuildSa(const char *str,const int n,int *sa)
{
	static int tmp[3][MAXN];
	int *x=tmp[0],*y=tmp[1],*c=tmp[2],k=256;
	for(int i=0;i<k;i++)c[i]=0;
	for(int i=0;i<n;i++)c[x[i]=str[i]]++;
	for(int i=1;i<k;i++)c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
	for(int move=1;move<n;move<<=1)
	{
		int cur=0;
		for(int i=n-move;i<n;i++)y[cur++]=i;
		for(int i=0;i<n;i++)if(sa[i]>=move)y[cur++]=sa[i]-move;
		for(int i=0;i<k;i++)c[i]=0;
		for(int i=0;i<n;i++)c[x[i]]++;
		for(int i=1;i<k;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		k=0,x[sa[0]]=k++;
		for(int i=1;i<n;i++)
		{
			if(y[sa[i]]!=y[sa[i-1]]||(sa[i]+move<n)!=(sa[i-1]+move<n))x[sa[i]]=k++;
			else assert(sa[i]+move<n&&sa[i-1]+move<n),x[sa[i]]=(y[sa[i]+move]==y[sa[i-1]+move]?k-1:k++);
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
int SA[MAXN],RANK[MAXN],HEIGHT[MAXN];
char S[MAXN];
vector<int>LOCS,LENGTHS;
int N;
int main()
{
//	BuildSa("aabaaaab",8,SA);
//	BuildHeight("aabaaaab",8,SA,RANK,HEIGHT);
//	for(int i=0;i<8;i++)printf("%d ",HEIGHT[i]);return 0;
//	freopen("in.txt","r",stdin);
	while(scanf("%s",S)==1)
	{
		LOCS.clear(),LENGTHS.clear();
		if(true)
		{
			int stringcount,cur=0;scanf("%d",&stringcount);
			while(S[cur])cur++;
			LOCS.push_back(cur),LENGTHS.push_back(cur);
			for(;stringcount--;)
			{
				cur++;
				scanf("%s",S+cur);
				int pre_cur=cur;
				while(S[cur])cur++;
				const int n=cur-pre_cur;
				LENGTHS.push_back(n);
				for(int i=0;i<n-1;i++)S[cur+i]=S[pre_cur+i];
				S[cur+=n-1]='\0';
				LOCS.push_back(cur);
			}
			S[N=cur]=1;
		}
		BuildSa(S,N,SA),BuildHeight(S,N,SA,RANK,HEIGHT);
		vector<int>sortedheight,sortedstring;
		if(true)
		{
			vector<pair<int,int> >sorting;
			for(int i=1;i<N;i++)sorting.push_back(make_pair(-HEIGHT[i],i));
			sort(sorting.begin(),sorting.end());
			for(const pair<int,int>&p:sorting)sortedheight.push_back(p.second);
			sorting.clear();
			for(int i=1;i<(int)LENGTHS.size();i++)sorting.push_back(make_pair(-LENGTHS[i],i));
			sort(sorting.begin(),sorting.end());
			for(const pair<int,int>&p:sorting)sortedstring.push_back(p.second);
			vector<pair<int,int> >().swap(sorting);
		}
		SEG_MGR.Clear(N);
		for(int i=0;i<LENGTHS[0];i++)SEG_MGR.SIZE[RANK[i]]++;
		int *ans=new int[LOCS.size()];
		auto hi=sortedheight.begin();
		for(const int si:sortedstring)
		{
//			printf("si=%d\n",si);
			for(;hi!=sortedheight.end()&&HEIGHT[*hi]>=LENGTHS[si];hi++)SEG_MGR.Merge((*hi)-1,*hi);
			vector<int>segs;
			for(int i=0;i<LENGTHS[si];i++)segs.push_back(SEG_MGR.Find(RANK[LOCS[si-1]+1+i]));
			sort(segs.begin(),segs.end()),segs.resize(unique(segs.begin(),segs.end())-segs.begin());
			ans[si]=0;
			for(const int v:segs)ans[si]+=SEG_MGR.SIZE[v];
		}
		for(int i=1;i<(int)LOCS.size();i++)printf("%d\n",ans[i]);
		delete[]ans;
	}
	return 0;
}
