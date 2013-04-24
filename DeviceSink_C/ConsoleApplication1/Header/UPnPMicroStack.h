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

#ifndef __UPnPMicrostack__
#define __UPnPMicrostack__


#include "ILibAsyncSocket.h"

/*! \file UPnPMicroStack.h 
	\brief MicroStack APIs for Device Implementation
*/

/*! \defgroup MicroStack MicroStack Module
	\{
*/

struct UPnPDataObject;
struct packetheader;

typedef void* UPnPMicroStackToken;
typedef void* UPnPSessionToken;

enum MULTICAST_EVENT_TYPE
{
	MULTICASTEVENT_TYPE_UNKNOWN =-1,
	MULTICASTEVENT_TYPE_GENERAL =0,
	MULTICASTEVENT_TYPE_INFO	=1,
	MULTICASTEVENT_TYPE_WARNING	=2,
	MULTICASTEVENT_TYPE_FAULT	=3,
	MULTICASTEVENT_TYPE_EMERGENCY=4
};
static char *MULTICAST_EVENT_TYPE_DESCRIPTION[5]={"upnp:/general","upnp:/info","upnp:/warning","upnp:/fault","upnp:/emergency"};
typedef void(*UPnPEvent_MulticastGeneric_Handler)(UPnPMicroStackToken sender, char *Origin_ServiceType, int Origin_ServiceVersion, char *Origin_ServiceID, char *Origin_DeviceUDN, enum MULTICAST_EVENT_TYPE eventType, char* VariableName, char *VariableValue);
extern UPnPEvent_MulticastGeneric_Handler UPnPOnEvent_MulticastGeneric;

;


/* Complex Type Parsers */


/* Complex Type Serializers */



/* UPnP Stack Management */
UPnPMicroStackToken UPnPCreateMicroStack(void *Chain, const char* FriendlyName, const char* UDN, const char* SerialNumber, const int NotifyCycleSeconds, const unsigned short PortNum);


void UPnPIPAddressListChanged(UPnPMicroStackToken MicroStackToken);
int UPnPGetLocalPortNumber(UPnPSessionToken token);
int   UPnPGetLocalInterfaceToHost(const UPnPSessionToken UPnPToken);
void* UPnPGetWebServerToken(const UPnPMicroStackToken MicroStackToken);
void UPnPSetTag(const UPnPMicroStackToken token, void *UserToken);
void *UPnPGetTag(const UPnPMicroStackToken token);
UPnPMicroStackToken UPnPGetMicroStackTokenFromSessionToken(const UPnPSessionToken token);

