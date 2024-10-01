#!/bin/bash

find . -type f -name "*.cpp" | while read file
do
  clang-format -i "$file"
  echo "Formatted: $file"
done