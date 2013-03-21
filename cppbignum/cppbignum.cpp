#include <Python.h>


static PyObject *
cppbignum_bignum(PyObject *self, PyObject *args) {
	return Py_BuildValue("i", 31337);
}

// Initialize python library
// methods which exports to python
static PyMethodDef bignum_methods[] = {
	{"bignum", cppbignum_bignum, METH_VARARGS, "test"},
	{NULL, NULL, 0, NULL}
};

// Python init func
PyMODINIT_FUNC
initcppbignum(void) {
	PyObject *m;
	m = Py_InitModule("cppbignum", bignum_methods);
	if (m == NULL)
		return;

}


