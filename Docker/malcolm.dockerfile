FROM alpine:3.23.3
USER root

RUN apk add --no-cache gcc git

WORKDIR /app

COPY src/malcolm ./src/malcolm
COPY src/common ./src/common
COPY include ./include
COPY Makefile .

RUN make ft_malcolm

CMD ["./ft_malcolm", "172.20.0.2", "AA:BB:CC:DD:EE:02", "172.20.0.3", "AA:BB:CC:DD:EE:03"]
