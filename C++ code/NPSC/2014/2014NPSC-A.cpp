#include<cstdio>
#include<map>
#include<vector>
using namespace std;
const int INF=2147483647;
int T,N,M,A[1000],B[100000];
map<int,vector<int> >S;
vector<int>L[1000],R[1000];
void getmin(int &a,const int &b){if(b<a)a=b;}
void getmax(int &a,const int &b){if(b>a)a=b;}
int &Last(vector<int>&v){return v[v.size()-1];}
int Solve()
{
	S.clear();
	for(int i=0;i<M;i++)S[B[i]].push_back(i);
	for(int i=0;i<N;i++)
	{
		if(S.find(A[i])==S.end())return 0;
		L[i].resize(S[A[i]].size()),R[i].resize(S[A[i]].size());
		for(int j=0;j<L[i].size();j++)L[i][j]=R[i][j]=INF;
	}
	for(int i=0;i<L[0].size();i++)L[0][i]=0;
	for(int i=1;i<N;i++)
	{
		for(int j=0;j<L[i].size();j++)
		{
			int &dp=L[i][j],&v=S[A[i]][j];
			for(int k=0;k<i;k++)
			{
				vector<int>&s=S[A[k]];
				int l=0,r=s.size(),mid;
				while(l<r)
				{
//					find max value s[l] < v
					mid=(l+r)/2;
					if(s[mid]<v)l=mid+1;
					else r=mid;
				}
				l--;
				if(l<0){dp=0;break;}
				getmin(dp,L[k][l]+1);
			}
		}
	}
	for(int i=0;i<R[N-1].size();i++)R[N-1][i]=0;
	for(int i=N-2;i>=0;i--)
	{
		for(int j=0;j<R[i].size();j++)
		{
			int &dp=R[i][j],&v=S[A[i]][j];
			for(int k=i+1;k<N;k++)
			{
				vector<int>&s=S[A[k]];
				int l=0,r=s.size(),mid;
				while(l<r)
				{
//					find min value s[l] > v
					mid=(l+r)/2;
					if(s[mid]<=v)l=mid+1;
					else r=mid;
				}
				if(l==s.size()){dp=0;break;}
				getmin(dp,R[k][l]+1);
			}
		}
	}
	int ans=INF;
	for(int i=0;i<N;i++)
	{
		int mx=-INF;
		for(int j=0;j<L[i].size();j++)getmax(mx,L[i][j]+R[i][j]+1);
		getmin(ans,mx);
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("pa.in","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<M;i++)scanf("%d",&B[i]);
		int ans=Solve();
		printf("%d\n",N-ans);
	}
	return 0;
}
