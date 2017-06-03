#include<cstdio>
#include<cassert>
#include<vector>
#include<string>
#include<map>
#include<queue>
using namespace std;
const int INF=2147483647;
vector<vector<int> >ET;
vector<string>STR;
map<string,int>ID;
vector<int>PRE,VIS;
int N;
bool Solve(const string s2,const string s1,vector<string>&ans)
{
	static int kase=0;kase++;
	if(ID.find(s1)==ID.end()||ID.find(s2)==ID.end())return false;
	const int goal=ID[s2];
	queue<int>q;
	q.push(ID[s1]),q.push(-1);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		const int pre=q.front();q.pop();
		if(VIS[u]==kase)continue;
		VIS[u]=kase;
		PRE[u]=pre;
		if(u==goal)
		{
			const int start=ID[s1];
			for(int cur=u;;cur=PRE[cur])
			{
				ans.push_back(STR[cur]);
				if(cur==start)return true;
			}
		}
		for(const int nxt:ET[u])q.push(nxt),q.push(u);
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static char str[18];
	for(;;)
	{
		assert(fgets(str,INF,stdin));
		int n=-1;
		bool tag=false;
		while(str[++n])
		{
			if(str[n]>='a'&&str[n]<='z')tag=true;
			if(str[n]=='\n'){str[n]='\0';break;}
		}
		if(!tag)break;
		ID[str]=-1;
	}
	N=0;
	for(auto &it:ID)it.second=N++,STR.push_back(it.first);
	ET.resize(N);
	vector<int>sot[17];
	for(int i=0;i<N;i++)sot[STR[i].size()].push_back(i);
	for(int len=1;len<=16;len++)
	{
		const vector<int>&s=sot[len];
		const int n=s.size();
		for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)
		{
			int cnt=0;
			for(int k=0;k<len;k++)if(STR[s[i]][k]!=STR[s[j]][k]&&cnt++)break;
			if(cnt==1)ET[s[i]].push_back(s[j]),ET[s[j]].push_back(s[i]);
		}
	}
	PRE.resize(N),VIS.resize(N,0);
	static char s1[1000],s2[1000];
	while(scanf("%s%s",s1,s2)==2)
	{
		static int kase=0;
		if(kase++)puts("");
		vector<string>ans;
		Solve(s1,s2,ans);
		if(ans.empty())puts("No solution.");
		else for(const string &s:ans)puts(s.c_str());
	}
	return 0;
}
