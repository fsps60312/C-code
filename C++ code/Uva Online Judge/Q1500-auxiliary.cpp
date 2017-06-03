#include<cstdio>
#include<vector>
#include<map>
using namespace std;
map<vector<int>,int> MAP;
int getSG(vector<int> v)
{
	if(MAP.find(v)!=MAP.end())return MAP[v];
	vector<int> vis;
	
}
void dfsinsert(vector<int> &v,int dep)
{
	if(dep==v.size())
	{
		MAP[v]=-1;
		return;
	}
	for(int i=1;i<=10;i++)
	{
		v[dep]=i;
		dfsinsert(v,dep+1);
	}
}
int main()
{
	freopen("out.txt","w",stdout);
	vector<int> v;
	for(int N=1;N<=5;N++)
	{
		v.push_back(0);
		dfsinsert(v,0);
	}
	return 0;
}
