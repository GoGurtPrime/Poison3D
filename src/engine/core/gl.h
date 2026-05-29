#ifdef _WIN32
    #include <windows.h>  // Must be included before GL on Windows
    #include <GL/gl.h>
    #include <GL/GLU.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif
