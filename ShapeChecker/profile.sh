#!/bin/bash

clang++ -std=c++11 -fprofile-instr-generate -fcoverage-mapping main.cpp checkShape.cpp validInput.cpp -o main
LLVM_PROFILE_FILE="main.profraw" ./main < data.txt > result.txt
xcrun llvm-profdata merge -sparse main.profraw -o main.profdata
xcrun llvm-cov show ./main -instr-profile=main.profdata
