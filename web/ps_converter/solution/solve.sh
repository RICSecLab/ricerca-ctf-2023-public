#!/bin/bash

if [ -z "$HOST" ]; then
    HOST="localhost"
fi

if [ -z "$PORT" ]; then
    PORT="51514"
fi

curl -F file=@poly.ps -H "X-Forwarded-for: 123.45.67.101" -H "X-Forwarded-for: 123.45.67.101" $HOST:$PORT/converter  | grep RicSec
