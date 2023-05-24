import os.path as path

ALPHABET = "abcdefghijklmnopqrstuvwxyz"

key_line, ex_line, ex_enc_line, flag_enc_line = open(path.join(path.dirname(__file__), "../distfiles/output.txt")).readlines()[:4]

key = key_line.strip().split("'")[1]
ex = ex_line.strip().split("'")[1]
ex_enc = ex_enc_line.strip().split(": ")[1]
flag_enc = flag_enc_line.strip().split(": ")[1]

def decode(enc):
  result = ""
  for ec, kc in zip(enc, key):
    if ec not in ALPHABET:
      result += ec
    else:
      result += ALPHABET[(ALPHABET.index(ec) - ALPHABET.index(kc)) % 26]
  return result

assert ex == decode(ex_enc)

print(decode(flag_enc))
