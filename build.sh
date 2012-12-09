#!/bin/bash

EXPECTED_ARGS=1
E_BADARGS=65

if [ $# -ne $EXPECTED_ARGS ]
then
  echo "Usage: `basename $0` server|client"
  exit $E_BADARGS
elif [ $1 == "server" ] || [ $1 == "Server" ]
then
    echo "Building Server..."
    make tap_server
    mv tap_server bin/
elif [ $1 == "client" ] || [ $1 == "Client" ]
then
    echo "Building Client..."
    make tap_client
    mv tap_client bin/
else
    echo "Usage: `basename $0` server|client"
fi

