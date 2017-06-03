#include<cstdio>
#include<cassert>
#include<algorithm>
#include<cmath>
using namespace std;
const double EPS=1e-9;
struct Student
{
	double chinese,english,height;
	int h;
//	Student(){}
//	Student(const double _c,const double _e,const double _h):chinese(_c),english(_e),height(_h){}
};
bool operator<(const Student &a,const Student &b)
{
	if(fabs((a.chinese+a.english)-(b.chinese+b.english))>=EPS)return a.chinese+a.english<b.chinese+b.english;
	else
	{
		if(fabs(a.chinese-b.chinese)>=EPS)return a.chinese<b.chinese;
		else return a.english<b.english;
	}
}
struct Bit
{
	int N,S[100001];
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	void Add(int i){for(;i<=N;i+=i&(-i))++S[i];}
	int Query(int i){int ans=0;for(;i;i-=i&(-i))ans+=S[i];return ans;}
}BIT;
int N;
Student S[100000];
void Discretize()
{
	vector<double>v;
	for(int i=0;i<N;i++)v.push_back(S[i].height);
	sort(v.begin(),v.end());
	for(int i=0;i<N;i++)S[i].h=(int)(lower_bound(v.begin(),v.end(),S[i].height)-v.begin())+1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%lf%lf%lf",&S[i].chinese,&S[i].english,&S[i].height);
	sort(S,S+N);
	Discretize();
	BIT.Clear(N);
	long long ans=0;
	for(int i=N-1;i>=0;i--)
	{
		ans+=BIT.Query(S[i].h-1);
		BIT.Add(S[i].h);
	}
	printf("%lld\n",ans);
	return 0;
}
