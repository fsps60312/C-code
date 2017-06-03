#include<cstdio>
#include<cassert>
#include<utility>
using namespace std;
template<class T>void getmax(T &a,const T &b){if(a<b)a=b;}
struct SegTree
{
	const static int DEFAULT_VALUE=-1;
	int N;
	pair<int,int>S[1000000*4];
	void Build(const int _N)
	{
		N=_N;
		for(int i=0;i<N*4;i++)S[i].first=DEFAULT_VALUE;
	}
	void Update(const int id,const int l,const int r,const int bl,const int br,const pair<int,int>&val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){getmax(S[id],val);return;}
		const int mid=(l+r)/2;
		Update(id*2,l,mid,bl,br,val),Update(id*2+1,mid+1,r,bl,br,val);
	}
	void Update(const int bl,const int br,const pair<int,int>&val){Update(1,1,N,bl,br,val);}
	void Query(const int id,const int l,const int r,const int loc,pair<int,int>&ans)
	{
		getmax(ans,S[id]);
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Query(id*2,l,mid,loc,ans);
			else Query(id*2+1,mid+1,r,loc,ans);
		}
	}
	pair<int,int>Query(const int loc){pair<int,int>ans;ans.first=DEFAULT_VALUE;Query(1,1,N,loc,ans);return ans;}
}SEG;
int N,K;
int S[20000];
char T[100];
void ReadInput()
{
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	for(int i=0;i<K;i++)
	{
		static char str[2];scanf("%s",str);
		T[i]=str[0];
	}
}
int PRE[20000];
void PrintAnswer(const int idx,const int loc)
{
	if(idx==0){printf("%d",S[loc]);return;}
	PrintAnswer(idx-1,PRE[loc]);
	printf(" %d",S[loc]);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		ReadInput();
		SEG.Build(1000000);
		pair<int,int>ans;ans.first=SegTree::DEFAULT_VALUE;
		for(int i=0;i<N;i++)
		{
			pair<int,int>prog=SEG.Query(S[i]);
			PRE[i]=prog.second;
			++prog.first,prog.second=i;
			getmax(ans,prog);
			switch(T[prog.first%K])
			{
				case'>':SEG.Update(1,S[i]-1,prog);break;
				case'=':SEG.Update(S[i],S[i],prog);break;
				case'<':SEG.Update(S[i]+1,1000000,prog);break;
				default:assert(0);break;
			}
		}
		printf("%d\n",ans.first+1);
		PrintAnswer(ans.first,ans.second);puts("");
	}
	return 0;
}
