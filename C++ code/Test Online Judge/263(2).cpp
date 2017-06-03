#include<cstdio>
#include<set>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N;
char S[500000];
int SA[500000],TMP[3][500000];
void BuildSA()
{
	int *x=TMP[0],*y=TMP[1],*c=TMP[2];
	int p=256;
	for(int i=0;i<p;i++)c[i]=0;
	for(int i=0;i<N;i++)c[x[i]=S[i]]++;
	for(int i=1;i<p;i++)c[i]+=c[i-1];
	for(int i=N-1;i>=0;i--)SA[--c[x[i]]]=i;//loc i, rank x[i]
	for(int move=1;move<=N;move<<=1)//rank r, loc SA[r]
	{
		int cnt=0;
		for(int i=N-move;i<N;i++)y[cnt++]=i;
		for(int i=0;i<N;i++)if(SA[i]>=move)y[cnt++]=SA[i]-move;
		for(int i=0;i<p;i++)c[i]=0;
		for(int i=0;i<N;i++)c[x[i]]++;
		for(int i=1;i<p;i++)c[i]+=c[i-1];
		for(int i=N-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];//rank r, loc y[i]
		swap(x,y);
		p=0;
		x[SA[0]]=p++;
		for(int i=1;i<N;i++)
		{
			if(y[SA[i-1]]!=y[SA[i]])x[SA[i]]=p++;
			else if((SA[i-1]+move<N)!=(SA[i]+move<N))x[SA[i]]=p++;
			else if(SA[i-1]+move>=N&&SA[i]+move>=N)x[SA[i]]=p-1;
			else x[SA[i]]=(y[SA[i-1]+move]==y[SA[i]+move]?p-1:p++);
		}
		assert(p<=N);
		if(p==N)break;
	}
}
int RANK[500000],HEIGHT[500000];
void BuildHEIGHT()
{
	for(int i=0;i<N;i++)RANK[SA[i]]=i;
	for(int i=0,ans=0;i<N;i++)
	{
		if(ans)ans--;
		if(RANK[i]==0){HEIGHT[0]=0;continue;}
		int a=i,b=SA[RANK[i]-1];
		while(S[a+ans]==S[b+ans])ans++;
		HEIGHT[RANK[i]]=ans;
	}
}
set<int>IDX;
multiset<int,greater<int> >VALUE;
void Erase(multiset<int,greater<int> >&s,const int v){auto it=s.find(v);assert(it!=s.end()),s.erase(it);}
void Update(const int v)
{
	assert(IDX.find(v)==IDX.end());
	auto it=IDX.upper_bound(v);
	if(it==IDX.end())printf("v=%d\n",v);
	assert(it!=IDX.end()&&it!=IDX.begin());
	int r=(*it);
	int l=(*--it);
	IDX.insert(v);
	Erase(VALUE,r-l);
	VALUE.insert(r-v),VALUE.insert(v-l);
}
void getmin(int &a,const int b){if(b<a)a=b;}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%s",S);
	N=-1;while(S[++N]);
	BuildSA();
	BuildHEIGHT();
//	for(int i=0;i<N;i++)printf("(%d,%d)\n",HEIGHT[i],SA[i]);
	int ans=N;
	IDX.clear(),VALUE.clear();
	IDX.insert(0),IDX.insert(N),VALUE.insert(N);
	for(int h=HEIGHT[RANK[0]],l=RANK[0],r=RANK[0];h>=1;h--)
	{
		while(l&&HEIGHT[l]>=h)Update(SA[--l]);
		while(r+1<N&&HEIGHT[r+1]>=h)Update(SA[++r]);
//		printf("h=%d,mn=%d:",h,*VALUE.begin());for(auto v:VALUE)printf(" %d",v);puts("");
		if((*VALUE.begin())<=h&&IDX.find(N-h)!=IDX.end())getmin(ans,h);
	}
	printf("%d\n",ans);
	return 0;
}
