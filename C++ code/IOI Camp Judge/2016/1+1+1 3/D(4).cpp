#include<cstdio>
#include<cassert>
#include<algorithm>
#include<utility>
#include<vector>
using namespace std;
const int INF=2147483647;
int N,Z[100000];
char S[100001];
int LEFT[100001],RIGHT[100001],CNT[100001],MX;
int FindR(const int a){return RIGHT[a]==a?a:(RIGHT[a]=FindR(RIGHT[a]));}
int FindL(const int a){return LEFT[a]==a?a:(LEFT[a]=FindL(LEFT[a]));}
void Merge(const int l1,const int l2)
{
	CNT[l1]--,CNT[l2]--;
	if(l1+l2>MX)MX=l1+l2;
	CNT[l1+l2]++;
}
vector<int>LOC[100001];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%s",&N,S);
		Z[0]=0;
		for(int i=1,mx=0;i<N;i++)
		{
			if(mx+Z[mx]>=i)Z[i]=min(mx+Z[mx]-i,Z[i-mx]);
			else Z[i]=0;
			while(S[i+Z[i]]==S[Z[i]])Z[i]++;
			if(i+Z[i]>=mx+Z[mx])mx=i;
//			printf("Z[%d]=%d\n",i,Z[i]);
		}
//		printf("Z[%d]=%d\n",N-1,Z[N-1]);
		for(int i=0;i<=N;i++)LEFT[i]=RIGHT[i]=i,CNT[i]=0;
		CNT[1]=N,MX=1;
		for(int i=0;i<=N;i++)LOC[i].clear();
		for(int i=1;i<N;i++)LOC[Z[i]].push_back(i);
		for(int height=1;;height++)
		{
			for(const int i:LOC[height-1])
			{
				const int l=LEFT[i]=FindL(i-1);
				const int r=RIGHT[i]=FindR(i+1);
//				printf("(%d,%d,%d)\n",l,i,r);
				Merge(i-l,r-i);
			}
//			printf("MX=%d:",MX);for(int i=0;i<=N;i++)printf(" %d",CNT[i]);puts("");
			if(height>=MX){printf("%d\n",height);break;}
		}
	}
	return 0;
}
