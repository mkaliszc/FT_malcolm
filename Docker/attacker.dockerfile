FROM apline:3.23.3
USER root

RUN apk add --no-cache gcc musl-dev libpcap-dev git

COPY . /app

WORKDIR /app

RUN make

CMD ["./ft_malcolm", "172.20.0.2", "AA:BB:CC:DD:EE:02", "172.20.0.3", "AA:BB:CC:DD:EE:03"]