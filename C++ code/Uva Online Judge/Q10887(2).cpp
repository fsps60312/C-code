#include<cstdio>
#include<vector>
#include<string>
#include<set>
using namespace std;
int T,M,N,F[11];
char LINE[10000];
vector<string>FIRST,SECOND;
void buildF(string s,int *f)
{
	f[0]=f[1]=0;
	for(int i=1;i<s.size();i++)
	{
		int u=f[i];
		while(u&&s[u]==s[i])u=f[u];
		f[i+1]=s[u]==s[i]?++u:0;
	}
}
void push(set<string>&s,string &s1,string &s2)
{
	buildF(s2,F);
	int i1,i2;
	for(i1=0,i2=0;i1<s1.size();i1++)
	{
		while(i2&&(i2>=s2.size()||s1[i1]!=s2[i2]))i2=F[i2];
		if(s1[i1]==s2[i2])i2++;
	}
	string ans=s1;
	ans+=&s2[i2];
	s.insert(ans);
}
int main()
{
	gets(LINE);sscanf(LINE,"%d",&T);
	while(T--)
	{
		gets(LINE);sscanf(LINE,"%d%d",&M,&N);
		FIRST.clear(),SECOND.clear();
		for(int i=0;i<M;i++){gets(LINE);FIRST.push_back(LINE);}
		for(int i=0;i<N;i++){gets(LINE);SECOND.push_back(LINE);}
		set<string>ans;
		for(int i=0;i<M;i++)
		{
			for(int j=0;j<N;j++)
			{
				push(ans,FIRST[i],SECOND[j]);
			}
		}
		int idx=0;
//		for(set<string>::iterator it=ans.begin();it!=ans.end();it++,idx++)printf("%d:%s\n",idx,(*it).c_str());
		printf("%d\n",ans.size());
	}
	return 0;
}