typedef void(*UPnP_ActionHandler_AVTransport_GetCurrentTransportActions) (void* upnptoken,unsigned int InstanceID);
typedef void(*UPnP_ActionHandler_AVTransport_GetDeviceCapabilities) (void* upnptoken,unsigned int InstanceID);
typedef void(*UPnP_ActionHandler_AVTransport_GetMediaInfo) (void* upnptoken,unsigned int InstanceID);
typedef void(*UPnP_ActionHandler_AVTransport_GetPositionInfo) (void* upnptoken,unsigned int InstanceID);
typedef void(*UPnP_ActionHandler_AVTransport_GetTransportInfo) (void* upnptoken,unsigned int InstanceID);
typedef void(*UPnP_ActionHandler_AVTransport_GetTransportSettings) (void* upnptoken,unsigned int InstanceID);
typedef void(*UPnP_ActionHandler_AVTransport_Next) (void* upnptoken,unsigned int InstanceID);
typedef void(*UPnP_ActionHandler_AVTransport_Pause) (void* upnptoken,unsigned int InstanceID);
typedef void(*UPnP_ActionHandler_AVTransport_Play) (void* upnptoken,unsigned int InstanceID,char* Speed);
typedef void(*UPnP_ActionHandler_AVTransport_Previous) (void* upnptoken,unsigned int InstanceID);
typedef void(*UPnP_ActionHandler_AVTransport_Seek) (void* upnptoken,unsigned int InstanceID,char* Unit,char* Target);
typedef void(*UPnP_ActionHandler_AVTransport_SetAVTransportURI) (void* upnptoken,unsigned int InstanceID,char* CurrentURI,char* CurrentURIMetaData);
typedef void(*UPnP_ActionHandler_AVTransport_SetPlayMode) (void* upnptoken,unsigned int InstanceID,char* NewPlayMode);
typedef void(*UPnP_ActionHandler_AVTransport_Stop) (void* upnptoken,unsigned int InstanceID);
typedef void(*UPnP_ActionHandler_ConnectionManager_GetCurrentConnectionIDs) (void* upnptoken);
typedef void(*UPnP_ActionHandler_ConnectionManager_GetCurrentConnectionInfo) (void* upnptoken,int ConnectionID);
typedef void(*UPnP_ActionHandler_ConnectionManager_GetProtocolInfo) (void* upnptoken);
typedef void(*UPnP_ActionHandler_RenderingControl_GetMute) (void* upnptoken,unsigned int InstanceID,char* Channel);
typedef void(*UPnP_ActionHandler_RenderingControl_GetVolume) (void* upnptoken,unsigned int InstanceID,char* Channel);
typedef void(*UPnP_ActionHandler_RenderingControl_GetVolumeDB) (void* upnptoken,unsigned int InstanceID,char* Channel);
typedef void(*UPnP_ActionHandler_RenderingControl_GetVolumeDBRange) (void* upnptoken,unsigned int InstanceID,char* Channel);
typedef void(*UPnP_ActionHandler_RenderingControl_ListPresets) (void* upnptoken,unsigned int InstanceID);
typedef void(*UPnP_ActionHandler_RenderingControl_SelectPreset) (void* upnptoken,unsigned int InstanceID,char* PresetName);
typedef void(*UPnP_ActionHandler_RenderingControl_SetMute) (void* upnptoken,unsigned int InstanceID,char* Channel,int DesiredMute);
typedef void(*UPnP_ActionHandler_RenderingControl_SetVolume) (void* upnptoken,unsigned int InstanceID,char* Channel,unsigned short DesiredVolume);
/* UPnP Set Function Pointers Methods */
extern void (*UPnPFP_PresentationPage) (void* upnptoken,struct packetheader *packet);
extern UPnP_ActionHandler_AVTransport_GetCurrentTransportActions UPnPFP_AVTransport_GetCurrentTransportActions;
extern UPnP_ActionHandler_AVTransport_GetDeviceCapabilities UPnPFP_AVTransport_GetDeviceCapabilities;
extern UPnP_ActionHandler_AVTransport_GetMediaInfo UPnPFP_AVTransport_GetMediaInfo;
extern UPnP_ActionHandler_AVTransport_GetPositionInfo UPnPFP_AVTransport_GetPositionInfo;
extern UPnP_ActionHandler_AVTransport_GetTransportInfo UPnPFP_AVTransport_GetTransportInfo;
extern UPnP_ActionHandler_AVTransport_GetTransportSettings UPnPFP_AVTransport_GetTransportSettings;
extern UPnP_ActionHandler_AVTransport_Next UPnPFP_AVTransport_Next;
extern UPnP_ActionHandler_AVTransport_Pause UPnPFP_AVTransport_Pause;
extern UPnP_ActionHandler_AVTransport_Play UPnPFP_AVTransport_Play;
extern UPnP_ActionHandler_AVTransport_Previous UPnPFP_AVTransport_Previous;
extern UPnP_ActionHandler_AVTransport_Seek UPnPFP_AVTransport_Seek;
extern UPnP_ActionHandler_AVTransport_SetAVTransportURI UPnPFP_AVTransport_SetAVTransportURI;
extern UPnP_ActionHandler_AVTransport_SetPlayMode UPnPFP_AVTransport_SetPlayMode;
extern UPnP_ActionHandler_AVTransport_Stop UPnPFP_AVTransport_Stop;
extern UPnP_ActionHandler_ConnectionManager_GetCurrentConnectionIDs UPnPFP_ConnectionManager_GetCurrentConnectionIDs;
extern UPnP_ActionHandler_ConnectionManager_GetCurrentConnectionInfo UPnPFP_ConnectionManager_GetCurrentConnectionInfo;
extern UPnP_ActionHandler_ConnectionManager_GetProtocolInfo UPnPFP_ConnectionManager_GetProtocolInfo;
extern UPnP_ActionHandler_RenderingControl_GetMute UPnPFP_RenderingControl_GetMute;
extern UPnP_ActionHandler_RenderingControl_GetVolume UPnPFP_RenderingControl_GetVolume;
extern UPnP_ActionHandler_RenderingControl_GetVolumeDB UPnPFP_RenderingControl_GetVolumeDB;
extern UPnP_ActionHandler_RenderingControl_GetVolumeDBRange UPnPFP_RenderingControl_GetVolumeDBRange;
extern UPnP_ActionHandler_RenderingControl_ListPresets UPnPFP_RenderingControl_ListPresets;
extern UPnP_ActionHandler_RenderingControl_SelectPreset UPnPFP_RenderingControl_SelectPreset;
extern UPnP_ActionHandler_RenderingControl_SetMute UPnPFP_RenderingControl_SetMute;
extern UPnP_ActionHandler_RenderingControl_SetVolume UPnPFP_RenderingControl_SetVolume;


