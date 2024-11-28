#!/bin/bash

# Define test cases
tests=(
    "input.txt 'cat' 'wc -l' output1.txt"
    "input.txt 'grep testing' 'wc -w' output2.txt"
    "input.txt 'head -n 1' 'tail -n 1' output3.txt"
)

# Run test cases
for test in "${tests[@]}"; do
    eval "../pipex $test"
    echo "Test case: ../pipex $test"
    echo "Output:"
    cat $(echo $test | awk '{print $NF}')
    echo "-------------------------"
done
