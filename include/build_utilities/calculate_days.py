# calculate_days.py
from datetime import datetime

start_date = datetime(2020, 1, 1)
today = datetime.today()
days_since_start = (today - start_date).days

print(days_since_start)
