#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long LL;
int N;
int FLAG[100000],ADD[100001];
struct Seg
{
	LL sz[400000],sum[400000];
	int addv,addloc;
	void clear(){sz[1]=sum[1]=0LL,addv=addloc=-1;}
	void Add(const int id,const int l,const int r,const int loc,const int v)
	{
		if(l==r){sz[id]+=v,sum[id]+=v;return;}
		if(sz[id]==0LL)sz[id*2]=sz[id*2+1]=sum[id*2]=sum[id*2+1]=0LL;
		const int mid=(l+r)/2;
		if(loc<=mid)Add(id*2,l,mid,loc,v);
		else Add(id*2+1,mid+1,r,loc,v);
		sz[id]=sz[id*2]+sz[id*2+1];
		sum[id]=sum[id*2]+sz[id*2+1]*(mid-l+1)+sum[id*2+1];
	}
	void AchieveGoal(const int id,const int l,const int r,int &v)
	{
//		printf("(%d,%d),v=%d\n",l,r,v);
		if(l==r)
		{
			assert(v<=r);
			addv=r-v,addloc=l-1;
			assert(sz[id]>=addv);
			sz[id]-=addv,sum[id]-=addv,sz[id]++,sum[id]++;
//			printf("addv=%d,addloc=%d,sz=%lld,sum=%lld\n",addv,addloc,sz[id],sum[id]);
			return;
		}
		if(sz[id]==0LL)sz[id*2]=sz[id*2+1]=sum[id*2]=sum[id*2+1]=0LL;
		const int mid=(l+r)/2;
		if(v+sum[id*2+1]<=mid)
		{
			v+=sum[id*2+1];
			Add(id*2,l,mid,mid,sz[id*2+1]);
			sz[id*2+1]=sum[id*2+1]=0LL;
			AchieveGoal(id*2,l,mid,v);
		}
		else AchieveGoal(id*2+1,mid+1,r,v);
		sz[id]=sz[id*2]+sz[id*2+1];
		sum[id]=sum[id*2]+sz[id*2+1]*(mid-l+1)+sum[id*2+1];
//		printf("(%d,%d,%d)\n",l,addloc,r);
		if(addloc>=l&&addloc<=r)Add(id,l,r,addloc,addv),addv=addloc=-1;//,printf("add %d to %d\n",addv,addloc);
	}
	void OutPut(const int id,const int l,const int r,vector<LL>&cnt)
	{
		if(sz[id]==0LL||r==0)return;
//		if(sz[id]==0LL)sz[id*2]=sz[id*2+1]=sum[id*2]=sum[id*2+1]=0LL;
		if(l==r)
		{
//			if(r==0)return;
			for(int i=0;i<sz[id];i++)cnt.push_back(l);
			return;
		}
		const int mid=(l+r)/2;
		OutPut(id*2,l,mid,cnt),OutPut(id*2+1,mid+1,r,cnt);
	}
	void Print(const int id,const int l,const int r)
	{
		if(!sz[id])return;
		if(l==r&&l!=0){for(int i=0;i<sz[id];i++)printf(" %d",l);return;}
		const int mid=(l+r)/2;
		Print(id*2,l,mid),Print(id*2+1,mid+1,r);
	}
}SEG;
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<100000;i++)ADD[i]=0;
	scanf("%d",&N);
	LL sum=0LL;
	for(int i=0,h,k;i<N;i++)
	{
		scanf("%d%d",&h,&k);
		ADD[h-k]++,ADD[h]--;
		sum+=k;
	}
	for(int i=0,cnt=0;i<100000;i++)FLAG[i]=(cnt+=ADD[i]);
//	for(int i=0;i<5;i++)printf("%d\n",FLAG[i]);
	SEG.clear();
//	bool zero=true;
	bool flagged=false;
//	LL tmp=0LL;
	for(int i=99999;i>=0;i--)if(flagged||FLAG[i]>0)
	{
//		cnt++;
		flagged=true;
//		if(FLAG[i])zero=false;
//		tmp+=FLAG[i]+1LL;
		SEG.AchieveGoal(1,0,N,FLAG[i]);
//		if(!zero)printf("h:"),SEG.Print(1,0,N),puts("");
		assert(SEG.addloc==-1);
//		assert(SEG.sz[1]==cnt);
//		assert(SEG.sum[1]==tmp);
	}
	vector<LL>cnt;
	SEG.OutPut(1,0,N,cnt);
	LL ans=0LL;
	for(int i=0;i<cnt.size();i++)ans+=cnt[i]*(cnt[i]-1LL)/2LL,sum-=cnt[i];//,printf(" %lld",cnt[i]);puts("");
	printf("%lld\n",ans);
//	printf("sum=%lld\n",sum);
//	assert(sum==0LL);
	return 0;
}
