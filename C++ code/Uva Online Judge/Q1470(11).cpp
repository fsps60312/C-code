#include<cstdio>
#include<set>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int T,N;
vector<char>S;
vector<int>DP;
struct Pair
{
	int l,r;
	Pair(){}
	Pair(const int _l,const int _r):l(_l),r(_r){}
};
struct CmpL{bool operator()(const Pair &a,const Pair &b)const{return a.l<b.l;}};
struct CmpR{bool operator()(const Pair &a,const Pair &b)const{return a.r<b.r;}};
struct CmpM{bool operator()(const Pair &a,const Pair &b)const{return a.l+a.r<b.l+b.r;}};
set<Pair,CmpL>LS;
set<Pair,CmpR>RS;
set<Pair,CmpM>MS;
void Erase(const Pair p){LS.erase(p),RS.erase(p),MS.erase(p);}
void Insert(const Pair p){LS.insert(p),RS.insert(p),MS.insert(p);}
int Solve()
{
	DP[0]=1;
	for(int i=1,mx=0;i<N;i++)
	{
		if(mx+DP[mx]-1>i)DP[i]=min(DP[mx-(i-mx)],mx+DP[mx]-1-i+1);
		else DP[i]=1;
		while(i-DP[i]>=0&&i+DP[i]<N&&S[i-DP[i]]==S[i+DP[i]])DP[i]++;
	}
	int ans=0;
	for(int i=0;i<N;i+=2)
	{
		while(!LS.empty()&&(*LS.begin()).l<i-DP[i]+1)Erase(*LS.begin());
		while(!RS.empty()&&(*RS.begin()).r<i)Erase(*RS.begin());
		if(!MS.empty())
		{
			const Pair &p=*MS.begin();
			getmax(ans,i-(p.l+p.r)/2);
		}
		if(DP[i]>1)Insert(Pair(i-DP[i]+1,i+DP[i]-1));
	}
	return ans*2;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static char tmp[300002];
	assert(fgets(tmp,INF,stdin)&&sscanf(tmp,"%d",&T)==1);
	while(T--)
	{
		assert(fgets(tmp,INF,stdin));
		S.clear(),S.push_back('\0');
		N=-1;
		while(tmp[++N])
		{
			if(tmp[N]=='\n')break;
			S.push_back(tmp[N]),S.push_back('\0');
		}
		N=S.size();
		DP.resize(N);
		printf("%d\n",Solve());
	}
	return 0;
}
