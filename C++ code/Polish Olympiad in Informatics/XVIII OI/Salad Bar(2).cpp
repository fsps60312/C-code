#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(a<b)a=b;}
void getmin(int &a,const int b){if(b<a)a=b;}
struct SegTree
{
	int S[1000000*4];
	void Clear(const int N){for(int i=0;i<N*4;i++)S[i]=0;}
	void Modify(const int id,const int l,const int r,const int bl,const int br,const int val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){getmax(S[id],val);return;}
		const int mid=(l+r)/2;
		Modify(id*2,l,mid,bl,br,val),Modify(id*2+1,mid+1,r,bl,br,val);
	}
	int Query(const int id,const int l,const int r,const int loc)
	{
		int ans=S[id];
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)getmax(ans,Query(id*2,l,mid,loc));
			else getmax(ans,Query(id*2+1,mid+1,r,loc));
		}
		return ans;
	}
}SEG;
int N,SUM[1000001],R[1000001],L[1000001];
char S[1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		scanf("%s",S);
		SUM[0]=0;
		for(int i=0;i<N;i++)SUM[i+1]=SUM[i]+(S[i]=='p'?1:-1);
		vector<int>stk;
		for(int i=N;i>=0;i--)
		{
			while(!stk.empty()&&SUM[i]<=SUM[stk.back()])stk.pop_back();
			if(stk.empty())R[i]=N;
			else R[i]=stk.back()-1;
			stk.push_back(i);
		}
		stk.clear();
		for(int i=0;i<=N;i++)
		{
			while(!stk.empty()&&SUM[stk.back()]<=SUM[i])stk.pop_back();
			if(stk.empty())L[i]=0;
			else L[i]=stk.back()+1;
			stk.push_back(i);
		}
		static pair<int,int>order[1000001];
		for(int i=0;i<=N;i++)order[i]=make_pair(R[i],i);
		sort(order,order+N+1);
		int ans=0;
		SEG.Clear(N);
		for(int i=0,j=0;i<=N;i++)
		{
			const pair<int,int>&p=order[i];
			for(;j<=p.first;j++)SEG.Modify(1,0,N,L[j],j,j);
			getmax(ans,SEG.Query(1,0,N,p.second)-p.second);
		}
		printf("%d\n",ans);
	}
	return 0;
}
