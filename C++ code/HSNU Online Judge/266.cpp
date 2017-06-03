#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,T,P;
bool GRID[2000][2000];
int GRADE[2000];
struct Person
{
	int grade,cnt,id;
	Person(){}
	Person(const int _g,const int _c,const int _i):grade(_g),cnt(_c),id(_i){}
	bool operator<(const Person &p)const
	{
		if(grade!=p.grade)return grade>p.grade;
		if(cnt!=p.cnt)return cnt>p.cnt;
		return id<p.id;
	}
};
vector<Person>S;
void PrintAns()
{
	for(int i=0;i<N;i++)if(S[i].id==P)
	{
		printf("%d %d\n",S[i].grade,i+1);
		return;
	}
	assert(0);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&T,&P)==3)
	{
		P--;
		S.clear();
		for(int i=0;i<N;i++)S.push_back(Person(0,0,i));
		for(int i=0;i<T;i++)GRADE[i]=0;
		for(int i=0;i<N;i++)for(int j=0;j<T;j++)
		{
			bool &g=GRID[i][j];
			int tmp;
			assert(scanf("%d",&tmp)==1);
			if(tmp==1)g=true;
			else if(tmp==0)g=false;
			else assert(0);
			if(g)S[i].cnt++;
			else GRADE[j]++;
		}
		for(int i=0;i<N;i++)for(int j=0;j<T;j++)if(GRID[i][j])S[i].grade+=GRADE[j];
		sort(S.begin(),S.end());
		PrintAns();
		break;
	}
}
