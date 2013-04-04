#!/usr/bin/python
from __future__ import division
import sys

firstFile = open(sys.argv[1], "r+")
secondFile = open(sys.argv[3], "r+")

first = int(firstFile.readline())
second = int(secondFile.readline())

firstFile.close()
secondFile.close()

# Compute
op = sys.argv[2]
if op == "+":
	res = first + second
elif op == "-":
	res = first - second
elif op == "*":
	res = first * second
elif op == "/":
	res = first // second
	if res < 0 and first % second != 0:
		res = first // second + 1 
elif op == "%":
	res = first % second


# Write to res file
f = open(sys.argv[4], "w+")
f.write(str(res))
f.close()
