#!/bin/bash

source _setup.sh

cd $FIRMWIRE_ROOT
while read content; do
  name_addr=($content)
  image="${name_addr[0]}"
  addr="${name_addr[1]}"
  if [[ ${image:0:1} == "#" ]]; then
      continue
  fi
  run_firmwire \
   --fuzz-triage preaka \
   --fuzz-input "$MY_EXPERIMENT_ROOT/inputs/AAAA" \
   --snapshot-at $addr,$image \
   --gdb-server --stop \
   "$MY_EXPERIMENT_ROOT/firmware/$image"
done < "$MY_EXPERIMENT_ROOT/fuzzing_snapshots.txt"

