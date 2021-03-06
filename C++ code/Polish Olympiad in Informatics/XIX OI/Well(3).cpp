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
	queue<int>q;
	static int inq[1000000];
	for(int i=0;i<N;i++)q.push(i),inq[i]=true;
	while(!q.empty())
	{
		const int x=q.front();q.pop();inq[x]=false;
		if(x-1>=0&&hs[x-1]-hs[x]>slope)
		{
			hs[x-1]=hs[x]+slope;
			if(!inq[x-1])q.push(x-1),inq[x-1]=true;
		}
		if(x+1<N&&hs[x+1]-hs[x]>slope)
		{
			hs[x+1]=hs[x]+slope;
			if(!inq[x+1])q.push(x+1),inq[x+1]=true;
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
	freopen("stu6b.in","r",stdin);
	scanf("%d%lld",&N,&M);
	for(int i=0;i<N;i++)scanf("%d",&H[i]);
	int l=0,r=1e9;
	while(l<r)
	{
		const int mid=(l+r)/2;
//		printf("(%d,%d,%d)\n",l,mid,r);
		if(Solve(mid,H)!=-1)r=mid;
		else l=mid+1;
	}
	const int ans=Solve(r,H);
	assert(ans!=-1);
	printf("%d %d\n",ans+1,r);
	return 0;
}
