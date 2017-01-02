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

    PyObject *pName, *pModule, *pFunc, *pArgs, *pResults, *pName1, *pModule1, *pFunc1, *pArgs1;
	Py_Initialize();
	pName = PyString_FromString("acoustid");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    pFunc = PyObject_GetAttrString(pModule, "match");
    pArgs = PyTuple_New(2);

    PyTuple_SetItem(pArgs, 0, PyString_FromString(apikey));
    PyTuple_SetItem(pArgs, 1, PyString_FromString(buf));
    //PyTuple_SetItem(pArgs, 2, PyString_FromString(META));

    pResults = PyObject_CallObject(pFunc, pArgs);
    
    std::cout<<"^&\n";

    char *score = NULL; char *rid = NULL; char *title = NULL; char *artist = NULL;

    pName1 = PyString_FromString("hello");
    pModule1 = PyImport_Import(pName1);
    Py_DECREF(pName1);
    if(pModule1 == NULL)
    {
        PyErr_Print();
        exit(-1);
    }
    std::cout<<"^&\n";
    
    pFunc1 = PyObject_GetAttrString(pModule1, "results");
    if(pFunc1 == NULL)
    {
        printf("ERROR getting func attribute");
        exit(-1);
    }
    std::cout<<"^&\n";
    pArgs1 = PyTuple_New(2);
    std::cout<<"^&\n";
    PyTuple_SetItem(pArgs1, 0, pResults);
    //std::cout<<"#$%\n";
    for(int i=0; i<4; ++i)
    {
    	switch(i)
    	{
    		case 0: PyTuple_SetItem(pArgs1, 1, PyLong_FromLong(0));
    		        score = PyString_AsString(PyObject_CallObject(pFunc1, pArgs1)); 
    		        break;// call get_results, send 0 as param and store return in score
    		case 1: PyTuple_SetItem(pArgs1, 1, PyLong_FromLong(1));
    		        rid = PyString_AsString(PyObject_CallObject(pFunc1, pArgs1)); 
    		        break;// call get_results, send 1 as param and store return in rid
    		case 2: PyTuple_SetItem(pArgs1, 1, PyLong_FromLong(2));
    		        title = PyString_AsString(PyObject_CallObject(pFunc1, pArgs1)); 
    		        break;// call get_results, send 2 as param and store return in title
    		case 3: PyTuple_SetItem(pArgs1, 1, PyLong_FromLong(3));
    		        artist = PyString_AsString(PyObject_CallObject(pFunc1, pArgs1)); 
    		        break;// call get_results, send 3 as param and store return in artist
    		default: break;
    	}
    }

    std::cout<<score<<"\n"<<rid<<"\n"<<title<<"\n"<<artist<<"\n";
    Py_Finalize();
    
	return 0;
}