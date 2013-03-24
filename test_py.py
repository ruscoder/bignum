#!/usr/bin/python
import sys
import cppbignum as bn

first = bn.Big(sys.argv[1])
second = bn.Big(sys.argv[3])

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
res.toFile(sys.argv[4])

