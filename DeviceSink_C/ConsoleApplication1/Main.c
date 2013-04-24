/*   
Copyright 2006 - 2011 Intel Corporation

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#if defined(WIN32)
	#ifndef MICROSTACK_NO_STDAFX
		#include "stdafx.h"
	#endif
	#define _CRTDBG_MAP_ALLOC
	#include <TCHAR.h>
#endif

#if defined(WINSOCK2)
	#include <winsock2.h>
	#include <ws2tcpip.h>
#elif defined(WINSOCK1)
	#include <winsock.h>
	#include <wininet.h>
#endif
#include "ILibParsers.h"

#include "UPnPMicroStack.h"
#include "ILibWebServer.h"
#include "ILibAsyncSocket.h"

#if defined(WIN32)
	#include <crtdbg.h>
#endif

void *MicroStackChain;

void *UPnPmicroStack;

int WaitForExit = 0;
void *ILib_Monitor;
int ILib_IPAddressLength;
int *ILib_IPAddressList;



void UPnPAVTransport_GetCurrentTransportActions(UPnPSessionToken upnptoken,unsigned int InstanceID)
{
	printf("Invoke: UPnPAVTransport_GetCurrentTransportActions(%u);\r\n", InstanceID);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_AVTransport_GetCurrentTransportActions(upnptoken,"Sample String");
}

void UPnPAVTransport_GetDeviceCapabilities(UPnPSessionToken upnptoken,unsigned int InstanceID)
{
	printf("Invoke: UPnPAVTransport_GetDeviceCapabilities(%u);\r\n", InstanceID);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_AVTransport_GetDeviceCapabilities(upnptoken,"Sample String","Sample String","Sample String");
}

void UPnPAVTransport_GetMediaInfo(UPnPSessionToken upnptoken,unsigned int InstanceID)
{
	printf("Invoke: UPnPAVTransport_GetMediaInfo(%u);\r\n", InstanceID);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_AVTransport_GetMediaInfo(upnptoken,250,"Sample String","Sample String","Sample String","Sample String","Sample String","Sample String","Sample String","Sample String");
}

void UPnPAVTransport_GetPositionInfo(UPnPSessionToken upnptoken,unsigned int InstanceID)
{
	printf("Invoke: UPnPAVTransport_GetPositionInfo(%u);\r\n", InstanceID);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_AVTransport_GetPositionInfo(upnptoken,250,"Sample String","Sample String","Sample String","Sample String","Sample String",25000,25000);
}

void UPnPAVTransport_GetTransportInfo(UPnPSessionToken upnptoken,unsigned int InstanceID)
{
	printf("Invoke: UPnPAVTransport_GetTransportInfo(%u);\r\n", InstanceID);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_AVTransport_GetTransportInfo(upnptoken,"Sample String","Sample String","Sample String");
}

void UPnPAVTransport_GetTransportSettings(UPnPSessionToken upnptoken,unsigned int InstanceID)
{
	printf("Invoke: UPnPAVTransport_GetTransportSettings(%u);\r\n", InstanceID);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_AVTransport_GetTransportSettings(upnptoken,"Sample String","Sample String");
}

void UPnPAVTransport_Next(UPnPSessionToken upnptoken,unsigned int InstanceID)
{
	printf("Invoke: UPnPAVTransport_Next(%u);\r\n", InstanceID);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_AVTransport_Next(upnptoken);
}

void UPnPAVTransport_Pause(UPnPSessionToken upnptoken,unsigned int InstanceID)
{
	printf("Invoke: UPnPAVTransport_Pause(%u);\r\n", InstanceID);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_AVTransport_Pause(upnptoken);
}

void UPnPAVTransport_Play(UPnPSessionToken upnptoken,unsigned int InstanceID,char* Speed)
{
	printf("Invoke: UPnPAVTransport_Play(%u,%s);\r\n", InstanceID, Speed);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_AVTransport_Play(upnptoken);
}

void UPnPAVTransport_Previous(UPnPSessionToken upnptoken,unsigned int InstanceID)
{
	printf("Invoke: UPnPAVTransport_Previous(%u);\r\n", InstanceID);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_AVTransport_Previous(upnptoken);
}

void UPnPAVTransport_Seek(UPnPSessionToken upnptoken,unsigned int InstanceID,char* Unit,char* Target)
{
	printf("Invoke: UPnPAVTransport_Seek(%u,%s,%s);\r\n", InstanceID, Unit, Target);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_AVTransport_Seek(upnptoken);
}

void UPnPAVTransport_SetAVTransportURI(UPnPSessionToken upnptoken,unsigned int InstanceID,char* CurrentURI,char* CurrentURIMetaData)
{
	printf("Invoke: UPnPAVTransport_SetAVTransportURI(%u,%s,%s);\r\n", InstanceID, CurrentURI, CurrentURIMetaData);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_AVTransport_SetAVTransportURI(upnptoken);
}

void UPnPAVTransport_SetPlayMode(UPnPSessionToken upnptoken,unsigned int InstanceID,char* NewPlayMode)
{
	printf("Invoke: UPnPAVTransport_SetPlayMode(%u,%s);\r\n", InstanceID, NewPlayMode);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_AVTransport_SetPlayMode(upnptoken);
}

void UPnPAVTransport_Stop(UPnPSessionToken upnptoken,unsigned int InstanceID)
{
	printf("Invoke: UPnPAVTransport_Stop(%u);\r\n", InstanceID);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_AVTransport_Stop(upnptoken);
}

void UPnPConnectionManager_GetCurrentConnectionIDs(UPnPSessionToken upnptoken)
{
	printf("Invoke: UPnPConnectionManager_GetCurrentConnectionIDs();\r\n");
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_ConnectionManager_GetCurrentConnectionIDs(upnptoken,"Sample String");
}

void UPnPConnectionManager_GetCurrentConnectionInfo(UPnPSessionToken upnptoken,int ConnectionID)
{
	printf("Invoke: UPnPConnectionManager_GetCurrentConnectionInfo(%d);\r\n", ConnectionID);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_ConnectionManager_GetCurrentConnectionInfo(upnptoken,25000,25000,"Sample String","Sample String",25000,"Sample String","Sample String");
}

void UPnPConnectionManager_GetProtocolInfo(UPnPSessionToken upnptoken)
{
	printf("Invoke: UPnPConnectionManager_GetProtocolInfo();\r\n");
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_ConnectionManager_GetProtocolInfo(upnptoken,"Sample String","Sample String");
}

void UPnPRenderingControl_GetMute(UPnPSessionToken upnptoken,unsigned int InstanceID,char* Channel)
{
	printf("Invoke: UPnPRenderingControl_GetMute(%u,%s);\r\n", InstanceID, Channel);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_RenderingControl_GetMute(upnptoken,1);
}

void UPnPRenderingControl_GetVolume(UPnPSessionToken upnptoken,unsigned int InstanceID,char* Channel)
{
	printf("Invoke: UPnPRenderingControl_GetVolume(%u,%s);\r\n", InstanceID, Channel);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_RenderingControl_GetVolume(upnptoken,250);
}

void UPnPRenderingControl_GetVolumeDB(UPnPSessionToken upnptoken,unsigned int InstanceID,char* Channel)
{
	printf("Invoke: UPnPRenderingControl_GetVolumeDB(%u,%s);\r\n", InstanceID, Channel);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_RenderingControl_GetVolumeDB(upnptoken,25000);
}

void UPnPRenderingControl_GetVolumeDBRange(UPnPSessionToken upnptoken,unsigned int InstanceID,char* Channel)
{
	printf("Invoke: UPnPRenderingControl_GetVolumeDBRange(%u,%s);\r\n", InstanceID, Channel);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_RenderingControl_GetVolumeDBRange(upnptoken,25000,25000);
}

void UPnPRenderingControl_ListPresets(UPnPSessionToken upnptoken,unsigned int InstanceID)
{
	printf("Invoke: UPnPRenderingControl_ListPresets(%u);\r\n", InstanceID);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_RenderingControl_ListPresets(upnptoken,"Sample String");
}

void UPnPRenderingControl_SelectPreset(UPnPSessionToken upnptoken,unsigned int InstanceID,char* PresetName)
{
	printf("Invoke: UPnPRenderingControl_SelectPreset(%u,%s);\r\n", InstanceID, PresetName);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_RenderingControl_SelectPreset(upnptoken);
}

void UPnPRenderingControl_SetMute(UPnPSessionToken upnptoken,unsigned int InstanceID,char* Channel,int DesiredMute)
{
	printf("Invoke: UPnPRenderingControl_SetMute(%u,%s,%d);\r\n", InstanceID, Channel, DesiredMute);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_RenderingControl_SetMute(upnptoken);
}

void UPnPRenderingControl_SetVolume(UPnPSessionToken upnptoken,unsigned int InstanceID,char* Channel,unsigned short DesiredVolume)
{
	printf("Invoke: UPnPRenderingControl_SetVolume(%u,%s,%u);\r\n", InstanceID, Channel, DesiredVolume);
	
	/* If you intend to make the response later, you MUST reference count upnptoken with calls to ILibWebServer_AddRef() */
	/* and ILibWebServer_Release() */
	
	/* TODO: Place Action Code Here... */
	
	/* UPnPResponse_Error(upnptoken, 404, "Method Not Implemented"); */
	UPnPResponse_RenderingControl_SetVolume(upnptoken);
}



