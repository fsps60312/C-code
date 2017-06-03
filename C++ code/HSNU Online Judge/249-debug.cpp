#include <bits/stdc++.h>
using namespace std;
const int maxn = 500000 + 10;
#define lc o<<1 , l , m
#define rc o<<1|1 , m+1 , r
struct Fish {
	int len , type;
	bool operator < (const Fish &ob) const {
		if(len != ob.len) return len < ob.len;
		else return type < ob.type;
	}
} A[maxn] , LONGEST[maxn];
int MOD , TR[maxn<<3];
void Build(int o , int l , int r) {
	TR[o] = 1;
	if(l != r) {
		int m = (l+r)>>1;
		Build(lc) , Build(rc);
	}
}
void Modify(int o , int l , int r , int p , int v) {
	if(l == r) {
		TR[o] = v%MOD;
		return;
	}
	int m = (l+r)>>1;
	if(p <= m) Modify(lc , p , v);
	else Modify(rc , p , v);
	TR[o] = (TR[o<<1]*TR[o<<1|1])%MOD;
}
int Query(int o , int l , int r , int ql , int qr) {
	if(ql <= l && r <= qr) return TR[o];
	int m = (l+r)>>1;
	if(qr <= m) return Query(lc , ql , qr);
	else if(m < ql) return Query(rc , ql , qr);
	else return Query(lc , ql , qr)*Query(rc , ql , qr)%MOD;
}
vector<int>LENS[maxn];
int FindPos(int type,int val)
{
	if(2*LENS[type][0]>val)return 0;
	int l=0,r=(int)LENS[type].size();
	while(r-l>1)
	{
		int m=(l+r)>>1;
		if(2*LENS[type][m]<=val)l=m;
		else r=m;
	}
	return l+1;
}
int CNT[maxn],RANK[maxn],N,K;
int main()
{
//	srand(time(NULL));
//	printf("%d\n",rand());
//	freopen("in.txt","r",stdin);
//	freopen("new.txt","w",stdout);
	while(scanf("%d%d%d",&N,&K,&MOD)==3)
	{
		for(int i=0;i<=N;i++)LENS[i].clear(),CNT[i]=RANK[i]=A[i].len=A[i].type=LONGEST[i].len=LONGEST[i].type=0;
		for(int i=1;i<=N;i++)
		{
			scanf("%d%d",&A[i].len,&A[i].type);
			LENS[A[i].type].push_back(A[i].len);
		} 
		for(int i=1;i<=K;i++)sort(LENS[i].begin(),LENS[i].end());
		sort(A+1,A+N+1);
		for(int i=N;i>=1;i--)if(LONGEST[A[i].type].len==0)LONGEST[A[i].type]=A[i];
		sort(LONGEST+1,LONGEST+K+1);
		for(int i=1;i<=K;i++)RANK[LONGEST[i].type]=i;
		Build(1,1,K);
		int ans=0;
		for(int i=1,j=0;i<=K;i++)
		{
			while(j<N&&2*A[j+1].len<=LONGEST[i].len)
			{
				j++;
				CNT[A[j].type]++;
				Modify(1,1,K,RANK[A[j].type],CNT[A[j].type]+1);
			}
			int l=i,r=K+1;
			int val=FindPos(LONGEST[i].type,LONGEST[i].len);
			while(r-l>1)
			{
				int m=(l+r)>>1;
				if(FindPos(LONGEST[i].type,LONGEST[m].len)>val)r=m;
				else l=m;
			}
			int tmp=i<l?Query(1,1,K,i+1,l):1;
			tmp=(tmp+CNT[LONGEST[i].type])%MOD;
			(tmp*=(i>1?Query(1,1,K,1,i-1):1))%=MOD;
			(ans+=tmp)%=MOD;
		}
		printf("%d\n",ans);
	}
	return 0;
}
