/*

JDA Backtesting Engine
/include/engine/Strategy.hpp
JohnDavid Abe

*/

#pragma once

#include <unordered_map>
#include <string>
#include "MarketDataBar.hpp"
#include "OrderManager.hpp"

/**
 * @brief Strategy of which the engine will test
 */
class Strategy {

public:
    // Constructor
    Strategy(OrderManager& order_manager);

    // The integral part of the strategy object, taking data and making decisions based on the data
    void on_data(const std::unordered_map<std::string, MarketDataBar>& bars);

    // Strategy API
    void buy(const std::string& symbol, int quantity);
    void sell(const std::string& symbol, int quantity);
    void limit_buy(const std::string& symbol, int quantity, double price);
    void limit_sell(const std::string& symbol, int quantity, double price);
    void stop_buy(const std::string& symbol, int quantity, double price);
    void stop_sell(const std::string& symbol, int quantity, double price);

private:

    // The order manager that will handle the strategy
    OrderManager& order_manager_;

    // Strategy-specific state
    int bars_seen_ = 0;
};