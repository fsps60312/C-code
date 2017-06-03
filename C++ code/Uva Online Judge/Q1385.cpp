#include<cstdio>
#include<string>
#include<vector>
#include<map>
#define debug(x,...) {}//printf(x,##__VA_ARGS__)
#define debu2(x,...) printf(x,##__VA_ARGS__)
using namespace std;
char PF1[12],PF2[12],TMP[2],NAME[21];
struct Trie
{
	struct Node
	{
		int bse[10];
		string v;
		int &operator[](int i){return bse[i];}
		Node():v(""){for(int i=0;i<10;i++)bse[i]=0;}
	};
	vector<Node>bse;
	int sz;
	void clear(){bse.clear(),bse.push_back(Node());sz=0;}
	int getnxt(int u,int c){debug("u=%d,c=%d\n",u,c);int &v=bse[u][c];if(v)return v;bse.push_back(Node());return bse[u][c]=++sz;}
	bool allisafter(char *s,int idx,char c)
	{
		for(int i=idx;s[i];i++)if(s[i]!=c)return false;
		return true;
	}
	void insert(char *s1,char *s2,int idx,int u,int _state,string &v,vector<char>now)
	{
		idx++;
now.push_back(0);debu2("%s~%s (%d)%s:%s(has %s)\n",s1,s2,u,v.c_str(),now.begin(),bse[u].v.c_str());now.pop_back();
		if(bse[u].v.size()){debu2("return because \"%s\"\n",bse[u].v.c_str());return;}
		if(!s1[idx]){bse[u].v=v;return;}
		if((_state&1)&&allisafter(s1,idx,'0'))if(!(_state&2)||allisafter(s2,idx,'9'))
			{bse[u].v=v;return;}
		if((_state&2)&&allisafter(s2,idx,'9'))if(!(_state&1)||allisafter(s1,idx,'0'))
			{bse[u].v=v;return;}
		int l=(_state&1)?s1[idx]-'0':0;
		int r=(_state&2)?s2[idx]-'0':9;
		for(int i=l;i<=r;i++)
		{
			int state=_state;
			if(i>l)state&=~1;
			if(i<r)state&=~2;
now.push_back('0'+i);
			insert(s1,s2,idx,getnxt(u,i),state,v,now);
now.pop_back();
		}
	}
	void insert(char *s1,char *s2,string v)
	{
		int l=s1[0]-'0',r=s2[0]-'0';
vector<char>now;
		for(int i=l;i<=r;i++)
		{
			int state=3;
			if(i>l)state&=~1;
			if(i<r)state&=~2;
now.push_back('0'+i);
			insert(s1,s2,0,getnxt(0,i),state,v,now);
now.pop_back();
		}
	}
	void exprt(int u,vector<int>&now,map<string,string>&m)
	{
for(int i=0;i<now.size();i++)PF1[i]='0'+now[i];
PF1[now.size()]=0;
debu2("%d:%s\n",u,PF1);
		if(bse[u].v.size())
		{
			debu2("find %s\n",bse[u].v.c_str());
			if(bse[u].v!="invalid")
			{
				for(int i=0;i<now.size();i++)PF1[i]='0'+now[i];
				PF1[now.size()]=0;
				m[PF1]=bse[u].v;
			}
			return;
		}
		for(int i=0;i<=9;i++)
		{
			int &v=bse[u][i];
			if(!v)continue;
			now.push_back(i);
			exprt(v,now,m);
			now.pop_back();
		}
	}
}TEL;
int N;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		TEL.clear();
		for(int i=0;i<N;i++)
		{
			scanf("%s%s%s%s",PF1,TMP,PF2,NAME);
			int n1=-1,n2=-1;while(PF1[++n1]);while(PF2[++n2]);
			PF2[n1]=0;
			for(int i=n2-1;i>=0;i--)PF2[i+n1-n2]=PF2[i];
			for(int i=n1-n2-1;i>=0;i--)PF2[i]=PF1[i];
debug("PF1:%s\n",PF1);
debug("PF2:%s\n",PF2);
			TEL.insert(PF1,PF2,NAME);
		}
		map<string,string>ans;
		vector<int>now;
		TEL.exprt(0,now,ans);
		printf("%d\n",ans.size());
		for(map<string,string>::iterator it=ans.begin();it!=ans.end();it++)
		{
			printf("%s %s\n",it->first.c_str(),it->second.c_str());
		}
	}
	return 0;
}
