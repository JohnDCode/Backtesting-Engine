/*

JDA Backtesting Engine
/include/engine/Order.hpp
JohnDavid Abe

*/

#pragma once

#include <string>
#include "OrderType.hpp"

/**
 * @brief Stores information on a single order (can represent a buy or sell order)
 */
struct Order {

    std::string symbol; ///< The symbol of which to trade
    int quantity; ///< The number of contracts (remaining) to execute
    OrderType type; ///< The type of order

    double price = 0.0; ///< The price to trigger trade for limit/stop orders


private:

    /**
     * @brief Default constructor called from static methods, eliminates convoluted overloads
     */
    Order(const std::string& theSymbol, int theQuantity, OrderType theType, double thePrice)
        : symbol(theSymbol), quantity(theQuantity), type(theType), price(thePrice) {}

public:
    // Static factory methods

    /**
     * @brief Creates a market order
     *
     * @param theSymbol The symbol to trade
     * @param theQuantity The number of contracts to execute
     */
    static Order Market(const std::string& theSymbol, int theQuantity) {
        return Order(theSymbol, theQuantity, OrderType::Market, 0.0);
    }

    /**
     * @brief Creates a limit order
     *
     * @param theSymbol The symbol to trade
     * @param theQuantity The number of contracts to execute
     * @param thePrice The price at which to trade
     */
    static Order Limit(const std::string& theSymbol, int theQuantity, double thePrice) {
        return Order(theSymbol, theQuantity, OrderType::Limit, thePrice);
    }

    /**
     * @brief Creates a stop order
     *
     * @param theSymbol The symbol to trade
     * @param theQuantity The number of contracts to execute
     * @param thePrice The price at which to execute the market order
     */
    static Order Stop(const std::string& theSymbol, int theQuantity, double thePrice) {
        return Order(theSymbol, theQuantity, OrderType::Stop, thePrice);
    }
};
