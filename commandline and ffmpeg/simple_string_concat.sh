#!/bin/bash
GREETING=""
GREETING+=$1
GREETING+=', my name is '
GREETING+=$2
GREETING+=' '
GREETING+=$3

echo $GREETING

#echo $1 'my name is' $2 $3
