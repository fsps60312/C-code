#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const double EPS=1e-9,ER=1e-5;
double A,B,P,Q;
double abs(double a){return a>=0.0?a:-a;}
double getvalue(vector<double> eqt,double x)
{
	double ans=eqt[0],now=1.0;
	for(int i=1;i<eqt.size();i++)
	{
		now*=x;
		ans+=eqt[i]*now;
	}
	return ans;
}
double aprox(vector<double> &eqt,double l,double r)
{
	bool ordered=getvalue(eqt,l)<getvalue(eqt,r);
	double mid;
	while(r-l>EPS)
	{
		mid=0.5*(l+r);
		if((getvalue(eqt,mid)>0.0)^ordered)l=mid;
		else r=mid;
	}
	return l;
}
vector<double> solve(vector<double> &eqt,int dep)
{
	if(eqt.size()==2)
	{
		vector<double> ans;
		ans.push_back(-eqt[0]/eqt[1]);
		if(abs(ans[0])>1.0)ans[0]=0.0;
		return ans;
	}
	vector<double> ans,dif;
	for(int i=1;i<eqt.size();i++)dif.push_back(eqt[i]*i);
	dif=solve(dif,dep+1);
	ans.push_back(aprox(eqt,-1.0,dif[0]));
	for(int i=1;i<dif.size();i++)ans.push_back(aprox(eqt,dif[i-1],dif[i]));
	ans.push_back(aprox(eqt,dif[dif.size()-1],1.0));
	vector<double> ta;
	ta.push_back(ans[0]);
	for(int i=1,j=0;i<ans.size();i++)
	{
		if(abs(ans[i]-ans[i-1])<ER)ta[j]=aprox(eqt,ans[i-1],ans[i]);
		else ta.push_back(ans[i]),j++;
	}
	ans.clear();
	for(int i=0;i<ta.size();i++)if(abs(getvalue(eqt,ta[i]))/A/B/A/B<ER)ans.push_back(ta[i]);
//	printf("%d: %d\n",dep,ans.size());
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%lf%lf%lf%lf",&A,&B,&P,&Q)==4&&A>=0.0)
	{
		//(A*sin-P,B*cos-Q)vertical to(A*cos,-B*sin)
		//A*A*sin*cos-P*A*cos-B*B*sin*cos+Q*B*sin==0
		//sin*(A*A*cos-B*B*cos+Q*B)==P*A*cos
		//sin==P*A*cos/(A*A*cos-B*B*cos+Q*B)==sqrt(1-cos*cos)
		//P*P*A*A*cos*cos==(A^4*cos^2 + B^4*cos^2 + Q*Q*B*B - 2*A*A*B*B*cos^2 - 2*Q*B^3*cos + 2*Q*A*A*B*cos)*(1-cos*cos)
		//(2*A*A*B*B-A^4-B^4)cos^4 + (2*Q*B^3-2*Q*A*A*B)cos^3 + (A^4+B^4-2*A*A*B*B-Q*Q*B*B-P*P*A*A)cos^2 + (2*Q*A*A*B-2*Q*B^3)cos + Q*Q*B*B
		//cos*(A*A*sin-B*B*sin-P*A)==-Q*B*sin
		//cos==Q*B*sin/(P*A+B*B*sin-A*A*sin)==sqrt(1-sin*sin)
		//Q*Q*B*B*sin^2==(B^4*sin^2 + A^4*sin^2 + P*P*A*A - 2*A*A*B*B*sin^2 + 2*P*A*B*B*sin - 2*P*A^3*sin)*(1-sin*sin)
		//(2*A*A*B*B-A^4-B^4)sin^4 + (2*P*A^3-2*P*A*B*B)sin^3 + (A^4+B^4-2*A*A*B*B-P*P*A*A-Q*Q*B*B)sin^2 + (2*P*A*B*B-2*P*A^3)sin + P*P*A*A
		vector<double> cos,sin;
		cos.push_back(Q*Q*B*B);
		cos.push_back(2.0*Q*A*A*B-2.0*Q*B*B*B);
		cos.push_back(A*A*A*A+B*B*B*B-2.0*A*A*B*B-Q*Q*B*B-P*P*A*A);
		cos.push_back(2.0*Q*B*B*B-2.0*Q*A*A*B);
		cos.push_back(2.0*A*A*B*B-A*A*A*A-B*B*B*B);
//		printf("f(x):%.5f\n",getvalue(cos,-2.94058/B));
//		printf("f(x):%.5f\n",getvalue(cos,49.60823/B));
//		printf("f(x):%.5f\n",getvalue(cos,-49.48640/B));
//		printf("f(x):%.5f\n",getvalue(cos,-3.84791/B));
		cos=solve(cos,0);
		sin.push_back(P*P*A*A);
		sin.push_back(2.0*P*A*B*B-2.0*P*A*A*A);
		sin.push_back(A*A*A*A+B*B*B*B-2.0*A*A*B*B-P*P*A*A-Q*Q*B*B);
		sin.push_back(2.0*P*A*A*A-2.0*P*A*B*B);
		sin.push_back(2.0*A*A*B*B-A*A*A*A-B*B*B*B);
		sin=solve(sin,0);
		sort(cos.begin(),cos.end());
		sort(sin.begin(),sin.end());
		printf("Case %d:\n",kase++);
//		printf("cos: sz=%d",cos.size());for(int i=0;i<cos.size();i++)printf(" %.5f",cos[i]);puts("");
//		printf("sin: sz=%d",sin.size());for(int i=0;i<sin.size();i++)printf(" %.5f",sin[i]);puts("");
		for(int i=0;i<sin.size();i++)
		{
			for(int j=0;j<cos.size();j++)
			{
				if(abs(sin[i]*sin[i]+cos[j]*cos[j]-1.0)>ER)continue;
				double x=A*sin[i],y=B*cos[j],dx=A*cos[j],dy=-B*sin[i];
				if(abs((x-P)*dx+(y-Q)*dy)/A/B<ER)printf("%.5f %.5f\n",x,y);
			}
		}
	}
	return 0;
}
