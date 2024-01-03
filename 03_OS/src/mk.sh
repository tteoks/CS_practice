#!/bin/bash

BIN_DIR="`pwd`/bin/"


function compile_list() {
  SRC_FILE="${1}"
  DST_FILE="${BIN_DIR}`echo ${SRC_FILE} | cut -d "." -f1`"
  
  echo "Compile: ${SRC_FILE}"

  gcc ${SRC_FILE} -o ${DST_FILE}

}

if [ ! -d ${BIN_DIR} ]; then
  echo "Create bin directory: ${BIN_DIR}"
  mkdir ${BIN_DIR}
fi


SRC_FILES=`ls *.c | grep -v temp`

for SRC_FILE in ${SRC_FILES}; do 
  compile_list ${SRC_FILE}
done
