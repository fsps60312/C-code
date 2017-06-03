#include<cstdio>
#include<string>
//#include<cassert>
#include<vector>
#include<map>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int H[25000];
struct Trie
{
	vector<map<char,int> >ch;
	vector<int>value;
	int sz;
	void clear(){ch.resize(1);value.resize(sz=1,-1);}
	int GetNxt(const int u,const char c)
	{
		const auto it=ch[u].find(c);
		if(it!=ch[u].end())return it->second;
		ch.push_back(map<char,int>());
		value.push_back(-1);
		return ch[u][c]=sz++;
	}
	void insert(const char *s,const int _v)
	{
		int u=0;
		for(int i=0;s[i]&&s[i]!='\n';i++)u=GetNxt(u,s[i]);
		value[u]=_v;
	}
	bool find(const char *s)
	{
		int u=0;
		for(int i=0;s[i]&&s[i]!='\n';i++)
		{
			auto it=ch[u].find(s[i]);
			if(it==ch[u].end())return false;
			u=it->second;
		}
		return value[u]!=-1;
	}
	void Match(const char *s,const int u,const int i,const bool edited,const int _v)
	{
		if(!s[i])
		{
			if(edited){if(value[u]!=-1&&value[u]>_v)getmax(H[value[u]],H[_v]+1);return;}
			for(const auto &it:ch[u])Match(s,it.second,i,true,_v);
			return;
		}
		if(ch[u].find(s[i])!=ch[u].end())Match(s,ch[u][s[i]],i+1,edited,_v);
		if(!edited)
		{
			Match(s,u,i+1,true,_v);//delete a char
			for(const auto &it:ch[u])
			{
				if(it.first!=s[i])Match(s,it.second,i+1,true,_v);//change a char
				Match(s,it.second,i,true,_v);//add a char
			}
		}
	}
	void Match(const char *s,const int _v){Match(s,0,0,false,_v);}
}TRIE;
int N;
char WORD[25000][18];
int main()
{
//	freopen("in.txt","r",stdin);
	TRIE.clear();
	for(N=0;fgets(WORD[N],INF,stdin);N++)
	{
		char *tmp=WORD[N];
		int n=-1;while(tmp[++n])if(tmp[n]=='\n'){tmp[n]='\0';break;}
		if(TRIE.find(tmp)){N--;continue;}
		assert(N<25000);
		TRIE.insert(tmp,N);
		H[N]=1;
	}
//	printf("N=%d\n",N);
	int ans=0;
	for(int i=0;i<N;i++)TRIE.Match(WORD[i],i),getmax(ans,H[i]);
	printf("%d\n",ans);
	return 0;
}
