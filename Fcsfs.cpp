#include<bits/stdc++.h>
#include<vector>
using namespace std;
int main()
{

    int n;
    int sum=0,c=0,m=0;
    double d=0,wt=0,rp=0,r=0;
    cout<<"Number of process:"<<endl;
    cin>>n;
    int b[n],a[n],p[n];
    for(int i=0;i<n;i++)
    {
        cin>>b[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        p[i]=a[i];
    }
    sort(a,a+n);
    vector<int>t;
    vector<int>w;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(a[i]==p[j])
            {
                sum+=b[j];
                t.push_back(sum);
                w.push_back(b[j]);
            }
        }
    }
    for(int i=0;i<n;i++)
    {
    c=t[i]-a[i];
    d=d+c;
    m=c-w[i];
    c=0;
    wt=m+wt;
    m=0;
    }
    for(int i=1;i<n-1;i++)
    {
        rp=t[i]-a[i];
        r=r+rp;
    }

    cout<<"Turnatound avg: "<<d/n<<endl;
    cout<<"Avg waiting time: "<<wt/n<<endl;
    cout<<"Avg response time: "<<r/n<<endl;

}
