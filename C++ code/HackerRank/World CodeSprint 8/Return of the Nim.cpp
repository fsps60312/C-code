#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
bool Solve(const int n,const int *s,const vector<pair<int,int> >&sg)
{
	if(n==2)
	{
		return find(sg.begin(),sg.end(),make_pair(s[0],s[1]))==sg.end();
	}
	else
	{
		assert(n>2&&n%2==1);
		int ans=s[0];
		for(int i=1;i<n;i+=2)
		{
			ans^=s[i+1]-s[i];
		}
		return ans!=0;
	}
}
int main()
{
	vector<pair<int,int> >sg;
	{
		bool *used=new bool[100001];
		for(int i=0;i<=100000;i++)used[i]=false;
		for(int i=0,j=0;i<=100000;i++)if(!used[i])
		{
			sg.push_back(make_pair(i,i+j));
//			printf("%d %d\n",i,i+j);
			if(i+j<=100000)used[i+j]=true;
			j++;
		}
		delete[]used;
	}
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		int n;
		scanf("%d",&n);
		int *s=new int[n];
		for(int i=0;i<n;i++)scanf("%d",&s[i]);
		sort(s,s+n);
		puts(Solve(n,s,sg)?"Sherlock":"Watson");
		delete[]s;
	}
	return 0;
}
