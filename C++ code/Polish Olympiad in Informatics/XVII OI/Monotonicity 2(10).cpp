#include<cstdio>
#include<cassert>
#include<utility>
#include<algorithm>
using namespace std;
void getmax(pair<int,int>&a,const pair<int,int>&b){if(b>a)a=b;}
struct SegTree
{
	int N;
	pair<int,int>MX[4000000];
	void Build(const int id,const int l,const int r)
	{
		MX[id]=make_pair(0,-1);
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Build(const int _N){N=_N;Build(1,1,N);}
	void Update(const int id,const int l,const int r,const int bl,const int br,const pair<int,int>&val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){getmax(MX[id],val);return;}
		const int mid=(l+r)/2;
		Update(id*2,l,mid,bl,br,val),Update(id*2+1,mid+1,r,bl,br,val);
	}
	void Update(const int bl,const int br,const pair<int,int>&val){Update(1,1,N,bl,br,val);}
	const pair<int,int>Query(const int id,const int l,const int r,const int loc)const
	{
		pair<int,int>ans=MX[id];
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)getmax(ans,Query(id*2,l,mid,loc));
			else getmax(ans,Query(id*2+1,mid+1,r,loc));
		}
		return ans;
	}
	const pair<int,int>Query(const int loc)const{return Query(1,1,N,loc);}
}SEG;
int N,K,A[500000],PRE[500000];
char S[500000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<K;i++)
		{
			char tmp[2];scanf("%s",tmp);
			S[i]=tmp[0];
		}
		for(int i=K;i<N;i++)S[i]=S[i%K];
		SEG.Build(1000000);
		pair<int,int>ans=make_pair(0,-1);
		for(int i=0;i<N;i++)
		{
			const pair<int,int>&j=SEG.Query(A[i]);
			PRE[i]=j.second;
			const pair<int,int>&p=make_pair(j.first+1,i);
//			printf("i=%d,j=%d\n",i,j);
			getmax(ans,p);
			switch(S[j.first])
			{
				case'<':SEG.Update(A[i]+1,1000000,p);break;
				case'=':SEG.Update(A[i],A[i],p);break;
				case'>':SEG.Update(1,A[i]-1,p);break;
				default:assert(0);break;
			}
		}
		printf("%d\n",ans.first);
		static int s[500000];
		for(int i=0,cur=ans.second;i<ans.first;i++,cur=PRE[cur])s[i]=A[cur];
		reverse(s,s+ans.first);
		for(int i=0;i<ans.first;i++)
		{
			if(i)putchar(' ');
			printf("%d",s[i]);
		}
		puts("");
	}
	return 0;
}
