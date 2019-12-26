#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
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
	 std::string author = "Mike";
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
	void broadcast(Quote &input)
	{
		input = *this;
		std::cout<<price<<std::endl;
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

class Disc_quote:public Quote
{ 
 public: 
 		Disc_quote(const std::string &book,double sales_price,int min,int dis):\
		Quote(book,sales_price),minimun(min),discount(dis){}
		double net_price(std::size_t cnt) const =0;
		/*{
			double ret;
			if(cnt > minimun)
              ret = (1-discount)*price*minimun+price*(cnt-minimun);
            else
              ret = cnt*(1-discount)*price; 
		}*/
 private:
 	int minimun;
 	double discount;

};
 double
print_total(std::ostream &os,const Quote &item,size_t n) 
{ 
	double ret =item.net_price(n); os<<"ISBN: "<< item.isbn()<< "# sold: "<< n<<" totaldue"<<ret;
    return ret; 
}

/*void broadcast(Bulk_Quote &in)
{
	std::cout<<in.author<<std::endl;
}*/

int main()
{
	Quote *base;
	Bulk_Quote bulk("1234",5,10,0.2);//("8934",20);
	//bulk.broadcast(base);
	base  = &bulk;
	//bulk.price;
	///Disc_quote dis("1234",5,10,0.2);
	//Quote ptr("4567",12);// = &bulk;//new Bulk_Quote;
    //broadcast(bulk);
	//std::cout<<bulk.price<<std::endl;
	//bulk.broadcast();
}