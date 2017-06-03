#include<cstdio>
#include<string>
#include<map>
#include<vector>
using namespace std;
const string UNDEFINE="zzzzzzzzzzzzzzzzzzzzz";
int N,L;
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
bool getmin(string &a,string b){if(b.compare(a)<0){a=b;return true;}return false;}
string get_DP(int idx,int l)
{
	string &ans=DP[idx][l];
	if(ans.compare(UNDEFINE)!=0)return ans;
//	printf("%d %d\n",idx,l);
	for(int j=0;j<RULE[idx].size();j++)
	{
		for(int i=0;i<=l;i++)
		{
			Trans &t=RULE[idx][j];
			if(t.i==-1)continue;
//			printf("\t%d %d\t%s\t%s\n",t.c,t.i,DP[t.c][i].c_str(),DP[t.i][l-i].c_str());
			string &dp1=DP[t.c][i],&dp2=DP[t.i][l-i];
			if(dp1.compare(UNDEFINE)==0||dp2.compare(UNDEFINE)==0)continue;
			if(getmin(ans,dp1+dp2))printf("\t%s (%d,%d) -> (%s %d)%s + (%s %d):%s\n",NAME[idx].c_str(),i,l-i,NAME[t.c].c_str(),t.c,dp1.c_str(),NAME[t.i].c_str(),t.i,dp2.c_str());
		}
	}
//	printf("%s -> %s\n",NAME[idx].c_str(),ans.c_str());
	return ans;
}
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
				if(DP[i][l].compare(UNDEFINE)==0)continue; 
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
			for(int i=0;i<DN;i++)
			{
				if(DP[i][0].compare(UNDEFINE)!=0)continue;//i can trans to ""
				for(int j=0;j<DN;j++)
				{
					for(int k=0;k<RULE[j].size();k++)//j can trans to ~i
					{
						Trans &t=RULE[j][k];
						if(t.c==i&&t.i!=-1)if(getmin(DP[j][l],DP[t.i][l]))printf("\ti=%d %s = %s + %s\n",i,NAME[j].c_str(),NAME[t.c].c_str(),NAME[t.i].c_str());
						if(t.i==i&&t.c!=-1)if(getmin(DP[j][l],DP[t.c][l]))printf("\ti=%d %s = %s + %s\n",i,NAME[j].c_str(),NAME[t.c].c_str(),NAME[t.i].c_str());
					}
				}
			}
		}
		printf("\tafter\n");
		for(int i=0;i<DN;i++)
		{
			for(int l=0;l<=L;l++)
			{
				if(DP[i][l].compare(UNDEFINE)==0)continue; 
				printf("%d %s %d : %s\n",i,NAME[i].c_str(),l,DP[i][l].c_str());
			}
		}
//		printf("pass2\n");
		string ans=DP[get_IDX('S')][L];
		if(ans.compare(UNDEFINE)==0)printf("-\n");
		else printf("%s\n",ans.c_str());
//		return 0;
	}
	return 0;
}
