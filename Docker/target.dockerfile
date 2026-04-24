FROM alpine:3.23.3
USER root

RUN apk add --no-cache gcc musl-dev make git iputils

WORKDIR /app

COPY ./src/target ./src/target
COPY ./src/common ./src/common
COPY ./include ./include
COPY ./Makefile .

RUN make target

CMD ["./src/script.sh"]

