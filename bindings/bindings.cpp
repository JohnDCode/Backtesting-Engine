/*

JDA Backtesting Engine
/bindings/bindings.cpp
JohnDavid Abe

*/

// Pybind11
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// Header files for components to expose to python
#include "engine/Engine.hpp"
#include "engine/Strategy.hpp"
#include "engine/OrderManager.hpp"
#include "engine/MarketDataFeed.hpp"
#include "engine/Portfolio.hpp"
#include "engine/MarketDataBar.hpp"


// Python subclass of Strategy
class PyStrategy : public Strategy {

public:
    // Inherit constructors
    using Strategy::Strategy;

    // Override the "on_data method" (Python file will implement this)
    void on_data(const std::unordered_map<std::string, MarketDataBar>& bars) override {
        PYBIND11_OVERRIDE_PURE(
            void,
            Strategy,
            on_data,
            bars);
    }
};


// Register the Pybind module
PYBIND11_MODULE(backtest_python, m) {


    // Expose Strategy
    pybind11::class_<Strategy, PyStrategy, std::shared_ptr<Strategy>>(m, "Strategy")

        // Strategy constructor
        .def(pybind11::init<OrderManager&>())

        // Strategy API
        .def("buy", &Strategy::buy)
        .def("sell", &Strategy::sell)
        .def("limit_buy", &Strategy::limit_buy)
        .def("limit_sell", &Strategy::limit_sell)
        .def("stop_buy", &Strategy::stop_buy)
        .def("stop_sell", &Strategy::stop_sell);


    // Expose Engine
    pybind11::class_<Engine, std::shared_ptr<Engine>>(m, "Engine")

        // Engine constructor
        .def(pybind11::init<
            std::shared_ptr<MarketDataFeed>,
            std::shared_ptr<OrderManager>,
            std::shared_ptr<Portfolio>,
            std::shared_ptr<Strategy>>())

        // Engine method to run the core test
        .def("run_backtest", &Engine::run_backtest);


    // Expose OrderManager
    pybind11::class_<OrderManager, std::shared_ptr<OrderManager>>(m, "OrderManager")

        // OrderManager constructor
        .def(pybind11::init<>());


    // Expose Portfolio
    pybind11::class_<Portfolio, std::shared_ptr<Portfolio>>(m, "Portfolio")

        // Portfolio constructor
        .def(pybind11::init<double>());


    // Expose MarketDataFeed
    pybind11::class_<MarketDataFeed, std::shared_ptr<MarketDataFeed>>(m, "MarketDataFeed")

        // MarketDataFeed constructor
        .def(pybind11::init<>())

        // MarketDataFeed Load CSV Data method
        .def("load_from_csv", &MarketDataFeed::load_from_csv);


    // Expose MarketDataBar type
    pybind11::class_<MarketDataBar>(m, "MarketDataBar")
        .def_readonly("timestamp", &MarketDataBar::timestamp)
        .def_readonly("open", &MarketDataBar::open)
        .def_readonly("close", &MarketDataBar::close)
        .def_readonly("high", &MarketDataBar::high)
        .def_readonly("low)", &MarketDataBar::low)
        .def_readonly("volume", &MarketDataBar::volume);

}
