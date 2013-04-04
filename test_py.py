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
elif op == "^":
	res = first ^ second

if len(sys.argv) > 5:
	mod = bn.Big(sys.argv[5])
	res = res % mod


# Write to res file
res.toFile(sys.argv[4])

