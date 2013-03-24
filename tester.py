#!/usr/bin/python
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
	res = first / second
elif op == "%":
	res = first % second


# Write to res file
f = open(sys.argv[4], "w+")
f.write(str(res))
f.close()
