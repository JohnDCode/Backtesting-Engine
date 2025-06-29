/*

JDA Backtesting Engine
/include/engine/OrderType.hpp
JohnDavid Abe

*/


#pragma once


/**
 * @brief Dictates what type of order is being processed (market, limit, stop orders)
 */
enum class OrderType {
    Market, ///< Market order, process immediately
    Limit, ///< Limit order, process upon certain price
    Stop ///< Stop order, switch to market order upon specific price
};
