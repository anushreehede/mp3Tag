#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <Python.h>

char apikey[] = "1GL74GpVcM";
//char META[] = "recordings";
/*static PyObject* fingerprint(samplerate, channels, pcmiter, maxlength=MAX_AUDIO_LENGTH)
{
	PyObject* f = audioread.audio_open(path);
}*/
int main(int argc, char* argv[])
{
	char buf[PATH_MAX + 1]; /* not sure about the "+ 1" */
    char *res = realpath(argv[1], buf);
    if (res) {
        std::cout<<"This source is at "<<buf<<"\n";
    } else {
        perror("realpath");
        exit(EXIT_FAILURE);
    }

    PyObject *pName, *pModule, *pFunc, *pArgs, *pResults, *pName1, *pModule1, *pFunc1, *pArgs1, *pValue;
	Py_Initialize();
    
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")"); 
	pName = PyString_FromString("acoustid");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if(pModule == NULL)
    {
        PyErr_Print();
        exit(-1);
    }
    pFunc = PyObject_GetAttrString(pModule, "match");
    if(pFunc == NULL)
    {
        printf("ERROR getting func attribute");
        exit(-1);
    }
    pArgs = PyTuple_New(2);

    PyTuple_SetItem(pArgs, 0, PyString_FromString(apikey));
    PyTuple_SetItem(pArgs, 1, PyString_FromString(buf));
    //PyTuple_SetItem(pArgs, 2, PyString_FromString(META));

    pResults = PyObject_CallObject(pFunc, pArgs);

    char *score = NULL; char *rid = NULL; char *title = NULL; char *artist = NULL;

    pName1 = PyString_FromString("result");
    pModule1 = PyImport_Import(pName1);
    Py_DECREF(pName1);
    if(pModule1 == NULL)
    {
        PyErr_Print();
        exit(-1);
    }
    pFunc1 = PyObject_GetAttrString(pModule1, "results");
    if(pFunc1 == NULL)
    {
        PyErr_Print();
        exit(-1);
    }
    pArgs1 = PyTuple_New(2); // changed from 2
    PyTuple_SetItem(pArgs1, 0, pResults);
    /*PyObject *f1, *f2, *f3, *f4;
    f1 = PyString_FromString("score");
    f2 = PyString_FromString("rid");
    f3 = PyString_FromString("title");
    f4 = PyString_FromString("artist");
    */
    PyTuple_SetItem(pArgs1, 1, PyLong_FromLong(0));
    pValue = PyObject_CallObject(pFunc1, pArgs1); 
    if(pValue == NULL)
    {
        std::cout<<"Found\n";
        exit(-1);
    }
    score = PyString_AsString(pValue);
    if(score == NULL)
      std::cout<<"yoyo\n";
    
    PyTuple_SetItem(pArgs1, 1, PyLong_FromLong(1));
    rid = PyString_AsString(PyObject_CallObject(pFunc1, pArgs1)); 
    if(rid == NULL)
    std::cout<<"yoyo\n";

    PyTuple_SetItem(pArgs1, 1, PyLong_FromLong(2));
    title = PyString_AsString(PyObject_CallObject(pFunc1, pArgs1)); 
    if(title == NULL)
        std::cout<<"yoyo\n";
    else std::cout<<title<<"$^&*\n";

    PyTuple_SetItem(pArgs1, 1, PyLong_FromLong(3));
    artist = PyString_AsString(PyObject_CallObject(pFunc1, pArgs1)); 
    if(artist == NULL)
        std::cout<<"null artist\n";
    else std::cout<<artist<<"$^&*\n";

    //std::cout<<"\n"<<score<<"\n"<<rid<<"\n"<<title<<"\n"<<artist<<"\n";

    Py_Finalize();
    
	return 0;
}