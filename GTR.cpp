//library
#include<iostream>
#include<math.h>
#include<fstream>
using namespace std;
//equation of state that shows the relation between density and pressure
double eq(double p, double r, double k)
{
	double d;
	d = k*pow(p,r);
	return d;//returns density of corresponding pressure
}
//function that returns the change in mass in each step
double cmass(double d, double r)
{
	double x;
	x = 4.1867*d*(pow(r+10,3)-pow(r,3));
	return x;
}
//function that returns the change in pressure in each step
double cpressure(double p, double m, double d, double r)
{
	double x = 7.49*pow(10,6)*log((r*(r+10-1.33*pow(10,-7)))/((r+10)*(r-1.33*pow(10,-7))));
	double y = 3.35*pow(10,-5)*p*m;
	double z = 62.8*p*(2*r+10-(13.34*m*pow(10,-8)));
	double a = 2.23*pow(10,-13)*p*m*m*log((r+10-(13.34*m*pow(10,-8)))/(r-(13.34*m*pow(10,-8))));
	double b = 6.67*pow(10,-8)*(p+d)*(x+y+z+a);
	return b;
}
//function to find radius and mass of the star
double GTR(double p,double m,double d,double r)
{
	//base condition
	if(p<= 0.001)
	{
		//when pressure is close to zero, it returns the mass
		//cout<<"pressure is"<<p<<"mass is"<<m<<"radius is"<<r<<"density is"<<endl;
		return m;
	}
	else
	{
		p = p - cpressure(p,m,d,r);//change in pressure
		m = m + cmass(d,r);//change in mass
		d = 0.6*pow(p,0.75);//change in density
		//cout<<p<<"  "<<m<<" "<<d<<" "<<r<<endl;
		return GTR(p,m,d,r+10);//recursion
	}
}
int main()
{
	//GTR(1,0,1,0.001);
	//GTR(0.999736 , 4192.95 ,0.599902 ,0.599881);
	ofstream outfile;
	//create a dat file to store values
	outfile.open("data7.dat");
	for(int i = 1;i<100;i++)//use for loop 
	{
		//store values in the dat file for "mass vs density at center" graph
		outfile<<0.6*pow(i,0.75)<<" "<<GTR(i,0,0.6*pow(i,0.75),0.001)<<endl;
	}
	outfile.close();
	return 0;
}
