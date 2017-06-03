#include<cstdio>
#include<string>
#include<map>
#include<vector>
#include<queue>
using namespace std;
char INPUT[2001],S1[2001],S2[2001];
int N,SZ;
bool VIS[1000000];
vector<string>WORD;
map<string,int>IDX;
vector<string>REI;
int GetIDX(string a)
{
	if(IDX.find(a)==IDX.end())
	{
		VIS[SZ]=false;
		REI.push_back(a);
		return IDX[a]=SZ++;
	}
	return IDX[a];
}
void BuildNode(string a,vector<int>&v)
{
	v.clear();
	for(int i=0;i<N;i++)
	{
		for(int j=0;;j++)
		{
			static int to;
			if(j==WORD[i].size()||j==a.size())
			{
				to=GetIDX(j==WORD[i].size()?a.substr(j):WORD[i].substr(j));
				v.push_back(to);
				break;
			}
			if(WORD[i][j]!=a[j])break;
		}
	}
//	printf("v.size()==%d\n",v.size());
}
bool cmp(string a,string b)
{
	if(a.size()!=b.size())return a.size()<b.size();
	return a<b;
}
struct Way
{
	int len;
	int idx;
	string s;
	Way(){}
	Way(int len,int idx,string s):len(len),idx(idx),s(s){}
	bool operator<(const Way &a)const{return len>a.len;}
};
int solve()
{
	static int n1,n2;
	for(int i=0;S1[i]&&S2[i];i++)if(S1[i]!=S2[i])return -1;
	n1=n2=-1;while(S1[++n1]);while(S2[++n2]);
	if(n1==n2)return n1;
	string source=n1>n2?S1+n2:S2+n1;
	gets(INPUT);sscanf(INPUT,"%d",&N);
	WORD.clear();
	IDX.clear();
	REI.clear();
	SZ=0;
	for(int i=0;i<N;i++)
	{
		gets(INPUT);
		WORD.push_back(INPUT);
	}
	priority_queue<Way>pq;
	pq.push(Way(0,GetIDX(source),n1>n2?S1:S2));
	while(!pq.empty())
	{
		Way w=pq.top();pq.pop();
		string &s=REI[w.idx];
		if(VIS[w.idx])continue;
		VIS[w.idx]=true;
		printf("%d %d %s\n",w.len,w.idx,w.s.c_str());
		if(!s.size())return w.len;
		static vector<int>v;
		BuildNode(s,v);
		for(int i=0;i<v.size();i++)
		{
			pq.push(Way(w.len+1,v[i],w.s+REI[v[i]]));
		}
	}
	return -1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int T;
	gets(INPUT);sscanf(INPUT,"%d",&T);
	while(T--)
	{
		gets(S1),gets(S2);
		printf("%d\n",solve());
	}
	return 0;
}
