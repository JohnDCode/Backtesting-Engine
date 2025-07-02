/*

JDA Backtesting Engine
/src/engine/Engine.cpp
JohnDavid Abe

*/

#include "engine/Engine.hpp"
#include "engine/Strategy.hpp"  // Required for calling strategy logic
#include <iostream>

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

        // Feed the strategy data and allow the strategy to operate (Ex: create a market order)
        strategy_->on_data(market_data);

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
