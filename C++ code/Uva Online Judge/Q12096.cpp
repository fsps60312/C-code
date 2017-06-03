#include<cstdio>
#include<map>
#include<stack>
#include<vector>
#define termin(x,...) {printf(x,##__VA_ARGS__);while(1){}}
#define min(a,b) (a<b?a:b)
using namespace std;
int T,N;
map<map<int,int>,int> IDX;
vector<map<int,int> > SET;
stack<int> STK;
char LINE[10];
map<int,int> TMP;
int getIDX(map<int,int> &s)
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
	map<int,int> ans=SET[a];
	for(map<int,int>::iterator it=SET[b].begin();it!=SET[b].end();it++)
	{
		int v;
		if(ans.find(it->first)==ans.end())v=ans[it->first]=0;
		else v=ans[it->first];
		if(it->second>v)ans[it->first]=it->second;
	}
	return getIDX(ans);
}
int Intersect(int a,int b)
{
	map<int,int> ans;
	for(map<int,int>::iterator it=SET[a].begin();it!=SET[a].end();it++)
	{
		if(SET[b].find(it->first)==SET[b].end())continue;
		ans[it->first]=min(it->second,SET[b][it->first]);
	}
	return getIDX(ans);
}
int Add(int a,int b)
{
	map<int,int> ans=SET[b];
	if(ans.find(a)==ans.end())ans[a]=0;
	ans[a]++;
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
				case'P':STK.push(getIDX(TMP=map<int,int>()));break;
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
