FROM tiangolo/uwsgi-nginx-flask:latest

RUN apt update
RUN groupadd -r ctf && useradd -r -g ctf ctf
RUN pip install Flask

WORKDIR /home/ctf
ADD ./distfiles/app.py    ./
ADD ./distfiles/images    ./images
ADD ./distfiles/templates ./templates
ADD ./distfiles/uwsgi.ini ./
ADD ./challenge/flag.txt  ./
RUN chown -R root:ctf ./
RUN chmod -R 550      ./
