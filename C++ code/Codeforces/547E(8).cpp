#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
struct SuffixArray
{
	int S[400000],R[400000],H[400000];
	void BuildSa(const char *str,const int n)
	{
		static int tmp[3][400000];
		int *x=tmp[0],*y=tmp[1],*c=tmp[2],p=256;
		for(int i=0;i<p;i++)c[i]=0;
		for(int i=0;i<n;i++)c[x[i]=str[i]]++;
		for(int i=1;i<p;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)S[--c[x[i]]]=i;
		for(int move=1;move<n;move<<=1)
		{
			int cur=0;
			for(int i=n-move;i<n;i++)y[cur++]=i;
			for(int i=0;i<n;i++)if(S[i]>=move)y[cur++]=S[i]-move;
			for(int i=0;i<p;i++)c[i]=0;
			for(int i=0;i<n;i++)c[x[i]]++;
			for(int i=1;i<p;i++)c[i]+=c[i-1];
			for(int i=n-1;i>=0;i--)S[--c[x[y[i]]]]=y[i];
			swap(x,y);
			p=0,x[S[0]]=p++;
			for(int i=1;i<n;i++)
			{
				if(y[S[i]]!=y[S[i-1]]||(S[i]+move<n)!=(S[i-1]+move<n))x[S[i]]=p++;
				else assert(S[i]+move<n&&S[i-1]+move<n),x[S[i]]=(y[S[i]+move]==y[S[i-1]+move]?p-1:p++);
			}
			if(p==n)break;
		}
	}
	void BuildHeight(const char *str,const int n)
	{
		for(int i=0;i<n;i++)R[S[i]]=i;
		for(int i=0,ans=0;i<n;i++)
		{
			if(ans)ans--;
			if(R[i]==0){H[0]=0;continue;}
			const int j=S[R[i]-1];
			while(str[i+ans]==str[j+ans])ans++;
			H[R[i]]=ans;
		}
	}
	void Build(const char *str,const int len)
	{
		BuildSa(str,len);
		BuildHeight(str,len);
	}
}SA;
struct DisjointSets
{
	int S[400000];
	void Clear(const int N){for(int i=0;i<N;i++)S[i]=i;}
	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
	bool Merge(int a,int b)
	{
		if((a=Find(a))==(b=Find(b)))return false;
		S[a]=b;return true;
	}
};
struct QueryType
{
	int l,r,max_rank,ans;
}QUERY[1000000];
struct Bit
{
	int S[400001],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	void Add(int i){i++;for(;i<=N;i+=(i&(-i)))S[i]++;}
	int Query(int i){i++;int ans=0;for(;i;i-=(i&(-i)))ans+=S[i];return ans;}
};
int LENGTH;
void AnswerQueries(const int querycount)
{
	vector<int>order;
	for(int i=0;i<querycount;i++)order.push_back(i);
	sort(order.begin(),order.end(),[](const int a,const int b)->bool{return QUERY[a].max_rank<QUERY[b].max_rank;});
	static Bit bit;bit.Clear(LENGTH);
	int max_rank=0;
	for(const int qi:order)
	{
		QueryType &q=QUERY[qi];
		for(;max_rank<LENGTH&&max_rank<=q.max_rank;max_rank++)bit.Add(SA.S[max_rank]);
		q.ans=bit.Query(q.r)-bit.Query(q.l-1);
	}
}
int N;
vector<int>LOCS;
pair<int,int>SEGS[200000];
void BuildWordHeightSegments()
{
	vector<int>sortedword,sortedheight;
	vector<pair<int,int> >sorting;
	for(int i=0;i<N;i++)sorting.push_back(make_pair(-(LOCS[i+1]-LOCS[i]),i));
	sort(sorting.begin(),sorting.end());
	for(const auto &p:sorting)sortedword.push_back(p.second);
	sorting.clear();
	for(int i=1;i<LENGTH;i++)sorting.push_back(make_pair(-SA.H[i],i));
	sort(sorting.begin(),sorting.end());
	for(const auto &p:sorting)sortedheight.push_back(p.second);
	vector<pair<int,int> >().swap(sorting);
	auto sw=sortedword.begin(),sh=sortedheight.begin();
	static DisjointSets djl,djr;
	djl.Clear(LENGTH),djr.Clear(LENGTH);
	assert((int)sortedword.size()==N&&(int)sortedheight.size()==LENGTH-1);
	for(;sw!=sortedword.end();sw++)
	{
		for(;sh!=sortedheight.end()&&SA.H[*sh]>=LOCS[(*sw)+1]-LOCS[*sw]-1;sh++)
		{
			djl.Merge(*sh,(*sh)-1),djr.Merge((*sh)-1,*sh);
		}
		SEGS[*sw]=make_pair(djl.Find(SA.R[LOCS[*sw]+1]),djr.Find(SA.R[LOCS[*sw]+1]));
	}
	vector<int>().swap(sortedword);
	vector<int>().swap(sortedheight);
}
int Q;
char S[400000];
int main()
{
//	BuildSa("aabaaaab",8,SA),BuildHeight("aabaaaab",8,SA,RANK,HEIGHT);
//	for(int i=0;i<8;i++)printf("%d ",HEIGHT[i]);return 0;
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&Q);
	LOCS.push_back(-1);
	for(int i=0,&len=LENGTH=-1;i<N;i++)
	{
		len++;
		scanf("%s",S+len);
		while(S[len])len++;
		LOCS.push_back(len);
	}
	SA.Build(S,LENGTH);
	BuildWordHeightSegments();
	for(int i=0,l,r,k;i<Q;i++)
	{
		scanf("%d%d%d",&l,&r,&k);
		QUERY[i*2].l=QUERY[i*2+1].l=LOCS[l-1]+1;
		QUERY[i*2].r=QUERY[i*2+1].r=LOCS[r]-1;
		QUERY[i*2].max_rank=SEGS[k-1].first-1;
		QUERY[i*2+1].max_rank=SEGS[k-1].second;
	}
	AnswerQueries(Q*2);
	for(int i=0;i<Q;i++)printf("%d\n",QUERY[i*2+1].ans-QUERY[i*2].ans);
	return 0;
}
