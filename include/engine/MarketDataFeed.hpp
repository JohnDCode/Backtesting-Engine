/*

JDA Backtesting Engine
/include/engine/MarketDataFeed.hpp
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

    // Adds a single symbol's dividends to the list of dividend payments
    void add_dividends(const std::string& symbol, const std::unordered_map<std::string, double>& dividend_map);

    // Adds a single symbol's stock splits to the list of all splits
    void add_splits(const std::string& symbol, const std::unordered_map<std::string, double>& split_map);

    // Accessor methods for all data stored in the feed
    std::unordered_map<std::string, std::vector<MarketDataBar>> get_bar_data() { return data_; }

    // Accessor methods for all data stored in the feed
    std::unordered_map<std::string, std::unordered_map<std::string, double>> get_dividends() { return dividends_; }

    // Accessor methods for all data stored in the feed
    std::unordered_map<std::string, std::unordered_map<std::string, double>> get_splits() { return splits_; }


private:

    // The data object, storing the bars for all symbols
    std::unordered_map<std::string, std::vector<MarketDataBar>> data_;

    // Data to store dividends for symbols (each map stores dividend dates and payouts for one symbol)
    // The vector stores a list of the dividends, where each entry is one symbol's historical dividends
    std::unordered_map<std::string, std::unordered_map<std::string, double>> dividends_;

    // Data to store stock splits for symbols (Similar to dividends structure except int for split ratio)
    std::unordered_map<std::string, std::unordered_map<std::string, double>> splits_;
};
