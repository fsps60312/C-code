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
		MOD=2147483647;
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
		LL full=0LL,part=0LL;
		for(int j1=0;j1<K;j1++)
		{
			LL tfull=1LL,tpart=1LL;
			for(int j2=0;j2<K;j2++)
			{
				if(j2==j1)tpart*=MXEAT[j1][j2],tpart%=MOD;
				else if(MXEAT[j2][j1]>=MXEAT[j1][j1]+1)continue;//eat no j2, else combine in j2
				else if(MXLEN[j2]>MXLEN[j1])tfull*=MXEAT[j1][j2]+1LL,tfull%=MOD;//full eat any j2, but part eat no j2
				else /*if(MXLEN[j2]<MXLEN[j1])*/tfull*=MXEAT[j1][j2]+1LL,tfull%=MOD,tpart*=MXEAT[j1][j2]+1LL,tpart%=MOD;//full eat any j2, 
			}
			full+=tfull,full%=MOD,part+=tpart,part%=MOD;
		}
		printf("%lld\n",(full+part)%MOD);
	}
	return 0;
}
