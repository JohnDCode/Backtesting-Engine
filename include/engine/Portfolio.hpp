/*

JDA Backtesting Engine
/include/engine/Portfolio.hpp
JohnDavid Abe

*/

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "Order.hpp"
#include "MarketDataBar.hpp"


/**
 * @brief Manages users portfolio, adjusted based on orders
 */
class Portfolio {
public:

    // Creates Portfolio object with certain amount of starting cash
    Portfolio(double starting_cash);

    // Takes any executable orders and actually executes them by applying changes to portfolio
    void apply_executed_orders(
        const std::vector<Order>& executed_orders,
        const std::unordered_map<std::string, MarketDataBar>& market_data
    );

    // Accessor methods for each component of the portfolio
    double get_cash() const;
    int get_position(const std::string& symbol) const;
    double get_equity(const std::unordered_map<std::string, MarketDataBar>& market_data) const;
    std::vector<std::string> get_symbols() const;

private:

    // Portfolio's cash and positions
    double cash_;

    // Positions is stored as key/value pair --> symbol/number of shares
    std::unordered_map<std::string, int> positions_;
};
