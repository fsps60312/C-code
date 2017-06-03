#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
vector<int>P;
void BuildPrimes()
{
	bool *isp=new bool[51001];
	for(int i=2;i<=51000;i++)isp[i]=true;
	for(int i=2;i<=51000;i++)
	{
		if(isp[i])P.push_back(i);
		for(int j=0;P[j]*i<=51000;j++)
		{
			isp[P[j]*i]=false;
			if(i%P[j]==0)break;
		}
	}
	delete[]isp;
}
vector<unsigned int>ADD,SUB;
void BuildADDSUB()
{
	map<unsigned int,bool>s;s[1]=true;
	for(int i=0;P[i]<=50000;i++)
	{
		for(map<unsigned int,bool>::const_iterator it=s.upper_bound(50000/P[i]);;)
		{
			--it;
			s[it->first*P[i]]=it->second^true;
			if(it==s.begin())break;
		}
	}
	ADD.clear(),SUB.clear();
	for(map<unsigned int,bool>::const_iterator it=s.begin();it!=s.end();++it)(it->second?ADD:SUB).push_back(it->first);
//	for(int i=0;i<10;i++)printf(" %u",ADD[i]);puts("");
//	for(int i=0;i<10;i++)printf(" %u",SUB[i]);puts("");
}
vector<unsigned int>::const_iterator LBound(const vector<unsigned int>&s,const unsigned int val){return lower_bound(s.begin(),s.end(),val);}
int main()
{
//	freopen("in.txt","r",stdin);
	BuildPrimes();
	BuildADDSUB();
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		unsigned int a,b,_d;
		scanf("%u%u%u",&a,&b,&_d),a/=_d,b/=_d;
		unsigned int ans=0;
		for(unsigned int d=1,pre_d;d<=a&&d<=b;)
		{
			pre_d=d;
			d=min(a/(a/d)+1,b/(b/d)+1);
			ans+=(unsigned int)(LBound(ADD,d)-LBound(ADD,pre_d))*((a/pre_d)*(b/pre_d));
			ans-=(unsigned int)(LBound(SUB,d)-LBound(SUB,pre_d))*((a/pre_d)*(b/pre_d));
		}
		printf("%u\n",ans);
	}
	return 0;
}
