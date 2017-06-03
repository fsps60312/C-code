#include<cstdio>
#include<string>
#include<map>
#include<vector>
#include<set>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=1LL<<61;
LL S,T,NR,L,DIST[202][202],PRE[202][202];
map<string,LL>IDX[21];
set<string>RULE;
vector<string>RI[21];
LL AddIdx(string str)
{
	for(LL i=0LL;i<str.size();i++)
	{
		string s=str.substr(i);
		LL len=s.size();
//		printf("len=%lld,sz=%lld\n",len,str.size());
		if(IDX[len].find(s)==IDX[len].end())
		{
			static LL sz;sz=IDX[len].size();
//			printf("%s\n",s.c_str());
			RI[len].push_back(s);
			assert(sz<202LL);
			IDX[len][s]=sz;
		}
	}
	assert(IDX[str.size()].find(str)!=IDX[str.size()].end());
	return IDX[str.size()][str];
}
LL AddIdx()
{
	static char tmp[21];
	scanf("%s",tmp);
	return AddIdx(tmp);
}
LL Solve()
{
//	printf("L=%lld\n",L);
	for(LL l=1LL;l<=L;l++)
	{
//		printf("l=%lld\n",l);
//		for(map<string,int>::iterator it=IDX[l].begin();it!=IDX[l].end();it++)printf("\t%s\n",it->first.c_str());
		LL sz=IDX[l].size();
		for(LL i=0LL;i<sz;i++)
		{
			for(LL j=0LL;j<sz;j++)
			{
				if(i==j){DIST[i][j]=0LL;continue;}
				string &si=RI[l][i],&sj=RI[l][j];
				if(RULE.find(si+"."+sj)!=RULE.end())DIST[i][j]=1;
				else if(l>1&&si[0LL]==sj[0LL])
				{
					string ti=si.substr(1LL),tj=sj.substr(1LL);
					assert(IDX[l-1LL].find(ti)!=IDX[l-1LL].end()&&IDX[l-1LL].find(tj)!=IDX[l-1LL].end());
					DIST[i][j]=PRE[IDX[l-1LL][ti]][IDX[l-1LL][tj]];
				}
				else DIST[i][j]=INF;
			}
		}
		for(LL m=0LL;m<sz;m++)for(LL i=0LL;i<sz;i++)for(LL j=0LL;j<sz;j++)
		if(DIST[i][j]>DIST[i][m]+DIST[m][j])DIST[i][j]=DIST[i][m]+DIST[m][j];
		for(LL i=0LL;i<sz;i++)for(LL j=0LL;j<sz;j++)PRE[i][j]=DIST[i][j];
	}
	return DIST[S][T];
}
int main()
{
//	freopen("in.txt","r",stdin);
	static char tstr[21];
	while(scanf("%s",tstr)==1&&!(tstr[0]=='.'&&!tstr[1]))
	{
		RULE.clear();
		for(LL i=1LL;i<=20LL;i++)IDX[i].clear(),RI[i].clear();
		for(LL i=0LL;;i++)if(!tstr[i]){L=i;break;}
		S=AddIdx(tstr),T=AddIdx();
		scanf("%lld",&NR);
		for(LL i=0LL;i<NR;i++)
		{
			static char a[21],b[21];
			scanf("%s%s",a,b);
			AddIdx(a),AddIdx(b);
			string s=a;s+=".";s+=b;
			RULE.insert(s);
		}
		static LL kase=1;
		printf("Case %lld: ",kase++);
		LL ans=Solve();
		if(ans==INF)puts("No solution");
		else printf("%lld\n",ans);
	}
	return 0;
}
