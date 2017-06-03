#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
int T,L,P;
struct Joint
{
	int _a,_b,idx;
	bool isup;
	Joint *b,*l,*r;
	Joint(){}
	Joint(int a,int b,bool isup):idx(a),_a(a),_b(b),b(NULL),isup(isup),l(NULL),r(NULL){}
	bool operator<(const Joint &j)const{return _a<j._a;}
};
vector<Joint>JOINT;
bool IsNeighbor(Joint* &a,Joint* &b)
{
	return a->r->_a==b->_a||b->r->_a==a->_a;
}
bool cmp(Joint *a,Joint *b){return a->_a<b->_a;}
bool solve()
{
	vector<Joint*>torem,tocheck;
	for(int i=0;i<JOINT.size();i++)tocheck.push_back(&JOINT[i]);
	int ans=JOINT.size();
	int kase=0;
	goto startindex;
	do
	{
		kase++;
		ans-=torem.size();
		if(!ans)return true;
		tocheck.clear();
		for(int i=0;i<torem.size();i++)
		{
			if(i&&torem[i]->_a==torem[i-1]->_a)continue;
			Joint* &j=torem[i];
			printf("(%d)remove %d\n",kase,j->idx);
			j->r->l=j->l;
			j->l->r=j->r;
			j->l=j->r=NULL;
			tocheck.push_back(j->l);
		}
//		if(tocheck.size())
//		{
//			
//			for(Joint* j=tocheck[0]->r;j->_a!=tocheck[0]->_a;j=j->r)printf(" %d",j->idx);
//			puts("");
//		}
		torem.clear();
		startindex:;
		for(int i=0;i<tocheck.size();i++)
		{
			if(i&&tocheck[i]->_a==tocheck[i-1]->_a)continue;
			if(tocheck[i]->l==NULL)continue;
			Joint* &j=tocheck[i];
			Joint* &r=j->r;
			if(j->b->_a==r->_a&&r->b->_a==j->_a)torem.push_back(j),torem.push_back(r);
			else if(j->isup&&r->isup&&IsNeighbor(j->b,r->b))
				torem.push_back(j),torem.push_back(r),
				torem.push_back(j->b),torem.push_back(r->b);
		}
		sort(torem.begin(),torem.end(),cmp);
	}while(torem.size());
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&L,&P);
		JOINT.clear();
		for(int i=0,a,b;i<P;i++)
		{
			scanf("%d%d",&a,&b);
			JOINT.push_back(Joint(a,b,true));
			JOINT.push_back(Joint(b,a,false));
		}
		sort(JOINT.begin(),JOINT.end());
		map<int,Joint*>ptr;
		for(int i=0;i<JOINT.size();i++)ptr[JOINT[i]._a]=&JOINT[i];
		for(int i=0,sz=JOINT.size();i<sz;i++)
		{
			JOINT[i].r=&JOINT[(i+1)%sz];
			JOINT[(i+1)%sz].l=&JOINT[i];
			JOINT[i].b=ptr[JOINT[i]._b];
		}
		static int kase=1;
		printf("Case #%d: %s\n",kase++,solve()?"YES":"NO");
	}
	return 0;
}
