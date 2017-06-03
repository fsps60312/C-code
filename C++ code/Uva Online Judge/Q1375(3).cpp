#include<cstdio>
#include<map>
#include<vector>
#include<queue>
using namespace std;
int N,L;
struct string
{
	char v[21];
	int sz;
	string()
	{
		sz=0;
		v[0]=0;
	}
	string(char *a)
	{
		for(sz=0;a[sz];sz++)v[sz]=a[sz];
		v[sz]=0;
	}
	const char* c_str(){return v;}
	bool isupper(char &a)const{return a>='A'&&a<='Z';}
	bool islower(char &a)const{return a>='a'&&a<='z';}
	bool cmp_char(char a,char b)const
	{
		if(isupper(a)&&isupper(b))return a<b;
		if(islower(a)&&islower(b))return a<b;
		if(isupper(a)&&islower(b))return false;
		if(islower(a)&&isupper(b))return true;
		printf("error %c %c\n",a,b);
	}
	bool operator<(const string &a)const
	{
		for(int i=0;i<sz&&i<a.sz;i++)
		{
			if(v[i]!=a.v[i])return cmp_char(v[i],a.v[i]);
		}
		return sz<a.sz;
	}
	bool operator>(const string &a)const
	{
		for(int i=0;i<sz&&i<a.sz;i++)
		{
			if(v[i]!=a.v[i])return !cmp_char(v[i],a.v[i]);
		}
		return sz>a.sz;
	}
	bool operator==(string a)const
	{
		if(sz!=a.sz)return false;
		for(int i=0;i<sz;i++)if(v[i]!=a.v[i])return false;
		return true;
	}
	bool operator!=(string a)const{return !((*this)==a);}
	string operator+(string a)
	{
		string ans;
		for(int i=0;i<sz;i++)ans.v[i]=v[i];
		for(int i=0;i<a.sz;i++)ans.v[sz+i]=a.v[i];
		ans.sz=sz+a.sz;
		ans.v[ans.sz]=0;
		return ans;
	}
	void assign(char *a,int len)
	{
		for(int i=0;i<len;i++)v[i]=a[i];
		v[len]=0;
		sz=len;
	}
};
const string UNDEFINE="ZZZZZZZZZZZZZZZZZZZZZ";
struct Trans
{
	int c;
	int i;
};
vector<Trans> RULE[500];
char STR[13];
string DP[500][21];
int DN;
map<string,int> IDX;
map<int,string> NAME;
int get_IDX(char *a,int len)
{
	if(len==0)return -1;
	char b[len+1];
	for(int i=0;i<len;i++)b[i]=a[i];
	b[len]=0;
	if(IDX.find(b)!=IDX.end())return IDX[b];
	for(int i=0;i<=L;i++)DP[DN][i]=UNDEFINE;
	RULE[DN].clear();
	IDX[b]=DN;
	NAME[DN]=b;
	return DN++;
}
int get_IDX(char a)
{
	char b[2]={a,0};
	return get_IDX(b,1);
}
bool getmin(string &a,string b){if(b<a){a=b;return true;}return false;}
string get_DP(int idx,int l)
{
	string &ans=DP[idx][l];
	if(ans!=UNDEFINE)return ans;
//	printf("%d %d\n",idx,l);
	for(int j=0;j<RULE[idx].size();j++)
	{
		for(int i=0;i<=l;i++)
		{
			Trans &t=RULE[idx][j];
			if(t.i==-1)continue;
//			printf("\t%d %d\t%s\t%s\n",t.c,t.i,DP[t.c][i].c_str(),DP[t.i][l-i].c_str());
			string &dp1=DP[t.c][i],&dp2=DP[t.i][l-i];
			if(dp1==UNDEFINE||dp2==UNDEFINE)continue;
			if(getmin(ans,dp1+dp2))printf("\t%s (%d,%d) -> (%s %d)%s + (%s %d):%s\n",NAME[idx].c_str(),i,l-i,NAME[t.c].c_str(),t.c,dp1.c_str(),NAME[t.i].c_str(),t.i,dp2.c_str());
		}
	}
//	printf("%s -> %s\n",NAME[idx].c_str(),ans.c_str());
	return ans;
}
struct Pq
{
	int i,j;
	string s;
	bool operator<(Pq a)const{return a.s<s;}
};
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout); 
	while(scanf("%d%d",&N,&L)==2&&(N||L))
	{
		DN=0;
		IDX.clear();
		NAME.clear();
		for(int i=0;i<26;i++)get_IDX('a'+i);
		for(int i=0;i<26;i++)get_IDX('A'+i);
		for(int i=0;i<N;i++)
		{
			scanf("%s",STR);
			int from,to;
			int n=-1;while(STR[++n]);
			if(n>=3)RULE[get_IDX(STR[0])].push_back((Trans){get_IDX(STR[2]),get_IDX(STR+3,n-3)});
			string s;s.assign(STR+2,n-2);
			getmin(DP[get_IDX(STR[0])][n-2],s);
			for(int i=3;i<n;i++)
			{
				int idx=get_IDX(STR+i,n-i);
				RULE[idx].push_back((Trans){get_IDX(STR[i]),get_IDX(STR+i+1,n-i-1)});
				string s;s.assign(STR+i,n-i);
				getmin(DP[idx][n-i],s);
			}
		}
		printf("\tbefore\n");
		for(int i=0;i<DN;i++)
		{
			for(int l=0;l<=L;l++)
			{
				if(DP[i][l]==UNDEFINE)continue; 
				printf("%d %s %d : %s\n",i,NAME[i].c_str(),l,DP[i][l].c_str());
			}
		}
//		printf("pass1\n");
		for(int l=0;l<=L;l++)
		{
			for(int i=0;i<DN;i++)
			{
				get_DP(i,l);
			}
			priority_queue<Pq> pq;
			for(int i=0;i<DN;i++)pq.push((Pq){i,l,DP[i][l]});
			while(!pq.empty())
			{
				Pq p=pq.top();pq.pop();
				for(int i=0;i<DN;i++)
				{
					if(DP[i][0]==UNDEFINE)continue;//i can trans to ""
					for(int j=0;j<DN;j++)
					{
						for(int k=0;k<RULE[j].size();k++)//j can trans to ~i
						{
							Trans &t=RULE[j][k];//check if j->t.c+t.i
							if(t.c==i&&t.i!=-1)
							{
								DP[j][l]=DP[t.i][l];
								pq.push((Pq){j,l,DP[j][l]});
							}
//							if(getmin(DP[j][l],DP[t.i][l]))printf("\ti=%d %s = %s + %s\n",i,NAME[j].c_str(),NAME[t.c].c_str(),NAME[t.i].c_str());
							if(t.i==i&&t.c!=-1)
							{
								DP[j][l]=DP[t.c][l];
								pq.push((Pq){j,l,DP[j][l]});
							}
//							if(getmin(DP[j][l],DP[t.c][l]))printf("\ti=%d %s = %s + %s\n",i,NAME[j].c_str(),NAME[t.c].c_str(),NAME[t.i].c_str());
						}
					}
				}
				getmin(DP[p.i][p.j],p.s);
			}
		}
		printf("\tafter\n");
		for(int i=0;i<DN;i++)
		{
			for(int l=0;l<=L;l++)
			{
				if(DP[i][l]==UNDEFINE)continue; 
				printf("%d %s %d : %s\n",i,NAME[i].c_str(),l,DP[i][l].c_str());
			}
		}
//		printf("pass2\n");
		string ans=DP[get_IDX('S')][L];
		if(ans==UNDEFINE)printf("-\n");
		else printf("%s\n",ans.c_str());
//		return 0;
	}
	return 0;
}
