#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int min(int x,int y){return x<y?x:y;}
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
int N;
vector<int> V,TMP;
int solve()
{
	int minv=1000,minp=-1;
	for(int i=0;i<N;i++)if(V[i]==TMP[i]&&V[i]<=minv)minv=V[i],minp=i;
	if(minv)
	{
		int sum=0,cnt=0;
		for(int i=0;i<N;i++)if(V[i]!=TMP[i]&&i!=minp)sum+=V[i],cnt++;
		return minv*cnt+sum;
	}
	return -1;
}
int main()
{
	freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		V.clear(),TMP.clear();
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			V.push_back(v),TMP.push_back(v);
		}
		sort(TMP.begin(),TMP.end());
		printf("Case %d: %d\n\n",kase++,solve());
	}
	return 0;
}
