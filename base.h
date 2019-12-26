class Base
{
public:
	virtual int funcB();
};

class D1 :public Base
{
public:
	virtual int funcB(int); //override
	virtual void funcD1();
};

class D2 : public D1
{
public:
	int funcB(int); //override
	int funcB();//overwrite
	void funcD1();//overwrite
};