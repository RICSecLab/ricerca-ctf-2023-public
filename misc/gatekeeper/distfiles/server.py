import subprocess

def base64_decode(s: str) -> bytes:
  proc = subprocess.run(['base64', '-d'], input=s.encode(), capture_output=True)
  if proc.returncode != 0:
    return ''
  return proc.stdout

if __name__ == '__main__':
  password = input('password: ')

  if password.startswith('b3BlbiBzZXNhbWUh'):
    exit(':(')

  if base64_decode(password) == b'open sesame!':
    print(open('/flag.txt', 'r').read())
  else:
    print('Wrong')
