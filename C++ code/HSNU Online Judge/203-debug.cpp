#include<bits/stdc++.h>
#define LL long long
using namespace std;
int H[100001],W[100001],N,L;
LL SUM[100001],DP[100001];
int DEQ[100001];
multiset<LL>MST;
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&L);
    for(int i=1;i<=N;i++)scanf("%d%d",&H[i],&W[i]);
    int l=0,r=-1;
    DEQ[++r]=0;
    for(int i=1;i<=N;i++)
    {
        SUM[i]=SUM[i-1]+W[i];
        while(r-l+1>=2&&H[DEQ[r]]<=H[i])
        {
        	MST.erase(MST.find(DP[DEQ[r-1]]+H[DEQ[r]]));
			r--;
		}
        MST.insert(DP[DEQ[r]]+H[i]);
        DEQ[++r]=i;
        while(SUM[i]-SUM[DEQ[l]]>L)
        {
            MST.erase(MST.find(DP[DEQ[l]]+H[DEQ[l+1]]));
            if(++DEQ[l]==DEQ[l+1])l++;
            else MST.insert(DP[DEQ[l]]+H[DEQ[l+1]]);
        }
        DP[i]=*MST.begin();
    }
    printf("%lld\n",DP[N]);
}
