# pip install pandas_market_calendars
import pandas_market_calendars as mcal
import pandas as pd

nyse = mcal.get_calendar('NYSE')
pd.Series(nyse.schedule(start_date='2017-01-01', end_date='2022-12-31').index.astype('str')).to_csv('market_calendar.csv',index = False, header = False)