#include<cstdio>
#include<set>
#include<stack>
#include<vector>
#include<map>
#define termin(x,...) {printf(x,##__VA_ARGS__);while(1){}}
#define min(a,b) (a<b?a:b)
using namespace std;
int T,N;
map<set<int>,int> IDX;
vector<set<int> > SET;
stack<int> STK;
char LINE[10];
set<int> TMP;
int getIDX(set<int> &s)
{
	if(IDX.find(s)==IDX.end())
	{
		IDX[s]=SET.size();
		SET.push_back(s);
	}
	return IDX[s];
}
int Union(int a,int b)
{
	set<int> ans=SET[a];
	for(set<int>::iterator it=SET[b].begin();it!=SET[b].end();it++)ans.insert(*it);
	return getIDX(ans);
}
int Intersect(int a,int b)
{
	set<int> ans;
	for(set<int>::iterator it=SET[a].begin();it!=SET[a].end();it++)
	{
		if(SET[b].find(*it)==SET[b].end())continue;
		ans.insert(*it);
	}
	return getIDX(ans);
}
int Add(int a,int b)
{
	set<int> ans=SET[b];
	ans.insert(a);
	return getIDX(ans);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		IDX.clear();
		SET.clear();
		STK=stack<int>();
		for(int i=0;i<N;i++)
		{
			scanf("%s",LINE);
			switch(LINE[0])
			{
				case'P':STK.push(getIDX(TMP=set<int>()));break;
				case'D':STK.push(STK.top());break;
				case'U':
					{
						int a=STK.top();STK.pop();
						int b=STK.top();STK.pop();
						STK.push(Union(a,b));
					}break;
				case'I':
					{
						int a=STK.top();STK.pop();
						int b=STK.top();STK.pop();
						STK.push(Intersect(a,b));
					}break;
				case'A':
					{
						int a=STK.top();STK.pop();
						int b=STK.top();STK.pop();
						STK.push(Add(a,b));
					}break;
				default:termin("can't handle LINE[0]:%c\n",LINE[0]);
			}
			printf("%d\n",SET[STK.top()].size());
		}
		puts("***");
	}
	return 0;
}
