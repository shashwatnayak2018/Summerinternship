//library 
#include<iostream>
#include<math.h>
#include<fstream>
using namespace std;
//define the equation of state
double fdensity(double p,double k,float r)
{
	double d;
	d = k*pow(p,r);
	return d;
}
//define change in pressure funtion
double cpressure(double m, double d, double r)
{
	double x;
	double y = 1/(r+10);
	double z = 1/r;
	x = 6.67*pow(10,-8)*m*d*(z-y);
	return x;
}
//define change in mass function
double cmass(double d, double r)
{
	double x,Y;
	x = 4.1867*d*(pow(r+10,3)-pow(r,3));
	return x;
}
//write the TOV solver functiondouble TOV(double p, double m, double d, double r)
double TOV(double p, double m, double d, double r)
{
	ofstream sfile;
	sfile.open("data6.dat");
	//base condition
	if(p<=0.0001)
	{
		cout<<"mass is "<<m<<" density is "<<d<<" radi is "<<r<<" press is "<<p<<endl;
		return d;
	}
	else
	{
		sfile<<p<<" "<<r+10<<endl;
		p = p - cpressure(m,d,r);
		m = m + cmass(d,r);
		d = 0.6*pow(p,0.75);
		cout<<d<<" ";
		cout<<r<<" "<<endl;
		return TOV(p,m,d,r+10);
	}
	sfile.close();
}
double mass(double p, double m, double d, double r)
{
	//base condition
	if(p<=0.0001)
	{
		//returns the mass when the pressure is very close to zero
		return m;
	}
	else
	{
		p = p - cpressure(m,d,r);//change in pressure
		m = m + cmass(d,r);//change in mass
		d = 0.6*pow(p,0.75);//change in density
		return mass(p,m,d,r+10);//use of recursion
	}
}
//write the main function
int main()
{
	TOV(1,0,1,0.001);
	ofstream outfile;
	outfile.open("data3.dat");//creating a dat file to store values
	for(int i = 1;i<100;i++)//using loop to find values for mass vs density graph
	{
		outfile<<0.6*pow(i,0.75);
		outfile<<" ";
		outfile<<mass(i,0,0.6*pow(i,0.75),0.001)<<endl;
	}
	outfile.close();
	ofstream infile;
	infile.open("data4.dat");//creating a dat file to store values
	for(int i = 1;i<100;i++)//using loop to find values for the pressure vs density graph
	{
		infile<<0.6*pow(i,0.75)<<" "<<i<<endl;
	}
	infile.close();
	return 0;
}
