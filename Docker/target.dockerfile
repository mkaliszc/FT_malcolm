FROM alpine:3.23.3
USER root

RUN apk add --no-cache net-tools iputils git

WORKDIR /app

COPY src/target ./src/target
COPY includes ./includes
COPY Makefile .

RUN make target

CMD ["./target"]

