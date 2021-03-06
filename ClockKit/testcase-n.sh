#!/bin/bash

# Ensure that one server and n clients run, and print plausible output.

if [[ $# -eq 0 ]]; then
  exit 1
fi
n=$1
if [[ $# -ge 2 ]]; then
  port=$2
else
  port=4444
fi

conf=$(mktemp /tmp/clockkit.XXXXXX)
srv=$(mktemp /tmp/clockkit.XXXXXX)
clis=''
for i in $(seq $n); do
  cli[i]=$(mktemp /tmp/clockkit.XXXXXX)
  clis+=${cli[i]}
  clis+=' '
done
# Clean up after all possible exits.
trap "rm -f $conf $srv $clis" 0 2 3 15

sed "s/^port:.*/port:$port/" < clockkit.conf > $conf
killall -q -w ckserver ckphaselock

./ckserver $port > $srv &
for i in $(seq $n); do
  ./ckphaselock $conf > ${cli[i]} &
done

sleep 4
killall -w ckserver ckphaselock

a=$(tail -10 $srv | grep -c -P '<time \d+ \d+>\s')
if [[ "$a" != "10" ]]; then
  exit 1
fi

for i in $(seq $n); do
  b=$(tail -20 ${cli[i]} | grep -c -P 'offset: [-\d]+')
  c=$(tail -20 ${cli[i]} | grep -c -P 'time: <time \d+ \d+>')
  if [[ "$b $c" != "10 10" ]]; then
    exit 2
  fi
done
