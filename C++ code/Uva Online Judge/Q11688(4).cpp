#include<cstdio>
struct Node
{
	Node *ch[2],*fa;
	int h,dep,idx,vis;
	int ans,d;
	void clear()
	{
		h=vis=dep=ans=0;
		ch[0]=ch[1]=NULL;
	}
}NODE[100001],*ROOT;
int H(Node *o){return o==NODE?0:o->h;}
int max(int a,int b){return a>b?a:b;}
void buildTREE(Node *o,int dep)
{
	if(o==NODE)return;
	o->dep=dep;
	buildTREE(o->ch[0],dep+1);
	buildTREE(o->ch[1],dep+1);
	o->h=1+max(H(o->ch[0]),H(o->ch[1]));
}
//int query(Node *o,int dep)
//{
//	//query(x)=max(
//	int &ans=o->ans;//tree height if o is dot
//	if(ans)return ans;
//	query(o->fa);
//	ans=H(o->fa->ch[o->d^1])+2+query(o->fa);
//	return ans;
//}
void buildans(Node *o,int and0,int dep0,int and1,int dep1)
{
//dep0: (node that will connect ch[0] after rotating).depth
//	ans(x)=max(max(H(x->ch[0]),and0)+dep0,max(H(x->ch[1]),and1)+dep1)
	if(o==NODE)return;
	o->ans=max(max(H(o->ch[0]),and0)+dep0,max(H(o->ch[1]),and1)+dep1);
	//rotate right
	buildans(o->ch[0],and0,dep0,max(H(o->ch[1]),and1-1),dep1+1);
	buildans(o->ch[1],max(H(o->ch[0]),and0-1),dep0+1,and1,dep1);
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=1;i<=100000;i++)NODE[i].idx=i;
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=1;i<=N;i++)NODE[i].clear();
		for(int i=1,a,b;i<=N;i++)
		{
			scanf("%d%d",&a,&b);
			NODE[i].ch[0]=&NODE[a];
			NODE[i].ch[1]=&NODE[b];
			NODE[a].vis=NODE[b].vis=1;
			NODE[a].fa=NODE[b].fa=&NODE[i];
			NODE[a].d=0,NODE[b].d=1;
		}
		for(int i=1;i<=N;i++)if(!NODE[i].vis){ROOT=&NODE[i];break;}
		buildTREE(ROOT,0);
		ROOT->ans=H(ROOT);
		buildans(ROOT->ch[0],H(ROOT->ch[1])+1,1,H(ROOT->ch[1]),2);
		buildans(ROOT->ch[1],H(ROOT->ch[0]),2,H(ROOT->ch[0])+1,1);
		for(int i=1;i<=N;i++)printf("%d\n",NODE[i].ans);
	}
	return 0;
}
