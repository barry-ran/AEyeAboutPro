#ifndef AEYEFACECAP_H
#define AEYEFACECAP_H

#define CALL_STYLE __stdcall
#ifdef  AEYEFACECOLL_EXPORTS
#ifdef __cplusplus
#define AEYE_API extern "C" __declspec(dllexport)
#else
#define AEYE_API __declspec(dllexport)
#endif
#else
#ifdef __cplusplus
#define AEYE_API extern "C" __declspec(dllimport)
#else
#define AEYE_API __declspec(dllimport)
#endif
#endif

typedef void (__stdcall* AEFaceCallback)(int msgType, const char* msg, void* userData);
typedef void* HAEFaceColl;

AEYE_API void CALL_STYLE AEFaceColl_GetSdkVersion(char* sdkVersion);

AEYE_API void CALL_STYLE AEFaceColl_GetAlgoVersion(char* algoVersion);

AEYE_API int  CALL_STYLE AEFaceColl_Init(HAEFaceColl* handle);

AEYE_API int  CALL_STYLE AEFaceColl_Release(HAEFaceColl handle);

AEYE_API void CALL_STYLE AEFaceColl_SetPreviewWindow(HAEFaceColl handle, void* previewWnd);

AEYE_API void CALL_STYLE AEFaceColl_SetNotifyWindow(HAEFaceColl handle, void* notifyWnd);

AEYE_API void CALL_STYLE AEFaceColl_SetCallback(HAEFaceColl handle, AEFaceCallback callback, void* userData);

AEYE_API void CALL_STYLE AEFaceColl_SetParameters(HAEFaceColl handle, const char* parameters);

AEYE_API int  CALL_STYLE AEFaceColl_OpenCamera(HAEFaceColl handle, int cameraType);

AEYE_API int  CALL_STYLE AEFaceColl_CloseCamera(HAEFaceColl handle);

AEYE_API int  CALL_STYLE AEFaceColl_GetCameraState(HAEFaceColl handle);

AEYE_API int  CALL_STYLE AEFaceColl_StartCollect(HAEFaceColl handle);

AEYE_API int  CALL_STYLE AEFaceColl_StopCollect(HAEFaceColl handle);

#endif