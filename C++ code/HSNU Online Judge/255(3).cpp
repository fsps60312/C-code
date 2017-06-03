#include<cstdio>
#include<set>
#include<cassert>
#include<vector>
using namespace std;
int N,S[1100000],H[1100000];
struct CmpH{bool operator()(const int a,const int b)const{return H[a]!=H[b]?H[a]<H[b]:a<b;}};
set<int,CmpH>GH;
struct Deq
{
	int l,r,s[1100000];
	void clear(){l=0,r=-1;}
	void push_back(const int v){s[++r]=v;}
	int pop_back(){return s[r--];}
	int pop_front(){return s[l++];}
	int front(){return s[l];}
	int back(){return s[r];}
	bool empty(){return r<l;}
	int size(){return r-l+1;}
	void print(){for(int i=l;i<=r;i++)printf(" %d",s[i]);puts("");}
}DEQ;
//#include<algorithm>
//#include<ctime>
int main()
{
//	srand(time(NULL));
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
//	N=10;
//	for(int i=0;i<N;i++)S[i]=i;
//	bool valid=false;
//	while(!valid)
//	{
//		valid=true;
//		random_shuffle(S,S+N);
//		for(int i=1;i<N;i++)if(S[i]==S[i-1]+1){valid=false;break;}
//	}
//	for(int i=0;i<N;i++)printf(" %d",S[i]);puts("");
//////////////////////////////////////////////////
	for(int i=0;i<N;i++)H[i]=S[i]-i;
	vector<int>vl,vr;
	DEQ.clear(),MX.clear();
	for(int i=0;i<N;i++)
	{
//		if(!DEQ.empty()&&S[DEQ.back()]>S[i])DEQ.clear(),GH.clear();
		while(!DEQ.empty()&&S[DEQ.back()]>S[i])GH.erase(DEQ.pop_back());
		auto it=GH.upper_bound(i);
//		printf("i=%d:",i);DEQ.print();
		if(it!=GH.begin()&&H[*(--it)]==H[i])
		{
			int lb=*it;
			assert(i-lb>=3);//assertion failed
			vl.push_back(lb);
			vr.push_back(i);
			while(!DEQ.empty()&&DEQ.front()<=lb)GH.erase(DEQ.pop_front());
		}
		DEQ.push_back(i),GH.insert(i);
		assert(DEQ.size()==GH.size());
	}
	printf("%d\n",vl.size());
	for(int i=0;i<vl.size();i++)printf("%d %d\n",vl[i]+1,vr[i]+1);
	return 0;
}
/*
10
6 9 4 1 5 3 2 8 0 7
*/
