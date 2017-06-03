#define SELF
#include "lib1894.h"
#include<cassert>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
#ifdef SELF
int getDistance(int x, int y){return 0;}
#endif
int D0[5000],DR[5000];
void findLocation(int N,int FIRST, int[]LOCATION, int[]TYPE)
{
	if(N==1){LOCATION[0]=FIRST,TYPE[0]=1;return;}
	for(int i=1;i<N;i++)D0[i]=getDistance(0,i);
	vector<int>order;
	for(int i=1;i<N;i++)order.push_back(i);
	sort(order.begin(),order.end(),[](const int a,const int b)->bool{return D0[a]<D0[b];});
	const int r=order[0];
	LOCATION[r]=FIRST+D0[r],TYPE[r]=2;
	if(N==2)return;
	int l=0;
	set<int>solved;
	solved.insert(r);
	vector<pair<int,int> >left,right;
	for(int i=1;i<N-1&&D0[order[i]]<D0[r]*2;i++)
	{
		const int id=order[i];
		const int DR[id]=getDistance(id,r);
		solved.insert(id);
		l=id;
		right.push_back(make_pair(D0[id],id));
	}
	LOCATION[id]=FIRST+D0[id]-d,TYPE[id]=1;
	for(auto &p:right)p.first-=D0[l]-d;
	for(auto it=right.begin();it!=right.end();it++)if(it->second==l){right.erase(it);break;}
	for(int i=1;i<N;i++)if(solved.find(i)==solved.end())
	{
		const int dr=getDistance(l,i),dl=getDistance(i,r);
		if(dl<dr)left.push_back(make_pair(dl,i));
		else right.push_back(make_pair(dr,i));
	}
	sort(left.begin(),left.end()),sort(right.begin(),right.end());
	
}
int main(){return 0;}
