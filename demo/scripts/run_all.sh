#!/bin/sh
# Runs every demo script in parallel and waits for them all. Each script's output goes to
# demo/logs/NAME.log; the images end up in demo/renderings/.
cd "$(dirname "$0")"
mkdir -p ../logs

pids=""
for s in base antialiasing texture_mapping normal_mapping area_light alpha_mapping refraction; do
  ./$s.sh > ../logs/$s.log 2>&1 &
  pids="$pids $!:$s"
done

status=0
for entry in $pids; do
  pid=${entry%%:*}
  name=${entry#*:}
  if wait "$pid"; then
    tail -n 1 "../logs/$name.log"
  else
    echo "$name: FAILED, see demo/logs/$name.log"
    status=1
  fi
done
exit $status
