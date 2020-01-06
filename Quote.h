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