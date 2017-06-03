#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(a<b)a=b;}
struct Point
{
	int X,Y;
	Point(){}
	Point(const int _X,const int _Y):X(_X),Y(_Y){}
};
struct Bit
{
	int S[100001];
	void Clear(){for(int i=1;i<=N;i++)S[i]=0;}
	void 
}BIT;
int N,A[100001];
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<N;i++)A[i]=(i+1)-A[i];
		int mn=INF,mx=-INF;
		if(true)
		{
			vector<Point>s;
			for(int i=0;i<N;i++)if(0<=A[i]&&A[i]<=i)s.push_back(Point(i-A[i],A[i])),getmin(mn,i-A[i]),getmax(mx,i-A[i]);
			for(int i=0;i<N;i++)s[i].X-=mn;
			mx-=mn;
		}
		//j-A[j]<i-A[i]<=i-A[j]
		//A[j]<=A[i]
		//j<i
		sort(s.begin(),s.end());
		Solve(s,0,mx);
	}
	return 0;
}
