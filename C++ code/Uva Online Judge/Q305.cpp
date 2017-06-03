#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int K;
struct Node
{
	Node *l,*r;
	int v;
	Node(const int _v):v(_v),l(NULL),r(NULL){}
};
bool Solve(const int m)
{
	vector<Node*>s;
	for(int i=1;i<=K*2;i++)s.push_back(new Node(i));
	for(int i=0;i<K*2;i++)
	{
		if(i)s[i]->l=s[i-1];
		else s[i]->l=s[K*2-1];
		if(i+1<K*2)s[i]->r=s[i+1];
		else s[i]->r=s[0];
	}
	Node *u=s[K*2-1];
	for(int cnt=0;cnt<K;cnt++)
	{
		for(int i=0;i<m%(K*2-cnt);i++)u=u->r;
		if(u->v<=K)return false;
		u->l->r=u->r;
		u->r->l=u->l;
		u=u->l;
	}
	return true;
}
int ANS[14];
int main()
{
	for(int i=1;i<=13;i++)ANS[i]=-1;
	while(scanf("%d",&K)==1&&K)
	{
		if(ANS[K]!=-1){printf("%d\n",ANS[K]);continue;}
		for(int &m=ANS[K]=K+1;;m+=K+1)
		{
			if(Solve(m)){printf("%d\n",m);break;}
			else if(Solve(m+1)){printf("%d\n",++m);break;}
		}
	}
	return 0;
}
