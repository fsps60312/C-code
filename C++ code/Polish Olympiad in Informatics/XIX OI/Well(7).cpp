#include<cstdio>
#include<cassert>
#include<queue>
#include<utility>
#include<algorithm>
using namespace std;
typedef long long LL;
int N;
LL M;
inline void CutRight(const int _x,int h,const int slope,const int *hs,LL &ans_f,int &ans_s)
{
	LL &sum=ans_f=h;
	for(int &x=ans_s=_x;x<N&&h<hs[x];x++,h+=slope)sum+=hs[x]-h;
}
inline void CutLeft(const int _x,int h,const int slope,const int *hs,LL &ans_f,int &ans_s)
{
	LL &sum=ans_f=h;
	for(int &x=ans_s=_x;x>=0&&h<hs[x];x--,h+=slope)sum+=hs[x]-h;
}
int ORDER[1000000];
int Solve(const int slope,const int *_hs)
{
	static int hs[1000000];
	for(int i=0;i<N;i++)hs[i]=_hs[i];
	static int q[1000000],r;r=-1;
	static bool inq[1000000];
	for(int i=N-1;i>=0;i--)q[++r]=ORDER[i],inq[i]=true;
	for(int x;r>=0;)
	{
		x=q[r--];
		inq[x]=false;
		if(x-1>=0&&hs[x-1]-hs[x]>slope)
		{
			hs[x-1]=hs[x]+slope;
			if(!inq[x-1])q[++r]=x-1,inq[x-1]=true;
		}
		if(x+1<N&&hs[x+1]-hs[x]>slope)
		{
			hs[x+1]=hs[x]+slope;
			if(!inq[x+1])q[++r]=x+1,inq[x+1]=true;
		}
	}
	static LL right_f[1000000];
	static int right_s[1000000];
	CutRight(0,0,slope,hs,right_f[0],right_s[0]);
	for(int i=1;i<N;i++)
	{
		CutRight(right_s[i-1],slope*(right_s[i-1]-i),slope,hs,right_f[i],right_s[i]);
		right_f[i]+=right_f[i-1];
	}
	static LL left_f[1000000];
	static int left_s[1000000];
	CutLeft(N-1,0,slope,hs,left_f[N-1],left_s[N-1]);
	for(int i=N-2;i>=0;i--)
	{
		CutLeft(left_s[i+1],slope*(i-left_s[i+1]),slope,hs,left_f[i],left_s[i]);
		left_f[i]+=left_f[i+1];
	}
	LL digged=0LL,sum=0LL;
	for(int i=0;i<N;i++)digged+=_hs[i]-hs[i],sum+=hs[i];
	for(int i=0;i<N;i++)
	{
		const LL ta=digged+left_f[i]+right_f[i]-sum;
		if(ta<=M)return i;
	}
	return -1;
}
int H[1000000];
bool CmpH(const int a,const int b){return H[a]<H[b];}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("stu7c.in","r",stdin);
	scanf("%d%lld",&N,&M);
	for(int i=0;i<N;i++)scanf("%d",&H[i]);
	for(int i=0;i<N;i++)ORDER[i]=i;
	sort(ORDER,ORDER+N,CmpH);
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
