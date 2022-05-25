FROM python:3.7-alpine

# Build environment
RUN apk add --no-cache socat gcc musl-dev linux-headers

RUN adduser -s /bin/false -D task

RUN pip install numpy

WORKDIR /home/task/

ADD ./code ./

RUN chmod 555 ./ -R

ENTRYPOINT ["socat", "TCP-LISTEN:31337,reuseaddr,fork", "EXEC:'./main.py',su=task"]
