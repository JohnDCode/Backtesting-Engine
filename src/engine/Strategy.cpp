/*

JDA Backtesting Engine
/src/engine/Strategy.cpp
JohnDavid Abe

*/

#include "engine/Strategy.hpp"
#include "engine/Order.hpp"

/**
 *
 * @brief Creates instance of strategy object with an order manager that the strategy will communicate orders to
 */
Strategy::Strategy(OrderManager& order_manager)
    : order_manager_(order_manager) {}

/**
 * @brief Submits a market buy order to the order manager
 *
 * @param symbol The symbol to trade
 * @param quantity The number of contracts to execute
 */
void Strategy::buy(const std::string& symbol, int quantity) {
    order_manager_.submit_order(Order::Market(symbol, quantity));
}

/**
 * @brief Submits a market sell order to the order manager
 *
 * @param symbol The symbol to trade
 * @param quantity The number of contracts to execute
 */
void Strategy::sell(const std::string& symbol, int quantity) {
    order_manager_.submit_order(Order::Market(symbol, -quantity));
}

/**
 * @brief Submits a limit buy order to the order manager
 * @param symbol The symbol to trade
 * @param quantity The number of contracts to execute
 * @param price The maximum price to execute the trade at
 */
void Strategy::limit_buy(const std::string& symbol, int quantity, double price) {
    order_manager_.submit_order(Order::Limit(symbol, quantity, price));
}

/**
 * @brief Submits a limit sell order to the order manager
 * @param symbol The symbol to trade
 * @param quantity The number of contracts to execute
 * @param price The minimum price to execute the trade at
 */
void Strategy::limit_sell(const std::string& symbol, int quantity, double price) {
    order_manager_.submit_order(Order::Limit(symbol, -quantity, price));
}

/**
 * @brief Submits a limit buy order to the order manager
 * @param symbol The symbol to trade
 * @param quantity The number of contracts to execute
 * @param price The maximum price to execute the trade at
 */
void Strategy::stop_buy(const std::string& symbol, int quantity, double price) {
    order_manager_.submit_order(Order::Stop(symbol, quantity, price));
}

/**
 * @brief Submits a stop sell order to the order manager
 * @param symbol The symbol to trade
 * @param quantity The number of contracts to execute
 * @param price The minimum price to execute the trade at
 */
void Strategy::stop_sell(const std::string& symbol, int quantity, double price) {
    order_manager_.submit_order(Order::Stop(symbol, -quantity, price));
}