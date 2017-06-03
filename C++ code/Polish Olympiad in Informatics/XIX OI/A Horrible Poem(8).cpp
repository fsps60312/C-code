#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
int FP[500001];
vector<int>P;
void BuildPrime()
{
	bool *isp=new bool[500001];
	for(int i=2;i<=500000;i++)isp[i]=true;
	for(int i=2;i<=500000;i++)
	{
		if(isp[i])P.push_back(i),FP[i]=i;
		for(int j=0;P[j]*i<=500000;j++)
		{
			isp[P[j]*i]=false;
			FP[P[j]*i]=P[j];
			if(i%P[j]==0)break;
		}
	}
	delete[]isp;
//	for(int i=0;i<100;i++)printf("P[%d]=%d\n",i,P[i]);
}
void Dfs(const vector<pair<int,int> >&fs,const int dep,const int now,vector<int>&ans)
{
	if(dep==-1){ans.push_back(now);return;}
	for(int i=0,f=1;i<=fs[dep].second;i++,f*=fs[dep].first)Dfs(fs,dep-1,now*f,ans);
}
vector<int>F[500001];
vector<int>GetFactors(int n)
{
	if(!F[n].empty())return F[n];
	vector<pair<int,int> >fs;
	vector<int>&ans=F[n];
	for(;n>1;n/=FP[n])
	{
		if(fs.empty()||fs.back().first!=FP[n])fs.push_back(make_pair(FP[n],1));
		else fs.back().second++;
	}
	Dfs(fs,(int)fs.size()-1,1,ans);
	sort(ans.begin(),ans.end());
	return ans;
}
struct SuffixArray
{
	int SA[500000],N;
	void BuildSuffixArray(const char *str)
	{
		static int tmp[3][500000];
		int *x=tmp[0],*y=tmp[1],*c=tmp[2];
		int k=256;
		for(int i=0;i<k;i++)c[i]=0;
		for(int i=0;i<N;i++)c[x[i]=str[i]]++;
		for(int i=1;i<k;i++)c[i]+=c[i-1];
		for(int i=N-1;i>=0;i--)SA[--c[x[i]]]=i;
		for(int move=1;move<N;move<<=1)
		{
			int cur=0;
			for(int i=N-move;i<N;i++)y[cur++]=i;
			for(int i=0;i<N;i++)if(SA[i]>=move)y[cur++]=SA[i]-move;
			for(int i=0;i<k;i++)c[i]=0;
			for(int i=0;i<N;i++)c[x[i]]++;
			for(int i=1;i<k;i++)c[i]+=c[i-1];
			for(int i=N-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];
			swap(x,y);
			k=0,x[SA[0]]=k++;
			for(int i=1;i<N;i++)
			{
				if(y[SA[i]]!=y[SA[i-1]]||(SA[i]+move<N)!=(SA[i-1]+move<N))x[SA[i]]=k++;
				else x[SA[i]]=(y[SA[i]+move]==y[SA[i-1]+move]?k-1:k++);
			}
			if(k==N)break;
		}
	}
	int RANK[500000],HEIGHT[500000];
	void BuildHeight(const char *str)
	{
		for(int i=0;i<N;i++)RANK[SA[i]]=i;
		for(int i=0,ans=0;i<N;i++)
		{
			if(ans)ans--;
			if(RANK[i]==0){HEIGHT[0]=0;continue;}
			else
			{
				const int j=SA[RANK[i]-1];
				while(str[i+ans]==str[j+ans])ans++;
				HEIGHT[RANK[i]]=ans;
			}
		}
	}
	int SPARSE[20][500000];
	void BuildSparseTable()
	{
		for(int i=1;i<N;i++)SPARSE[0][i]=HEIGHT[i];
		for(int b=1;(1<<b)<N;b++)
		{
			for(int i=1;i+(1<<b)-1<N;i++)
			{
				SPARSE[b][i]=min(SPARSE[b-1][i],SPARSE[b-1][i+(1<<(b-1))]);
			}
		}
	}
	int BITS[500001];
	void Build(const char *str,const int _N)
	{
		N=_N;
		BuildSuffixArray(str);
		BuildHeight(str);
		BuildSparseTable();
		for(int i=1,bit=0;i<=500000;i++)
		{
			while((1<<(bit+1))<=i)bit++;
			BITS[i]=bit;
		}
	}
	inline int QueryLCS(const int _a,const int _b)
	{
		int a=RANK[_a],b=RANK[_b];
		if(a>b)swap(a,b);
		a++;
		const int bit=BITS[b-a+1];
		return min(SPARSE[bit][a],SPARSE[bit][b-(1<<bit)+1]);
	}
}SA;
int N,SUM[500001][26];
char S[500001];
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("okr16b.in","r",stdin);
//	freopen("out.txt","w",stdout);
	BuildPrime();
	scanf("%d%s",&N,S);
	for(int i=0;i<=N;i++)for(int j=0;j<26;j++)SUM[i][j]=0;
	for(int i=0;i<N;i++)SUM[i+1][S[i]-'a']++;
	for(int i=1;i<=N;i++)for(int j=0;j<26;j++)SUM[i][j]+=SUM[i-1][j];
	SA.Build(S,N);
	int querycount;scanf("%d",&querycount);
	for(int a,b;querycount--;)
	{
		scanf("%d%d",&a,&b),a--,b--;
		const int len=b-a+1;
		int g=len;
		for(int i=0;i<26;i++)g=__gcd(g,SUM[b+1][i]-SUM[a][i]);
		const vector<int>&fs=GetFactors(g);
		int ans=len;
		for(int i=(int)fs.size()-1;i>=0;i--)if(SA.QueryLCS(a,a+len/fs[i])>=len-len/fs[i])
		{
			ans=len/fs[i];break;
		}
		printf("%d\n",ans);
	}
	return 0;
}
