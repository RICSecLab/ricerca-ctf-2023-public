FROM python:3.11.2-slim-bullseye

ENV DEBIAN_FRONTENT noninteractive

RUN apt-get update && apt-get install -yqq socat
RUN groupadd -r ctf && useradd -r -g ctf ctf

RUN echo "RicSec{b4s364_c4n_c0nt41n_p4ddin6}" > /flag.txt
RUN chmod 444 /flag.txt

USER ctf
WORKDIR /app
ADD distfiles/server.py .

CMD socat TCP-L:9999,fork,reuseaddr EXEC:"python server.py",pty,ctty,stderr,echo=0
