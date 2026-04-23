FROM alpine:3.23.3
USER root

RUN apk add --no-cache net-tools iputils git

WORKDIR /app

COPY src/target ./src/target
COPY src/common ./src/common
COPY include ./include
COPY Makefile .

RUN make target

CMD ["sudo ./target", "AA:BB:CC:DD:EE:03"]

