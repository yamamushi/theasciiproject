#!/bin/bash

EXPECTED_ARGS=1
E_BADARGS=65

if [ $# -ne $EXPECTED_ARGS ]
then
  echo "Usage: `basename $0` server|client"
  exit $E_BADARGS
elif [ $1 == "server" ] || [ $1 == "Server" ]
then
    echo "Server Launching..."
    cd bin/
    ./tap_server
elif [ $1 == "client" ] || [ $1 == "Client" ]
then
    echo "Client Launching..."
    cd bin/
    ./tap_client
else
    echo "Usage: `basename $0` server|client"
fi

