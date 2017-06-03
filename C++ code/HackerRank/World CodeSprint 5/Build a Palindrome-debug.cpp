#include<cstdio>
#include<cassert>
#include<string>
using namespace std;
bool IsP(string &s)
{
	for(int l=0,r=(int)s.size()-1;l<r;l++,r--)if(s[l]!=s[r])return false;
	return true;
}
string A,B,ANS;
void Update(string s)
{
	if(!IsP(s))return;
	if(s.size()>ANS.size())ANS=s;
	else if(s.size()==ANS.size()&&s<ANS)ANS=s;
}
int main()
{
	freopen("inn.txt","r",stdin);
	freopen("new.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		static char a[1000],b[1000];
		scanf("%s%s",a,b);
		A=a,B=b;
		ANS="";
		for(int i=0;i<(int)A.size();i++)
		{
			for(int j=1;i+j<=(int)A.size();j++)
			{
				for(int k=0;k<(int)B.size();k++)
				{
					for(int l=1;k+l<=(int)B.size();l++)
					{
						Update(A.substr(i,j)+B.substr(k,l));
					}
				}
			}
		}
		if(ANS=="")puts("-1");
		else puts(ANS.c_str());
	}
	return 0;
}
