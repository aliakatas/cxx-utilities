import requests
import os
import json

GITHUB_TOKEN = os.getenv("GH_TOKEN")
print(GITHUB_TOKEN)
if not GITHUB_TOKEN:
    raise ValueError("GitHub token not found. Please set the GH_TOKEN environment variable.")

OWNER = "aliakatas"
REPO = "cxx-utilities"

# API Endpoint
url = f"https://api.github.com/repos/{OWNER}/{REPO}/traffic/clones"
headers = {"Authorization": f"token {GITHUB_TOKEN}"}

response = requests.get(url, headers=headers)

if response.status_code == 200:
   data = response.json()
   clone_count = data['count']
   unique_clones = data['uniques']

   # Prepare badge JSON data
   badge_data = {
      "schemaVersion": 1,
      "label": "clones",
      "message": f"{clone_count} total, {unique_clones} unique",
      "color": "blue"
   }

   # Write badge JSON to file
   with open("clone_stats.json", "w") as file:
      json.dump(badge_data, file, indent=4)
else:
   print(f"Error: {response.status_code} - {response.text}")