void UPnPSetDisconnectFlag(UPnPSessionToken token,void *flag);

/* Invocation Response Methods */
void UPnPResponse_Error(const UPnPSessionToken UPnPToken, const int ErrorCode, const char* ErrorMsg);
void UPnPResponseGeneric(const UPnPSessionToken UPnPToken,const char* ServiceURI,const char* MethodName,const char* Params);
void UPnPResponse_AVTransport_GetCurrentTransportActions(const UPnPSessionToken UPnPToken, const char* Actions);
void UPnPResponse_AVTransport_GetDeviceCapabilities(const UPnPSessionToken UPnPToken, const char* PlayMedia, const char* RecMedia, const char* RecQualityModes);
void UPnPResponse_AVTransport_GetMediaInfo(const UPnPSessionToken UPnPToken, const unsigned int NrTracks, const char* MediaDuration, const char* CurrentURI, const char* CurrentURIMetaData, const char* NextURI, const char* NextURIMetaData, const char* PlayMedium, const char* RecordMedium, const char* WriteStatus);
void UPnPResponse_AVTransport_GetPositionInfo(const UPnPSessionToken UPnPToken, const unsigned int Track, const char* TrackDuration, const char* TrackMetaData, const char* TrackURI, const char* RelTime, const char* AbsTime, const int RelCount, const int AbsCount);
void UPnPResponse_AVTransport_GetTransportInfo(const UPnPSessionToken UPnPToken, const char* CurrentTransportState, const char* CurrentTransportStatus, const char* CurrentSpeed);
void UPnPResponse_AVTransport_GetTransportSettings(const UPnPSessionToken UPnPToken, const char* PlayMode, const char* RecQualityMode);
void UPnPResponse_AVTransport_Next(const UPnPSessionToken UPnPToken);
void UPnPResponse_AVTransport_Pause(const UPnPSessionToken UPnPToken);
void UPnPResponse_AVTransport_Play(const UPnPSessionToken UPnPToken);
void UPnPResponse_AVTransport_Previous(const UPnPSessionToken UPnPToken);
void UPnPResponse_AVTransport_Seek(const UPnPSessionToken UPnPToken);
void UPnPResponse_AVTransport_SetAVTransportURI(const UPnPSessionToken UPnPToken);
void UPnPResponse_AVTransport_SetPlayMode(const UPnPSessionToken UPnPToken);
void UPnPResponse_AVTransport_Stop(const UPnPSessionToken UPnPToken);
void UPnPResponse_ConnectionManager_GetCurrentConnectionIDs(const UPnPSessionToken UPnPToken, const char* ConnectionIDs);
void UPnPResponse_ConnectionManager_GetCurrentConnectionInfo(const UPnPSessionToken UPnPToken, const int RcsID, const int AVTransportID, const char* ProtocolInfo, const char* PeerConnectionManager, const int PeerConnectionID, const char* Direction, const char* Status);
void UPnPResponse_ConnectionManager_GetProtocolInfo(const UPnPSessionToken UPnPToken, const char* Source, const char* Sink);
void UPnPResponse_RenderingControl_GetMute(const UPnPSessionToken UPnPToken, const int CurrentMute);
void UPnPResponse_RenderingControl_GetVolume(const UPnPSessionToken UPnPToken, const unsigned short CurrentVolume);
void UPnPResponse_RenderingControl_GetVolumeDB(const UPnPSessionToken UPnPToken, const short CurrentVolume);
void UPnPResponse_RenderingControl_GetVolumeDBRange(const UPnPSessionToken UPnPToken, const short MinValue, const short MaxValue);
void UPnPResponse_RenderingControl_ListPresets(const UPnPSessionToken UPnPToken, const char* CurrentPresetNameList);
void UPnPResponse_RenderingControl_SelectPreset(const UPnPSessionToken UPnPToken);
void UPnPResponse_RenderingControl_SetMute(const UPnPSessionToken UPnPToken);
void UPnPResponse_RenderingControl_SetVolume(const UPnPSessionToken UPnPToken);

/* State Variable Eventing Methods */
void UPnPSetState_AVTransport_LastChange(UPnPMicroStackToken microstack,char* val);
void UPnPSetState_ConnectionManager_SourceProtocolInfo(UPnPMicroStackToken microstack,char* val);
void UPnPSetState_ConnectionManager_SinkProtocolInfo(UPnPMicroStackToken microstack,char* val);
void UPnPSetState_ConnectionManager_CurrentConnectionIDs(UPnPMicroStackToken microstack,char* val);
void UPnPSetState_RenderingControl_LastChange(UPnPMicroStackToken microstack,char* val);

/* State Variable Multicast-Eventing Methods */





/*! \} */
#endif
