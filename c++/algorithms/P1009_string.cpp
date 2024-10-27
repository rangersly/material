//string + *
#include<iostream>
using namespace std;
string operator *(string a,string b)
{
	string c;
	int al=a.length(),bl=b.length(),cl=0;
	int *ci;
	ci=new int[al+bl+5];
	for(int i=0;i<(al+bl+5);i++)ci[i]=0;
	for(int i=0;i<al;i++) a[i]=a[i]-48;
	for(int i=0;i<bl;i++) b[i]=b[i]-48;
	
	for(int j=0;j<bl;j++)
		for(int i=0;i<al;i++)
			ci[i+j]+=a[al-i-1]*b[bl-j-1];
	for(int i=0;i<(al+bl+3);i++)
	{
		ci[i+1]+=ci[i]/10;
		ci[i]%=10;
		if(ci[i+1]!=0)cl=i+1;
	}
	c.resize(cl+1);
	for(int i=0;i<=cl;i++)
		c[i]=ci[cl-i]+48;
	delete []ci;
	return c;
}
string operator+(string a,string b)
{
	string c;
	int al=a.length(),bl=b.length(),cl=0;
	int l=al>bl?al:bl;
	c.resize(l+3);
	for(int i=0;i<al;i++)a[i]=a[i]-48;//string转int
	for(int i=0;i<bl;i++)b[i]=b[i]-48;
	for(int i=0;i<(l+3);i++)c[i]=0;//c初始化
	for(int i=0;i<l;i++)//加法计算核心
	{
		if((al-i-1)>=0)c[i]=a[al-i-1]+c[i];
		if((bl-i-1)>=0)c[i]=b[bl-i-1]+c[i];
	}
	for(int i=0;i<(l+2);i++)//处理进位
	{
		c[i+1]+=c[i]/10;
		if(c[i+1]!=0)cl=i+1;
		c[i]=c[i]%10+48;
	}
	if(c[cl]<10)c[cl]+=48;
	char t;		//c反转
	for(int i=0;i<=cl/2;i++){t=c[i];c[i]=c[cl-i];c[cl-i]=t;}
	c.resize(cl+1);
	return c;
}
int main()
{
	string a,b;
	cin>>a>>b;
	cout<<a*b;
	return 0;
}
