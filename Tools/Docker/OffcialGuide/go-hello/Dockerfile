FROM golang:1.24 AS builder
WORKDIR /src
COPY main.go ./
RUN go build -o /bin/hello ./main.go


FROM scratch AS final
WORKDIR /src
COPY --from=builder /bin/hello ./
CMD [ "./hello" ]
