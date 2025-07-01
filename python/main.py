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










# Step 1: Implement Strategy

# The engine will subclass the Strategy class from the cpp module
class MyStrategy(backtest_python.Strategy):
    # Constructor for Strategy
    def __int__(self, order_manager):
        # Simply call the cpp base class constructor
        super().init_(order_manager)
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

        # Example strategy:
        if bars["AAPL"].high > 500:
            self.buy("AAPL", 10)










# Step 2: Import Data

# The engine will simulate the implemented trading strategy with only the data
# it has been given. In order to ensure the trading strategy is properly tested,
# import data for each symbol utilized in the trading strategy.
#
# To begin, set the start and end dates for the test. Utilize the following
# convention for setting the start and end dates:
    #     "YEAR-MONTH-DAY" --> "2020-01-01"
start = "2020-01-01"
end = "2020-12-31"
# Next, populate the "symbols" array with each symbol utilized in the trading
# strategy:
    #     ["AAPL", "TSLA", "MSFT"]
symbols = ["AAPL", "TSLA", "MSFT"]
# Finally, an instance of the data class is created, and the appropriate data is
# collected and loaded into a new data feed object
data = Data(symbols, start, end)
data.collect_data()
market_data = backtest_python.MarketDataFeed()
for csv in data.csv_paths:
    market_data.load_from_csv(csv[0], csv[1])










# Step 0: Set Options (will add custon config later)










# Step 3: Run the Engine

# Here, define the amount of cash you wish the Portfolio to begin with
cash = 1000
# Finally, the Engine is initialized with the previously created objects
portfolio = backtest_python.Portfolio(cash)
order_manager = backtest_python.OrderManager()
strategy = backtest_python.Strategy(order_manager)
engine = backtest_python.Engine(market_data, order_manager, portfolio, strategy)
# Run the Engine!
engine.run_backtest()
