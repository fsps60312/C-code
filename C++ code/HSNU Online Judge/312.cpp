#include<cstdio>
#include<map>
using namespace std;
int MILK,N;
int main()
{
	scanf("%d%d",&MILK,&N);
	multimap<int,int>sot;
	for(int i=0,price,cnt;i<N;i++)scanf("%d%d",&price,&cnt),sot.insert(make_pair(price,cnt));
	int ans=0;
	for(const auto &it:sot)
	{
		if(it.second>=MILK){ans+=MILK*it.first;break;}
		else ans+=it.first*it.second,MILK-=it.second;
	}
	printf("%d\n",ans);
	return 0;
}
