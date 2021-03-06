#include <stdio.h>
#include <string>
#include <iostream>
class Quote
{
public:
	Quote() = default;
	Quote(const std::string &book,double sales_price)\
	 :bookNo(book),price(sales_price){}
	 std::string isbn() const {return bookNo;}
	 virtual double net_price(std::size_t n) const 
	 {
	 	return n*price;
	 }
	  void debug()
	 {
	 	std::cout<<"ISBN: "<<bookNo<<std::endl;
	 	std::cout<<"price: "<<price<<std::endl;
	 }
private:
	std::string bookNo;
protected:
	double price=0.0;
};

class Bulk_Quote:public Quote
{
public:
	Bulk_Quote(const std::string &book,double sales_price,size_t min,double dis) :\
	Quote(book,sales_price),min_qty(min),discount(dis) {}
	double net_price(std::size_t cnt) const 
	{
       if(cnt >= min_qty)
       	return cnt * (1-discount) * price;
       else
       	return price;
	}
	void broadcast()
	{
		printf("%d %d",min_qty,discount);
	}
	void setDiscount(size_t qty,double dis)
	{
		min_qty = qty;
		discount = dis;
	}
	 void debug() 
	{
	 	Quote::debug();
	 	std::cout<<"minimun number: "<<min_qty<<std::endl;
	 	std::cout<<"discount : "<<discount<<std::endl;
	}
private:
	size_t min_qty;
	double discount;
};
class Bulk_Quote_ : public Bulk_Quote
{
	void debug()
	{
		//cout<<"success"<<enndl;
	}
};
double print_total(std::ostream &os,const Quote &item,size_t n)
{
	double ret = item.net_price(n);
	os<<"ISBN: "<< item.isbn()<< "# sold: "<< n<<" total due"<<ret;
    return ret;
}

int main()
{
	Bulk_Quote bulk("1234",5,10,0.2);//("8934",20);
	Quote *ptr = &bulk;//new Bulk_Quote;
	//bulk.setDiscount(10,0.2);
	ptr->debug();
    //print_total(std::cout,normal,5);
    //print_total(cout,bulk,5);
}