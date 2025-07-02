# --------------------------------------------------------------------

# JDA Backtesting Engine
# /python/main.py
# JohnDavid Abe

# --------------------------------------------------------------------

# Data class for handling backtest data
from DataCollection import Data

# Packages
import sys
import os

# Import the bound engine
sys.path.append(os.path.abspath("../cmake-build-debug"))
import backtest_python










# Step 1: Choose Starting Cash

# First, the user Portfolio must be generated. Choose starting cash for the Portfolio
cash = 1000
portfolio = backtest_python.Portfolio(cash)










# Step 2: Implement Strategy

# The engine will subclass the Strategy class from the cpp module
class MyStrategy(backtest_python.Strategy):
    # Constructor for Strategy
    def __int__(self, order_m):
        # Simply call the cpp base class constructor
        super().init_(order_m)

# Now, this subclass must override the base class "on_data" method
# This method controls the Strategy response to each new bar of data
# Implement your Strategy here
    def on_data(self, bars):
        # The user has the following actions available for the Strategy to perform:

            # self.buy(symbol, # contracts)                       -->     Market Orders
            # self.sell(symbol, # contracts)

            # self.limit_buy(symbol, # contracts, price)          -->     Limit Orders
            # self.limit_sell(symbol, # contracts, price)

            # self.stop_buy(symbol, # contracts, price)           -->     Stop Orders
            # self.stop_sell(symbol, # contracts, price)

        # The user can also access each symbol's data for the current bar via:

            # aapl_bar = bars["AAPL"]       -->     Get the bar data for the symbol "AAPL"

            # aapl_bar.open                 -->     Retrieve data from the bar
            # aapl_bar.close
            # aapl_bar.high
            # aapl_bar.low
            # aapl_bar.volume
            # aapl_bar.timestamp

        # Finally, the user can also access information on their portfolio:

            # portfolio.get_cash()              -->     Get cash on hand
            # portfolio.get_equity(bars)        -->     Get current equity
            # portfolio.get_position("AAPL")    -->     Get position on a particular symbol


        # Example strategy (buying and selling Apple):
        if bars["AAPL"].open < 202 and portfolio.get_cash() > 203:
            self.buy("AAPL", 1)

        if bars["AAPL"].open > 203 and portfolio.get_position("AAPL") > 0:
            self.sell("AAPL", 1)










# Step 3: Import Data

# The engine will simulate the implemented trading strategy in steps of bars.
# The following bar sizes are available:
    # Option            Bar Length          Max Historical Date Available

    # "1m"              1 Minute            7 Days
    # "2m"              2 Minutes           60 Days
    # "60m"             60 Minutes          730 Days
    # "1d"              1 Day               ~50 Years
# Choose the bar size:
barSize = "2m"

# Next, set the start and end dates for the test.
# Use the following convention for setting the dates:
    # "YEAR-MONTH-DAY" --> "2020-01-01"
start = "2025-06-25"
end = "2025-06-26"

# Next, populate the "symbols" array with each symbol utilized in the strategy:
    # ["AAPL", "TSLA", "MSFT"]
symbols = ["AAPL"]

# Finally, an instance of the data class is created, and the appropriate data is collected
data = Data(symbols, start, end, barSize)
data.collect_data()
market_data = backtest_python.MarketDataFeed()
for csv in data.csv_paths:
    market_data.load_from_csv(csv[0], csv[1])










# Step 4: Run the Engine

# # No input is required here. Each component is used to create the engine, and the engine is run
order_manager = backtest_python.OrderManager()
strategy = MyStrategy(order_manager)
engine = backtest_python.Engine(market_data, order_manager, portfolio, strategy)
# # Run the Engine!
engine.run_backtest()
