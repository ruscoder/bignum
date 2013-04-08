#!/usr/bin/python
import sys
import cppbignum as bn

binary = False
if len(sys.argv) > 5:
	binary = sys.argv[5] == '-b'

first = bn.Big(sys.argv[1], binary)
second = bn.Big(sys.argv[3], binary)

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

# SHIT CODE. NIGHT!
if len(sys.argv) > 5:
	if binary:
		if len(sys.argv) > 6:
			mod = bn.Big(sys.argv[6], binary)
			res = res % mod
	else:
		mod = bn.Big(sys.argv[5])
		res = res % mod


# Write to res file
res.toFile(sys.argv[4])

