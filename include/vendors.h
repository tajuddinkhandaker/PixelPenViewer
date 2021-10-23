#ifndef VENDORS_H
#define VENDORS_H

#include <fstream>
#include <memory>
#include <string>
#include <stdio.h>  /* defines FILENAME_MAX */

// #define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define DEF_NO_COPY(TClass) \
    TClass (const TClass&) = delete; \
    TClass& operator= (const TClass&) = delete;

#include<iostream>

// How to use glad directly from CMAKE
// https://github.com/Dav1dde/glad/issues/186
// Also, https://github.com/Dav1dde/glad/issues/174
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>
// Views
#include "IView.h"

#endif // VENDORS_H