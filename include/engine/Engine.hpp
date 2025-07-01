/*

JDA Backtesting Engine
/include/engine/Engine.hpp
JohnDavid Abe

*/


#pragma once

#include <memory>
#include "MarketDataFeed.hpp"
#include "OrderManager.hpp"
#include "Portfolio.hpp"

// Forward declare the strategy running on the engine
class Strategy;

/**
 * @brief The core backtesting engine, running the test and referencing appropriate order and market handlers
 */
class Engine {
public:
    Engine(
        std::shared_ptr<MarketDataFeed> market_data_feed,
        std::shared_ptr<OrderManager> order_manager,
        std::shared_ptr<Portfolio> portfolio,
        std::shared_ptr<Strategy> strategy
    );

    // Runs the core backtest using the created strategy and available data
    void run_backtest();

private:
    std::shared_ptr<MarketDataFeed> market_data_feed_;
    std::shared_ptr<OrderManager> order_manager_;
    std::shared_ptr<Portfolio> portfolio_;
    std::shared_ptr<Strategy> strategy_;
};
