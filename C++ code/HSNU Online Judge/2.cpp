#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
struct Seg
{
	int a,b;
	Seg(){}
	Seg(int a,int b):a(a),b(b){}
	bool operator<(const Seg &s)const{return a<s.a;} 
};
vector<Seg>SEG;
int T,N;
bool Solve()
{
	stack<int>s;
	for(int i=0;i<N;i++)
	{
		int &a=SEG[i].a,&b=SEG[i].b;
		while(!s.empty()&&s.top()<a)s.pop();
		if(!s.empty()&&s.top()<b)return false;
		s.push(b);
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d",&N);
			SEG.clear();
			for(int i=0;i<N;i++)
			{
				static int a,b;
				scanf("%d%d",&a,&b);
				if(a>b)swap(a,b);
				SEG.push_back(Seg(a,b));
			}
			sort(SEG.begin(),SEG.end());
			puts(Solve()?"Y":"N");
		}
	}
	return 0;
}
