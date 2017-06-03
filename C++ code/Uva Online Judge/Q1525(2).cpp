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
void Dfs(Node* &o,const int u,const int dep,const char bl,const char br)
{
	const char uchar=TREE[dep][u];
	printf("(%c,%c,%c)\n",bl,uchar,br);
	o=new Node(uchar);
	if(dep==0)return;
	for(int l=0;l<(int)TREE[dep-1].size()&&TREE[dep-1][l]<uchar;l++)if(TREE[dep-1][l]>=bl)
	{
		Dfs(o->ch[0],l,dep-1,bl,uchar-1);
		break;
	}
	for(int r=(int)TREE[dep-1].size()-1;r>=0&&TREE[dep-1][r]>uchar;r--)if(TREE[dep-1][r]<=br)
	{
		Dfs(o->ch[1],r,dep-1,uchar+1,br);
		break;
	}
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
	freopen("in.txt","r",stdin);
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
		assert(TREE[(int)TREE.size()-1].size()==1);
		Node *root=NULL;
		Dfs(root,0,(int)TREE.size()-1,'A','Z');
		CNT=0;
		Print(root);
		assert(CNT==n);
		puts("");
		if(lastchar=='$')break;
	}
	return 0;
}
