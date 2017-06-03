#include<cstdio>
#include<cstdlib>
#include<map>
#include<set>
#include<string>
using namespace std;
map<string,set<string> > M,M2;
int T,N;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		M.clear(),M2.clear();
		char tstr1[21],tstr2[21];
		for(int i=0;i<N;i++)
		{
			scanf("%s",tstr1);
			set<string> ts,ts2;
			M[tstr1]=ts,M2[tstr1]=ts2;
		}
		int m,i;scanf("%d",&m);
		while(m--)
		{
			scanf("%s%d",tstr1,&i);
			while(i--)
			{
				scanf("%s",tstr2);
				M[tstr1].insert(tstr2);
				M2[tstr1].insert(tstr2);
			}
		}
		for(map<string,set<string> >::iterator it1=M2.begin();it1!=M2.end();it1++)
		{
			for(map<string,set<string> >::iterator it2=M2.begin();it2!=M2.end();it2++)
			{
				if(it1->first==it2->first||it1->second.find(it2->first)==it1->second.end())continue;
				for(set<string>::iterator it3=it2->second.begin();it3!=it2->second.end();it3++)
				{
					it1->second.insert(*it3);
				}
			}
		}
		for(map<string,set<string> >::iterator it1=M.begin();it1!=M.end();it1++)
		{
			for(map<string,set<string> >::iterator it2=M2.begin();it2!=M2.end();it2++)
			{
				if(it1->first==it2->first||it1->second.find(it2->first)==it1->second.end())continue;
				for(set<string>::iterator it3=it2->second.begin();it3!=it2->second.end();it3++)
				{
					it1->second.erase(*it3);
				}
			}
		}
		for(map<string,set<string> >::iterator it1=M.begin();it1!=M.end();it1++)
		{
			if(!it1->second.size())continue;
			printf("%s %d",it1->first.c_str(),it1->second.size());
			for(set<string>::iterator it2=it1->second.begin();it2!=it1->second.end();it2++)
			{
				printf(" %s",it2->c_str());
			}printf("\n");
		}
	}
	return 0;
}
