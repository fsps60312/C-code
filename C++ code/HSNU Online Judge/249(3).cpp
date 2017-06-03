#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
void getmax(int &a,const int b){if(b>a)a=b;}
int F,K;
LL MOD;
struct Fish
{
	int len,jewel;
	Fish(){}
	Fish(const int _l,const int _j):len(_l),jewel(_j){}
	bool operator<(const Fish &f)const{return len<f.len;}
};
vector<Fish>FISH;
int MXLEN[500000];
vector<vector<int> >MXEAT;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d%lld",&F,&K,&MOD)==3)
	{
//		MOD=2147483647;
		for(int i=0;i<K;i++)MXLEN[i]=-1;
		FISH.clear();
		for(int i=0,l,j;i<F;i++)
		{
			scanf("%d%d",&l,&j);
			j--;
			FISH.push_back(Fish(l,j));
			getmax(MXLEN[j],l);
		}
		MXEAT.resize(K);
		for(int i=0;i<K;i++)for(int j=0;j<K;j++)MXEAT[i].push_back(0);
		for(int i=0;i<F;i++)
		{
			const Fish &f=FISH[i];
			for(int k=0;k<K;k++)if(MXLEN[k]>=f.len*2)MXEAT[k][f.jewel]++;
		}
		LL full=0LL;
		for(int j1=0;j1<K;j1++)
		{
			LL ta=1LL;
			for(int j2=0;j2<K;j2++)
			{
				if(j2==j1)continue;
				else if(MXEAT[j2][j1]>MXEAT[j1][j1])continue;//eat no j2
				else ta*=MXEAT[j1][j2]+1LL,ta%=MOD;
			}
			full+=ta,full%=MOD;
		}
		LL part=0LL;
		for(int j1=0;j1<K;j1++)
		{
			LL ta=1LL;
			for(int j2=0;j2<K;j2++)
			{
				if(j2==j1)ta*=MXEAT[j1][j2],ta%=MOD;
				else if(MXLEN[j2]>=MXLEN[j1])continue;//eat no j2
				else ta*=MXEAT[j1][j2]+1LL,ta%=MOD;
			}
			part+=ta,part%=MOD;
		}
		printf("%lld\n",(full+part)%MOD);
	}
	return 0;
}
