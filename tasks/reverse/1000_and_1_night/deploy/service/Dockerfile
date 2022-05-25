FROM python:3.6

RUN apt update && \
    apt install -y socat

RUN useradd -s /bin/false -m task

WORKDIR /home/task/

ADD check_server.py ./

RUN chmod 555 check_server.py

ENTRYPOINT ["socat", "TCP-LISTEN:31337,reuseaddr,fork", "EXEC:'./check_server.py',su=task"]