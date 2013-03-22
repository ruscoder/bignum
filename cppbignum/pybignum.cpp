#include <Python.h>
#include <string>
#include "cppbignum.h"

static PyObject *
bignum_fromFile(PyObject *self, PyObject *args) {
	const char *name;
	if (!PyArg_ParseTuple(args, "s", &name))
		return NULL;
	Big num = Big(name);
	//return Py_BuildValue("O", num);
}

// Initialize python library
// methods which exports to python
static PyMethodDef bignum_methods[] = {
	{"fromFile", bignum_fromFile, METH_VARARGS, "Load from file"},
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