void ILib_IPAddressMonitor(void *data)
{
	int length;
	int *list;
	
	UNREFERENCED_PARAMETER( data );

	length = ILibGetLocalIPAddressList(&list);
	if (length != ILib_IPAddressLength || memcmp((void*)list, (void*)ILib_IPAddressList, sizeof(int)*length) != 0)
	{

UPnPIPAddressListChanged(UPnPmicroStack);
		free(ILib_IPAddressList);
		ILib_IPAddressList = list;
		ILib_IPAddressLength = length;
	}
	else
	{
		free(list);
	}
	ILibLifeTime_Add(ILib_Monitor, NULL, 4, (void*)&ILib_IPAddressMonitor, NULL);
}

void ILib_LinuxQuit(void *data)
{
	UNREFERENCED_PARAMETER( data );

	if(MicroStackChain != NULL)
	{
		ILibStopChain(MicroStackChain);
		MicroStackChain = NULL;
	}
}
void BreakSink(int s)
{
	if(WaitForExit == 0)
	{
		ILibLifeTime_Add(ILib_Monitor, NULL, 0, (void*)&ILib_LinuxQuit, NULL);
		WaitForExit = 1;
	}
}

int main(void) 
{
	struct sigaction setup_action;
    sigset_t block_mask;
     
	MicroStackChain = ILibCreateChain();


	// TODO: Each device must have a unique device identifier (UDN)
	UPnPmicroStack = UPnPCreateMicroStack(MicroStackChain, "MediaMonkey Renderer", "c7cc24ef-6dee-46a1-8d22-dad3b0f034aa", "0000001", 1800, 0);


	UPnPFP_AVTransport_GetCurrentTransportActions = (UPnP_ActionHandler_AVTransport_GetCurrentTransportActions)&UPnPAVTransport_GetCurrentTransportActions;
	UPnPFP_AVTransport_GetDeviceCapabilities = (UPnP_ActionHandler_AVTransport_GetDeviceCapabilities)&UPnPAVTransport_GetDeviceCapabilities;
	UPnPFP_AVTransport_GetMediaInfo = (UPnP_ActionHandler_AVTransport_GetMediaInfo)&UPnPAVTransport_GetMediaInfo;
	UPnPFP_AVTransport_GetPositionInfo = (UPnP_ActionHandler_AVTransport_GetPositionInfo)&UPnPAVTransport_GetPositionInfo;
	UPnPFP_AVTransport_GetTransportInfo = (UPnP_ActionHandler_AVTransport_GetTransportInfo)&UPnPAVTransport_GetTransportInfo;
	UPnPFP_AVTransport_GetTransportSettings = (UPnP_ActionHandler_AVTransport_GetTransportSettings)&UPnPAVTransport_GetTransportSettings;
	UPnPFP_AVTransport_Next = (UPnP_ActionHandler_AVTransport_Next)&UPnPAVTransport_Next;
	UPnPFP_AVTransport_Pause = (UPnP_ActionHandler_AVTransport_Pause)&UPnPAVTransport_Pause;
	UPnPFP_AVTransport_Play = (UPnP_ActionHandler_AVTransport_Play)&UPnPAVTransport_Play;
	UPnPFP_AVTransport_Previous = (UPnP_ActionHandler_AVTransport_Previous)&UPnPAVTransport_Previous;
	UPnPFP_AVTransport_Seek = (UPnP_ActionHandler_AVTransport_Seek)&UPnPAVTransport_Seek;
	UPnPFP_AVTransport_SetAVTransportURI = (UPnP_ActionHandler_AVTransport_SetAVTransportURI)&UPnPAVTransport_SetAVTransportURI;
	UPnPFP_AVTransport_SetPlayMode = (UPnP_ActionHandler_AVTransport_SetPlayMode)&UPnPAVTransport_SetPlayMode;
	UPnPFP_AVTransport_Stop = (UPnP_ActionHandler_AVTransport_Stop)&UPnPAVTransport_Stop;
	UPnPFP_ConnectionManager_GetCurrentConnectionIDs = (UPnP_ActionHandler_ConnectionManager_GetCurrentConnectionIDs)&UPnPConnectionManager_GetCurrentConnectionIDs;
	UPnPFP_ConnectionManager_GetCurrentConnectionInfo = (UPnP_ActionHandler_ConnectionManager_GetCurrentConnectionInfo)&UPnPConnectionManager_GetCurrentConnectionInfo;
	UPnPFP_ConnectionManager_GetProtocolInfo = (UPnP_ActionHandler_ConnectionManager_GetProtocolInfo)&UPnPConnectionManager_GetProtocolInfo;
	UPnPFP_RenderingControl_GetMute = (UPnP_ActionHandler_RenderingControl_GetMute)&UPnPRenderingControl_GetMute;
	UPnPFP_RenderingControl_GetVolume = (UPnP_ActionHandler_RenderingControl_GetVolume)&UPnPRenderingControl_GetVolume;
	UPnPFP_RenderingControl_GetVolumeDB = (UPnP_ActionHandler_RenderingControl_GetVolumeDB)&UPnPRenderingControl_GetVolumeDB;
	UPnPFP_RenderingControl_GetVolumeDBRange = (UPnP_ActionHandler_RenderingControl_GetVolumeDBRange)&UPnPRenderingControl_GetVolumeDBRange;
	UPnPFP_RenderingControl_ListPresets = (UPnP_ActionHandler_RenderingControl_ListPresets)&UPnPRenderingControl_ListPresets;
	UPnPFP_RenderingControl_SelectPreset = (UPnP_ActionHandler_RenderingControl_SelectPreset)&UPnPRenderingControl_SelectPreset;
	UPnPFP_RenderingControl_SetMute = (UPnP_ActionHandler_RenderingControl_SetMute)&UPnPRenderingControl_SetMute;
	UPnPFP_RenderingControl_SetVolume = (UPnP_ActionHandler_RenderingControl_SetVolume)&UPnPRenderingControl_SetVolume;
	
	

// All evented state variables MUST be initialized before UPnPStart is called.
UPnPSetState_AVTransport_LastChange(UPnPmicroStack, "Sample String");
UPnPSetState_ConnectionManager_SourceProtocolInfo(UPnPmicroStack, "Sample String");
UPnPSetState_ConnectionManager_SinkProtocolInfo(UPnPmicroStack, "Sample String");
UPnPSetState_ConnectionManager_CurrentConnectionIDs(UPnPmicroStack, "Sample String");
UPnPSetState_RenderingControl_LastChange(UPnPmicroStack, "Sample String");

	printf("MicroStack 1.0 - MediaMonkey Renderer \r\n\r\n");

ILib_Monitor = ILibCreateLifeTime(MicroStackChain);	ILib_IPAddressLength = ILibGetLocalIPAddressList(&ILib_IPAddressList);
	ILibLifeTime_Add(ILib_Monitor, NULL, 4, (void*)&ILib_IPAddressMonitor, NULL);
	sigemptyset(&block_mask);
	// Block other terminal-generated signals while handler runs.
    sigaddset(&block_mask, SIGINT);
    sigaddset(&block_mask, SIGQUIT);
    setup_action.sa_handler = BreakSink;
    setup_action.sa_mask = block_mask;
    setup_action.sa_flags = 0;
    sigaction(SIGINT, &setup_action, NULL);
	WaitForExit = 0;
	ILibStartChain(MicroStackChain);
	free(ILib_IPAddressList);
	return 0;
}

