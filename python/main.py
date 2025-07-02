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
cash = 5000
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
            # aapl_bar.bid                 -->     Simulated bid/ask prices with 0.02% spread
            # aapl_bar.ask
            # aapl_bar.volume
            # aapl_bar.timestamp

        # Finally, the user can also access information on their portfolio:

            # portfolio.get_cash()              -->     Get cash on hand
            # portfolio.get_equity(bars)        -->     Get current equity
            # portfolio.get_position("AAPL")    -->     Get position on a particular symbol


        # Example strategy (buying and selling Apple):
        if bars["AAPL"].ask < 100 and portfolio.get_cash() > 500:
            self.buy("AAPL", 5)

        if bars["AAPL"].bid > 120 and portfolio.get_position("AAPL") > 5:
            self.sell("AAPL", 5)











# Step 3: Import Data

# The engine will simulate the implemented trading strategy in steps of bars.
# The following bar sizes are available:
    # Option            Bar Length          Max Historical Date Available

    # "1m"              1 Minute            7 Days
    # "2m"              2 Minutes           60 Days
    # "60m"             60 Minutes          730 Days
    # "1d"              1 Day               ~50 Years
# Choose the bar size:
barSize = "1d"

# Next, set the start and end dates for the test.
# Use the following convention for setting the dates:
    # "YEAR-MONTH-DAY" --> "2020-01-01"
start = "2020-01-01"
end = "2022-01-01"

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

# finish features first, then add reports, then make examples, project done (1 each night)
# make webiste entry with examples, publish github of just the .so file and the python files and the examples and the output of each example once report gen works
# Order flow question
# Partial Fills, ORder Queue Priorty, Latency, Corporate Actions, Buying power, Short Selling, Position Sizing, Lookahead Bias Protection, Suriviosrship Bias Elimination, Data Snoooping & Curve Fitting Control, Smulated Market Impact