#!/usr/bin/python
from __future__ import division
import sys 
#     0      1    2    3    4   5   6
# progname first op second res mod -b

if len(sys.argv) < 5:
	print("Usage: %s <first> <op> <second> <res> [module] [-b]" % sys.argv[0])
	sys.exit()


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
elif op == "^":
	res = first ** second

# Module file is defined
if len(sys.argv) > 5:
	modFile = open(sys.argv[5], "r+")
	module = int(modFile.readline())
	modFile.close()
	res = res % module

# Write to res file
f = open(sys.argv[4], "w+")
f.write(str(res))
f.close()
