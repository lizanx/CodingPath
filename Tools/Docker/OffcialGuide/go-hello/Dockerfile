FROM golang:1.24 AS builder
WORKDIR /src
COPY main.go ./
RUN go build -o /bin/program ./main.go


FROM scratch AS final
WORKDIR /src
COPY --from=builder /bin/program ./
CMD [ "./program" ]
