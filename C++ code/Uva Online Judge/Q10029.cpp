#include<cstdio>
#include<string>
#include<map>
#include<cassert>
#include<vector>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
map<string,int>DICT;
vector<string>WORD;
int N,H[25000];
int main()
{
	freopen("in.txt","r",stdin);
	DICT.clear();
	static char tmp[18];
	for(N=0;fgets(tmp,INF,stdin);N++)
	{
		int n=-1;while(tmp[++n])if(tmp[n]=='\n'){tmp[n]='\0';break;}
		if(DICT.find(tmp)!=DICT.end()){N--;continue;}
		assert(N<25000);
		H[DICT[tmp]=N]=1;
		WORD.push_back(tmp);
	}
	for(int i=0;i<N;i++)
	{
		string &s=WORD[i];
		for(int j=0;j<(int)s.size();j++)
		{
			const char prec=s[j];
			for(char &c=++s[j];c<='z';c++)
			{
				auto it=DICT.find(s);
				if(it!=DICT.end())getmax(H[it->second],H[i]+1);
			}
			s[j]=prec;
		}
	}
	return 0;
}
