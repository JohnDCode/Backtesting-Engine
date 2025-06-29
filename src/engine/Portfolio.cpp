/*

JDA Backtesting Engine
/src/engine/Portfolio.cpp
JohnDavid Abe

*/

#include "engine/Portfolio.hpp"
#include <stdexcept>

/**
 * @brief Creates Portfolio object with certain amount of starting cash
 *
 * @param starting_cash Amount of money that the portfolio is created with
 */
Portfolio::Portfolio(double starting_cash)
    : cash_(starting_cash) {}


/**
 * @brief Takes any executable orders and actually executes them by applying changes to portfolio
 *
 * @param executed_orders
 * @param market_data
 */
void Portfolio::apply_executed_orders(const std::vector<Order>& executed_orders, const std::unordered_map<std::string, MarketDataBar>& market_data) {

    // Orders have already been tested for their ability to be executed by the order manager

    // Loop through each executable order
    for (const auto& order : executed_orders) {

        // Find the market bar data with the symbol concerning the current order
        auto it = market_data.find(order.symbol);

        // Ensure the data for that symbol exists
        if (it == market_data.end()) {
            continue;
        }

        // Retrieve the bar (is value in key/value pair from map)
        const MarketDataBar& bar = it->second;

        // Trade using the closing price of the bar
        double execution_price = bar.close;

        // Get the number of shares and the cost of the execution from the order
        int shares = order.quantity;
        double cost = execution_price * shares;


        // Update the portfolio based on the trade (cash and positions)
        cash_ -= cost;
        positions_[order.symbol] += shares;
    }
}

/**
 * @brief Accessor method for portfolio's cash
 *
 * @return Cash of the portfolio
 */
double Portfolio::get_cash() const {
    return this->cash_;
}

/**
 * @brief Gets the portfolio's position on a particular symbol
 *
 * @param symbol The position of which symbol to be returned
 *
 * @return Integer representing the portfolio's position on a particular symbol (neg/short, pos/long)
 */
int Portfolio::get_position(const std::string& symbol) const {

    // Find the entry with the key matching the symbol
    auto it = positions_.find(symbol);

    //  Ensuring the entry in positions exist and then returning the value in the pair (which is the position itself)
    return (it != positions_.end()) ? it->second : 0;
}

/**
 * @brief Gets the portfolio's total equity based on some particular market bar data
 *
 * @param market_data The market data for each symbol in the portfolio
 *
 * @return Double representing the portfolio's total equity
 */
double Portfolio::get_equity(const std::unordered_map<std::string, MarketDataBar>& market_data) const {

    // Retrieve the cash of the Portfolio
    double total = this->cash_;

    // Loop through each symbol/shares pair in positions
    for (const auto& [symbol, shares] : this->positions_) {

        // Get the corresponding bar data for the current symbol
        auto it = market_data.find(symbol);

        // If the data exists, add the equity for that symbol (product of shares times the symbol's value)
        if (it != market_data.end()) {
            total += shares * it->second.close;
        }
    }

    // Return the total equity
    return total;
}
