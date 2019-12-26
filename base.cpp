#include "base.h"
#include <iostream>
using namespace std;
 int Base:: funcB()
{
	cout<<"base::funcB"<<endl;
	return true;
}

int D1::  funcB(int x)
{
	cout<<"D1:: int funcB("<<x<<")"<<endl;
	return true;
}

void D1::  funcD1()
{
	cout<<"D1:: void funcD1()"<<endl;
}

int D2:: funcB(int)//override
{
	cout<<"D2::int funcB(int);"<<endl;
	return true;
}

int D2:: funcB()//overwrite
{
	cout<<"D2::int funcB()"<<endl;
	return true;
}

void D2:: funcD1()
{
   cout<<"D2::void funcD1()"<<endl;
}//overwrite}
