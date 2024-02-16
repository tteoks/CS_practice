#!/bin/bash

TARGET_FILE="Makefile"
CSV_FILE="Stat_sort.csv"
RUN_TMP="run.tmp"

function chk_fail() {
  echo "RETURN CODE: ${?}"
  if [ ${?} -eq 0 ]; then
    echo "SUCCESS to execute binary with NUM_ARRAY: ${1}"
  else
    echo "FAILED to execute binary with NUM_ARRAY: ${1}"
  fi
  echo
}

echo "Num dataset, Bubble sort, Select sort, Insert sort, Heap sort, Shell sort, Radix sort, Quick sort, Merge sort" > ${CSV_FILE}


for IDX in {1000..5000}; do
  echo "##### NUM_ARRAY: ${IDX}"
  sed -i '' "s/^NUM_ARRAY=.*/NUM_ARRAY=${IDX}/g" ${TARGET_FILE}
  make clean
  echo "COMPILE..."
  make 2>/dev/null
  echo

  echo "EXECUTE BINARY..."
  ./main > ${RUN_TMP}
  cat ${RUN_TMP}
  echo

  chk_fail ${IDX}
  RUNTIME_TMP=`cat ${RUN_TMP} |grep "End of fun" | cut -d ":" -f 2`
  echo -n "${IDX}, " >> ${CSV_FILE}
  for RUNTIME in ${RUNTIME_TMP}; do
    echo -n "${RUNTIME}, " >> ${CSV_FILE}
  done
  echo "" >> ${CSV_FILE}
  sleep 0.3
  echo
done
