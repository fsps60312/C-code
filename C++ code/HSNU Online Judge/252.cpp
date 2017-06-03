#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,M;
int NXT[4000004];
bool VIS[4000004],PLACED[2000001];
bool Walk(const int source,int &midcnt,int &transmit)
{
	assert(!VIS[source]&&(source&1));
	int u=source;VIS[u]=true;
	for(;;)
	{
		if(NXT[u]==u)NXT[u]=((u>>1)+1)<<1;
		if(VIS[NXT[u]])return false;
		VIS[NXT[u]]=true;
		if(u!=source&&!(u&1)&&!(NXT[u]&1))midcnt++;
		if(NXT[u]&1)transmit++,printf("transmit %d to %d\n",u>>1,NXT[u]>>1);
		u=NXT[u];
		if(u==2000001*2)return true;
	}
}
struct PathInfo
{
	int midcnt,transmit;
	PathInfo(){}
	PathInfo(const int _m,const int _t):midcnt(_m),transmit(_t){}
	bool operator<(const PathInfo &p)const{return transmit>p.transmit;}
};
int Solve()
{
	int midcnt=0;
	int transmit=0;
	assert(Walk(1,midcnt,transmit));
	printf("midcnt=%d,transmit=%d\n",midcnt,transmit);
	if(!midcnt)return transmit;
	vector<PathInfo>info,extra;
	for(int i=1;i<=2000000;i++)
	{
		if(VIS[i*2]||VIS[i*2+1]||PLACED[i])continue;
		int m=0,t=0;
		assert(!Walk(i*2+1,m,t));
		(m==0?extra:info).push_back(PathInfo(m,t+2));
	}
	sort(info.begin(),info.end());
	sort(extra.begin(),extra.end());
	printf("info :");for(int i=0;i<info.size();i++)printf("(%d,%d)",info[i].midcnt,info[i].transmit);puts("");
	printf("extra:");for(int i=0;i<extra.size();i++)printf("(%d,%d)",extra[i].midcnt,extra[i].transmit);puts("");
	for(int a=0,b=0;M&&(a<info.size()||b<extra.size());)
	{
		M--;
		PathInfo p;
		if(a==info.size())p=extra[b++];
		else if(b==extra.size())p=info[a++];
		else if(M==0||midcnt>=2)p=(info[a].transmit>=extra[b].transmit?info[a++]:extra[b++]);
		else p=info[a++];
		midcnt--;
		assert(midcnt>=0);
		midcnt+=p.midcnt;
		transmit+=p.transmit;
	}
	while(midcnt>=4&&M>=2)midcnt-=4,M-=2,transmit+=4;
	return transmit;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<=2000001;i++)PLACED[i]=false;
		for(int i=0;i<2000002*2;i++)NXT[i]=i,VIS[i]=false;
		for(int i=0,a,b;i<N;i++)
		{
			scanf("%d%d",&a,&b);
			PLACED[a]=PLACED[b]=true;
			NXT[a*2]=b*2+1;
			NXT[b*2]=a*2+1;
		}
		printf("%d\n",Solve());
	}
	return 0;
}
