#include<cstdio>
#include<cassert>
#include<string>
#include<unordered_map>
using namespace std;
typedef long long LL;
const int MAX_HL=4;
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
int Initialize()
{
	LL p[8]={2,3,5,7,11,13,17,19};
	for(int i=0;i<L;i++)if(MOD==p[i])return R==0?2:0;
	if(R==0)return 0;
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
	return 1;
}
string ANS;
int Solve()
{
	{
		const int result=Initialize();
		if(result!=1)return result;
	}
//	puts("a");
	unordered_map<LL,pair<string,bool> >lm[5];
	lm[0][1]=make_pair(string(""),true);
//	puts("ccc");
	for(int loc=0;loc<MAX_HL&&loc<L;loc++)
	{
		auto &nxtlm=lm[loc+1];
		for(const auto &p:lm[loc])
		{
			for(int c=1;c<=26;c++)
			{
				auto nxtp=make_pair(p.first*P[loc][c]%MOD,make_pair(p.second.first+(char)('A'+(c-1)),true));
				if(nxtlm.find(nxtp.first)!=nxtlm.end())nxtp.second.second=false;
				nxtlm[nxtp.first]=nxtp.second;
			}
		}
	}
//	puts("aaa");
	if(L<=MAX_HL)
	{
		const auto &it=lm[L].find(R);
		if(it==lm[L].end())return 0;
		else if(!it->second.second)return 2;
		else
		{
			ANS=it->second.first;
			return 1;
		}
	}
	else
	{
		unordered_map<LL,pair<string,bool> >rm[9];
		rm[L][R]=make_pair(string(""),true);
		for(int loc=L-1;loc>=MAX_HL;loc--)
		{
			auto &nxtrm=rm[loc];
			for(const auto &p:rm[loc+1])
			{
				for(int c=1;c<=26;c++)
				{
					auto nxtp=make_pair(p.first*Q[loc][c]%MOD,make_pair((char)('A'+(c-1))+p.second.first,true));
					if(nxtrm.find(nxtp.first)!=nxtrm.end())nxtp.second.second=false;
					nxtrm[nxtp.first]=nxtp.second;
				}
			}
		}
//		puts("bbb");
		int cnt=0;
		for(const auto &p:rm[MAX_HL])
		{
			const auto &it=lm[MAX_HL].find(p.first);
			if(it!=lm[MAX_HL].end())
			{
				if(!it->second.second||!p.second.second)return 2;
				ANS=it->second.first+p.second.first;
				if(++cnt==2)return 2;
			}
		}
		if(cnt==0)return 0;
		return 1;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
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
