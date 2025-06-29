/*

JDA Backtesting Engine
/src/engine/Engine.cpp
JohnDavid Abe

*/

#include "engine/Engine.hpp"
#include "engine/Strategy.hpp"  // Required for calling strategy logic

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

    // Get the number of steps (bars) that the data contains and that the test will execute
    int num_timesteps = market_data_feed_->num_bars();

    // Loop through each bar
    for (int i = 0; i < num_timesteps; ++i) {

        // Get the bar data for the current bar
        auto market_data = market_data_feed_->get_bar_at(i);

        // Feed the strategy data and allow the strategy to operate (Ex: create a market order)
        strategy_->on_data(market_data);

        // have order manager process orders made by strategy
        auto executed_orders = order_manager_->process_orders(market_data);

        // "Simulate" each executed order by updating the portfolio to match
        portfolio_->apply_executed_orders(executed_orders, market_data);

        // Clear all pending orders
        order_manager_->clear();
    }
}