#include<cstdio>
#include<string>
#include<map>
#include<vector>
using namespace std;
int S,T,NR;
map<string,int>IDX;
vector<string>RI,RA,RB;
vector<vector<int> >AD;
vector<bool>VIS;
int GetIdx(string s)
{
	if(IDX.find(s)==IDX.end())
	{
		static int sz;sz=IDX.size();
		RI.push_back(s);
		AD.push_back(vector<int>());
		VIS.push_back(false);
		return IDX[s]=sz;
	}
	return IDX[s];
}
int GetIdx()
{
	static char tmp[21];
	scanf("%s",tmp);
	return GetIdx(tmp);
}
void BuildAD(int u)
{
	string s=RI[u];
	for(int i=0;i<NR;i++)
	{
//	puts("a");
		string &a=RA[i],&b=RB[i];
//	printf("b %d %d\n",i,RA.size());
//	printf("%d",a.size()),printf(" %d\n",s.size());
		if(a.size()>s.size())continue;
		bool found=true;
		for(int j=0;j<a.size();j++)if(s[s.size()-a.size()+j]!=a[j]){found=false;break;}
		if(!found)continue;
//		printf("%s match %s\n",a.c_str(),s.c_str());
		static char tmp[21];
		for(int j=0;j<s.size()-b.size();j++)tmp[j]=s[j];
		for(int j=s.size()-b.size();j<s.size();j++)tmp[j]=b[j-s.size()+b.size()];
		tmp[s.size()]=0;
		AD[u].push_back(GetIdx(tmp));
//		puts("pass");
	}
}
#include<queue>
queue<int>QU,QV;
void Push(int u,int v){QU.push(u),QV.push(v);}
void Pop(int &u,int &v){u=QU.front();QU.pop();v=QV.front();QV.pop();}
int Solve()
{
	QU=QV=queue<int>();
	Push(S,0);
	while(!QU.empty())
	{
		static int u,v;
		Pop(u,v);
		if(VIS[u])continue;
		VIS[u]=true;
//		printf("u=%d,v=%d,s=%s\n",u,v,RI[u].c_str());
		if(u==T)return v;
		BuildAD(u);
		for(int i=0;i<AD[u].size();i++)
		{
			int &j=AD[u][i];
			Push(j,v+1);
		}
	}
	return -1;
}
int main()
{
	freopen("in.txt","r",stdin);
	static char tstr[21];
	while(scanf("%s",tstr)==1&&!(tstr[0]=='.'&&!tstr[1]))
	{
		IDX.clear(),RI.clear(),AD.clear(),VIS.clear(),RA.clear(),RB.clear();
		S=GetIdx(tstr),T=GetIdx();
		scanf("%d",&NR);
		for(int i=0;i<NR;i++)
		{
			static char a[21],b[21];
			scanf("%s%s",a,b);
			RA.push_back(a),RB.push_back(b);
		}
		static int kase=1;
		printf("Case %d: ",kase++);
		int ans=Solve();
		if(ans==-1)puts("No solution");
		else printf("%d\n",ans);
	}
	return 0;
}
