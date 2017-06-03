#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
struct Frog
{
	int x,reach,id,eat;
	Frog(){}
	Frog(const int _x,const int _reach,const int _id):x(_x),reach(_reach),id(_id),eat(0){}
	bool operator<(const Frog &f)const{return reach<f.reach;}
};
int N,M;
bool EatMosquito(const Frog &frog,multimap<int,int>&alive,int &b)
{
	auto it=alive.lower_bound(frog.x);
	if(it==alive.end()||(it->first)>frog.reach)return false;
	b=it->second;
	alive.erase(it);
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		vector<Frog>frogs;//all frogs
		for(int i=0,x,t;i<N;i++)scanf("%d%d",&x,&t),frogs.push_back(Frog(x,x+t,i));
		sort(frogs.begin(),frogs.end(),[](const Frog &a,const Frog &b)->bool{return a.x<b.x;});
		map<int,int>happy;//frogs possible to eat mosquitoes
		for(const Frog &f:frogs)if(happy.empty()||f.reach>(happy.rbegin()->first))happy[f.reach]=f.id;
		sort(frogs.begin(),frogs.end(),[](const Frog &a,const Frog &b)->bool{return a.id<b.id;});
		multimap<int,int>alive;//mosquitoes still alive
		for(int i=0,p,b;i<M;i++)
		{
			scanf("%d%d",&p,&b);
			auto it=happy.lower_bound(p);
			if(it!=happy.end()&&frogs[it->second].x<=p)
			{
				Frog &frog=frogs[it->second];
				happy.erase(it++);
				do
				{
					frog.reach+=b;
					frog.eat++;
					while(it!=happy.end()&&(it->first)<=frog.reach)happy.erase(it++);
				}while(EatMosquito(frog,alive,b));
				happy[frog.reach]=frog.id;
			}
			else alive.insert(make_pair(p,b));
		}
		for(int i=0;i<N;i++)printf("%d %d\n",frogs[i].eat,frogs[i].reach-frogs[i].x);
	}
	return 0;
}
