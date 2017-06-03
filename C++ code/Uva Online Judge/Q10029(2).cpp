#include<cstdio>
#include<string>
//#include<cassert>
#include<vector>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int H[25000];
struct Trie
{
	vector<int>ch[26],value;
	int sz;
	void clear(){for(int i=0;i<26;i++)ch[i].resize(1,0);value.resize(sz=1,-1);}
	int GetNxt(const int c,const int u)
	{
		if(ch[c][u])return ch[c][u];
		for(int i=0;i<26;i++)ch[i].push_back(0);
		value.push_back(-1);
		return ch[c][u]=sz++;
	}
	void insert(const char *s,const int _v)
	{
		int u=0;
		for(int i=0;s[i]&&s[i]!='\n';i++)
		{
			assert(s[i]>='a'&&s[i]<='z');
			u=GetNxt(s[i]-'a',u);
		}
		value[u]=_v;
	}
	bool find(const char *s)
	{
		int u=0;
		for(int i=0;s[i]&&s[i]!='\n';i++)
		{
			assert(s[i]>='a'&&s[i]<='z');
			if(!(u=ch[s[i]-'a'][u]))return false;
		}
		return value[u]!=-1;
	}
	void Match(const char *s,const int u,const int i,const bool edited,const int _v)
	{
		if(!s[i])
		{
			if(edited){if(value[u]!=-1&&value[u]>_v)getmax(H[value[u]],H[_v]+1);return;}
			for(int c=0;c<26;c++)if(ch[c][u])Match(s,ch[c][u],i,true,_v);
			return;
		}
		assert(s[i]>='a'&&s[i]<='z');
		const int nowc=s[i]-'a';
		if(ch[nowc][u])Match(s,ch[nowc][u],i+1,edited,_v);
		if(!edited)
		{
			Match(s,u,i+1,true,_v);//delete a char
			for(int c=0;c<26;c++)if(ch[c][u])
			{
				if(c!=nowc)Match(s,ch[c][u],i+1,true,_v);//change a char
				Match(s,ch[c][u],i,true,_v);//add a char
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
