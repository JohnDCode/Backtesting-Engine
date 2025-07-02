/*

JDA Backtesting Engine
/include/engine/MarketDataBar.hpp
JohnDavid Abe

*/


#pragma once

#include <string>

/**
 * @brief Stores information on a single bar of data for a single symbol
 */
struct MarketDataBar {

    std::string timestamp; ///< Time at which the bar started

    double open = 0.0; ///< Price for the symbol at start of bar
    double close = 0.0; ///< Price for the symbol at end of bar
    double high = 0.0; ///< Highest price for the symbol during the bar
    double low =  0.0; ///< Lowest price for the symbol during the bar

    double volume = 0.0; ///< Number of contracts during the bar

    double bid = 0.0; ///< Simulated bid price (in order to minimize overestimation of profits)
    double ask = 0.0; ///< Simulated ask price (in order to minimize overestimation of profits)
};
