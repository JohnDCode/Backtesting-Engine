/*

JDA Backtesting Engine
/include/engine/OrderManager.hpp
JohnDavid Abe

*/

#pragma once

#include <vector>
#include <unordered_map>
#include "Order.hpp"
#include "MarketDataBar.hpp"


/**
 * @brief Handles all orders and determines which should execute and stores pending orders
 */
class OrderManager {
public:

    // Submits an order to the queue
    void submit_order(const Order& order);

    // Attempts to process all queued orders in list and returns executed orders to execute based on current data
    std::vector<Order> process_orders(
        const std::unordered_map<std::string, MarketDataBar>& market_data
    );

    // Clear all pending orders
    void clear();

    // Simulate a price slipping prior to execution
    static double simulate_slippage(const Order& order, const MarketDataBar& bar);

private:

    // All pending orders (orders that have been submitted but have not been executed yet)
    std::vector<Order> pending_orders_;
};
