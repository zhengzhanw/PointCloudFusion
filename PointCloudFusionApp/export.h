#ifndef POINTCLOUDFUSIONAPP_EXPORT_H
#define POINTCLOUDFUSIONAPP_EXPORT_H

#ifdef _WIN32
    #ifdef POINTCLOUDFUSIONAPP_LIBRARY
        #define POINTCLOUDFUSIONAPP_EXPORT __declspec(dllexport)
    #else
        #define POINTCLOUDFUSIONAPP_EXPORT __declspec(dllimport)
    #endif
#else
    #define POINTCLOUDFUSIONAPP_EXPORT
#endif


/* Define NULL pointer value */

#ifndef NULL
    #ifdef __cplusplus
        #define NULL   0
    #else
        #define NULL   ((void *)0)
    #endif
#endif

#endif // POINTCLOUDFUSIONAPP_EXPORT_H

