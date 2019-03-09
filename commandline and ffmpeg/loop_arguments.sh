#!/bin/bash

echo "looping through all arguments"

while [ "$1" != "" ]; do
  echo "Parameter: $1"
  echo "You now have $# positional parameters"
  #shift all parameters down by one
  shift

done
