#include<cstdio>
#include<stack>
#include<vector>
#include<algorithm>
#include<utility>
#include<cassert>
using namespace std;
const int INF=2147483647;
vector<pair<int,int> >B;
struct SegTree
{
	int N,MX[800000];
	void Maintain(const int id){MX[id]=max(MX[id*2],MX[id*2+1]);}
	void Build(const int _n){N=_n,Build(1,0,N);}
	void Build(const int id,const int l,const int r)
	{
		if(l==r){MX[id]=min(B[r].first,B[r].second)+r;return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		Maintain(id); 
	}
	int Query(const int br){return Query(1,0,N,0,br);}
	int Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return -INF;
		if(bl<=l&&r<=br)return MX[id];
		const int mid=(l+r)/2;
		return max(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
	}
	void Sub(const int d){Sub(1,0,N,d);}
	void Sub(const int id,const int l,const int r,const int d)
	{
		if(l==r){(d==0?B[r].first:B[r].second)--,MX[id]=min(B[r].first,B[r].second)+r;return;}
		const int mid=(l+r)/2;
		Sub(id*2,l,mid,d),Sub(id*2+1,mid+1,r,d);
		Maintain(id); 
	}
}SEG;
char S[2][200001];
vector<pair<int,int> >LOC;
int main()
{
	freopen("in.txt","r",stdin);
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%s%s",S[0],S[1]);
		stack<int>b[2];
		for(int d=0;d<2;d++)for(int i=0;S[d][i];i++)if(S[d][i]=='B')b[d].push(i);
		B.clear(),LOC.clear();
		B.push_back(make_pair(b[0].size(),b[1].size()));
		if(true)
		{
			int i0=-1,i1=-1;
			while(S[0][++i0]);while(S[1][++i1]);
			LOC.push_back(make_pair(i0,i1));
			for(;i0>=0;i0--)if(S[0][i0]=='C')
			{
				while(i1>=0&&S[1][i1]!='C')i1--;
				if(i1==-1)break;
				while(!b[0].empty()&&b[0].top()>i0)b[0].pop();
				while(!b[1].empty()&&b[1].top()>i1)b[1].pop();
				B.push_back(make_pair(b[0].size(),b[1].size()));
				LOC.push_back(make_pair(i0,i1));
				i1--;
			}
		}
		int c0=0,c1=0;
		for(int i=0;S[0][i];i++)if(S[0][i]=='C')c0++;
		for(int i=0;S[1][i];i++)if(S[1][i]=='C')c1++;
		assert(min(c0,c1)+1==(int)LOC.size()&&B.size()==LOC.size());
		SEG.Build(min(c0,c1));
		int a=0;
		int ans=a+SEG.Query(min(c0,c1));
		for(int i0=0,i1=0;S[0][i0];i0++)
		{
			if(S[0][i0]=='A')
			{
				while(S[1][i1]&&S[1][i1]!='A')
				{
					if(S[1][i1]=='B')SEG.Sub(1);
					else if(S[1][i1]=='C')c1--;
					else assert(0);
					i1++;
				}
				if(!S[1][i1])break;
				a++;
				ans=max(ans,a+SEG.Query(min(c0,c1)));
				i1++;
			}
			else if(S[0][i0]=='B')SEG.Sub(0);
			else if(S[0][i0]=='C')c0--;
			else assert(0);
		}
		printf("%d\n",ans);
	}
	return 0;
}
