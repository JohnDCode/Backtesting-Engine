/*

JDA Backtesting Engine
/src/engine/OrderManager.cpp
JohnDavid Abe

*/

#include "engine/OrderManager.hpp"


/**
 * @brief Submits an order to the queue
 *
 * @param order The order object to be submitted
 *
 * @note Any order of any type can be added to the queue here
 */
void OrderManager::submit_order(const Order& order) {

    // Add the order to the pending queue, will check to execute at next step
    pending_orders_.push_back(order);
}

/**
 * @brief // Attempts to process all queued orders in list and returns executed orders to execute based on current data
 *
 * @param market_data Map holding all symbols and their data for the current bar
 * @return A list of orders that can be executed based on current bar data
 */
std::vector<Order> OrderManager::process_orders( const std::unordered_map<std::string, MarketDataBar>& market_data) {

    // List of orders that will be executed
    std::vector<Order> executed;

    // Loop through all orders
    for (auto& order : pending_orders_) {

        // Look for the entry in the data map with the key of the symbol of the current order
        auto it = market_data.find(order.symbol);

        // If past the last element, can skip, there was no matching data for the symbol concerning the order
        if (it == market_data.end()) continue;

        // If valid data is found, retrieve the bar data for the symbol (which is the second/value component of the map)
        const MarketDataBar& bar = it->second;

        // Read the type of order
        switch (order.type) {

            // Market Order
            case OrderType::Market:

                // Market orders always execute, so add it to the list of orders to execute
                executed.push_back(order);
                break;

            case OrderType::Limit:

                // Limit Buy: fill if bar.low <= limit price
                // Limit Sell: fill if bar.high >= limit price
                if ((order.quantity > 0 && bar.low <= order.price) || (order.quantity < 0 && bar.high >= order.price)) {
                    executed.push_back(order);
                }
                break;

            case OrderType::Stop:
                // Stop Buy: trigger if bar.high >= stop price
                // Stop Sell: trigger if bar.low <= stop price
                if ((order.quantity > 0 && bar.high >= order.price) || (order.quantity < 0 && bar.low <= order.price)) {
                    executed.push_back(order);
                }
                break;
        }
    }

    // Return a list of all orders that can now be executed
    return executed;
}

/**
 * @brief Clear all pending orders
 */
void OrderManager::clear() {
    pending_orders_.clear();
}