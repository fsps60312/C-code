#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,M,Q,S[80000],MX[283][283];
map<int,int>IDX[80000];
int CNT[80000];
int Query(const int v,const int l,const int r)
{
	auto itl=IDX[v].lower_bound(l),itr=IDX[v].upper_bound(r);
	const int a=(itl==IDX[v].end()?IDX[v].size():itl->second),b=(itr==IDX[v].end()?IDX[v].size():itr->second);
	return b-a;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&Q);
	if(true)
	{
		vector<int>tmp; 
		for(int i=0;i<N;i++)scanf("%d",&S[i]),tmp.push_back(S[i]);
		sort(tmp.begin(),tmp.end()),tmp.resize(unique(tmp.begin(),tmp.end())-tmp.begin());
		M=tmp.size();
		for(int i=0;i<N;i++)S[i]=lower_bound(tmp.begin(),tmp.end(),S[i])-tmp.begin();
	}
	if(true)
	{
		int *cnt=new int[M];
		for(int i=0;i<M;i++)IDX[i].clear(),cnt[i]=0;
		for(int i=0;i<N;i++)IDX[S[i]][i]=cnt[S[i]]++;
		delete[] cnt;
	}
	const int sq=sqrt(N);
	for(int i=0;i<=(N-1)/sq;i++)
	{
		for(int j=0;j<M;j++)CNT[j]=0;
		int mxnow=0;
		int r=i*sq-1;
		for(int j=i;j<=(N-1)/sq;j++)
		{
			while(r+1<N&&r<(j+1)*sq-1)getmax(mxnow,++CNT[S[++r]]);
			MX[i][j]=mxnow;
		}
	}
	while(Q--)
	{
		static int a,b;
		scanf("%d%d",&a,&b),a--,b--;
		const int l=(a+sq-1)/sq,r=b/sq-1;
		int ans=(l<=r?MX[l][r]:0);
		for(int i=a;i<l*sq;i++)getmax(ans,Query(S[i],a,b));
		for(int i=(r+1)*sq;i<=b;i++)getmax(ans,Query(S[i],a,b));
		printf("%d\n",ans);
	}
	return 0;
}
