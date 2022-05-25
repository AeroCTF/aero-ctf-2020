FROM python:3.6

RUN apt update && \
    apt install -y socat

RUN useradd -s /bin/false -m task

WORKDIR /home/task/

ADD requirements.txt ./

RUN pip install -r requirements.txt

ADD main.py ./

RUN chmod 555 main.py

ENTRYPOINT ["socat", "TCP-LISTEN:31337,reuseaddr,fork", "EXEC:'./main.py',su=task"]