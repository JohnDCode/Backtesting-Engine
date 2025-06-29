#include <iostream>

#include "engine/Order.hpp"

int main() {
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        std::cout << "i = " << i << std::endl;
    }

    // Testing creating orders
    Order myOrder = Order::Market("AAPL", 50);

    return 0;
}