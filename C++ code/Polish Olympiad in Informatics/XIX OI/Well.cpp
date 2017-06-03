#include<cstdio>
#include<cassert>
#include<queue>
#include<utility>
using namespace std;
typedef long long LL;
int N;
LL M;
pair<LL,int>CutRight(int x,int h,const int slope,const int *hs)
{
	LL sum=0LL;
	for(;x<N&&h<hs[x];x++,h+=slope)sum+=hs[x]-h;
	return make_pair(sum,x);
}
pair<LL,int>CutLeft(int x,int h,const int slope,const int *hs)
{
	LL sum=0LL;
	for(;x>=0&&h<hs[x];x--,h+=slope)sum+=hs[x]-h;
	return make_pair(sum,x);
}
int Solve(const int slope,const int *_hs)
{
	static int hs[1000000];
	for(int i=0;i<N;i++)hs[i]=_hs[i];
	priority_queue<pair<int,int> >pq;
	for(int i=0;i<N;i++)pq.push(make_pair(-hs[i],i));
	while(!pq.empty())
	{
		const pair<int,int>p=pq.top();pq.pop();
		const int x=p.second;
		if(hs[x]!=-p.first)continue;
		if(x-1>=0&&hs[x-1]-hs[x]>slope)
		{
			hs[x-1]=hs[x]+slope;
			pq.push(make_pair(-hs[x-1],x-1));
		}
		if(x+1<N&&hs[x+1]-hs[x]>slope)
		{
			hs[x+1]=hs[x]+slope;
			pq.push(make_pair(-hs[x+1],x+1));
		}
	}
	static pair<LL,int>right[1000000];
	right[0]=CutRight(0,0,slope,hs);
	for(int i=1;i<N;i++)
	{
		right[i]=CutRight(right[i-1].second,slope*(right[i-1].second-i),slope,hs);
		right[i].first+=right[i-1].first;
		right[i].first+=slope*(right[i-1].second-(i-1)-1);
	}
	static pair<LL,int>left[1000000];
	left[N-1]=CutLeft(N-1,0,slope,hs);
	for(int i=N-2;i>=0;i--)
	{
		left[i]=CutLeft(left[i+1].second,slope*(i-left[i+1].second),slope,hs);
		left[i].first+=left[i+1].first;
		left[i].first+=slope*((i+1)-left[i+1].second-1);
	}
	LL digged=0LL,sum=0LL;
	for(int i=0;i<N;i++)digged+=_hs[i]-hs[i],sum+=hs[i];
//	printf("slope=%d,digged=%lld,sum=%lld\n",slope,digged,sum);
	for(int i=0;i<N;i++)
	{
		const LL ta=digged+left[i].first+right[i].first-sum;
//		printf("i=%d,ta=%lld\n",i,ta);
		if(ta<=M)return i;
	}
//	printf("slope=%d,return -1\n",slope);
	return -1;
}
int H[1000000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%lld",&N,&M);
	for(int i=0;i<N;i++)scanf("%d",&H[i]);
	int l=0,r=1e9;
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(Solve(mid,H)!=-1)r=mid;
		else l=mid+1;
	}
	const int ans=Solve(r,H);
	assert(ans!=-1);
	printf("%d %d\n",ans+1,r);
	return 0;
}
