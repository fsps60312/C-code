#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
unsigned int Rand()
{
	static unsigned int seed=rand();
	seed=seed*0xdefaced+185849;
	return seed+=seed>>20;
}
int Rand(int a,int b)
{
	return a+(int)(Rand()%(b-a+1));
}
const int N=100003;
const int mod=1000000007, X=991;
LL hashval(char s[],int n) {
  LL ret=0;
  for(int i=0;i<n;i++)
    ret = (ret*X + s[i]) % mod;
  return ret;
}
LL make_pre(int n,const string &a) {
	LL ans=0;
  for(int i=0;i<n;i++)ans= (ans*X + a[i]) %mod;
  return ans;
}
int main() {
	map<LL,string>vis;
	for(;;)
	{
		string s;
		for(int i=0;i<15;i++)s.push_back('a'+Rand(0,25));
		const LL key=make_pre(15,s);
		if(vis.find(key)!=vis.end()){printf("%s\n%s\n",vis[key].c_str(),s.c_str());break;}
		else vis[key]=s;
	}
}
