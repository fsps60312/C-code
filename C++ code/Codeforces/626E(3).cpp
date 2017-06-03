#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
int N;
LL S[200001],SUM[200001];
double ANS_BEST;
int ANS_L1,ANS_L2,ANS_R1,ANS_R2;
void Update(const double &ans_best,const int ans_l1,const int ans_l2,const int ans_r1,const int ans_r2)
{
	if(ans_best<=ANS_BEST)return;
	ANS_BEST=ans_best,ANS_L1=ans_l1,ANS_L2=ans_l2,ANS_R1=ans_r1,ANS_R2=ans_r2;
}
double OddAns(const int mid,const int k)
{
	return (double)((SUM[mid]-SUM[mid-k-1])+(SUM[N]-SUM[N-k]))/(k*2+1)-S[mid];
}
double EvenAns(const int mid,const int k)
{
	return (double)((SUM[mid+1]-SUM[mid-k-1])+(SUM[N]-SUM[N-k]))/(k*2+2)-0.5*(S[mid]+S[mid+1]);
}
void Solve(vector<int>&ans)
{
	ANS_BEST=-1.0;
	sort(S+1,S+N+1);
	for(int i=1;i<=N;i++)SUM[i]=SUM[i-1]+S[i];
	for(int i=1;i<=N;i++)
	{
		int l=0,r=min(i-1,N-i);
		while(r-l>=3)
		{
			const int ml=(l*2+r)/3,mr=(l+r*2)/3;
			if(OddAns(i,ml)<OddAns(i,mr))l=ml;
			else r=mr;
		}
		for(int k=l;k<=r;k++)assert(k>=0),Update(OddAns(i,k),i-k-1,i,N-k,N);
	}
	for(int i=1;i<N;i++)
	{
		int l=0,r=min(i-1,N-(i+1));
		while(r-l>=3)
		{
			const int ml=(l*2+r)/3,mr=(l+r*2)/3;
			if(EvenAns(i,ml)<EvenAns(i,mr))l=ml;
			else r=mr;
		}
		for(int k=l;k<=r;k++)assert(k>=0),Update(EvenAns(i,k),i-k-1,i+1,N-k,N);
	}
	ans.clear();
	assert(ANS_L1<ANS_L2);
	for(int i=ANS_L1+1;i<=ANS_L2;i++)ans.push_back(S[i]);
	for(int i=ANS_R1+1;i<=ANS_R2;i++)ans.push_back(S[i]);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)scanf("%I64d",&S[i]);
		vector<int>ans;
		Solve(ans);
		printf("%d\n",(int)ans.size());
		for(int i=0;i<(int)ans.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]);
		}
		puts("");
	}
	return 0;
}
