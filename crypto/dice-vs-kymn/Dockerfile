FROM sagemath/sagemath:latest

RUN sudo apt-get -y update --fix-missing
RUN sudo apt-get -y upgrade
RUN sudo apt-get install -y socat

ADD distfiles/server.sage server.sage

CMD ["socat", "TCP-L:9999,fork,reuseaddr", "EXEC:'sage server.sage'"]
