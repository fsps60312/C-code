#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int min(int x,int y){return x<y?x:y}
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
int N,SUM,MN1,MN2,MP1,MP2,SAVE,SAVN;
vector<int> V,TMP;
int solve()
{
	if(MP1>0)return (N-2)*MN1+SUM-SAVE-SAVN*MN1;
	return min((N-2)*MN2+SUM-SAVE,MN1+MN2+(N-2)*MN1+SUM);
}
int main()
{
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
//		if(N>100)termin();
		SUM=0,MN1=1000,MP1=-1,MN2=1000,MP2=-1,SAVE=0,SAVN=0;
		V.clear(),TMP.clear();
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			V.push_back(v),TMP.push_back(v);
			SUM+=v;
			if(v<=MN1)MN2=MN1,MP2=MP1,MN1=v,MP1=i;
			else if(v<=MN2)MN2=v,MP2=i;
		}
		sort(TMP.begin(),TMP.end());
		for(int i=0;i<N;i++)if(V[i]==TMP[i])SAVE+=V[i],SAVN++;
		printf("Case %d: %d\n\n",kase++,solve());
	}
	return 0;
}
