#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
int T,L,P;
vector<int>S;
struct Joint
{
	int idx;
	bool isup;
	Joint *a,*b,*l,*r;
	Joint(){}
	Joint(int idx,Joint *a,Joint *b,bool isup):idx(idx),a(a),b(b),isup(isup),l(NULL),r(NULL){}
}JOINT[1000000];
void Remove(int &ans,Joint *j)
{
	if(!j->a)return;
//	printf("remove %d\n",j->idx);
	ans--;
	j->l->r=j->r;
	j->r->l=j->l;
	j->a=NULL;
}
bool IsNeighbor(Joint *j1,Joint *j2)
{
	if(j1->r->idx==j2->idx&&j2->l->idx==j1->idx)return true;
	if(j1->l->idx==j2->idx&&j2->r->idx==j1->idx)return true;
	return false;
}
bool SelfLoop(Joint *j1,Joint *j2)
{
	if(j1->isup==j2->isup)return false;
	if(j1->b->idx!=j2->idx)return false;
	if(j1->idx!=j2->b->idx)return false;
	if(!IsNeighbor(j1,j2))return false;
	return true;
}
bool Passing(Joint *j1,Joint *j2)
{
	if(j1->isup!=j2->isup)return false;
	if(!IsNeighbor(j1,j2))return false;
	Joint *a=j1->b,*b=j2->b;
	if(!IsNeighbor(a,b))return false;
	return true;
}
bool VIS[1000000];
queue<Joint*>Q;
void Push(Joint *j)
{
	if(VIS[j->idx])return;
	VIS[j->idx]=true;
	Q.push(j);
}
bool solve()
{
	Q=queue<Joint*>();
	for(int i=0;i<S.size();i++)
	{
		Joint *j=&JOINT[S[i]];
		VIS[j->idx]=true;
		Q.push(j);
	}
	int ans=S.size();
	while(!Q.empty())
	{
		Joint *u=Q.front();Q.pop();
		VIS[u->idx]=false;
		if(!u->a)continue;
		Joint *r=u->r;
		if(SelfLoop(u,r))
		{
			Push(u->l);
			Remove(ans,u),Remove(ans,r);
		}
		else if(Passing(u,r))
		{
			Push(u->l);
			Joint *a=u->b,*b=r->b;
			Push(a->l);
			Push(b->l);
			Remove(ans,a),Remove(ans,b);
			Remove(ans,u),Remove(ans,r);
		}
	}
	return ans==0;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&L,&P);
		S.clear();
		for(int i=0,a,b;i<P;i++)
		{
			scanf("%d%d",&a,&b);
			JOINT[a]=Joint(a,&JOINT[a],&JOINT[b],true);
			JOINT[b]=Joint(b,&JOINT[b],&JOINT[a],false);
			S.push_back(a),S.push_back(b);
		}
		sort(S.begin(),S.end());
		for(int i=0,sz=S.size();i<sz;i++)
		{
			JOINT[S[i]].r=&JOINT[S[(i+1)%sz]];
			JOINT[S[(i+1)%sz]].l=&JOINT[S[i]];
		}
		static int kase=1;
		printf("Case #%d: %s\n",kase++,solve()?"YES":"NO");
	}
	return 0;
}
