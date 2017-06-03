#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
LL N;
struct Cake
{
	LL w,h;
}CAKE[4000];
LL CNT[4000][4000];
map<LL,LL>IDXW,IDXH;
vector<LL>RW,RH;
int main()
{
	scanf("%I64d",&N);
	for(LL i=0;i<N;i++)
	{
		LL &w=CAKE[i].w,&h=CAKE[i].h;
		scanf("%I64d%I64d",&w,&h);
		if(w>h)swap(w,h);
		IDXW[w]=IDXH[h]=0;
	}
	LL cnt=0;
	for(auto it=IDXW.begin();it!=IDXW.end();it++)it->second=cnt++,RW.push_back(it->first);
	cnt=0;
	for(auto it=IDXH.begin();it!=IDXH.end();it++)it->second=cnt++,RH.push_back(it->first);
	for(LL i=0;i<IDXW.size();i++)for(LL j=0;j<IDXH.size();j++)CNT[i][j]=0;
	for(LL i=0;i<N;i++)CNT[IDXW[CAKE[i].w]][IDXH[CAKE[i].h]]++;
	for(LL i=int(IDXW.size())-2;i>=0;i--)for(LL j=0;j<IDXH.size();j++)CNT[i][j]+=CNT[i+1][j];
	for(LL i=0;i<IDXW.size();i++)for(LL j=int(IDXH.size())-2;j>=0;j--)CNT[i][j]+=CNT[i][j+1];
	LL mx=0,wans=-1,hans=-1;
	for(LL i=0;i<IDXW.size();i++)for(LL j=0;j<IDXH.size();j++)
	{
		if(CNT[i][j]*RW[i]*RH[j]>mx)mx=CNT[i][j]*RW[i]*RH[j],wans=RW[i],hans=RH[i];
	}
	printf("%I64d\n%I64d %I64d\n",mx,wans,hans);
	return 0;
}
