#include<cstdio>
#include<cassert>
#include<map>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void AssignAnswers(const map<int,int>&s,const int l,const int r,int &ans1,int &ans2,int &ans3)
{
	if(l>r){AssignAnswers(s,r,l,ans2,ans1,ans3);return;}
	assert(l<r);
	int sum;
	if(true)
	{
		map<int,int>::const_iterator it=s.end();--it;
		sum=it->second;
	}
	const int mid=l+(r-l)/2;
	map<int,int>::const_iterator it=s.upper_bound(mid);--it;
	ans2=sum-(it->second);
	if((l+r)%2==0&&it->first==mid)ans3=it->second,--it,ans3-=it->second;
	else ans3=0;
	ans1=it->second;
}
struct Point
{
	int X,Y;
	Point(){}
	Point(const int _X,const int _Y):X(_X),Y(_Y){}
};
int N,M,Z,P;
Point A,B;
map<int,int>X,Y,T1,T2;
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("str1.in","r",stdin);
	while(scanf("%d%d%d%d",&N,&M,&Z,&P)==4)
	{
		X.clear(),Y.clear(),T1.clear(),T2.clear();
		for(int i=0,x,y;i<Z;i++)
		{
			scanf("%d%d",&x,&y);
			++X[x],++Y[y],++T1[x+y],++T2[x-y];
		}
		X[-INF]=Y[-INF]=T1[-INF]=T2[-INF]=0;
		int sum;
		sum=0;for(map<int,int>::iterator it=X.begin();it!=X.end();++it)it->second=(sum+=it->second);X[INF]=sum;
		sum=0;for(map<int,int>::iterator it=Y.begin();it!=Y.end();++it)it->second=(sum+=it->second);Y[INF]=sum;
		sum=0;for(map<int,int>::iterator it=T1.begin();it!=T1.end();++it)it->second=(sum+=it->second);T1[INF]=sum;
		sum=0;for(map<int,int>::iterator it=T2.begin();it!=T2.end();++it)it->second=(sum+=it->second);T2[INF]=sum;
		for(int i=0;i<P;i++)
		{
			scanf("%d%d%d%d",&A.X,&A.Y,&B.X,&B.Y);
			int ans1,ans2,ans3;
				 if(A.X==B.X)AssignAnswers(Y,A.Y,B.Y,ans1,ans2,ans3);
			else if(A.Y==B.Y)AssignAnswers(X,A.X,B.X,ans1,ans2,ans3);
			else if((A.X<B.X)==(A.Y<B.Y))AssignAnswers(T1,A.X+A.Y,B.X+B.Y,ans1,ans2,ans3);
			else if((A.X<B.X)!=(A.Y<B.Y))AssignAnswers(T2,A.X-A.Y,B.X-B.Y,ans1,ans2,ans3);
			else assert(0);
			printf("%d %d %d\n",ans1,ans2,ans3);
		}
	}
	return 0;
}
