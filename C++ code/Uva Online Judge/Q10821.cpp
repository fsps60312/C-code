#include<cstdio>
struct Node
{
	Node *ch[2];
	int color;
	Node():ch{NULL,NULL}{}
}*ROOT;
int N,H;
void Build(Node* &o,const int dep,int &cnt)
{
	if(dep==H||cnt==N)return;
	o=new Node();
	cnt++;
	Build(o->ch[0],dep+1,cnt),Build(o->ch[1],dep+1,cnt);
}
void Color(Node* &o,int &cnt)
{
	if(!o)return;
	Color(o->ch[1],cnt);
	o->color=++cnt;
	Color(o->ch[0],cnt);
}
void Print(Node* &o)
{
	if(!o)return;
	printf(" %d",o->color);
	Print(o->ch[1]),Print(o->ch[0]);
}
int main()
{
	while(scanf("%d%d",&N,&H)==2&&!(N==0&&H==0))
	{
		static int kase=1;
		printf("Case %d:",kase++);
		ROOT=NULL;
		int cnt=0;
		Build(ROOT,0,cnt);
		if(cnt<N)puts(" Impossible.");
		else Color(ROOT,cnt=0),Print(ROOT),puts("");
	}
	return 0;
} 
