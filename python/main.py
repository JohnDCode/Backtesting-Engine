# Data class for handling backtest data
from DataCollection import Data


# Step 1: Implement Strategy





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
# collected:
data = Data(symbols, start, end)
data.collect_data()





# Step 3: Set Options (will add this later)





# Step 4: Run the Engine