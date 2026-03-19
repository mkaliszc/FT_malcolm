FROM apline:3.23.3

RUN apk add --no-cache net-tools iputils

CMD ["sleep", "infinity"]

