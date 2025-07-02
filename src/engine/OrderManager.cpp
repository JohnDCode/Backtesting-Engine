/*

JDA Backtesting Engine
/src/engine/OrderManager.cpp
JohnDavid Abe

*/

#include "engine/OrderManager.hpp"
#include <random>
#include <algorithm>
#include <iostream>


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
    std::vector<Order> uncompleted;

    // Loop through all orders
    for (auto& order : pending_orders_) {

        // Look for the entry in the data map with the key of the symbol of the current order
        auto it = market_data.find(order.symbol);

        // If past the last element, can skip, there was no matching data for the symbol concerning the order
        if (it == market_data.end()) continue;

        // If valid data is found, retrieve the bar data for the symbol (which is the second/value component of the map)
        const MarketDataBar& bar = it->second;

        // Get the accessible volume of the symbol for the order
        int availVol = bar.volume * 0.2; // Assume only 20% is accessible to trader

        // Read the type of order
        switch (order.type) {

            // Market Order
            case OrderType::Market:

                // Market orders always execute, so add it to the list of orders to execute

                // Ensure the market can fill the order, if not cancel the rest of the order
                if (order.quantity > 0) {
                    order.quantity = std::min(order.quantity, availVol);
                } else {
                    order.quantity = std::max(order.quantity, availVol * -1);
                }
                executed.push_back(order);
                break;

            case OrderType::Limit:

                // Limit Buy: fill if bar.ask <= limit price
                // Limit Sell: fill if bar.bid >= limit price
                if ((order.quantity > 0 && bar.ask <= order.price) || (order.quantity < 0 && bar.bid >= order.price)) {

                    // Ensure the market can fill the order, queue new order with any remaining contracts
                    if (order.quantity > 0) {
                        // If the order quantity is too large, queue an identical limit order with remaining contracts
                        if (order.quantity > availVol) {
                            Order unfilled = order;
                            unfilled.quantity = order.quantity - availVol;
                            order.quantity = availVol;
                            uncompleted.push_back(unfilled);
                        }
                        executed.push_back(order);
                    } else {
                        // If the order quantity is too large, queue an identical limit order with remaining contracts
                        if (order.quantity < availVol * -1) {
                            Order unfilled = order;
                            unfilled.quantity = order.quantity + availVol;
                            order.quantity = availVol * -1;
                            uncompleted.push_back(unfilled);
                        }
                        executed.push_back(order);
                    }

                } else {
                    uncompleted.push_back(order);
                }
                break;

            case OrderType::Stop:
                // Stop Buy: trigger if bar.high >= stop price
                // Stop Sell: trigger if bar.low <= stop price
                if ((order.quantity > 0 && bar.high >= order.price) || (order.quantity < 0 && bar.low <= order.price)) {

                    // Ensure the market can fill the order, if not cancel the rest of the order (like a market order)
                    if (order.quantity > 0) {
                        order.quantity = std::min(order.quantity, availVol);
                    } else {
                        order.quantity = std::max(order.quantity, availVol * -1);
                    }
                    executed.push_back(order);

                } else {
                    uncompleted.push_back(order);
                }
                break;
        }
    }

    // Ensure orders that were not filled remain on book
    this->pending_orders_ = uncompleted;

    // Return a list of all orders that can now be executed
    return executed;
}

/**
 * @brief Clear all pending orders
 */
void OrderManager::clear() {
    pending_orders_.clear();
}

/**
 * @brief Simulates the slippage for a particular order
 *
 * @param order The order in which to simulate the slip for
 * @param bar The market data to base the slip off
 *
 * @return Returns the execution price of the order with randomized volume based slippage
 */
double OrderManager::simulate_slippage(const Order& order, const MarketDataBar& bar) {

    // Volume based slippage (100% is max)
    double volumeFraction = std::min(std::abs(order.quantity) / static_cast<double>(bar.volume), 1.0);

    // Applies base slippage
    double slipPct = 0.001 * volumeFraction;

    // Random noise as a fraction of price (normal distribution centered at 0)
    static thread_local std::mt19937 rng(std::random_device{}());
    std::normal_distribution<double> noiseDist(0.0, slipPct * 0.75);

    double noise = noiseDist(rng);

    // If buying, price slips up
    double slip{};
    if (order.quantity > 0) {
        slip = 1.0 + slipPct + noise;

    // If selling, price slips down
    } else {
        slip = 1.0 - slipPct + noise;
    }

    // Clamp slip to at least 1% of the price
    slip = std::max(slip, 0.01);

    // Calculate execution price using slip and correct bid/ask price
    if (order.quantity > 0) {
        return bar.ask * slip;
    }
    return bar.bid * slip;
}
