#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long LL;
int N;
struct Seg
{
	int s[400000];
	void Build(const int id,const int l,const int r)
	{
		s[id]=0;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void Add(const int id,const int l,const int r,const int bl,const int br)
	{
		if(l>br||r<bl)return;
		if(bl<=l&&r<=br){s[id]++;return;}
		const int mid=(l+r)/2;
		Add(id*2,l,mid,bl,br),Add(id*2+1,mid+1,r,bl,br);
	}
	void OutPut(const int id,const int l,const int r,LL *result)
	{
		if(l==r){result[l-1]=s[id];return;}
		s[id*2]+=s[id],s[id*2+1]+=s[id],s[id]=0;
		const int mid=(l+r)/2;
		OutPut(id*2,l,mid,result),OutPut(id*2+1,mid+1,r,result);
	}
}SEG;
LL CNT[100000],ANS[100000];
bool Check(const int mxcnt)
{
	LL remain=0LL;
	for(int i=99999;i>=0;i--)
	{
		remain+=CNT[i];
		if(remain>=mxcnt)remain-=mxcnt,ANS[i]=mxcnt;
		else ANS[i]=remain,remain=0LL;
	}
	return remain==0LL;
}
struct CmpMnANS{bool operator()(const int a,const int b){return ANS[a]>ANS[b];}};
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	SEG.Build(1,1,100000);
	for(int i=0,h,k;i<N;i++)
	{
		scanf("%d%d",&h,&k);
		SEG.Add(1,1,100000,h-k+1,h);
	}
	SEG.OutPut(1,1,100000,CNT);
	int l=1,r=N;
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(Check(mid))r=mid;
		else l=mid+1;
	}
	Check(l);
	priority_queue<int,vector<int>,CmpMnANS>pq;
	bool omit=false;
	for(int i=0;i<=99999;i++)
	{
		if(ANS[i]==l)
		{
			if(!pq.empty())
			{
				const int u=pq.top();pq.pop();
				ANS[i]--;
				if(++ANS[u]<l-1)pq.push(u);
			}
			else omit=true;
		}
		else if(ANS[i]<l-1)pq.push(i);
	}
	assert(omit);
	LL ans=0LL;
	for(int i=0;i<=99999;i++)ans+=ANS[i]*(ANS[i]-1LL)/2LL;
	printf("%lld\n",ans);
	return 0;
}
