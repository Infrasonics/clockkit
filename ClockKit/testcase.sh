#!/bin/bash

# Ensure that one server and one client run, and print plausible output.
# Fancier tests would run more clients, parse the outputs,
# and measure how close they are.

if [[ $# -ge 1 ]]; then
  port=$1
else
  port=4444
fi

srv=$(mktemp /tmp/clockkit.XXXXXX)
cli=$(mktemp /tmp/clockkit.XXXXXX)
conf=$(mktemp /tmp/clockkit.XXXXXX)
# Clean up after all possible exits.
trap "rm -f $srv $cli $conf" 0 2 3 15

sed "s/^port:.*/port:$port/" < clockkit.conf > $conf
killall -q -w ckserver ckphaselock
./ckserver $port > $srv &
./ckphaselock $conf > $cli &
sleep 3
killall -w ckserver ckphaselock
a=$(tail -3 $srv | grep -c -P '<time \d+ \d+>\s')
b=$(tail -4 $cli | grep -c -P 'offset: [-\d]+')
c=$(tail -4 $cli | grep -c -P 'time: <time \d+ \d+>')
if [[ "$a $b $c" == "3 2 2" ]]; then
  # Test passed.
  exit 0
fi
exit 1
