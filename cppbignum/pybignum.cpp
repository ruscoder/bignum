#include <Python.h>
#include <string>
#include "cppbignum.h"

static PyObject *
bignum_bignum(PyObject *self, PyObject *args) {
	return Py_BuildValue("i", 31337);
}

// Initialize python library
// methods which exports to python
static PyMethodDef bignum_methods[] = {
	{"bignum", bignum_bignum, METH_VARARGS, "test"},
	{NULL, NULL, 0, NULL}
};

// Python init func
PyMODINIT_FUNC
initpybignum(void) {
	PyObject *m;
	m = Py_InitModule("pybignum", bignum_methods);
	if (m == NULL)
		return;

}


