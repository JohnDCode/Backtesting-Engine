# --------------------------------------------------------------------

# JDA Backtesting Engine
# /python/main.py
# JohnDavid Abe

# --------------------------------------------------------------------



import yfinance
import pandas


# Class handling the data fed to the engine to properly complete the backtest
class Data:

    # Tuple of CSV data exports the Data class makes and their corresponding symbol
    csv_paths = []


    # Constructor
    def __init__(self, symbols, start_date, end_date):

        # The symbols to trade
        self.symbols = symbols

        # Start/End date to the backtest
        self.startDate = start_date
        self.endDate = end_date




    # Accessor methods for each property
    def get_symbols(self):
        return self.symbols
    def get_start(self):
        return self.startDate
    def get_end(self):
        return self.endDate

    # Mutator methods for each property
    def set_symbols(self, symbols):
        self.symbols = symbols
    def set_start(self, start):
        self.startDate = start
    def set_end(self, end):
        self.endDate = end


    # Collect data based on the Data object's properties
    def collect_data(self):

        # Loop through each symbol
        for symbol in self.symbols:

            # Get the file name and save it to the list of exported csvs
            file_name = symbol + "_" + self.startDate + "_" + self.endDate
            saved_tuple = (symbol, f"../data/{file_name}.csv")
            self.csv_paths.append(saved_tuple)

            # Retrieve the data from Yahoo finance
            data = yfinance.download(symbol, start=self.startDate, end=self.endDate)

            # Handle MultiIndex columns (e.g., ('Open', 'AAPL')) → 'Open'
            if isinstance(data.columns, pandas.MultiIndex):
                data.columns = data.columns.get_level_values(0)


            # Rename the headers
            data.reset_index(inplace=True)
            data = data.rename(columns={
                "Date": "timestamp",
                "Open": "open",
                "High": "high",
                "Low": "low",
                "Close": "close",
                "Volume": "volume"
            })
            data = data[["timestamp", "open", "high", "low", "close", "volume"]]

            # Export the data to the appropriate csv
            data.to_csv(f"../data/{file_name}.csv", index=False)
