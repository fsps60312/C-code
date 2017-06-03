#include<cstdio>
#include<string>
#include<map>
#include<vector>
#include<queue>
using namespace std;
int N,L;
/*Structure*/
struct Geto{int s1,s2;Geto(int _s1,int _s2){s1=_s1,s2=_s2;}};
struct From{int o,ch;From(int _o,int _ch){o=_o,ch=_ch;}};
struct Dp
{
	int i;
	string s;
	Dp(int _i,string _s):i(_i),s(_s){}
	bool operator<(Dp a)const{return s>a.s;}
};
/*Transform*/
map<string,int> ID_BASE;string STR[500+52];int IDN;
vector<Geto> GETO[500+52];
vector<From> FROM[500+52];
/*Dynamic Program*/
string DP[500+52][21];
/*Trash*/
int VIS[500+52];
/*Function*/
void cin_str(string &s);
int ID(string s);
void add_rule(string _o,string _s1,string _s2)
{
//	printf("%s -> \"%s\" + \"%s\"\n",_o.c_str(),_s1.c_str(),_s2.c_str());
	int o=ID(_o),s1=ID(_s1),s2=ID(_s2);
	GETO[o].push_back(Geto(s1,s2));
	FROM[s1].push_back(From(o,s2));
	FROM[s2].push_back(From(o,s1));
}
void build_rule()
{
	for(int i=0;i<N;i++)
	{
		string str;cin_str(str);
		add_rule(str.substr(0,1),str.substr(2),"");
		for(int j=2;j<str.length();j++)
			add_rule(str.substr(j),str.substr(j,1),str.substr(j+1));
	}
}
bool islower(char a){return a>='a'&&a<='z';}
bool all_lower(string a){for(int i=0;i<a.length();i++)if(!islower(a[i]))return false;return true;}
bool better(string a,string b)
{
	if(!all_lower(a))return false;
	if(b=="-")return true;
	return a<b;
}
void getmin(string &a,string b){if(a=="-"||b<a)a=b;}
/*Main*/
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout); 
	while(scanf("%d%d",&N,&L)==2&&(N||L))
	{
		ID_BASE.clear();
		ID("");
		build_rule();
		IDN=ID_BASE.size();
		DP[0][0]="";
		for(int l=0;l<=L;l++)
		{
			for(int i=0;i<IDN;i++)
			{
				if(STR[i].length()==l&&all_lower(STR[i]))DP[i][l]=STR[i];
				if(STR[i].length()<2)continue;
				for(int j=0;j<GETO[i].size();j++)
				{
					Geto &g=GETO[i][j];
					for(int k=1;k<l;k++)
					{
						string &s1=DP[g.s1][k],&s2=DP[g.s2][l-k];
						if(s1=="-"||s2=="-")continue;
						getmin(DP[i][l],s1+s2);
					}
				}
			}
			priority_queue<Dp> pq;
			for(int i=0;i<IDN;i++)
			{
				if(DP[i][l]!="-")pq.push(Dp(i,DP[i][l]));
				VIS[i]=0;
			}
//			printf("length %d:\n",l);
			while(!pq.empty())
			{
				Dp d=pq.top();pq.pop();
				if(VIS[d.i]++)continue;
//				printf("\t\tpq:%s\n",d.s.c_str());
				for(int i=0;i<FROM[d.i].size();i++)
				{
					From &f=FROM[d.i][i];
					if(DP[f.ch][0]=="-")continue;
					if(DP[f.o][l]!="-"&&d.s>DP[f.o][l])continue;
//					printf("\tupdate %s to %s\n",STR[f.o].c_str(),d.s.c_str());
					DP[f.o][l]=d.s;
					pq.push(Dp(f.o,d.s));
				}
			}
//			for(int i=0;i<IDN;i++)
//			{
//				printf("\t%s to %s\n",STR[i].c_str(),DP[i][l].c_str());
//			}
		}
		printf("%s\n",DP[ID("S")][L].c_str());
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int ID(string s)
{
	if(ID_BASE.find(s)==ID_BASE.end())
	{
		int sz=ID_BASE.size();
		GETO[sz].clear(),FROM[sz].clear();
		ID_BASE[s]=sz;
		STR[sz]=s;
		for(int i=0;i<=L;i++)
			DP[sz][i]="-";
	}
	return ID_BASE[s];
}
void cin_str(string &s)
{
	char t_str[13];
	scanf("%s",t_str);
	s=t_str;
}
