#include<cstdio>
#include<string>
#include<map>
#include<algorithm>
#include<vector>
using namespace std;
char NAME[1000000];
map<string,string> STU;
string SUBJ="";
bool islower(char a){return a>='a'&&a<='z';}
bool allcapital(string a)
{
	for(int i=0;i<a.size();i++)
	{
		if(islower(a[i]))return false;
	}
	return true;
}
struct Ans
{
	string subj;
	int cnt;
};
bool cmp_ANS(Ans a,Ans b)
{
	if(a.cnt!=b.cnt)return a.cnt>b.cnt;
	for(int i=0;i<a.subj.size()&&i<b.subj.size();i++)
	{
		if(a.subj[i]!=b.subj[i])return a.subj[i]<b.subj[i];
	}
	return a.subj.size()<b.subj.size(); 
}
map<string,int> ANS;
vector<string> NONE;
bool cmp_NONE(string a,string b)
{
	for(int i=0;i<a.size()&&i<b.size();i++)
	{
		if(a[i]!=b[i])return a[i]<b[i];
	}
	return a.size()<b.size(); 
}
void printans()
{
	ANS.clear();
	for(map<string,string>::iterator it=STU.begin();it!=STU.end();it++)
	{
		string subjname=it->second;
		if(subjname.size()==0)continue;
		if(ANS.find(subjname)==ANS.end())ANS[subjname]=1;
		else ANS[subjname]++;
	}
	vector<Ans> ans;
	for(map<string,int>::iterator it=ANS.begin();it!=ANS.end();it++)
	{
		ans.push_back((Ans){it->first,it->second});
	}
	sort(ans.begin(),ans.end(),cmp_ANS);
	sort(NONE.begin(),NONE.end(),cmp_NONE);
	for(int i=0;i<ans.size();i++)
	{
		printf("%s %d\n",ans[i].subj.c_str(),ans[i].cnt);
	}
	for(int i=0;i<NONE.size();i++)
	{
		if(ANS.find(NONE[i])==ANS.end())
		{
			printf("%s 0\n",NONE[i].c_str());
		}
	}
}
int main()
{
	//freopen("in.txt","r",stdin); 
	SUBJ="";
	while(gets(NAME))
	{
		if(NAME[0]=='0')break;
		else if(NAME[0]=='1')
		{
			printans();
			STU.clear();
			SUBJ="";
			NONE.clear();
		}
		else if(allcapital(NAME))
		{
			SUBJ=NAME;
			NONE.push_back(NAME);
		}
		else
		{
			if(SUBJ.size()==0)continue;
			if(STU.find(NAME)!=STU.end())
			{
				if(STU[NAME]==SUBJ)continue;
				else STU[NAME]="";
			}
			else
			{
				STU[NAME]=SUBJ;
			}
		}
	}
	return 0;
}
