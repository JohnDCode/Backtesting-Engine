#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(backtest_python, m) {
    m.doc() = "Python bindings for backtest engine";
    m.def("greet", []() { return "Hello from C++!"; });
}