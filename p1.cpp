#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;
int test_1(int i);
int test_2(int i);
int test_3(int i);
int test_4(int i);

int main()
{ 
	int f=0;// flag for whether the input is true 
	int i,t;// integer and test number 
	int succeed=0;	// The return value 
	while(f==0)
	{
		cout<<"Please enter the integer and the test number: ";
		cin>>i>>t;
		if(i>0 && t>0 && t<=4)
			f=1; 
	}
	switch(t)
	{
		case 1:
		{
			succeed=test_1(i);
			break;
		}
		case 2:
		{ 
			succeed=test_2(i);
			break;
		}
		case 3:
		{  
			succeed=test_3(i);
			break;
		}
		case 4:
		{  
			succeed=test_4(i);
			break;
		}
		default: break;
	}
	cout<<succeed<<endl;
	return 0;
}

// Triangle number
int test_1(int i)
{
	int succeed=0;
	double i1=(double)i;
	int n1=(int)floor(sqrt(2*i1));
	if(i==n1*(n1+1)/2)
		succeed=1;
	return succeed;
}

// Palindrome
int test_2(int i)
{
	int succeed=1;
	string i2=to_string(i); 
	int n2=(int)log10(i)+1;
	for(int j=0;j<n2;j++)
	{
		if(i2[j]!=i2[n2-1-j])
		{
			succeed=0;
			break;
		}
	}
	return succeed;
}

// Odious number
int test_3(int i)
{
	int succeed=0;
	int n3=0;
	while(i!=0)
	{ 
		if(i%2==1)
		n3=n3+1;
		i=i/2;
	}
	if(n3%2==1)
		succeed=1;
	return succeed;
}

// Extravagant number
int test_4(int i)
{
	int succeed=0;
	int d_i=(int)log10(i)+1; // the digit in the number
	int d_p=0;        // the digit in prime factorization
	int n4=2;         // starting from the smallest prime
	int p4=0;      // The exponent part of the prime 
	while(i!=1)
	{
		if(i%n4==0)
		{
			i=i/n4;
			p4=p4+1;
		}
		else
		{
		    if(p4==1)
			{
				d_p=d_p+(int)log10(n4)+1;
			}
			else if(p4>1)
			{
				d_p=d_p+(int)log10(n4)+1+(int)log10(p4)+1;
			}
			n4=n4+1;
			p4=0;
		}
				
	}
	// The last prime to make i=1 is counted here
	if(p4==1)
	{
		d_p=d_p+(int)log10(n4)+1;
	}
	else if(p4>1)
	{
		d_p=d_p+(int)log10(n4)+1+(int)log10(p4)+1;
	}
	if(d_i<d_p)
		succeed=1;
	return succeed;
}



