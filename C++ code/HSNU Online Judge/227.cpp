#include<cstdio>
#include<vector>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int &b){if(b>a)a=b;}
int T,N,S[200000],L[200000];//,ONLY[200000],MN[200000][2],IDX[200000][2],CHECK[200000];
//bool VIS[200000];
//void UpdateMN(const int &i,const int &v,const int &i)
//{
//	if(v<MN[i][0])MN[i][1]=MN[i][0],MN[i][0]=v,IDX[i][1]=IDX[i][0],IDX[i][0]=i;;
//	else if(v<MN[i][1])MN[i][1]=v,IDX[i][1]=i;
//}
int GetLIS()
{
//	for(int i=0;i<N;i++)ONLY[i]=-1,MN[i][0]=MN[i][1]=INF;
	static int dp[200000];
	int ans=0;
	for(int i=0;i<N;i++)
	{
		int l=0,r=ans,mid;
		while(l<r)
		{
			mid=(l+r)/2;
			if(dp[mid]<=S[i])l=mid+1;
			else r=mid;
		}
		dp[L[i]=l]=S[i];
//		UpdateMN(l,S[i],i);
//		if(l==0)ONLY[i]=-1;
//		else
//		{
//			if(S[i]<=MN[l-1][1])ONLY[i]=IDX[l-1][0];
//			else ONLY[i]=-1;
//		}
		if(l==ans)ans++;
	}
	return ans;
}
//#include<stack>
//using namespace std;
int NOW[200001],CNT[200001],IDX[200001];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
//		for(int i=0;i<N;i++)NODE[i]=NULL;
		int mx=GetLIS();
		for(int i=0;i<mx;i++)NOW[i]=-INF,CNT[i]=0;
		NOW[mx]=INF,CNT[mx]++;
		for(int i=N-1;i>=0;i--)
		{
			if(!CNT[L[i]+1])continue;
			if(S[i]>=NOW[L[i]+1])continue;
			getmax(NOW[L[i]],S[i]);
			IDX[L[i]]=i+1;
			CNT[L[i]]++;
		}
		int a1=0,a2=0;
		for(int i=0;i<mx;i++)
		{
			if(CNT[i]==1)
			{
				a1++,a2^=IDX[i]+a1;
//				printf("tt=%d %d\n",IDX[i],a1);
			}
		}
		printf("%d %d\n",a1,a2);
	}
	return 0;
}
