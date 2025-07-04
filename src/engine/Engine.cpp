/*

JDA Backtesting Engine
/src/engine/Engine.cpp
JohnDavid Abe

*/

#include "engine/Engine.hpp"
#include "engine/Strategy.hpp"  // Required for calling strategy logic
#include <iostream>
#include <unordered_map>

/**
 * @brief Constructor for the core engine
 *
 * @param market_data_feed The feed handling all bar data
 * @param order_manager The manager for all orders (queued and executing)
 * @param portfolio The portfolio storing cash, equities, positions, etc.
 * @param strategy The strategy in which the engine will test
 */
Engine::Engine(
    std::shared_ptr<MarketDataFeed> market_data_feed,
    std::shared_ptr<OrderManager> order_manager,
    std::shared_ptr<Portfolio> portfolio,
    std::shared_ptr<Strategy> strategy
) : market_data_feed_(market_data_feed),
    order_manager_(order_manager),
    portfolio_(portfolio),
    strategy_(strategy) {}


/**
 * @brief Runs the core backtest using the created strategy and available data
 */
void Engine::run_backtest() {

    double startingCash = portfolio_->get_cash();

    // Get the number of steps (bars) that the data contains and that the test will execute
    int num_timesteps = market_data_feed_->num_bars();

    // Loop through each bar
    for (int i = 0; i < num_timesteps; ++i) {

        // Get the bar data for the current bar
        auto market_data = market_data_feed_->get_bar_at(i);

        // Check for corporate actions
        this->apply_corporate_actions(market_data);

        // Feed the strategy data and allow the strategy to operate (Ex: create a market order)
        strategy_->on_data(market_data, *portfolio_);

        // Have order manager process orders made by strategy
        auto executed_orders = order_manager_->process_orders(market_data);

        // "Simulate" each executed order by updating the portfolio to match
        portfolio_->apply_executed_orders(executed_orders, market_data);
    }

    // Print results of test
    std::cerr << "----------------------------------------------------------" << std::endl;
    std::cerr << "Backtest Report:\n" << std::endl;

    std::cerr << "Starting Cash: " << startingCash << std::endl;
    std::cerr << "Ending Cash: " << portfolio_->get_cash() << std::endl;

    // Get the equity at the end of the test using the last set of bar data
    auto finalBars = market_data_feed_->get_bar_at(market_data_feed_->num_bars() - 1);
    std::cerr << "Total Equity: " << portfolio_->get_equity(finalBars) << "\n"  << std::endl;

    for (std::string symbol : portfolio_->get_symbols()) {
        std::cerr << "Symbol: " << symbol << " | Position: " << portfolio_->get_position(symbol) << std::endl;
    }

    std::cerr << "----------------------------------------------------------" << std::endl;
}

/**
 * @brief Checks for corporate actions (dividend payments, stock splits, etc.) and applies appropriate changes
 *
 * @param bars Current bar data for each symbol
 */
void Engine::apply_corporate_actions(std::unordered_map<std::string, MarketDataBar>& bars) {

    // Dividend payments

    // Loop through each entry and check if the current timestamp matches any of the entries
    for (const auto& symbolDividends : this->market_data_feed_->get_dividends()) {

        // Get the current date
        std::string date = bars[symbolDividends.first].timestamp;

        // Possible suffixes for first bar of the day (2 due to daylight savings shifting market open)
        std::string suffix1 = " 13:30:00+00:00";
        std::string suffix2 = " 14:30:00+00:00";

        // Attempt to remove either time suffix from date (if bar is first of day)
        if (date.size() >= suffix1.size() && date.compare(date.size() - suffix1.size(), suffix1.size(), suffix1) == 0) {
            date.erase(date.size() - suffix1.size());
        }
        if (date.size() >= suffix2.size() && date.compare(date.size() - suffix2.size(), suffix2.size(), suffix2) == 0) {
            date.erase(date.size() - suffix2.size());
        }


        // Lookup the dividend entry for the current date for the symbol
        auto divValue = symbolDividends.second.find(date);

        if (divValue != symbolDividends.second.end()) {
            // Apply the particular dividend
            this->portfolio_->add_cash(divValue->second * this->portfolio_->get_position(symbolDividends.first));
        }
    }



    // Stock splits

    // (Same as dividends but for splits)
    for (const auto& symbolSplits : this->market_data_feed_->get_splits()) {

        // Get the current date
        std::string date = bars[symbolSplits.first].timestamp;

        // Possible suffixes for first bar of the day (2 due to daylight savings shifting market open)
        std::string suffix1 = " 13:30:00+00:00";
        std::string suffix2 = " 14:30:00+00:00";

        // Attempt to remove either time suffix from date (if bar is first of day)
        if (date.size() >= suffix1.size() && date.compare(date.size() - suffix1.size(), suffix1.size(), suffix1) == 0) {
            date.erase(date.size() - suffix1.size());
        }
        if (date.size() >= suffix2.size() && date.compare(date.size() - suffix2.size(), suffix2.size(), suffix2) == 0) {
            date.erase(date.size() - suffix2.size());
        }


        // Lookup the split entry for the current date for the symbol
        auto splitRatio = symbolSplits.second.find(date);

        if (splitRatio != symbolSplits.second.end()) {
            // Apply the split
            std::cerr << "Date: " << date << "" << std::endl;
            this->portfolio_->split_position(symbolSplits.first, splitRatio->second);
        }
    }
}