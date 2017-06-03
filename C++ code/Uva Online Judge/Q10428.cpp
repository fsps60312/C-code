#include<cstdio>
#include<vector>
using namespace std;
const double EPS=1e-9;
int N;
double valueof(vector<double> &eqt,double x)
{
    double ans=0.0,p=1.0;
    for(int i=0;i<eqt.size();i++,p*=x)ans+=eqt[i]*p;
    return ans;
}
double aprox(vector<double> &eqt,double l,double r)
{
    bool lnega=valueof(eqt,l)<0.0;
    double mid;
    while(r-l>EPS)
    {
        mid=0.5*(l+r);
        if((valueof(eqt,mid)<0.0)^lnega)r=mid;
        else l=mid;
    }
    return l;
}
vector<double> solve(vector<double> &eqt)
{
    vector<double>ans;
    if(eqt.size()==2)
    {
        ans.push_back(-eqt[0]/eqt[1]);
        return ans;
    }
    vector<double>te;
    for(int i=1;i<eqt.size();i++)te.push_back(i*eqt[i]);
    vector<double>dif=solve(te);
    ans.push_back(aprox(eqt,-25.0,dif[0]));
    for(int i=1;i<dif.size();i++)ans.push_back(aprox(eqt,dif[i-1],dif[i]));
    ans.push_back(aprox(eqt,dif[dif.size()-1],25.0));
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    int kase=1;
    while(scanf("%d",&N)==1&&N)
    {
        vector<double> eqt;
        for(int i=0;i<=N;i++)eqt.push_back(0.0);
        for(int i=N;i>=0;i--)scanf("%lf",&eqt[i]);
        printf("Equation %d:",kase++);
        vector<double> ans=solve(eqt);
        for(int i=0;i<ans.size();i++)printf(" %.4f",ans[i]);
        puts("");
    }
    return 0;
}
