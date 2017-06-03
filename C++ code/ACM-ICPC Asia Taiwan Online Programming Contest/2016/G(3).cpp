#include<cstdio>
#include<cassert>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAX_HL=4;
struct Pair
{
	LL first;
	string second;
	Pair(LL a,string b):first(a),second(b){}
};
bool operator<(Pair a,Pair b){return a.first<b.first;}
int L;
LL R,MOD;
void Exgcd(const LL a,const LL b,LL &x,LL &y)
{
	if(b==0){assert(a==1);x=1,y=0;}
	else
	{
		Exgcd(b,a%b,y,x);
		(y-=a/b*x)%=MOD;
	}
}
LL Inv(const LL v)
{
	LL x,y;
	Exgcd(v,MOD,x,y);
	return (x+MOD)%MOD;
}
LL P[8][27],Q[8][27];
bool Initialize()
{
	LL p[8]={2,3,5,7,11,13,17,19};
	for(int i=0;i<L;i++)if(MOD==p[i])return false;
	for(int i=0;i<L;i++)
	{
		P[i][0]=1;
		for(int j=1;j<=26;j++)P[i][j]=(P[i][j-1]*p[i])%MOD;
	}
	for(int i=0;i<L;i++)p[i]=Inv(p[i]);
	for(int i=0;i<L;i++)
	{
		Q[i][0]=1;
		for(int j=1;j<=26;j++)Q[i][j]=(Q[i][j-1]*p[i])%MOD;
	}
	return true;
}
string ANS;
int Solve()
{
	if(!Initialize())return 2;
	vector<Pair>lm[5];
	lm[0].push_back(Pair(1,string("")));
//	puts("ccc");
	for(int loc=0;loc<MAX_HL&&loc<L;loc++)
	{
		auto &nxtlm=lm[loc+1];
		for(const auto &p:lm[loc])
		{
			for(int c=1;c<=26;c++)
			{
				auto nxtp=Pair(p.first*P[loc][c]%MOD,p.second+(char)('A'+(c-1)));
//				if(nxtlm.find(nxtp.first)!=nxtlm.end())nxtp.second.second=false;
				nxtlm.push_back(nxtp);
			}
		}
	}
//	puts("aaa");
	if(L<=MAX_HL)
	{
		sort(lm[L].begin(),lm[L].end());
		const auto &itl=lower_bound(lm[L].begin(),lm[L].end(),Pair(R,"")),&itr=upper_bound(lm[L].begin(),lm[L].end(),Pair(R,""));
		if(itl==itr)return 0;
		else if(itr-itl>1)return 2;
		else
		{
			ANS=itl->second;
			return 1;
		}
	}
	else
	{
		vector<Pair>rm[9];
		rm[L].push_back(Pair(R,string("")));
		for(int loc=L-1;loc>=MAX_HL;loc--)
		{
			auto &nxtrm=rm[loc];
			for(const auto &p:rm[loc+1])
			{
				for(int c=1;c<=26;c++)
				{
					auto nxtp=Pair(p.first*Q[loc][c]%MOD,(char)('A'+(c-1))+p.second);
					nxtrm.push_back(nxtp);
				}
			}
		}
//		puts("bbb");
		int cnt=0;
		printf("%d %d\n",(int)lm[MAX_HL].size(),(int)rm[MAX_HL].size());
		vector<int>lo,ro;
		for(int i=0;i<(int)lm[MAX_HL].size();i++)lo.push_back(i);
		for(int i=0;i<(int)rm[MAX_HL].size();i++)ro.push_back(i);
		sort(lo.begin(),lo.end(),[&](int a,int b)->bool{return lm[MAX_HL][a]<lm[MAX_HL][b];});
		sort(ro.begin(),ro.end(),[&](int a,int b)->bool{return rm[MAX_HL][a]<rm[MAX_HL][b];});
//		puts("ddd");
		for(auto p=ro.begin(),nxtp=ro.begin();p!=ro.end();p=nxtp)
		{
					   nxtp=upper_bound(ro.begin(),ro.end(),*p,[&](int a,int b)->bool{return rm[MAX_HL][a]<rm[MAX_HL][b];});
			const auto &itl=lower_bound(lo.begin(),lo.end(),*p,[&](int a,int b)->bool{return lm[MAX_HL][a]<lm[MAX_HL][b];})
					  ,&itr=upper_bound(lo.begin(),lo.end(),*p,[&](int a,int b)->bool{return lm[MAX_HL][a]<lm[MAX_HL][b];});
			if(itl!=itr&&p!=nxtp)
			{
				if(itr-itl>1||nxtp-p>1)return 2;
				ANS=lm[MAX_HL][*itl].second+rm[MAX_HL][*p].second;
				if(++cnt==2)return 2;
			}
		}
		if(cnt==0)return 0;
		return 1;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%lld%lld",&L,&R,&MOD)==3)
	{
		if(L==0&&R==0&&MOD==0)break;
		Initialize();
		const int result=Solve();
		switch(result)
		{
			case 0:puts("not a word");break;
			case 2:puts("ambiguous");break;
			case 1:puts(ANS.c_str());break;
			default:assert(0);break;
		}
	}
	return 0;
}
