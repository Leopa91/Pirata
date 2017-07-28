// The following ifdef block is created to make the export from the DLL easier
// macro standard method. All the files in this DLL are defined on the command line with YBAOJKSD_EXPORTS
// symbolic compilation. In the use of this DLL
// This symbol should not be defined on any other items. This will allow any other items in the source file that contain this file
// The YBAOJKSD_API function is considered to be imported from the DLL, and this DLL will be defined with this macro
// The symbol is considered to be exported.
#ifdef YBAOJKSD_EXPORTS
#define YBAOJKSD_API __declspec (dllexport)
#else
#define YBAOJKSD_API __declspec (dllimport)
#endif

// This class is derived from YBAOJKSD.dll

#ifdef __cplusplus
extern "C"{
#endif
YBAOJKSD_API short gFindDevice(unsigned int index);
YBAOJKSD_API void  gSetTimeout(unsigned int readtimout,unsigned int wrttimout);
YBAOJKSD_API short gDestroyDevice(void);

YBAOJKSD_API short gReadCardData(char sndmode,short desorundes,char *RtData);
YBAOJKSD_API short gReadPinData(char sndmode,short desorundes,char *RtData);
YBAOJKSD_API short gKeypadPinPlainTextKey(char mode);
YBAOJKSD_API short gKeypadReadKey(char *ReadBuff);
#ifdef __cplusplus
}
#endif