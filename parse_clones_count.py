import requests
import os

# Replace with your credentials
GITHUB_TOKEN = os.getenv("GH_TOKEN")
if not GITHUB_TOKEN:
    raise ValueError("GitHub token not found. Please set the GITHUB_TOKEN environment variable.")

OWNER = "aliakatas"
REPO = "cxx-utilities"

# API Endpoint
url = f"https://api.github.com/repos/{OWNER}/{REPO}/traffic/clones"
headers = {"Authorization": f"token {GITHUB_TOKEN}"}

response = requests.get(url, headers=headers)

if response.status_code == 200:
    data = response.json()
    print(data)
   #  print(f"Total Clones: {data['count']}")
   #  print(f"Unique Cloners: {data['uniques']}")
else:
    print(f"Error: {response.status_code} - {response.text}")
