#include "Order.h"
#include "Restaurant.h"
#include "myString.h"
#include <iostream>

int main() {
	Restaurant pizzaDelivery;
	pizzaDelivery.addItem("Margarita");
	Order myOrder;
	myOrder.addItem("Margarita");

	try
	{
		pizzaDelivery.order(myOrder);	
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
}
