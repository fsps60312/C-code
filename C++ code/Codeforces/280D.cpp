#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,A[100000];
vector<int>MX[400000];
vector<int>Merge(const vector<int>&ls,const vector<int>&rs)
{
	vector<int>s;
	s.resize(21,0);
	for(int i=0;i<=20;i++)for(int j=0;i+j<=20;j++)getmax(s[i+j],ls[i]+rs[j]);
	return s;
}
void Build(const int id,const int l,const int r)
{
	MX[id].clear(),MX[id].resize(21,0);
	if(l==r){for(int i=1;i<=20;i++)MX[id][i]=max(0,A[r]);return;}
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	MX[id]=Merge(MX[id*2],MX[id*2+1]);
}
void Modify(const int id,const int l,const int r,const int loc,const int val)
{
	if(l==r){assert(loc==r);A[r]=val;for(int i=1;i<=20;i++)MX[id][i]=max(0,val);return;}
	const int mid=(l+r)/2;
	if(loc<=mid)Modify(id*2,l,mid,loc,val);
	else Modify(id*2+1,mid+1,r,loc,val);
	MX[id]=Merge(MX[id*2],MX[id*2+1]);
}
vector<int>Query(const int id,const int l,const int r,const int bl,const int br)
{
	if(bl<=l&&r<=br)return MX[id];
	if(r<bl||br<l)
	{
		vector<int>ans;
		ans.resize(21,0);
		return ans;
	}
	const int mid=(l+r)/2;
	return Merge(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		Build(1,0,N-1);
		int querycount;scanf("%d",&querycount);
		while(querycount--)
		{
			int type;scanf("%d",&type);
			if(type==0)
			{
				int i,val;scanf("%d%d",&i,&val),i--;
				Modify(1,0,N-1,i,val);
			}
			else if(type==1)
			{
				int l,r,k;scanf("%d%d%d",&l,&r,&k),l--,r--;
				printf("%d\n",Query(1,0,N-1,l,r)[k]);
			}
			else assert(0);
		}
	}
	return 0;
}
