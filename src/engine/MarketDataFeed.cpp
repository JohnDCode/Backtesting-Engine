/*

JDA Backtesting Engine
/src/engine/MarketDataFeed.cpp
JohnDavid Abe

*/


#include "engine/MarketDataFeed.hpp"
#include <unordered_map>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>


/**
 * @brief Utilizes a csv of bar data for a single symbol to create a vector of the bars, which is added to data_
 *
 * @param symbol The symbol of which the csv holds data for, such as "AAPL"
 * @param filepath Path to the csv that holds the data for the symbol
 *
 * @note Ensure the csv only holds data on a single symbol
 */
void MarketDataFeed::load_from_csv(const std::string& symbol, const std::string& filepath) {

    // Open the csv file
    std::ifstream file(filepath);

    // Ensure the csv file could be properly opened
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return;
    }

    // Create a vector of bars (represents the symbol over time, each line in the csv is a bar)
    std::vector<MarketDataBar> bars;

    // Stores each line in the csv
    std::string line;

    // Reads the first line and stores it in line (read first line before loop to skip csv header)
    std::getline(file, line);

    // Loop until can no longer extract lines from the csv
    while (std::getline(file, line)) {

        // Create a stream object of the string (line)
        std::stringstream ss(line);

        // Stores each individual value from the bar
        std::string token;

        // The bar object which corresponds to each line in the csv
        MarketDataBar bar;

        // Get the timestamp string and assign the property
        std::getline(ss, bar.timestamp, ',');

        // Extract each numerical value from the line and set the respective properties
        std::getline(ss, token, ','); bar.open = std::stod(token);
        std::getline(ss, token, ','); bar.high = std::stod(token);
        std::getline(ss, token, ','); bar.low  = std::stod(token);
        std::getline(ss, token, ','); bar.close = std::stod(token);
        std::getline(ss, token, ','); bar.volume = std::stod(token);

        // Add the bar to the list of bars for the symbol
        bars.push_back(bar);
    }

    // Create a new index in the map of symbol data, where the symbol name is the key and its list of bars is the value
    data_[symbol] = bars;
}


/**
 * @brief Retrieves the bar for each symbol at a particular time
 *
 * @param index The index of the desired bar in each symbol's bar vector, representing a particular time
 * @return Returns a map where the symbols are keys and the values are the bar for that symbol at the chosen time
 */
std::unordered_map<std::string, MarketDataBar> MarketDataFeed::get_bar_at(size_t index) const {

    // Create the map to return of symbols and their respective bar at the chosen time
    std::unordered_map<std::string, MarketDataBar> bars;

    // Loop over the data property (looping over each symbol's data)
    for (const auto& [symbol, bar_series] : data_) {

        // Ensure that some bar does exist for the chosen time
        if (index < bar_series.size()) {

            // Set the return map's key/value pair with the symbol and the bar for the chosen time
            bars[symbol] = bar_series[index];
        }
    }

    // Return the map with the bars for each symbol
    return bars;
}

/**
 * @brief Retrieves the size of the data (the number of bars in the dataset)
 *
 * @return Returns the number of bars in the dataset
 *
 * @note Assume each symbol has the same number of bars
 */
size_t MarketDataFeed::num_bars() const {

    // If no csvs have been imported yet, there are 0 bars
    if (data_.empty()) return 0;

    // Return size of the value in the first symbol's data (value holds the bars, so gets size of bars for the first symbol)
    return data_.begin()->second.size();
}
