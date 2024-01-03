#!/bin/bash

TARGET_FILE="Makefile"

function chk_fail() {
  echo "RETURN CODE: ${?}"
  if [ ${?} -eq 0 ]; then
    echo "SUCCESS to execute binary with NUM_ARRAY: ${1}"
  else
    echo "FAILED to execute binary with NUM_ARRAY: ${1}"
  fi
  echo
}

for IDX in {1000..100000}; do
  echo "##### NUM_ARRAY: ${IDX}"
  sed -i '' "s/^NUM_ARRAY=.*/NUM_ARRAY=${IDX}/g" ${TARGET_FILE}
  echo "COMPILE..."
  make 2>/dev/null
  echo

  echo "EXECUTE BINARY..."
  ./main
  echo

  chk_fail ${IDX}
  sleep 0.3
  echo
done
