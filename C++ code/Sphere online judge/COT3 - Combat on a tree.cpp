#include<cstdio>
//#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
struct Node
{
	Node *ch[2];
	int sum,tag;
	vector<int>*ids;
	Node():ch{NULL,NULL},sum(0),tag(0),ids(new vector<int>()){}
};
void PutDown(Node *o,const int depth)
{
	if((1<<depth)&o->tag)swap(o->ch[0],o->ch[1]);
	for(int d=0;d<2;d++)if(o->ch[d])o->ch[d]->tag^=o->tag;
	o->tag=0;
}
int Sum(Node *o){return o?o->sum:0;}
void Maintain(Node *o)
{
	o->sum=Sum(o->ch[0])+Sum(o->ch[1]);
}
void Insert(Node* &o,const int depth,const int value,const int id)
{
	if(!o)o=new Node();
	if(depth==-1){o->sum=1,o->ids->push_back(id);return;}
	PutDown(o,depth);
	Insert((o->ch[(1<<depth)&value)>>depth],depth-1,value,id);//note the priority of bitwise operators
	Maintain(o);
}
vector<int>*Merge(vector<int>*a,vector<int>*b)
{
	if(a->size()<b->size())swap(a,b);
	for(const int v:*b)a->push_back(v);
	return a;
}
Node *Merge(Node *a,Node *b,const int depth)
{
	if(!a||!b)return a?a:b;
	Node *ans=new Node();
	if(depth==-1)ans->sum=(a->sum)|(b->sum),ans->ids=Merge(a->ids,b->ids);
	else
	{
		PutDown(a,depth),PutDown(b,depth);
		ans->ch[0]=Merge(a->ch[0],b->ch[0],depth-1);
		ans->ch[1]=Merge(a->ch[1],b->ch[1],depth-1);
		Maintain(ans);
	}
	return ans;
}
int GetSG(Node *o,const int depth,const int now)
{
	if(!o||depth==-1)return now;
	PutDown(o,depth);
	if(Sum(o->ch[0])<(1<<depth))return GetSG(o->ch[0],depth-1,now);
	else
	{
		assert(Sum(o->ch[1])<(1<<depth));
		return GetSG(o->ch[1],depth-1,now+(1<<depth));
	}
}
int N,COLOR[100000];
vector<int>ET[100000];
Node *GetTree(const int u,const int parent,int &allsg)
{
	vector<Node*>ch_trees;
	vector<int>ch_sgs;
	allsg=0;
	for(const int nxt:ET[u])if(nxt!=parent)
	{
		int ch_sg;
		ch_trees.push_back(GetTree(nxt,u,ch_sg));
		ch_sgs.push_back(ch_sg);
		allsg^=ch_sg;
	}
	Node *ans=NULL;
	for(int i=0;i<(int)ch_trees.size();i++)if(ch_trees[i])
	{
		ch_trees[i]->tag^=allsg^ch_sgs[i];
		ans=Merge(ans,ch_trees[i],30);
	}
	if(COLOR[u]==0)Insert(ans,30,allsg,u),allsg=GetSG(ans,30,0);
	return ans;
}
vector<int>*GetIds(Node *o)
{
	for(int depth=30;depth>=0;depth--)
	{
		PutDown(o,depth);
		o=o->ch[0],assert(o);
	}
	return o->ids;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<N;i++)scanf("%d",&COLOR[i]);
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		int ans;
		Node *o=GetTree(0,-1,ans);
		ans=GetSG(o,30,0);
		if(ans==0)puts("-1");
		else
		{
			assert(o);
			vector<int>*ans=GetIds(o);
			sort(ans->begin(),ans->end());
			for(const int v:*ans)printf("%d\n",v+1);
		}
	}
	return 0;
}
