#include<iostream>
using namespace std;
bool zs(int a)
{
	for(int i=2;i*i<=a;i++)if(a%i==0)return false;
	return true;
}
int main()
{
	int l,max=0;
	cin>>l;
	for(int i=2;l<i;i++)
	{
		if(zs(i))
		{
			cout<<i<<endl;
			l=l-i;
			cout<<l<<endl;
			max++;
		}
	}
	cout<<max;
	return 0;
}
