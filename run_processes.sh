#!/bin/bash
for i in {1..5}; do
  sleep 10 &
done
wait
echo "$(( $(jobs -p | wc -l) ))" > processed_count.txt
sleep 3600
