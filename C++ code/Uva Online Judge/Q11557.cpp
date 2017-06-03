#include<cstdio>
#include<string>
#include<vector>
#include<map>
#include<cassert>
using namespace std;
const int INF=2147483647;
bool Match(char *a,const char *b)
{
	bool ans=true;
	int i;
	for(i=0;a[i];i++)
	{
		if(a[i]=='\n'){a[i]='\0';break;}
		ans&=(a[i]==b[i]);
	}
	return ans&=(a[i]==b[i]);
}
map<vector<char>,int>IDX;
int GetIdx(vector<char>&s)
{
	auto it=IDX.find(s);
	if(it!=IDX.end())return it->second;
	const int sz=IDX.size();
	return IDX[s]=sz;
}
bool GetIdx(char *a,int &ans)
{
	vector<char>s;
	while((*a)==' ')a++;
	if(!(*a))return false;
	s.push_back(a[0]);
	for(int i=1;a[i];i++)if(a[i-1]!=' '||a[i]!=' ')s.push_back(a[i]);
	for(int i=(int)s.size()-1;s[i]==' ';i--)s.pop_back();
	ans=GetIdx(s);
	return true;
}
vector<int>GetCode()
{
	static char tmp[256]; 
	vector<int>ans;
	for(;;)
	{
		assert(fgets(tmp,INF,stdin));
		if(Match(tmp,"***END***"))return ans;
		static int idx;
		if(GetIdx(tmp,idx))ans.push_back(idx);
	}
}
void BuildFail(const vector<int>&s,vector<int>&fail)
{
	fail.clear();
	fail.push_back(0),fail.push_back(0);
	for(int i=1;i<(int)s.size();i++)
	{
		int f=fail[i];
		while(f&&s[f]!=s[i])f=fail[f];
		fail.push_back(s[f]==s[i]?++f:0);
	}
}
void getmax(int &a,const int b){if(b>a)a=b;}
int MxFit(const vector<int>&a,const vector<vector<int> >&b,const vector<vector<int> >&fail)
{
	int ans=0;
	for(int len=b.size()-1;len>=0&&len+1>ans;len--)
	{
		for(int i=0,u=0;i<(int)a.size();i++)
		{
			while(u&&b[len][u]!=a[i])u=fail[len][u];
			if(b[len][u]==a[i])getmax(ans,++u);
			if(u==(int)b[len].size())return ans;
		}
	}
	return ans;
}
int N;
vector<string>NAME;
vector<vector<int> >CODE;
int main()
{
//	freopen("in.txt","r",stdin);
	static char tmp[256];
	while(fgets(tmp,INF,stdin))
	{
		assert(sscanf(tmp,"%d",&N)==1);
		NAME.clear(),CODE.clear();
		for(int i=0;i<N;i++)
		{
			assert(fgets(tmp,INF,stdin));
			Match(tmp,"");
			NAME.push_back(tmp);
			CODE.push_back(GetCode());
//			printf("code %d:",i);for(int j=0;j<(int)CODE[i].size();j++)printf(" %d",CODE[i][j]);puts("");
		}
		vector<int>s=GetCode();
//		printf("s: ");for(int j=0;j<(int)s.size();j++)printf(" %d",s[j]);puts("");
		if(s.empty())puts("0");
		else
		{
			vector<vector<int> >str,fail;
			for(int i=s.size()-1;i>=0;i--)
			{
				vector<int>v,f;
				for(int j=i;j<(int)s.size();j++)v.push_back(s[j]);
				BuildFail(v,f);
				str.push_back(v);
				fail.push_back(f);
			}
			vector<int>ans;
			int mx=0;
			for(int i=0,v;i<N;i++)getmax(mx,v=MxFit(CODE[i],str,fail)),ans.push_back(v);
//			for(int i=0;i<N;i++)printf(" %d",ans[i]);puts("");
			printf("%d",mx);
			if(mx)for(int i=0;i<N;i++)if(ans[i]==mx)printf(" %s",NAME[i].c_str());
			puts("");
		}
	}
	return 0;
}
