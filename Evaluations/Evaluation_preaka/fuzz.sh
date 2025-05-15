#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <port-number>"
    exit 1
fi

source _setup.sh


fuzz_target="preaka"

IMAGES=(
	"modem.bin"
)



cd $FIRMWIRE_ROOT
for image in ${IMAGES[@]}; do
  mkdir -p "$MY_EXPERIMENT_ROOT/results/"

  echo "Starting fuzzer $1 for image $image"
  run_out="$MY_EXPERIMENT_ROOT/results/${fuzz_target}_run_$1"
  mkdir -p "${run_out}"

  run_afl \
          -i "$MY_EXPERIMENT_ROOT/inputs" \
          -o "${run_out}" \
          -t 86400 \
          -m none \
          -M "main" \
          -U -- "$FIRMWIRE_ROOT/firmwire.py" \
            --fuzz $fuzz_target \
            --fuzz-input @@  \
            --consecutive-ports $1 \
            --restore-snapshot $image \
            "$MY_EXPERIMENT_ROOT/firmware/$image"
  done
