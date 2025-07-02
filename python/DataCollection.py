# --------------------------------------------------------------------

# JDA Backtesting Engine
# /python/main.py
# JohnDavid Abe

# --------------------------------------------------------------------



import yfinance
import pandas
import os


# Class handling the data fed to the engine to properly complete the backtest
class Data:

    # Tuple of CSV data exports the Data class makes and their corresponding symbol
    csv_paths = []


    # Constructor
    def __init__(self, symbols, start_date, end_date, bar_size):

        # The symbols to trade
        self.symbols = symbols

        # Start/End date to the backtest
        self.startDate = start_date
        self.endDate = end_date

        # Bar size for the test
        self.barSize = bar_size

    # Collect data based on the Data object's properties
    def collect_data(self):

        # Loop through each symbol
        for symbol in self.symbols:

            # Get the file name and save it to the list of exported csvs
            file_name = symbol + "_" + self.startDate + "_" + self.endDate + "_" + self.barSize
            saved_tuple = (symbol, f"../data/{file_name}.csv")
            self.csv_paths.append(saved_tuple)

            # Check if the data already exists in the /data folder
            found = False
            for entry in os.listdir("../data"):
                if f"{file_name}.csv" == entry:
                    found = True
                    break
            if found: continue

            # Retrieve the data from Yahoo finance (throw if args are wrong)
            try:
                # Ensure data filled
                data = yfinance.download(symbol, start=self.startDate, end=self.endDate, interval=self.barSize)
                if data.empty:
                    raise ValueError("Improper data request(s), see step 3 instructions.")

            except Exception:
                print("Improper data request(s), see step 3 instructions.")
                raise


            # Handle MultiIndex columns (e.g., ('Open', 'AAPL')) → 'Open'
            if isinstance(data.columns, pandas.MultiIndex):
                data.columns = data.columns.get_level_values(0)
            data.reset_index(inplace=True)

            # Export the data to the appropriate csv
            data.to_csv(f"../data/{file_name}.csv", index=False)
