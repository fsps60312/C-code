#include<cstdio>
#include<map>
#include<string>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
struct Person
{
	int money;
	string name;
	Person(){}
	Person(char *_n,int _m):money(_m),name(_n){}
	bool operator<(const Person &p)const{return money>p.money;}
};
int N,T;
map<string,int>IDX;
vector<Person>PERSON;
int GetIdx(char *str)
{
	auto it=IDX.find(str);
	if(it!=IDX.end())return it->second;
	const int sz=IDX.size();
	PERSON.push_back(Person(str,0));
	return IDX[str]=sz;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		assert(scanf("%d%d",&N,&T)==2);
		if(!(N|T))break;
		static char name1[1000000],name2[1000000];
		for(int i=0;i<N;i++)assert(scanf("%s",name1)==1);
		IDX.clear(),PERSON.clear();
		for(int i=0;i<T;i++)
		{
			static int v;
			scanf("%s%s%d",name1,name2,&v);
			const int a=GetIdx(name1),b=GetIdx(name2);
			Person &pa=PERSON[a],&pb=PERSON[b];
			pa.money-=v,pb.money+=v;
		}
		sort(PERSON.begin(),PERSON.end());
		static int kase=1;
		printf("Case #%d\n",kase++);
		for(int now=0,i=0;i+1<PERSON.size();i++)
		{
			Person &pa=PERSON[i],&pb=PERSON[i+1];
			now=pa.money;
			printf("%s %s %d\n",pa.name.c_str(),pb.name.c_str(),now);
			pa.money-=now,pb.money+=now;
		}
		if(!PERSON.empty())assert(PERSON[(int)PERSON.size()-1].money==0);
		puts("");
	}
	return 0;
}
