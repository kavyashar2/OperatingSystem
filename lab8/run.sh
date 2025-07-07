#!/bin/bash
make
echo "----------FIFO----------"
cat testInput.txt | ./fifo 10
echo "----------End FIFO----------"
echo
echo "----------LRU----------"
cat testInput.txt | ./lru 10
echo "----------End LRU----------"
echo
echo "----------Second Chance----------"
cat testInput.txt | ./sec_chance 10
echo "----------End Second Chance----------"

# Testing with larger cache sizes and displaying actual page faults
echo "FIFO 10K Test with cache size = 10, 50, 100, 250, 500"
cat accessesForReport.txt | ./fifo 10
cat accessesForReport.txt | ./fifo 50
cat accessesForReport.txt | ./fifo 100
cat accessesForReport.txt | ./fifo 250
cat accessesForReport.txt | ./fifo 500
echo

echo "LRU 10K Test with cache size = 10, 50, 100, 250, 500"
cat accessesForReport.txt | ./lru 10
cat accessesForReport.txt | ./lru 50
cat accessesForReport.txt | ./lru 100
cat accessesForReport.txt | ./lru 250
cat accessesForReport.txt | ./lru 500
echo

echo "Second Chance 10K Test with cache size = 10, 50, 100, 250, 500"
cat accessesForReport.txt | ./sec_chance 10
cat accessesForReport.txt | ./sec_chance 50
cat accessesForReport.txt | ./sec_chance 100
cat accessesForReport.txt | ./sec_chance 250
cat accessesForReport.txt | ./sec_chance 500
echo

make clean
echo
