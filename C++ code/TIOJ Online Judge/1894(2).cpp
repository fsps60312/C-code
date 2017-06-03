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
int D0[5000],DM[5000];
void findLocation(int N,int FIRST, int[]LOCATION, int[]TYPE)
{
	if(N==1){LOCATION[0]=FIRST,TYPE[0]=1;return;}
	for(int i=1;i<N;i++)D0[i]=getDistance(0,i);
	vector<int>o0s;
	for(int i=1;i<N;i++)o0s.push_back(i);
	sort(o0s.begin(),o0s.end(),[](const int a,const int b)->bool{return D0[a]<D0[b];});
	const int r=o0s.front();
	LOCATION[r]=FIRST+D0[r],TYPE[r]=2;
	if(N==2)return;
	const int mid=o0s.back();
	for(int i=1;i<N;i++)if(i!=r)DM[i]=getDistance(mid,i);
	vector<int>oms;
	for(int i=1;i<N;i++)if(i!=r)oms.push_back(i);
	sort(oms.begin(),oms.end(),[](const int a,const int b)->bool{return DM[a]<DM[b];});
	const int l=oms.front();
	const int dis_m0=getDistance(l,r)-2*getDistance(l,mid)-2*getDistance(0,r);
	const int m=dis_m0+D0[o0s.back()];
	assert(m%2==0);
	for(int i=1;i<N;i++)LOCATION[i]=FIRST+D0[i],TYPE[i]=2;
	for(int i=1;i<N;i++)if(LOCATION[i]>=m/2)
	{
		LOCATION[i]=(m/2)-LOCATION[i],TYPE[i]=1;
	}
}
int main(){return 0;}
