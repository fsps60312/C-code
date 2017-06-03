#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
vector<vector<char> >TREE;
struct Node
{
	Node *ch[2];
	char c;
	Node(const char _c):ch{NULL,NULL},c(_c){}
};
void Dfs(Node* &o,vector<vector<char> >s)
{
	int dep=s.size();
	while(!s.empty()&&s[dep-1].empty())s.pop_back(),dep--;
	if(s.empty())return;
	assert(s[dep-1].size()==1);
	const char uchar=s[dep-1][0];
	o=new Node(uchar);
	vector<vector<char> >nxt;
	nxt.clear();
	for(int i=0;i<dep-1;i++)
	{
		vector<char>tmp;
		for(int j=0;j<(int)s[i].size()&&s[i][j]<uchar;j++)tmp.push_back(s[i][j]);
		nxt.push_back(tmp);
	}
	Dfs(o->ch[0],nxt);
	nxt.clear();
	for(int i=0;i<dep-1;i++)
	{
		vector<char>tmp;
		int j;
		for(j=0;j<(int)s[i].size()&&s[i][j]<uchar;j++);
		while(j<(int)s[i].size())tmp.push_back(s[i][j++]);
		nxt.push_back(tmp);
	}
	Dfs(o->ch[1],nxt);
}
int CNT;
void Print(Node* &o)
{
	if(!o)return;
	putchar(o->c),CNT++;
	Print(o->ch[0]),Print(o->ch[1]);
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		TREE.clear();
		char lastchar;
		int n=0;
		for(;;)
		{
			static char tmp[1000000];
			assert(scanf("%s",tmp)==1);
			if(tmp[0]=='*'||tmp[0]=='$'){lastchar=tmp[0];break;}
			vector<char>s;
			for(int i=0;tmp[i];i++)s.push_back(tmp[i]),assert(tmp[i]>='A'&&tmp[i]<='Z'),n++;
			sort(s.begin(),s.end());
			TREE.push_back(s);
		}
		Node *root=NULL;
		Dfs(root,TREE);
		CNT=0;
		Print(root);
		assert(CNT==n);
		puts("");
		if(lastchar=='$')break;
	}
	return 0;
}
