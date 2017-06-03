#include<cstdio>
#include<string>
#include<map>
using namespace std;
char LINE[1001];
map<string,string>CNV;
bool ContainHe(string s)
{
	for(int i=0;i<s.size();i++)
	{
		if(s[i]>='A'&&s[i]<='Z')s[i]+='a'-'A';
		else if(s[i]<'a'||s[i]>'z')s[i]=' '; 
	}
//	printf("change to:%s\n",s.c_str());
	int i=0;
	for(;i<s.size();)
	{
		while(i<s.size()&&s[i]==' ')i++;
		if(i==s.size())break;
		bool hehe=true;
		while(i<s.size()&&s[i]!=' ')
		{
			if(!hehe)i++;
			else
			{
				if(i+1<s.size()&&s[i]=='h'&&s[i+1]=='e')i+=2;
				else hehe=false;
			}
		}
		if(hehe)return true;
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(gets(LINE))
	{
		int idx=0,a;
		while(LINE[idx]!=':')
		{
			if(LINE[idx]=='-'&&LINE[idx+1]=='>')a=idx;
			idx++;
		}
//		printf("a=%d,idx=%d\n",a,idx);
		LINE[a]=0;a+=2;
		LINE[idx++]=0;
		string s1=LINE,s2=LINE+a;
		string s=s1<s2?s1+"->"+s2:s2+"->"+s1;
		CNV[s]=LINE+idx;
	}
	int cnt=0;
	for(map<string,string>::iterator it=CNV.begin();it!=CNV.end();it++)
	{
//		printf("%s:%s\n",it->first.c_str(),it->second.c_str());
		string s=it->second;
		if(ContainHe(s))cnt++;
	}
//	printf("%d %d\n",cnt,CNV.size());
	cnt=cnt*1000/CNV.size();
	if(cnt%10>=5)cnt+=10;
	cnt/=10;
	printf("%d%%\n",cnt);
	return 0;
}
