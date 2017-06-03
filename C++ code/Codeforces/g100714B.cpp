#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
struct SuffixArray
{
	static const int maxn=1000001;
	char s[maxn];
	int sa[maxn],rank[maxn],pri[maxn],c[maxn],n;
	void build_sa(int m)
	{
		n=-1;while(s[++n]);s[n++]=0;
		memset(c,0,sizeof(c));
		for(int i=0;i<n;i++) c[rank[i]=s[i]]++;
		for(int i=1;i<m;i++) c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--) sa[--c[rank[i]]]=i;

		for(int k=1;k<=n;k<<=1)
		{
			int p=0;
			for(int i=n-k;i<n;i++) pri[p++]=i;
			for(int i=0;i<n;i++) if(sa[i]>=k) pri[p++]=sa[i]-k;

			memset(c,0,sizeof(c));
			for(int i=0;i<n;i++) c[rank[pri[i]]]++;
			for(int i=1;i<m;i++) c[i]+=c[i-1];
			for(int i=n-1;i>=0;i--) sa[--c[rank[pri[i]]]]=pri[i];

			swap(pri,rank);
			p=1;rank[sa[0]]=0;
			for(int i=1;i<n;i++)
				rank[sa[i]] = pri[sa[i-1]]==pri[sa[i]] && pri[sa[i-1]+k]==pri[sa[i]+k]?p-1:p++;
			if(p>=n) break;
			m=p;
		}
	}
	int m;
	int cmp_suffix(char* pattern,int p)
	{
		return strncmp(pattern,s+sa[p],m);
	}
	int find(char* p)
	{
		m=(int)strlen(p);
		if(cmp_suffix(p,0)<0) return -1;
		if(cmp_suffix(p,n-1)>0) return -1;
		int l=0,r=n-1;
		while(r>=l)
		{
			int mid=l+(r-l)/2;
			int res=cmp_suffix(p,mid);
			if(!res) return mid;
			if(res<0) r=mid-1;
			else l=mid+1;
		}
		return -1;
	}
	int height[maxn];
	void getheight()
	{
		int k=0;
		for(int i=1;i<n;i++) rank[sa[i]]=i;
		for(int i=0;i<n-1;i++)
		{
			if(k) k--;
			int j=sa[rank[i]-1];
			while(s[i+k]==s[j+k]) k++;
			height[rank[i]]=k;
		}
	}
	int sparse[13][maxn];
	void buildsparse()
	{
		for(int i=0;i<n;i++)sparse[0][i]=height[i];
		for(int b=1;(1<<b)<=n;b++)
		{
			for(int i=0;i+(1<<b)<=n;i++)sparse[b][i]=min(sparse[b-1][i],sparse[b-1][i+(1<<(b-1))]);
		}
	}
	int querysparse(int l,int r)
	{
		if(l>r)return querysparse(r,l);
		++l;
		assert(l<=r);
		int b=0;
		while((1<<(b+1))<=r-l+1)++b;
		return min(sparse[b][l],sparse[b][r-(1<<b)+1]);
	}
	void Build()
	{
		build_sa(256);
		getheight();
		buildsparse();
	}
	int Query(const int i,const int j)
	{
		assert(i!=j);
		return querysparse(rank[i],rank[j]);
	}
}SA;
int DigitWidth(int n)
{
	int ans=0;
	while(n)++ans,n/=10;
	return ans;
}
int N,K;
int S[100000],SORT[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]),SORT[i]=S[i];
		sort(SORT,SORT+N);
		int cur=K;
		while(cur>=0&&DigitWidth(SORT[cur])==DigitWidth(SORT[K]))--cur;
		++cur;
		int remain=K-cur;
		vector<int>ans,loc;
		for(int i=0;i<N;i++)if(DigitWidth(S[i])>=DigitWidth(SORT[K]))ans.push_back(S[i]);
		int M=0;
		for(int v:ans)
		{
			vector<int>s;
			while(v)s.push_back(v%10),v/=10;
			loc.push_back(M);
			while(!s.empty())SA.s[M++]=(char)('0'+s.back()),s.pop_back();
		}
		SA.s[M]='\0';
//		puts(SA.s);
		SA.build_sa(256);
		SA.getheight();
		vector<bool>remove;remove.resize(ans.size(),false);
		for(int i=0;i<(int)ans.size();i++)
		{
			if(DigitWidth(ans[i])>DigitWidth(SORT[K]))remove[i]=false;
			else
			{
				assert(DigitWidth(ans[i])==DigitWidth(SORT[K]));
				if(i+1<(int)ans.size()&&SA.rank[loc[i]]<SA.rank[loc[i+1]])remove[i]=true,--remain;
				else remove[i]=false;
			}
		}
		if(remain>0)
		{
			for(int i=(int)ans.size()-1;remain>0&&i>=0;i--)if(DigitWidth(ans[i])==DigitWidth(SORT[K])&&!remove[i])remove[i]=true,--remain;
		}
		if(remain<0)
		{
			for(int i=(int)ans.size()-1;remain<0&&i>=0;i--)if(DigitWidth(ans[i])==DigitWidth(SORT[K])&&remove[i])remove[i]=false,++remain;
		}
		assert(remain==0);
		int check_cnt=0;
		for(int i=0;i<(int)ans.size();i++)if(!remove[i])printf("%d",ans[i]),++check_cnt;
		puts("");
		assert(check_cnt+K==N);
	}
	return 0;
}
