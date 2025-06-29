/*

JDA Backtesting Engine
/include/engine/MarketDataFeed.hpp - MarketDataFeed class handles individual bars for each symbol
JohnDavid Abe

*/


#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "MarketDataBar.hpp"


/**
 * @brief Contains data from all symbols and respective bars and appropriate accessor/mutator methods to handle bars
 */
class MarketDataFeed {


public:

    // Utilizes a csv of bar data for a single symbol to create a vector of the bars, which is added to data_
    void load_from_csv(const std::string& symbol, const std::string& filepath);

    // Retrieves the bar for each symbol at a particular time
    std::unordered_map<std::string, MarketDataBar> get_bar_at(size_t index) const;

    // Retrieves the size of the data (the number of bars in the dataset)
    size_t num_bars() const;


private:

    // The data object, storing the bars for all symbols
    std::unordered_map<std::string, std::vector<MarketDataBar>> data_;
};
