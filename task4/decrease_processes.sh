#!/bin/bash
pids=$(pgrep -f "sleep 100" | head -n 3)
for pid in $pids; do
  kill -9 "$pid"
done