FROM alpine:3.23.3
USER root

RUN apk add --no-cache gcc musl-dev make git iputils net-tools linux-headers

WORKDIR /app

COPY ./src/target ./src/target
COPY ./src/common ./src/common
COPY ./include ./include
COPY ./Makefile .

RUN make target
RUN chmod +x ./src/target/script.sh
RUN ./src/target/script.sh

CMD ["sleep", "infinity"]

