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

#if defined(WIN32) || defined(_WIN32_WCE)
#	ifndef MICROSTACK_NO_STDAFX
#		include "stdafx.h"
#	endif
char* UPnPPLATFORM = "WINDOWS";
#elif defined(__SYMBIAN32__)
char* UPnPPLATFORM = "SYMBIAN";
#else
char* UPnPPLATFORM = "POSIX";
#endif

#if defined(WIN32)
#define snprintf sprintf_s
#define _CRTDBG_MAP_ALLOC
#endif

#if defined(WINSOCK2)
#	include <winsock2.h>
#	include <ws2tcpip.h>
#elif defined(WINSOCK1)
#	include <winsock.h>
#	include <wininet.h>
#endif

#include "ILibParsers.h"
#include "UPnPMicroStack.h"
#include "ILibWebServer.h"
#include "ILibWebClient.h"
#include "ILibAsyncSocket.h"
#include "ILibAsyncUDPSocket.h"

#if defined(WIN32) && !defined(_WIN32_WCE)
#include <crtdbg.h>
#endif

#define UPNP_SSDP_TTL 4
#define UPNP_HTTP_MAXSOCKETS 5
#define UPNP_MAX_SSDP_HEADER_SIZE 4096
#define UPNP_PORT 1900
#define UPNP_MULTICASTEVENT_PORT 1800
#define UPNP_MCASTv4_GROUP "239.255.255.250"
#define UPNP_MCASTv6_GROUP "FF05:0:0:0:0:0:0:C" // Site local
#define UPNP_MCASTv6_GROUPB "[FF05:0:0:0:0:0:0:C]"
#define UPNP_MCASTv6_LINK_GROUP "FF02:0:0:0:0:0:0:C" // Link local
#define UPNP_MCASTv6_LINK_GROUPB "[FF02:0:0:0:0:0:0:C]"
#define UPnP_MAX_SUBSCRIPTION_TIMEOUT 7200
#define UPnPMIN(a,b) (((a)<(b))?(a):(b))

#define LVL3DEBUG(x)
#define INET_SOCKADDR_LENGTH(x) ((x==AF_INET6?sizeof(struct sockaddr_in6):sizeof(struct sockaddr_in)))

#if defined(WIN32)
#pragma warning( push, 3 ) // warning C4310: cast truncates constant value
#endif
//{{{ObjectDefintions}}}
UPnPMicroStackToken UPnPCreateMicroStack(void *Chain, const char* FriendlyName, const char* UDN, const char* SerialNumber, const int NotifyCycleSeconds, const unsigned short PortNum);
/* UPnP Set Function Pointers Methods */
void (*UPnPFP_PresentationPage) (void* upnptoken,struct packetheader *packet);
/*! \var UPnPFP_AVTransport_GetCurrentTransportActions
\brief Dispatch Pointer for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> GetCurrentTransportActions
*/
UPnP_ActionHandler_AVTransport_GetCurrentTransportActions UPnPFP_AVTransport_GetCurrentTransportActions;
/*! \var UPnPFP_AVTransport_GetDeviceCapabilities
\brief Dispatch Pointer for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> GetDeviceCapabilities
*/
UPnP_ActionHandler_AVTransport_GetDeviceCapabilities UPnPFP_AVTransport_GetDeviceCapabilities;
/*! \var UPnPFP_AVTransport_GetMediaInfo
\brief Dispatch Pointer for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> GetMediaInfo
*/
UPnP_ActionHandler_AVTransport_GetMediaInfo UPnPFP_AVTransport_GetMediaInfo;
/*! \var UPnPFP_AVTransport_GetPositionInfo
\brief Dispatch Pointer for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> GetPositionInfo
*/
UPnP_ActionHandler_AVTransport_GetPositionInfo UPnPFP_AVTransport_GetPositionInfo;
/*! \var UPnPFP_AVTransport_GetTransportInfo
\brief Dispatch Pointer for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> GetTransportInfo
*/
UPnP_ActionHandler_AVTransport_GetTransportInfo UPnPFP_AVTransport_GetTransportInfo;
/*! \var UPnPFP_AVTransport_GetTransportSettings
\brief Dispatch Pointer for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> GetTransportSettings
*/
UPnP_ActionHandler_AVTransport_GetTransportSettings UPnPFP_AVTransport_GetTransportSettings;
/*! \var UPnPFP_AVTransport_Next
\brief Dispatch Pointer for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> Next
*/
UPnP_ActionHandler_AVTransport_Next UPnPFP_AVTransport_Next;
/*! \var UPnPFP_AVTransport_Pause
\brief Dispatch Pointer for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> Pause
*/
UPnP_ActionHandler_AVTransport_Pause UPnPFP_AVTransport_Pause;
/*! \var UPnPFP_AVTransport_Play
\brief Dispatch Pointer for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> Play
*/
UPnP_ActionHandler_AVTransport_Play UPnPFP_AVTransport_Play;
/*! \var UPnPFP_AVTransport_Previous
\brief Dispatch Pointer for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> Previous
*/
UPnP_ActionHandler_AVTransport_Previous UPnPFP_AVTransport_Previous;
/*! \var UPnPFP_AVTransport_Seek
\brief Dispatch Pointer for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> Seek
*/
UPnP_ActionHandler_AVTransport_Seek UPnPFP_AVTransport_Seek;
/*! \var UPnPFP_AVTransport_SetAVTransportURI
\brief Dispatch Pointer for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> SetAVTransportURI
*/
UPnP_ActionHandler_AVTransport_SetAVTransportURI UPnPFP_AVTransport_SetAVTransportURI;
/*! \var UPnPFP_AVTransport_SetPlayMode
\brief Dispatch Pointer for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> SetPlayMode
*/
UPnP_ActionHandler_AVTransport_SetPlayMode UPnPFP_AVTransport_SetPlayMode;
/*! \var UPnPFP_AVTransport_Stop
\brief Dispatch Pointer for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> Stop
*/
UPnP_ActionHandler_AVTransport_Stop UPnPFP_AVTransport_Stop;
/*! \var UPnPFP_ConnectionManager_GetCurrentConnectionIDs
\brief Dispatch Pointer for ConnectionManager >> urn:schemas-upnp-org:service:ConnectionManager:1 >> GetCurrentConnectionIDs
*/
UPnP_ActionHandler_ConnectionManager_GetCurrentConnectionIDs UPnPFP_ConnectionManager_GetCurrentConnectionIDs;
/*! \var UPnPFP_ConnectionManager_GetCurrentConnectionInfo
\brief Dispatch Pointer for ConnectionManager >> urn:schemas-upnp-org:service:ConnectionManager:1 >> GetCurrentConnectionInfo
*/
UPnP_ActionHandler_ConnectionManager_GetCurrentConnectionInfo UPnPFP_ConnectionManager_GetCurrentConnectionInfo;
/*! \var UPnPFP_ConnectionManager_GetProtocolInfo
\brief Dispatch Pointer for ConnectionManager >> urn:schemas-upnp-org:service:ConnectionManager:1 >> GetProtocolInfo
*/
UPnP_ActionHandler_ConnectionManager_GetProtocolInfo UPnPFP_ConnectionManager_GetProtocolInfo;
/*! \var UPnPFP_RenderingControl_GetMute
\brief Dispatch Pointer for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> GetMute
*/
UPnP_ActionHandler_RenderingControl_GetMute UPnPFP_RenderingControl_GetMute;
/*! \var UPnPFP_RenderingControl_GetVolume
\brief Dispatch Pointer for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> GetVolume
*/
UPnP_ActionHandler_RenderingControl_GetVolume UPnPFP_RenderingControl_GetVolume;
/*! \var UPnPFP_RenderingControl_GetVolumeDB
\brief Dispatch Pointer for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> GetVolumeDB
*/
UPnP_ActionHandler_RenderingControl_GetVolumeDB UPnPFP_RenderingControl_GetVolumeDB;
/*! \var UPnPFP_RenderingControl_GetVolumeDBRange
\brief Dispatch Pointer for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> GetVolumeDBRange
*/
UPnP_ActionHandler_RenderingControl_GetVolumeDBRange UPnPFP_RenderingControl_GetVolumeDBRange;
/*! \var UPnPFP_RenderingControl_ListPresets
\brief Dispatch Pointer for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> ListPresets
*/
UPnP_ActionHandler_RenderingControl_ListPresets UPnPFP_RenderingControl_ListPresets;
/*! \var UPnPFP_RenderingControl_SelectPreset
\brief Dispatch Pointer for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> SelectPreset
*/
UPnP_ActionHandler_RenderingControl_SelectPreset UPnPFP_RenderingControl_SelectPreset;
/*! \var UPnPFP_RenderingControl_SetMute
\brief Dispatch Pointer for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> SetMute
*/
UPnP_ActionHandler_RenderingControl_SetMute UPnPFP_RenderingControl_SetMute;
/*! \var UPnPFP_RenderingControl_SetVolume
\brief Dispatch Pointer for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> SetVolume
*/
UPnP_ActionHandler_RenderingControl_SetVolume UPnPFP_RenderingControl_SetVolume;


const int UPnPDeviceDescriptionTemplateLengthUX = 1455;
const int UPnPDeviceDescriptionTemplateLength = 601;
const char UPnPDeviceDescriptionTemplate[601]={
	0x68,0x3C,0x3F,0x78,0x6D,0x6C,0x20,0x76,0x65,0x72,0x73,0x69,0x6F,0x6E,0x3D,0x22,0x31,0x2E,0x30,0x22
	,0x20,0x65,0x6E,0x63,0x6F,0x64,0x69,0x6E,0x67,0x3D,0x22,0x75,0x74,0x66,0x2D,0x38,0x22,0x3F,0x3E,0x3C
	,0x72,0x6F,0x6F,0x74,0x20,0x63,0x6F,0x6E,0x66,0x69,0x67,0x49,0x64,0x3D,0x22,0x25,0x64,0x22,0x20,0x78
	,0x6D,0x6C,0x6E,0x73,0x3D,0x22,0x75,0x72,0x6E,0x3A,0x73,0x63,0x68,0x65,0x6D,0x61,0x73,0x2D,0x75,0x70
	,0x6E,0x70,0x2D,0x6F,0x72,0x67,0x3A,0x64,0x65,0x76,0x69,0x63,0x65,0x2D,0x31,0x2D,0x30,0x22,0x3E,0x3C
	,0x73,0x70,0x65,0x63,0x56,0x46,0x18,0x0B,0x3E,0x3C,0x6D,0x61,0x6A,0x6F,0x72,0x3E,0x31,0x3C,0x2F,0x46
	,0x02,0x04,0x3C,0x6D,0x69,0x6E,0x07,0x04,0x00,0x45,0x02,0x02,0x3C,0x2F,0x8D,0x0B,0x00,0x06,0x12,0x00
	,0x08,0x02,0x05,0x54,0x79,0x70,0x65,0x3E,0x1B,0x1C,0x12,0x3A,0x4D,0x65,0x64,0x69,0x61,0x52,0x65,0x6E
	,0x64,0x65,0x72,0x65,0x72,0x3A,0x31,0x3C,0x2F,0x0B,0x0E,0x12,0x3C,0x66,0x72,0x69,0x65,0x6E,0x64,0x6C
	,0x79,0x4E,0x61,0x6D,0x65,0x3E,0x25,0x73,0x3C,0x2F,0x4D,0x04,0x15,0x3C,0x6D,0x61,0x6E,0x75,0x66,0x61
	,0x63,0x74,0x75,0x72,0x65,0x72,0x3E,0x56,0x65,0x6E,0x74,0x69,0x73,0x20,0x05,0x14,0x08,0x2C,0x20,0x49
	,0x6E,0x63,0x2E,0x3C,0x2F,0x4D,0x08,0x00,0xCD,0x0B,0x20,0x55,0x52,0x4C,0x3E,0x68,0x74,0x74,0x70,0x3A
	,0x2F,0x2F,0x77,0x77,0x77,0x2E,0x70,0x6C,0x75,0x74,0x69,0x6E,0x6F,0x73,0x6F,0x66,0x74,0x2E,0x63,0x6F
	,0x6D,0x3C,0x2F,0x10,0x0B,0x0E,0x3C,0x6D,0x6F,0x64,0x65,0x6C,0x44,0x65,0x73,0x63,0x72,0x69,0x70,0x74
	,0xC4,0x45,0x00,0x45,0x2E,0x0C,0x4D,0x6F,0x6E,0x6B,0x65,0x79,0x20,0x55,0x50,0x6E,0x50,0x20,0x48,0x31
	,0x02,0x3C,0x2F,0x11,0x0B,0x00,0x86,0x0F,0x00,0x85,0x31,0x00,0xCC,0x0D,0x00,0x8F,0x0C,0x00,0x47,0x35
	,0x00,0xC5,0x0A,0x0E,0x75,0x6D,0x62,0x65,0x72,0x20,0x2F,0x3E,0x3C,0x73,0x65,0x72,0x69,0x61,0x07,0x04
	,0x00,0xC5,0x40,0x00,0x4D,0x04,0x0A,0x3C,0x55,0x44,0x4E,0x3E,0x75,0x75,0x69,0x64,0x3A,0x84,0x47,0x03
	,0x55,0x44,0x4E,0x45,0x0C,0x00,0x44,0x72,0x04,0x4C,0x69,0x73,0x74,0x49,0x03,0x00,0x89,0x05,0x00,0xDA
	,0x63,0x00,0xC7,0x0D,0x0E,0x3A,0x41,0x56,0x54,0x72,0x61,0x6E,0x73,0x70,0x6F,0x72,0x74,0x3A,0x31,0x85
	,0x1B,0x00,0xCA,0x63,0x00,0xC7,0x16,0x02,0x49,0x64,0x85,0x74,0x00,0xD0,0x0E,0x02,0x49,0x64,0x4C,0x0F
	,0x02,0x3C,0x2F,0x8A,0x0B,0x05,0x3C,0x53,0x43,0x50,0x44,0x84,0x5C,0x00,0x4B,0x17,0x0B,0x2F,0x73,0x63
	,0x70,0x64,0x2E,0x78,0x6D,0x6C,0x3C,0x2F,0x88,0x07,0x08,0x3C,0x63,0x6F,0x6E,0x74,0x72,0x6F,0x6C,0x90
	,0x0A,0x00,0xC7,0x05,0x02,0x3C,0x2F,0x0B,0x08,0x09,0x3C,0x65,0x76,0x65,0x6E,0x74,0x53,0x75,0x62,0xD0
	,0x15,0x00,0x05,0x06,0x02,0x3C,0x2F,0xCC,0x07,0x02,0x3C,0x2F,0xD0,0x41,0x00,0x2B,0x44,0x06,0x43,0x6F
	,0x6E,0x6E,0x65,0x63,0x84,0x7C,0x07,0x4D,0x61,0x6E,0x61,0x67,0x65,0x72,0xB2,0x45,0x00,0xD1,0x10,0x00
	,0x15,0x47,0x00,0x51,0x1A,0x00,0x9F,0x48,0x00,0x12,0x0C,0x00,0x21,0x4A,0x00,0xD2,0x18,0x00,0xBF,0x4B
	,0x00,0x91,0x8F,0x00,0x46,0xF2,0x04,0x69,0x6E,0x67,0x43,0xC6,0x72,0x00,0xF2,0x90,0x00,0x90,0x10,0x00
	,0x15,0x92,0x00,0xD0,0x19,0x00,0x5F,0x93,0x00,0xD1,0x0B,0x00,0xA1,0x94,0x00,0x51,0x18,0x00,0xDE,0x95
	,0x01,0x2F,0x4D,0xDD,0x03,0x2F,0x64,0x65,0xC7,0x05,0x02,0x72,0x6F,0x00,0x00,0x03,0x6F,0x74,0x3E,0x00
	,0x00};
/* AVTransport */
const int UPnPAVTransportDescriptionLengthUX = 12534;
const int UPnPAVTransportDescriptionLength = 2403;
const char UPnPAVTransportDescription[2403] = {
	0x4E,0x48,0x54,0x54,0x50,0x2F,0x31,0x2E,0x31,0x20,0x32,0x30,0x30,0x20,0x20,0x4F,0x4B,0x0D,0x0A,0x43
	,0x4F,0x4E,0x54,0x45,0x4E,0x54,0x2D,0x54,0x59,0x50,0x45,0x3A,0x20,0x20,0x74,0x65,0x78,0x74,0x2F,0x78
	,0x6D,0x6C,0x3B,0x20,0x63,0x68,0x61,0x72,0x73,0x65,0x74,0x3D,0x22,0x75,0x74,0x66,0x2D,0x38,0x22,0x0D
	,0x0A,0x53,0x65,0x72,0x76,0x65,0x72,0x3A,0x20,0x50,0x4F,0x53,0x49,0x58,0x2C,0x20,0x55,0x50,0x6E,0xC5
	,0x12,0x4C,0x2C,0x20,0x4D,0x69,0x63,0x72,0x6F,0x53,0x74,0x61,0x63,0x6B,0x2F,0x31,0x2E,0x30,0x2E,0x34
	,0x31,0x34,0x34,0x0D,0x0A,0x43,0x6F,0x6E,0x74,0x65,0x6E,0x74,0x2D,0x4C,0x65,0x6E,0x67,0x74,0x68,0x3A
	,0x20,0x31,0x32,0x34,0x30,0x33,0x0D,0x0A,0x0D,0x0A,0x3C,0x3F,0x78,0x6D,0x6C,0x20,0x76,0x65,0x72,0x73
	,0x69,0x6F,0x6E,0x3D,0x22,0x31,0x2E,0x30,0x22,0x20,0x65,0x6E,0x63,0x6F,0x64,0x69,0x6E,0x67,0x48,0x1B
	,0x37,0x3F,0x3E,0x3C,0x73,0x63,0x70,0x64,0x20,0x78,0x6D,0x6C,0x6E,0x73,0x3D,0x22,0x75,0x72,0x6E,0x3A
	,0x73,0x63,0x68,0x65,0x6D,0x61,0x73,0x2D,0x75,0x70,0x6E,0x70,0x2D,0x6F,0x72,0x67,0x3A,0x73,0x65,0x72
	,0x76,0x69,0x63,0x65,0x2D,0x31,0x2D,0x30,0x22,0x3E,0x3C,0x73,0x70,0x65,0x63,0x56,0x06,0x15,0x0B,0x3E
	,0x3C,0x6D,0x61,0x6A,0x6F,0x72,0x3E,0x31,0x3C,0x2F,0x46,0x02,0x04,0x3C,0x6D,0x69,0x6E,0x07,0x04,0x00
	,0x45,0x02,0x02,0x3C,0x2F,0x8D,0x0B,0x0A,0x61,0x63,0x74,0x69,0x6F,0x6E,0x4C,0x69,0x73,0x74,0x08,0x03
	,0x1B,0x3E,0x3C,0x6E,0x61,0x6D,0x65,0x3E,0x47,0x65,0x74,0x43,0x75,0x72,0x72,0x65,0x6E,0x74,0x54,0x72
	,0x61,0x6E,0x73,0x70,0x6F,0x72,0x74,0x41,0x05,0x0B,0x03,0x73,0x3C,0x2F,0x45,0x08,0x09,0x3C,0x61,0x72
	,0x67,0x75,0x6D,0x65,0x6E,0x74,0x47,0x0F,0x00,0x87,0x03,0x00,0xC7,0x0F,0x0A,0x49,0x6E,0x73,0x74,0x61
	,0x6E,0x63,0x65,0x49,0x44,0xC8,0x0B,0x04,0x64,0x69,0x72,0x65,0x46,0x18,0x04,0x69,0x6E,0x3C,0x2F,0x8A
	,0x03,0x1C,0x3C,0x72,0x65,0x6C,0x61,0x74,0x65,0x64,0x53,0x74,0x61,0x74,0x65,0x56,0x61,0x72,0x69,0x61
	,0x62,0x6C,0x65,0x3E,0x41,0x5F,0x41,0x52,0x47,0x5F,0x04,0x66,0x01,0x5F,0xCC,0x12,0x00,0x15,0x0B,0x02
	,0x3C,0x2F,0x4A,0x1F,0x00,0xCF,0x21,0x00,0xCF,0x2C,0x00,0x0A,0x21,0x03,0x6F,0x75,0x74,0x62,0x21,0x00
	,0x59,0x40,0x00,0xE1,0x21,0x01,0x2F,0x4E,0x47,0x04,0x2F,0x61,0x63,0x74,0xCB,0x5B,0x00,0xCA,0x58,0x02
	,0x44,0x65,0xC4,0x71,0x0B,0x43,0x61,0x70,0x61,0x62,0x69,0x6C,0x69,0x74,0x69,0x65,0xBF,0x57,0x00,0xBF
	,0x57,0x00,0xAF,0x57,0x09,0x50,0x6C,0x61,0x79,0x4D,0x65,0x64,0x69,0x61,0x37,0x58,0x08,0x50,0x6F,0x73
	,0x73,0x69,0x62,0x6C,0x65,0x04,0x12,0x0B,0x62,0x61,0x63,0x6B,0x53,0x74,0x6F,0x72,0x61,0x67,0x65,0xC7
	,0x14,0x00,0x30,0x7B,0x03,0x52,0x65,0x63,0x7F,0x23,0x00,0x45,0x23,0x06,0x52,0x65,0x63,0x6F,0x72,0x64
	,0xFF,0x22,0x0E,0x65,0x63,0x51,0x75,0x61,0x6C,0x69,0x74,0x79,0x4D,0x6F,0x64,0x65,0x73,0xBF,0x24,0x00
	,0x86,0x24,0x00,0x4E,0x14,0x00,0xBF,0xA0,0x00,0x4A,0xF9,0x00,0x05,0x70,0x04,0x49,0x6E,0x66,0x6F,0xFF
	,0xF5,0x00,0xFF,0xF5,0x00,0xEE,0xF5,0x07,0x4E,0x72,0x54,0x72,0x61,0x63,0x6B,0x38,0xF6,0x08,0x4E,0x75
	,0x6D,0x62,0x65,0x72,0x4F,0x66,0x48,0x11,0x00,0x30,0xBE,0x00,0x05,0xBD,0x04,0x44,0x75,0x72,0x61,0x44
	,0xF5,0x00,0x37,0xBF,0x07,0x43,0x75,0x72,0x72,0x65,0x6E,0x74,0xCF,0x12,0x00,0xB0,0xE0,0x00,0x87,0x11
	,0x03,0x55,0x52,0x49,0xF7,0xE0,0x0A,0x41,0x56,0x54,0x72,0x61,0x6E,0x73,0x70,0x6F,0x72,0x46,0x11,0x00
	,0x7A,0x20,0x08,0x4D,0x65,0x74,0x61,0x44,0x61,0x74,0x61,0x7F,0x22,0x02,0x6F,0x72,0x4E,0x13,0x00,0xF1
	,0x86,0x02,0x65,0x78,0xFB,0x43,0x00,0x84,0x0F,0x00,0xFF,0x44,0x00,0x88,0x20,0x00,0x3F,0x44,0x00,0x92
	,0x22,0x00,0x3A,0x45,0x04,0x50,0x6C,0x61,0x79,0x04,0xFA,0x02,0x75,0x6D,0x77,0xCC,0x00,0x44,0x10,0x0B
	,0x62,0x61,0x63,0x6B,0x53,0x74,0x6F,0x72,0x61,0x67,0x65,0x08,0x13,0x00,0xF0,0xED,0x06,0x52,0x65,0x63
	,0x6F,0x72,0x64,0xBD,0x22,0x00,0xC6,0x10,0x00,0x3F,0x22,0x05,0x57,0x72,0x69,0x74,0x65,0x84,0xFB,0x02
	,0x75,0x73,0xFD,0x21,0x00,0x06,0x55,0x00,0x8D,0x13,0x00,0x61,0xF0,0x00,0x09,0xF3,0x03,0x4C,0x69,0x73
	,0xC5,0x03,0x00,0x87,0xE7,0x00,0x08,0x02,0x00,0xC5,0xF5,0x07,0x47,0x65,0x74,0x50,0x6F,0x73,0x69,0xC4
	,0xF1,0x04,0x49,0x6E,0x66,0x6F,0x08,0xF7,0x00,0xCE,0x0E,0x00,0x8F,0xE2,0x0A,0x49,0x6E,0x73,0x74,0x61
	,0x6E,0x63,0x65,0x49,0x44,0x92,0xE0,0x02,0x69,0x6E,0x63,0xE0,0x0A,0x5F,0x41,0x52,0x47,0x5F,0x54,0x59
	,0x50,0x45,0x5F,0xCC,0x12,0x00,0x30,0xE0,0x05,0x54,0x72,0x61,0x63,0x6B,0xB7,0xDF,0x07,0x43,0x75,0x72
	,0x72,0x65,0x6E,0x74,0xC7,0x10,0x00,0xB5,0x1E,0x04,0x44,0x75,0x72,0x61,0xC4,0xFB,0x00,0xBF,0x20,0x00
	,0xCE,0x12,0x00,0x35,0x41,0x00,0xCA,0xEB,0x00,0x3F,0x43,0x02,0x63,0x6B,0xBA,0xFE,0x00,0x85,0x63,0x03
	,0x55,0x52,0x49,0x7F,0x64,0x00,0x89,0x11,0x00,0xB2,0xFC,0x05,0x6C,0x54,0x69,0x6D,0x65,0x79,0xFB,0x06
	,0x6C,0x61,0x74,0x69,0x76,0x65,0xC4,0x10,0x00,0x08,0xC4,0x00,0xB2,0xFB,0x03,0x41,0x62,0x73,0x3B,0x21
	,0x07,0x41,0x62,0x73,0x6F,0x6C,0x75,0x74,0x3F,0x21,0x08,0x52,0x65,0x6C,0x43,0x6F,0x75,0x6E,0x74,0x7F
	,0x42,0x00,0x05,0x11,0x02,0x65,0x72,0x3D,0x43,0x00,0x3C,0x22,0x00,0x48,0x43,0x00,0x32,0x22,0x00,0xC9
	,0xED,0x03,0x4C,0x69,0x73,0xC5,0x03,0x00,0x87,0xE1,0x00,0x08,0x02,0x00,0x85,0xF0,0x02,0x47,0x65,0x04
	,0xFF,0x0A,0x6E,0x73,0x70,0x6F,0x72,0x74,0x49,0x6E,0x66,0x6F,0x48,0xF1,0x00,0x0E,0x0F,0x00,0xCF,0xFD
	,0x0A,0x49,0x6E,0x73,0x74,0x61,0x6E,0x63,0x65,0x49,0x44,0x12,0xFD,0x02,0x69,0x6E,0x63,0x78,0x0A,0x5F
	,0x41,0x52,0x47,0x5F,0x54,0x59,0x50,0x45,0x5F,0xCC,0x12,0x00,0x30,0xFD,0x00,0x0A,0xEC,0x00,0x06,0x30
	,0x00,0x85,0xF3,0x00,0x37,0xFF,0x00,0x50,0x11,0x00,0x3F,0x23,0x00,0x05,0x23,0x02,0x75,0x73,0x7F,0x23
	,0x00,0x89,0x11,0x00,0xB7,0x46,0x05,0x53,0x70,0x65,0x65,0x64,0x7F,0x44,0x05,0x74,0x50,0x6C,0x61,0x79
	,0x47,0x12,0x00,0xFF,0x9C,0x00,0xD3,0x9C,0x08,0x53,0x65,0x74,0x74,0x69,0x6E,0x67,0x73,0xFF,0x9D,0x00
	,0xFF,0x9D,0x00,0x6E,0xF4,0x00,0x44,0x44,0x03,0x4D,0x6F,0x64,0xB8,0x9A,0x00,0x87,0xAD,0x00,0x8A,0x11
	,0x00,0xF0,0xBD,0x09,0x52,0x65,0x63,0x51,0x75,0x61,0x6C,0x69,0x74,0xBF,0x21,0x00,0x04,0xCF,0x06,0x52
	,0x65,0x63,0x6F,0x72,0x64,0xCD,0x13,0x00,0x7F,0x79,0x00,0x07,0xE7,0x04,0x4E,0x65,0x78,0x74,0x7F,0x75
	,0x00,0x7F,0x75,0x00,0xFF,0xAA,0x00,0xC6,0x7A,0x04,0x61,0x75,0x73,0x65,0xFF,0x31,0x00,0xFF,0x31,0x00
	,0xFF,0x31,0x00,0x89,0xAC,0x00,0xBF,0xD8,0x00,0xBF,0xD8,0x00,0xAE,0xD8,0x05,0x53,0x70,0x65,0x65,0x64
	,0x36,0xF9,0x08,0x54,0x72,0x61,0x6E,0x73,0x70,0x6F,0x72,0x05,0xD8,0x00,0x07,0x12,0x00,0x3F,0x83,0x00
	,0xC8,0xFD,0x07,0x72,0x65,0x76,0x69,0x6F,0x75,0x73,0xBF,0xB5,0x00,0xBF,0xB5,0x00,0x3F,0xE7,0x00,0xC6
	,0x57,0x03,0x65,0x65,0x6B,0xFF,0x83,0x00,0xFF,0x83,0x00,0xEE,0x83,0x04,0x55,0x6E,0x69,0x74,0xBF,0xD5
	,0x02,0x45,0x5F,0x44,0x3D,0x04,0x4D,0x6F,0x64,0x65,0xB2,0xA3,0x05,0x54,0x61,0x72,0x67,0x65,0x7F,0x20
	,0x00,0x47,0x20,0x00,0xC8,0x12,0x00,0x3F,0x72,0x00,0x09,0x72,0x03,0x74,0x41,0x56,0x49,0xBC,0x03,0x55
	,0x52,0x49,0x3F,0xF9,0x00,0x3F,0xF9,0x00,0x2E,0xF9,0x06,0x43,0x75,0x72,0x72,0x65,0x6E,0x8C,0x2D,0x00
	,0xAF,0xC8,0x00,0x8F,0x3E,0x00,0x3A,0x20,0x08,0x4D,0x65,0x74,0x61,0x44,0x61,0x74,0x61,0x3F,0x22,0x01
	,0x72,0x0E,0x13,0x00,0xFF,0x78,0x00,0xCA,0x78,0x04,0x50,0x6C,0x61,0x79,0x46,0xAE,0x00,0xBF,0xEC,0x00
	,0xBF,0xEC,0x00,0xAC,0xEC,0x03,0x4E,0x65,0x77,0xD0,0x2D,0x00,0x6E,0xEE,0x00,0x87,0x87,0x00,0x0A,0x3F
	,0x00,0xBF,0xCC,0x00,0x88,0xCC,0x03,0x74,0x6F,0x70,0x7F,0xC9,0x00,0x7F,0xC9,0x00,0x37,0xFE,0x00,0x87
	,0x87,0x00,0x46,0xF4,0x07,0x73,0x65,0x72,0x76,0x69,0x63,0x65,0xC5,0xE5,0x01,0x54,0x06,0xDA,0x01,0x73
	,0xCC,0xE8,0x10,0x20,0x73,0x65,0x6E,0x64,0x45,0x76,0x65,0x6E,0x74,0x73,0x3D,0x22,0x6E,0x6F,0x22,0x47
	,0xFE,0x00,0x4B,0xEE,0x04,0x53,0x65,0x65,0x6B,0x4D,0x67,0x10,0x61,0x74,0x61,0x54,0x79,0x70,0x65,0x3E
	,0x73,0x74,0x72,0x69,0x6E,0x67,0x3C,0x2F,0x49,0x04,0x0D,0x3C,0x61,0x6C,0x6C,0x6F,0x77,0x65,0x64,0x56
	,0x61,0x6C,0x75,0x65,0xC7,0x9C,0x00,0x8B,0x04,0x0B,0x3E,0x52,0x45,0x4C,0x5F,0x54,0x49,0x4D,0x45,0x3C
	,0x2F,0xCD,0x05,0x00,0x4E,0x09,0x08,0x54,0x52,0x41,0x43,0x4B,0x5F,0x4E,0x52,0x50,0x09,0x01,0x2F,0x52
	,0x17,0x02,0x2F,0x73,0x4E,0xF0,0x00,0x64,0x36,0x04,0x4E,0x65,0x78,0x74,0xCE,0xE1,0x00,0x23,0x36,0x00
	,0x74,0x1A,0x00,0xC4,0xE2,0x11,0x62,0x61,0x63,0x6B,0x53,0x74,0x6F,0x72,0x61,0x67,0x65,0x4D,0x65,0x64
	,0x69,0x75,0x6D,0x3F,0x51,0x06,0x75,0x65,0x3E,0x4E,0x4F,0x4E,0x1E,0x50,0x07,0x55,0x4E,0x4B,0x4E,0x4F
	,0x57,0x4E,0x1D,0x59,0x05,0x43,0x44,0x2D,0x44,0x41,0x9D,0x61,0x03,0x48,0x44,0x44,0x9D,0x69,0x07,0x4E
	,0x45,0x54,0x57,0x4F,0x52,0x4B,0x7F,0x69,0x00,0x98,0x9F,0x06,0x52,0x65,0x63,0x6F,0x72,0x64,0xBF,0x4E
	,0x00,0x92,0x4E,0x0D,0x54,0x5F,0x49,0x4D,0x50,0x4C,0x45,0x4D,0x45,0x4E,0x54,0x45,0x44,0x3F,0x98,0x00
	,0x63,0xCE,0x00,0x4C,0xF3,0x00,0xCF,0xCE,0x03,0x75,0x69,0x34,0x3F,0x98,0x0D,0x3E,0x43,0x75,0x72,0x72
	,0x65,0x6E,0x74,0x54,0x72,0x61,0x63,0x6B,0x20,0x18,0x00,0x0C,0xE6,0x12,0x52,0x61,0x6E,0x67,0x65,0x3E
	,0x3C,0x6D,0x69,0x6E,0x69,0x6D,0x75,0x6D,0x3E,0x30,0x3C,0x2F,0xC8,0x02,0x04,0x3C,0x6D,0x61,0x78,0x05
	,0x05,0x07,0x36,0x35,0x35,0x33,0x35,0x3C,0x2F,0xC8,0x03,0x09,0x3C,0x73,0x74,0x65,0x70,0x3E,0x31,0x3C
	,0x2F,0x05,0x02,0x02,0x3C,0x2F,0x93,0x13,0x00,0x7F,0x30,0x09,0x6B,0x44,0x75,0x72,0x61,0x74,0x69,0x6F
	,0x6E,0x3F,0xE3,0x00,0x19,0xE3,0x07,0x6F,0x73,0x73,0x69,0x62,0x6C,0x65,0x13,0xE5,0x01,0x61,0xFF,0xE4
	,0x00,0xFF,0xE4,0x00,0xFF,0xE4,0x00,0xFF,0xE4,0x00,0xF2,0x9B,0x00,0x84,0x50,0x04,0x4D,0x6F,0x64,0x65
	,0xFF,0xE3,0x00,0xC5,0xE3,0x04,0x52,0x4D,0x41,0x4C,0x1D,0x4E,0x0A,0x52,0x45,0x50,0x45,0x41,0x54,0x5F
	,0x4F,0x4E,0x45,0xE4,0x09,0x02,0x41,0x4C,0x9E,0x13,0x07,0x53,0x48,0x55,0x46,0x46,0x4C,0x45,0x24,0x09
	,0x03,0x5F,0x4E,0x4F,0x06,0x1F,0x00,0x63,0x53,0x07,0x64,0x65,0x66,0x61,0x75,0x6C,0x74,0x4E,0x35,0x00
	,0x4D,0x05,0x00,0xF5,0xF7,0x0F,0x54,0x72,0x61,0x6E,0x73,0x70,0x6F,0x72,0x74,0x53,0x74,0x61,0x74,0x75
	,0x73,0xBF,0xA9,0x05,0x75,0x65,0x3E,0x4F,0x4B,0x1D,0xA9,0x0E,0x45,0x52,0x52,0x4F,0x52,0x5F,0x4F,0x43
	,0x43,0x55,0x52,0x52,0x45,0x44,0x7F,0x91,0x00,0xDF,0xFC,0x0C,0x52,0x65,0x63,0x6F,0x72,0x64,0x51,0x75
	,0x61,0x6C,0x69,0x74,0xBF,0x93,0x00,0x0A,0xE1,0x0B,0x54,0x5F,0x49,0x4D,0x50,0x4C,0x45,0x4D,0x45,0x4E
	,0x54,0x3F,0x30,0x00,0x67,0x65,0x00,0x3F,0xC1,0x00,0xC5,0xA4,0x05,0x54,0x4F,0x50,0x50,0x45,0xDE,0xF5
	,0x0E,0x50,0x41,0x55,0x53,0x45,0x44,0x5F,0x50,0x4C,0x41,0x59,0x42,0x41,0x43,0x5E,0x71,0x00,0x44,0x09
	,0x03,0x49,0x4E,0x47,0x5D,0xD5,0x0A,0x54,0x52,0x41,0x4E,0x53,0x49,0x54,0x49,0x4F,0x4E,0xA0,0x0A,0x10
	,0x4E,0x4F,0x5F,0x4D,0x45,0x44,0x49,0x41,0x5F,0x50,0x52,0x45,0x53,0x45,0x4E,0x54,0x7F,0x85,0x00,0x5F
	,0x85,0x08,0x54,0x72,0x61,0x63,0x6B,0x55,0x52,0x49,0xA3,0xBA,0x00,0x34,0xD4,0x02,0x41,0x56,0x89,0xD4
	,0x00,0x7F,0x19,0x00,0x5C,0x19,0x16,0x62,0x73,0x6F,0x6C,0x75,0x74,0x65,0x43,0x6F,0x75,0x6E,0x74,0x65
	,0x72,0x50,0x6F,0x73,0x69,0x74,0x69,0x6F,0x6E,0x51,0xEF,0x02,0x69,0x34,0xFF,0x33,0x09,0x3E,0x50,0x6F
	,0x73,0x73,0x69,0x62,0x6C,0x65,0xD1,0xD2,0x01,0x73,0x3F,0xD3,0x00,0x3F,0xD3,0x00,0x20,0xD3,0x03,0x79
	,0x65,0x73,0x48,0xD3,0x0A,0x4C,0x61,0x73,0x74,0x43,0x68,0x61,0x6E,0x67,0x65,0xFF,0x7C,0x00,0x98,0xEB
	,0x04,0x4E,0x65,0x78,0x74,0xCE,0x7D,0x08,0x4D,0x65,0x74,0x61,0x44,0x61,0x74,0x61,0x3F,0x99,0x00,0xA2
	,0xB2,0x00,0x46,0x9A,0x02,0x41,0x63,0x84,0x7F,0x01,0x73,0xBF,0xB4,0x00,0x99,0xB4,0x14,0x5F,0x41,0x52
	,0x47,0x5F,0x54,0x59,0x50,0x45,0x5F,0x53,0x65,0x65,0x6B,0x54,0x61,0x72,0x67,0x65,0x74,0x7F,0xB6,0x00
	,0x60,0xB6,0x04,0x54,0x69,0x6D,0x65,0x99,0xB5,0x00,0x7F,0xEA,0x00,0x47,0xEA,0x00,0x86,0xB4,0x10,0x4D
	,0x65,0x64,0x69,0x75,0x6D,0x57,0x72,0x69,0x74,0x65,0x53,0x74,0x61,0x74,0x75,0xFF,0xB5,0x00,0xFF,0xB5
	,0x00,0xAC,0x65,0x00,0x7F,0x9C,0x00,0x2F,0x4B,0x05,0x6C,0x61,0x74,0x69,0x76,0xFF,0x65,0x00,0x2F,0xB7
	,0x02,0x63,0x6B,0xFF,0xD1,0x00,0xE7,0xD1,0x00,0xC4,0x80,0x05,0x61,0x44,0x75,0x72,0x61,0x7F,0x9B,0x00
	,0x9C,0xEC,0x00,0xC9,0xEA,0x09,0x50,0x6C,0x61,0x79,0x53,0x70,0x65,0x65,0x64,0x3F,0x9A,0x04,0x75,0x65
	,0x3E,0x31,0xBF,0x96,0x00,0x60,0x7B,0x07,0x43,0x6F,0x75,0x6E,0x74,0x65,0x72,0xD9,0xE1,0x02,0x69,0x34
	,0xBF,0xFB,0x09,0x3E,0x4E,0x75,0x6D,0x62,0x65,0x72,0x4F,0x66,0x45,0x7B,0x00,0x92,0xDE,0x03,0x75,0x69
	,0x34,0xD8,0xDD,0x12,0x52,0x61,0x6E,0x67,0x65,0x3E,0x3C,0x6D,0x69,0x6E,0x69,0x6D,0x75,0x6D,0x3E,0x30
	,0x3C,0x2F,0xC8,0x02,0x04,0x3C,0x6D,0x61,0x78,0x05,0x05,0x07,0x36,0x35,0x35,0x33,0x35,0x3C,0x2F,0xC8
	,0x03,0x02,0x3C,0x2F,0x13,0x10,0x00,0x74,0xDE,0x15,0x50,0x6F,0x73,0x73,0x69,0x62,0x6C,0x65,0x52,0x65
	,0x63,0x6F,0x72,0x64,0x53,0x74,0x6F,0x72,0x61,0x67,0x65,0x05,0x91,0x00,0xFF,0x74,0x12,0x75,0x65,0x3E
	,0x4E,0x4F,0x54,0x5F,0x49,0x4D,0x50,0x4C,0x45,0x4D,0x45,0x4E,0x54,0x45,0x44,0x73,0x78,0x09,0x2F,0x73
	,0x65,0x72,0x76,0x69,0x63,0x65,0x53,0x44,0xF9,0x01,0x54,0x08,0x05,0x01,0x63,0x00,0x00,0x03,0x70,0x64
	,0x3E,0x00,0x00};
/* ConnectionManager */
const int UPnPConnectionManagerDescriptionLengthUX = 3525;
const int UPnPConnectionManagerDescriptionLength = 934;
const char UPnPConnectionManagerDescription[934] = {
	0x4E,0x48,0x54,0x54,0x50,0x2F,0x31,0x2E,0x31,0x20,0x32,0x30,0x30,0x20,0x20,0x4F,0x4B,0x0D,0x0A,0x43
	,0x4F,0x4E,0x54,0x45,0x4E,0x54,0x2D,0x54,0x59,0x50,0x45,0x3A,0x20,0x20,0x74,0x65,0x78,0x74,0x2F,0x78
	,0x6D,0x6C,0x3B,0x20,0x63,0x68,0x61,0x72,0x73,0x65,0x74,0x3D,0x22,0x75,0x74,0x66,0x2D,0x38,0x22,0x0D
	,0x0A,0x53,0x65,0x72,0x76,0x65,0x72,0x3A,0x20,0x50,0x4F,0x53,0x49,0x58,0x2C,0x20,0x55,0x50,0x6E,0xC5
	,0x12,0x4B,0x2C,0x20,0x4D,0x69,0x63,0x72,0x6F,0x53,0x74,0x61,0x63,0x6B,0x2F,0x31,0x2E,0x30,0x2E,0x34
	,0x31,0x34,0x34,0x0D,0x0A,0x43,0x6F,0x6E,0x74,0x65,0x6E,0x74,0x2D,0x4C,0x65,0x6E,0x67,0x74,0x68,0x3A
	,0x20,0x33,0x33,0x39,0x35,0x0D,0x0A,0x0D,0x0A,0x3C,0x3F,0x78,0x6D,0x6C,0x20,0x76,0x65,0x72,0x73,0x69
	,0x6F,0x6E,0x3D,0x22,0x31,0x2E,0x30,0x22,0x20,0x65,0x6E,0x63,0x6F,0x64,0x69,0x6E,0x67,0x08,0x1B,0x37
	,0x3F,0x3E,0x3C,0x73,0x63,0x70,0x64,0x20,0x78,0x6D,0x6C,0x6E,0x73,0x3D,0x22,0x75,0x72,0x6E,0x3A,0x73
	,0x63,0x68,0x65,0x6D,0x61,0x73,0x2D,0x75,0x70,0x6E,0x70,0x2D,0x6F,0x72,0x67,0x3A,0x73,0x65,0x72,0x76
	,0x69,0x63,0x65,0x2D,0x31,0x2D,0x30,0x22,0x3E,0x3C,0x73,0x70,0x65,0x63,0x56,0x06,0x15,0x0B,0x3E,0x3C
	,0x6D,0x61,0x6A,0x6F,0x72,0x3E,0x31,0x3C,0x2F,0x46,0x02,0x04,0x3C,0x6D,0x69,0x6E,0x07,0x04,0x00,0x45
	,0x02,0x02,0x3C,0x2F,0x8D,0x0B,0x0A,0x61,0x63,0x74,0x69,0x6F,0x6E,0x4C,0x69,0x73,0x74,0x08,0x03,0x16
	,0x3E,0x3C,0x6E,0x61,0x6D,0x65,0x3E,0x47,0x65,0x74,0x43,0x75,0x72,0x72,0x65,0x6E,0x74,0x43,0x6F,0x6E
	,0x6E,0x65,0xC5,0x09,0x05,0x49,0x44,0x73,0x3C,0x2F,0x85,0x07,0x09,0x3C,0x61,0x72,0x67,0x75,0x6D,0x65
	,0x6E,0x74,0x87,0x0E,0x00,0x87,0x03,0x00,0x07,0x0F,0x00,0x95,0x0C,0x03,0x64,0x69,0x72,0x86,0x11,0x06
	,0x3E,0x6F,0x75,0x74,0x3C,0x2F,0xCA,0x03,0x16,0x3C,0x72,0x65,0x6C,0x61,0x74,0x65,0x64,0x53,0x74,0x61
	,0x74,0x65,0x56,0x61,0x72,0x69,0x61,0x62,0x6C,0x65,0x3E,0x56,0x1F,0x00,0xD5,0x0A,0x02,0x3C,0x2F,0x0A
	,0x20,0x01,0x2F,0x4E,0x26,0x04,0x2F,0x61,0x63,0x74,0x0B,0x3A,0x00,0x1C,0x37,0x03,0x6E,0x66,0x6F,0x71
	,0x37,0x00,0x12,0x37,0x02,0x69,0x6E,0xE2,0x36,0x06,0x41,0x5F,0x41,0x52,0x47,0x5F,0xC4,0x9C,0x01,0x5F
	,0x4E,0x13,0x00,0xA1,0x37,0x00,0x0F,0x5A,0x05,0x52,0x63,0x73,0x49,0x44,0x37,0x58,0x00,0x4B,0x21,0x03
	,0x52,0x63,0x73,0xB4,0x1F,0x0B,0x41,0x56,0x54,0x72,0x61,0x6E,0x73,0x70,0x6F,0x72,0x74,0xBF,0x21,0x00
	,0xC5,0x42,0x00,0xCF,0x13,0x00,0x30,0x43,0x08,0x50,0x72,0x6F,0x74,0x6F,0x63,0x6F,0x6C,0x0C,0x72,0x00
	,0xFA,0x44,0x00,0x8E,0x13,0x00,0x31,0x23,0x03,0x65,0x65,0x72,0x8A,0xCD,0x07,0x4D,0x61,0x6E,0x61,0x67
	,0x65,0x72,0x3F,0x6A,0x03,0x50,0x45,0x5F,0xD3,0x14,0x00,0xBE,0x26,0x00,0x7F,0x8F,0x00,0xBF,0xB0,0x00
	,0x84,0xE2,0x01,0x44,0x48,0xCE,0x00,0xBF,0xB1,0x03,0x50,0x45,0x5F,0xCB,0x12,0x00,0x30,0xD2,0x00,0xC4
	,0xE7,0x02,0x75,0x73,0x7F,0x68,0x00,0x8D,0xF3,0x00,0x88,0x14,0x00,0xA1,0xF4,0x00,0x49,0xF7,0x03,0x4C
	,0x69,0x73,0xC5,0x03,0x00,0x07,0xED,0x00,0x08,0x02,0x00,0x05,0xFA,0x03,0x47,0x65,0x74,0xD4,0xB7,0x00
	,0xCE,0x0E,0x00,0x10,0x35,0x05,0x6F,0x75,0x72,0x63,0x65,0xF7,0xE5,0x00,0x46,0x0F,0x00,0x7E,0xC1,0x04
	,0x53,0x69,0x6E,0x6B,0xF8,0x1F,0x03,0x69,0x6E,0x6B,0xAF,0xE0,0x00,0x18,0x52,0x00,0x47,0x54,0x00,0x86
	,0x57,0x07,0x73,0x65,0x72,0x76,0x69,0x63,0x65,0x85,0xFD,0x01,0x54,0x46,0xF1,0x01,0x73,0x0C,0xF5,0x10
	,0x20,0x73,0x65,0x6E,0x64,0x45,0x76,0x65,0x6E,0x74,0x73,0x3D,0x22,0x6E,0x6F,0x22,0xC7,0xF3,0x00,0x9D
	,0x78,0x00,0x47,0xF5,0x10,0x61,0x74,0x61,0x54,0x79,0x70,0x65,0x3E,0x73,0x74,0x72,0x69,0x6E,0x67,0x3C
	,0x2F,0x49,0x04,0x0D,0x3C,0x61,0x6C,0x6C,0x6F,0x77,0x65,0x64,0x56,0x61,0x6C,0x75,0x65,0x87,0x6A,0x00
	,0x8B,0x04,0x05,0x3E,0x4F,0x4B,0x3C,0x2F,0x4D,0x04,0x00,0xCE,0x07,0x15,0x43,0x6F,0x6E,0x74,0x65,0x6E
	,0x74,0x46,0x6F,0x72,0x6D,0x61,0x74,0x4D,0x69,0x73,0x6D,0x61,0x74,0x63,0x68,0x9D,0x0C,0x14,0x49,0x6E
	,0x73,0x75,0x66,0x66,0x69,0x63,0x69,0x65,0x6E,0x74,0x42,0x61,0x6E,0x64,0x77,0x69,0x64,0x74,0x9E,0x0C
	,0x05,0x55,0x6E,0x72,0x65,0x6C,0x45,0xF6,0x07,0x43,0x68,0x61,0x6E,0x6E,0x65,0x6C,0x9F,0x0B,0x05,0x6B
	,0x6E,0x6F,0x77,0x6E,0x90,0x2D,0x01,0x2F,0x12,0x3A,0x02,0x2F,0x73,0x4E,0xE0,0x00,0x39,0x5B,0x02,0x49
	,0x44,0x11,0x5A,0x02,0x69,0x34,0x0C,0x59,0x00,0xBF,0x1A,0x01,0x44,0x88,0xFC,0x00,0xFF,0x73,0x00,0x85
	,0x5F,0x03,0x70,0x75,0x74,0x9D,0x74,0x06,0x4F,0x75,0x74,0x70,0x75,0x74,0xFF,0x4F,0x00,0xE3,0xAA,0x03
	,0x52,0x63,0x73,0x3F,0x4E,0x00,0x8C,0xC3,0x03,0x79,0x65,0x73,0xC8,0xC3,0x06,0x53,0x6F,0x75,0x72,0x63
	,0x65,0x0E,0xE8,0x00,0xA1,0xC1,0x00,0xB6,0x1A,0x03,0x69,0x6E,0x6B,0x3F,0x1A,0x00,0x2F,0xF8,0x00,0xBF
	,0x1B,0x00,0xB9,0xB8,0x07,0x4D,0x61,0x6E,0x61,0x67,0x65,0x72,0x7F,0x38,0x00,0x63,0xD5,0x0B,0x41,0x56
	,0x54,0x72,0x61,0x6E,0x73,0x70,0x6F,0x72,0x74,0xBF,0x87,0x00,0x97,0x87,0x07,0x43,0x75,0x72,0x72,0x65
	,0x6E,0x74,0x4C,0xEF,0x01,0x73,0x33,0x88,0x09,0x2F,0x73,0x65,0x72,0x76,0x69,0x63,0x65,0x53,0x44,0xF6
	,0x01,0x54,0x08,0x05,0x01,0x63,0x00,0x00,0x03,0x70,0x64,0x3E,0x00,0x00};
/* RenderingControl */
const int UPnPRenderingControlDescriptionLengthUX = 5089;
const int UPnPRenderingControlDescriptionLength = 1020;
const char UPnPRenderingControlDescription[1020] = {
	0x4E,0x48,0x54,0x54,0x50,0x2F,0x31,0x2E,0x31,0x20,0x32,0x30,0x30,0x20,0x20,0x4F,0x4B,0x0D,0x0A,0x43
	,0x4F,0x4E,0x54,0x45,0x4E,0x54,0x2D,0x54,0x59,0x50,0x45,0x3A,0x20,0x20,0x74,0x65,0x78,0x74,0x2F,0x78
	,0x6D,0x6C,0x3B,0x20,0x63,0x68,0x61,0x72,0x73,0x65,0x74,0x3D,0x22,0x75,0x74,0x66,0x2D,0x38,0x22,0x0D
	,0x0A,0x53,0x65,0x72,0x76,0x65,0x72,0x3A,0x20,0x50,0x4F,0x53,0x49,0x58,0x2C,0x20,0x55,0x50,0x6E,0xC5
	,0x12,0x4B,0x2C,0x20,0x4D,0x69,0x63,0x72,0x6F,0x53,0x74,0x61,0x63,0x6B,0x2F,0x31,0x2E,0x30,0x2E,0x34
	,0x31,0x34,0x34,0x0D,0x0A,0x43,0x6F,0x6E,0x74,0x65,0x6E,0x74,0x2D,0x4C,0x65,0x6E,0x67,0x74,0x68,0x3A
	,0x20,0x34,0x39,0x35,0x39,0x0D,0x0A,0x0D,0x0A,0x3C,0x3F,0x78,0x6D,0x6C,0x20,0x76,0x65,0x72,0x73,0x69
	,0x6F,0x6E,0x3D,0x22,0x31,0x2E,0x30,0x22,0x20,0x65,0x6E,0x63,0x6F,0x64,0x69,0x6E,0x67,0x08,0x1B,0x37
	,0x3F,0x3E,0x3C,0x73,0x63,0x70,0x64,0x20,0x78,0x6D,0x6C,0x6E,0x73,0x3D,0x22,0x75,0x72,0x6E,0x3A,0x73
	,0x63,0x68,0x65,0x6D,0x61,0x73,0x2D,0x75,0x70,0x6E,0x70,0x2D,0x6F,0x72,0x67,0x3A,0x73,0x65,0x72,0x76
	,0x69,0x63,0x65,0x2D,0x31,0x2D,0x30,0x22,0x3E,0x3C,0x73,0x70,0x65,0x63,0x56,0x06,0x15,0x0B,0x3E,0x3C
	,0x6D,0x61,0x6A,0x6F,0x72,0x3E,0x31,0x3C,0x2F,0x46,0x02,0x04,0x3C,0x6D,0x69,0x6E,0x07,0x04,0x00,0x45
	,0x02,0x02,0x3C,0x2F,0x8D,0x0B,0x0A,0x61,0x63,0x74,0x69,0x6F,0x6E,0x4C,0x69,0x73,0x74,0x08,0x03,0x10
	,0x3E,0x3C,0x6E,0x61,0x6D,0x65,0x3E,0x47,0x65,0x74,0x4D,0x75,0x74,0x65,0x3C,0x2F,0x85,0x03,0x09,0x3C
	,0x61,0x72,0x67,0x75,0x6D,0x65,0x6E,0x74,0x87,0x0A,0x00,0x87,0x03,0x00,0x07,0x0B,0x0A,0x49,0x6E,0x73
	,0x74,0x61,0x6E,0x63,0x65,0x49,0x44,0xC8,0x0B,0x04,0x64,0x69,0x72,0x65,0x86,0x13,0x04,0x69,0x6E,0x3C
	,0x2F,0x8A,0x03,0x1C,0x3C,0x72,0x65,0x6C,0x61,0x74,0x65,0x64,0x53,0x74,0x61,0x74,0x65,0x56,0x61,0x72
	,0x69,0x61,0x62,0x6C,0x65,0x3E,0x41,0x5F,0x41,0x52,0x47,0x5F,0x04,0x61,0x01,0x5F,0xCC,0x12,0x00,0x15
	,0x0B,0x02,0x3C,0x2F,0x4A,0x1F,0x00,0xCF,0x21,0x07,0x43,0x68,0x61,0x6E,0x6E,0x65,0x6C,0x3F,0x21,0x02
	,0x45,0x5F,0x09,0x12,0x00,0x71,0x20,0x05,0x75,0x72,0x72,0x65,0x6E,0x0D,0x4E,0x00,0x4A,0x42,0x03,0x6F
	,0x75,0x74,0xA2,0x42,0x00,0xC6,0x5C,0x00,0x61,0x3E,0x01,0x2F,0xCE,0x63,0x04,0x2F,0x61,0x63,0x74,0x8B
	,0x73,0x00,0x8A,0x70,0x05,0x56,0x6F,0x6C,0x75,0x6D,0x3F,0x71,0x00,0x3F,0x71,0x00,0x3F,0x71,0x00,0x3F
	,0x71,0x00,0x39,0x71,0x00,0x8E,0x4E,0x00,0xAF,0x71,0x00,0xC8,0x5D,0x00,0x3F,0x72,0x00,0x10,0x72,0x02
	,0x44,0x42,0xBF,0x72,0x00,0xBF,0x72,0x00,0xBF,0x72,0x00,0xBF,0x72,0x00,0xBF,0x72,0x00,0xBC,0x72,0x02
	,0x44,0x42,0x3F,0x73,0x00,0x14,0x73,0x04,0x52,0x61,0x6E,0x67,0xFF,0xE6,0x00,0xFF,0xE6,0x00,0xFF,0xE6
	,0x00,0xFF,0xE6,0x00,0xF2,0xE6,0x07,0x4D,0x69,0x6E,0x56,0x61,0x6C,0x75,0x3F,0x73,0x01,0x42,0x73,0x1E
	,0x02,0x61,0x78,0x7F,0x1E,0x00,0x7F,0x91,0x00,0x4E,0x91,0x00,0x84,0xFD,0x07,0x50,0x72,0x65,0x73,0x65
	,0x74,0x73,0x3F,0x90,0x00,0x3F,0x90,0x00,0x35,0xE4,0x00,0x86,0x2E,0x04,0x4E,0x61,0x6D,0x65,0x44,0xCA
	,0x00,0x37,0xE6,0x00,0x50,0x11,0x00,0xBF,0xE7,0x00,0x87,0xE7,0x05,0x53,0x65,0x6C,0x65,0x63,0xC7,0x56
	,0x00,0xBF,0xE6,0x00,0xBF,0xE6,0x00,0xAE,0xE6,0x00,0xCA,0x54,0x00,0x7F,0xE7,0x02,0x45,0x5F,0xCC,0x12
	,0x00,0x7F,0x55,0x00,0x49,0x55,0x05,0x74,0x4D,0x75,0x74,0x65,0xBF,0xAA,0x00,0xBF,0xAA,0x00,0xAF,0xAA
	,0x06,0x68,0x61,0x6E,0x6E,0x65,0x6C,0xBF,0xCB,0x02,0x45,0x5F,0x09,0x12,0x00,0xF0,0xCA,0x0A,0x44,0x65
	,0x73,0x69,0x72,0x65,0x64,0x4D,0x75,0x74,0xB7,0x74,0x03,0x4D,0x75,0x74,0x7F,0x70,0x00,0x4D,0x70,0x05
	,0x56,0x6F,0x6C,0x75,0x6D,0xFF,0x70,0x00,0xFF,0x70,0x00,0xFF,0x70,0x00,0xFF,0x70,0x00,0xF9,0x70,0x00
	,0x8E,0x4E,0x00,0xEE,0xE5,0x00,0x88,0x5D,0x00,0x39,0xE2,0x00,0x47,0xE4,0x00,0x86,0xE7,0x07,0x73,0x65
	,0x72,0x76,0x69,0x63,0x65,0x85,0xFE,0x01,0x54,0xC6,0xF2,0x01,0x73,0x8C,0xF6,0x10,0x20,0x73,0x65,0x6E
	,0x64,0x45,0x76,0x65,0x6E,0x74,0x73,0x3D,0x22,0x6E,0x6F,0x22,0xC7,0xEF,0x00,0x0D,0xA1,0x11,0x61,0x74
	,0x61,0x54,0x79,0x70,0x65,0x3E,0x62,0x6F,0x6F,0x6C,0x65,0x61,0x6E,0x3C,0x2F,0x89,0x04,0x03,0x3C,0x2F
	,0x73,0x8E,0xD7,0x00,0x24,0x17,0x00,0xD7,0xEB,0x00,0x4F,0x1B,0x03,0x75,0x69,0x34,0x7F,0x1A,0x00,0x87
	,0x52,0x02,0x44,0x42,0x51,0x32,0x02,0x69,0x32,0x0C,0x31,0x23,0x61,0x6C,0x6C,0x6F,0x77,0x65,0x64,0x56
	,0x61,0x6C,0x75,0x65,0x52,0x61,0x6E,0x67,0x65,0x3E,0x3C,0x6D,0x69,0x6E,0x69,0x6D,0x75,0x6D,0x3E,0x2D
	,0x33,0x32,0x37,0x36,0x37,0x3C,0x2F,0x08,0x04,0x04,0x3C,0x6D,0x61,0x78,0x45,0x06,0x00,0x08,0x06,0x00
	,0xC7,0x03,0x02,0x3C,0x2F,0x53,0x11,0x00,0xFA,0x2C,0x00,0x53,0x43,0x00,0xA8,0x2C,0x01,0x30,0x53,0x2B
	,0x03,0x31,0x30,0x30,0xCB,0x2A,0x08,0x73,0x74,0x65,0x70,0x3E,0x31,0x3C,0x2F,0x05,0x02,0x00,0x7F,0x2E
	,0x00,0x55,0x75,0x08,0x50,0x72,0x65,0x73,0x65,0x74,0x4E,0x61,0x13,0x32,0x06,0x73,0x74,0x72,0x69,0x6E
	,0x67,0x58,0x5F,0x00,0x06,0xB2,0x00,0xCC,0x63,0x10,0x3E,0x46,0x61,0x63,0x74,0x6F,0x72,0x79,0x44,0x65
	,0x66,0x61,0x75,0x6C,0x74,0x73,0x0E,0x5A,0x03,0x3E,0x3C,0x2F,0xD2,0x0F,0x00,0xB4,0xA4,0x00,0x8A,0x2C
	,0x00,0xC4,0xD2,0x00,0xBF,0x2D,0x00,0xBF,0x2D,0x00,0x20,0xE9,0x03,0x79,0x65,0x73,0x48,0xE9,0x09,0x4C
	,0x61,0x73,0x74,0x43,0x68,0x61,0x6E,0x67,0x64,0x5A,0x00,0xBF,0xEA,0x00,0x04,0x1A,0x03,0x6E,0x65,0x6C
	,0xBF,0x74,0x09,0x75,0x65,0x3E,0x4D,0x61,0x73,0x74,0x65,0x72,0x73,0x72,0x09,0x2F,0x73,0x65,0x72,0x76
	,0x69,0x63,0x65,0x53,0x84,0xFE,0x01,0x54,0x08,0x05,0x01,0x63,0x00,0x00,0x03,0x70,0x64,0x3E,0x00,0x00
};

#if defined(WIN32)
#pragma warning( pop )
#endif

struct UPnPDataObject;

// It should not be necessary to expose/modify any of these structures. They are used by the internal stack
struct SubscriberInfo
{
	char* SID;		// Subscription ID
	int SIDLength;
	int SEQ;
	
	int NotLegacy;
	int Address;
	unsigned short Port;
	char* Path;
	int PathLength;
	int RefCount;
	int Disposing;
	
	struct timeval RenewByTime;
	
	struct SubscriberInfo *Next;
	struct SubscriberInfo *Previous;
};

struct UPnPDataObject
{
	// Absolutely DO NOT put anything above these 3 function pointers
	ILibChain_PreSelect PreSelect;
	ILibChain_PostSelect PostSelect;
	ILibChain_Destroy Destroy;
	
	void *EventClient;
	void *Chain;
	int UpdateFlag;
	
	// Network Poll
	unsigned int NetworkPollTime;
	
	int ForceExit;
	char *UUID;
	char *UDN;
	char *Serial;
	void *User;
	void *User2;
	
	void *WebServerTimer;
	void *HTTPServer;
	char *DeviceDescription;
	int DeviceDescriptionLength;	int InitialNotify;
	char* AVTransport_LastChange;
	char* ConnectionManager_SourceProtocolInfo;
	char* ConnectionManager_SinkProtocolInfo;
	char* ConnectionManager_CurrentConnectionIDs;
	char* RenderingControl_LastChange;
	
	struct sockaddr_in addr;
	int addrlen;
	
	// Current local interfaces
	struct sockaddr_in* AddressListV4;
	int AddressListV4Length;
	struct sockaddr_in6* AddressListV6;
	int AddressListV6Length;
	
	// Multicast Addresses
	struct sockaddr_in MulticastAddrV4;
	struct sockaddr_in6 MulticastAddrV6SL;
	struct sockaddr_in6 MulticastAddrV6LL;
	
	int _NumEmbeddedDevices;
	int WebSocketPortNumber;
	
	void **NOTIFY_RECEIVE_socks;
	void **NOTIFY_SEND_socks;
	void **NOTIFY_RECEIVE_socks6;
	void **NOTIFY_SEND_socks6;
	int ConfigID;
	unsigned short UnicastReceiveSocketPortNumber;
	void **UnicastReceiveSockets;
	struct timeval CurrentTime;
	struct timeval NotifyTime;
	
	int SID;
	int NotifyCycleTime;
	void *MulticastEventListener;
	sem_t EventLock;
	struct SubscriberInfo *HeadSubscriberPtr_AVTransport;
	int NumberOfSubscribers_AVTransport;
	struct SubscriberInfo *HeadSubscriberPtr_ConnectionManager;
	int NumberOfSubscribers_ConnectionManager;
	struct SubscriberInfo *HeadSubscriberPtr_RenderingControl;
	int NumberOfSubscribers_RenderingControl;
	
};

struct MSEARCH_state
{
	char *ST;
	int STLength;
	void *upnp;
	struct sockaddr_in6 dest_addr;
	struct sockaddr_in6 localIPAddress;
	void *Chain;
	void *SubChain;
};
struct UPnPFragmentNotifyStruct
{
	struct UPnPDataObject *upnp;
	int packetNumber;
};

/* Pre-declarations */
void UPnPFragmentedSendNotify(void *data);
void UPnPSendNotify(const struct UPnPDataObject *upnp);
void UPnPSendByeBye(const struct UPnPDataObject *upnp);
void UPnPMainInvokeSwitch();
void UPnPSendDataXmlEscaped(const void* UPnPToken, const char* Data, const int DataLength, const int Terminate);
void UPnPSendData(const void* UPnPToken, const char* Data, const int DataLength, const int Terminate);
int UPnPPeriodicNotify(struct UPnPDataObject *upnp);
void UPnPSendEvent_Body(void *upnptoken, char *body, int bodylength, struct SubscriberInfo *info);
void UPnPProcessMSEARCH(struct UPnPDataObject *upnp, struct packetheader *packet);
struct in_addr UPnP_inaddr;

/*! \fn UPnPGetWebServerToken(const UPnPMicroStackToken MicroStackToken)
\brief Converts a MicroStackToken to a WebServerToken
\par
\a MicroStackToken is the void* returned from a call to UPnPCreateMicroStack. The returned token, is the server token
not the session token.
\param MicroStackToken MicroStack Token
\returns WebServer Token
*/
void* UPnPGetWebServerToken(const UPnPMicroStackToken MicroStackToken)
{
	return(((struct UPnPDataObject*)MicroStackToken)->HTTPServer);
}
#define UPnPMulticastPacketTemplate "NOTIFY * HTTP/1.1\r\nHost: %s:%d\r\nContent-Type: text/xml; charset=\"utf-8\"\r\nUSN: uuid:%s::%s\r\nNT: upnp:event\r\nNTS: upnp:propchange\r\nSEQ: %d\r\nLVL: %s\r\nBOOTID.UPNP.ORG: %d\r\n\r\n<?xml version=\"1.0\"?><e:propertyset xmlns:e=\"urn:schemas-upnp-org:event-1-0\"><e:property><%s>%s</%s></e:property></e:propertyset>"
UPnPEvent_MulticastGeneric_Handler UPnPOnEvent_MulticastGeneric = NULL;
int UPnPBuildSendSsdpResponsePacket(void* module, const struct UPnPDataObject *upnp, struct sockaddr* local, struct sockaddr* target, int EmbeddedDeviceNumber, char* USNex, char* ST, char* NTex)
{
	int len;
	
	if (local->sa_family == AF_INET)
	{
		// IPv4 address format
		ILibInet_ntop(local->sa_family, &(((struct sockaddr_in*)local)->sin_addr), ILibScratchPad2, sizeof(ILibScratchPad2));
	}
	else if (local->sa_family == AF_INET6)
	{
		// IPv6 address format
		size_t len;
		ILibScratchPad2[0] = '[';
		ILibInet_ntop(local->sa_family, &(((struct sockaddr_in6*)local)->sin6_addr), ILibScratchPad2 + 1, sizeof(ILibScratchPad2) - 2);
		len = strlen(ILibScratchPad2);
		ILibScratchPad2[len] = ']';
		ILibScratchPad2[len + 1] = 0;
	}
	
	len = snprintf(ILibScratchPad, sizeof(ILibScratchPad), "HTTP/1.1 200 OK\r\nCONFIGID.UPNP.ORG: %d\r\nSEARCHPORT.UPNP.ORG: %u\r\nBOOTID.UPNP.ORG: %d\r\nMAXVERSION.UPNP.ORG: %d\r\nLOCATION: http://%s:%d/\r\nEXT:\r\nSERVER: %s, UPnP/1.1, MicroStack/1.0.4144\r\nUSN: uuid:%s%s\r\nCACHE-CONTROL: max-age=%d\r\nST: %s%s\r\n\r\n", upnp->ConfigID, upnp->UnicastReceiveSocketPortNumber, upnp->InitialNotify, 1, ILibScratchPad2, upnp->WebSocketPortNumber, UPnPPLATFORM, upnp->UDN, USNex, upnp->NotifyCycleTime, ST, NTex);
	return ILibAsyncUDPSocket_SendTo(module, target, ILibScratchPad, len, ILibAsyncSocket_MemoryOwnership_USER);
}

int UPnPBuildSendSsdpNotifyPacket(void* module, const struct UPnPDataObject *upnp, struct sockaddr* local, int EmbeddedDeviceNumber, char* USNex, char* NT, char* NTex)
{
	int len;
	struct sockaddr* multicast;
	char* mcaststr;
	
	if (local->sa_family == AF_INET)
	{
		// IPv4 address format
		ILibInet_ntop(local->sa_family, &(((struct sockaddr_in*)local)->sin_addr), ILibScratchPad2, sizeof(ILibScratchPad2));
		multicast = (struct sockaddr*)&(upnp->MulticastAddrV4);
		mcaststr = UPNP_MCASTv4_GROUP;
	}
	else if (local->sa_family == AF_INET6)
	{
		// IPv6 address format
		size_t len;
		ILibScratchPad2[0] = '[';
		ILibInet_ntop(local->sa_family, &(((struct sockaddr_in6*)local)->sin6_addr), ILibScratchPad2 + 1, sizeof(ILibScratchPad2) - 2);
		len = strlen(ILibScratchPad2);
		ILibScratchPad2[len] = ']';
		ILibScratchPad2[len + 1] = 0;
		// multicast = (struct sockaddr*)&(upnp->MulticastAddrV6); // TODO: Old code line. To be removed.
		if (ILibAsyncSocket_IsIPv6LinkLocal(local)) { multicast = (struct sockaddr*)&(upnp->MulticastAddrV6LL); } else { multicast = (struct sockaddr*)&(upnp->MulticastAddrV6SL); }
		mcaststr = UPNP_MCASTv6_GROUPB;
	}
	
	len = snprintf(ILibScratchPad, sizeof(ILibScratchPad), "NOTIFY * HTTP/1.1\r\nCONFIGID.UPNP.ORG: %d\r\nSEARCHPORT.UPNP.ORG: %u\r\nBOOTID.UPNP.ORG: %d\r\nMAXVERSION.UPNP.ORG: %d\r\nLOCATION: http://%s:%d/\r\nHOST: %s:1900\r\nSERVER: %s, UPnP/1.1, MicroStack/1.0.4144\r\nNTS: ssdp:alive\r\nUSN: uuid:%s%s\r\nCACHE-CONTROL: max-age=%d\r\nNT: %s%s\r\n\r\n", upnp->ConfigID, upnp->UnicastReceiveSocketPortNumber, upnp->InitialNotify, 1, ILibScratchPad2, upnp->WebSocketPortNumber, mcaststr, UPnPPLATFORM, upnp->UDN, USNex, upnp->NotifyCycleTime, NT, NTex);
	return ILibAsyncUDPSocket_SendTo(module, multicast, ILibScratchPad, len, ILibAsyncSocket_MemoryOwnership_USER);
}
void UPnPUnicastSSDPSink(ILibAsyncUDPSocket_SocketModule socketModule,char* buffer, int bufferLength, int remoteInterface, unsigned short remotePort, void *user, void *user2, int *PAUSE)
{
	struct packetheader *packet;
	struct UPnPDataObject *UPnPObject = (struct UPnPDataObject*)user;
	
	packet = ILibParsePacketHeader(buffer, 0, bufferLength);
	if (packet != NULL)
	{
		// Fill in the source and local interface addresses
		memcpy(&(packet->Source), &(UPnPObject->addr), INET_SOCKADDR_LENGTH(UPnPObject->addr.sin_family));
		ILibAsyncUDPSocket_GetLocalInterface(socketModule, (struct sockaddr*)&(packet->ReceivingAddress));
		
		if (packet->StatusCode == -1 && memcmp(packet->Directive, "M-SEARCH", 8) == 0)
		{
			// Process the search request with our regular Multicast M-SEARCH Handler
			UPnPProcessMSEARCH((struct UPnPDataObject*)UPnPObject, packet);
		}
		ILibDestructPacket(packet);
	}
}

void UPnPFreeUnicastReceiveSockets(struct UPnPDataObject *obj)
{
	int i;
	if (obj->UnicastReceiveSockets != NULL)
	{
		for(i = 0; i < obj->AddressListV4Length; ++i) if (obj->UnicastReceiveSockets[i] != NULL) ILibChain_SafeRemove(obj->Chain, obj->UnicastReceiveSockets[i]);
		free(obj->UnicastReceiveSockets);
		obj->UnicastReceiveSockets = NULL;
	}
}

void UPnPBindUnicastReceiveSockets(struct UPnPDataObject *obj)
{
	int i, OK = 0;
	UPnPFreeUnicastReceiveSockets(obj);
	if ((obj->UnicastReceiveSockets = (void**)malloc(obj->AddressListV4Length * sizeof(void*))) == NULL) ILIBCRITICALEXIT(254);
	
	do
	{
		obj->UnicastReceiveSocketPortNumber = (unsigned short)(1901 + ((unsigned short)rand() % 98));
		for(i = 0; i < obj->AddressListV4Length; ++i)
		{
			((struct sockaddr_in*)&(obj->AddressListV4[i]))->sin_port = obj->UnicastReceiveSocketPortNumber;
			
			obj->UnicastReceiveSockets[i] = ILibAsyncUDPSocket_CreateEx(
			obj->Chain,
			UPNP_MAX_SSDP_HEADER_SIZE,
			(struct sockaddr*)&(obj->AddressListV4[i]),
			ILibAsyncUDPSocket_Reuse_SHARED,
			&UPnPUnicastSSDPSink,
			NULL,
			obj);
			if (obj->UnicastReceiveSockets[i] == NULL)
			{
				UPnPFreeUnicastReceiveSockets(obj);
				OK = 0;
				break;
			}
			else
			{
				OK = 1;
			}
		}
	} while(!OK);
}
void UPnPSetDisconnectFlag(UPnPSessionToken token,void *flag)
{
	((struct ILibWebServer_Session*)token)->Reserved10=flag;
}

/*! \fn UPnPIPAddressListChanged(UPnPMicroStackToken MicroStackToken)
\brief Tell the underlying MicroStack that an IPAddress may have changed
\param MicroStackToken Microstack
*/
void UPnPIPAddressListChanged(UPnPMicroStackToken MicroStackToken)
{
	((struct UPnPDataObject*)MicroStackToken)->UpdateFlag = 1;
	ILibForceUnBlockChain(((struct UPnPDataObject*)MicroStackToken)->Chain);
}

void UPnPSSDPSink(ILibAsyncUDPSocket_SocketModule socketModule, char* buffer, int bufferLength, struct sockaddr_in6 *remoteInterface, void *user, void *user2, int *PAUSE)
{
	struct packetheader *packet;
	UNREFERENCED_PARAMETER( user2 );
	UNREFERENCED_PARAMETER( PAUSE );
	
	packet = ILibParsePacketHeader(buffer, 0, bufferLength);
	if (packet != NULL)
	{
		// Fill in the source and local interface addresses
		memcpy(&(packet->Source), remoteInterface, INET_SOCKADDR_LENGTH(remoteInterface->sin6_family));
		ILibAsyncUDPSocket_GetLocalInterface(socketModule, (struct sockaddr*)&(packet->ReceivingAddress));
		
		if (packet->StatusCode == -1 && memcmp(packet->Directive, "M-SEARCH", 8) == 0 && ((struct sockaddr_in6*)(packet->ReceivingAddress))->sin6_family != 0)
		{
			// Process the search request with our Multicast M-SEARCH Handler
			UPnPProcessMSEARCH(user, packet);
		}
		ILibDestructPacket(packet);
	}
}
void OnUPnPMulticastEvent(ILibAsyncUDPSocket_SocketModule socketModule, char* buffer, int bufferLength, int remoteInterface, unsigned short remotePort, void *user, void *user2, int *PAUSE)
{
	int i;
	char *LVL;
	struct packetheader *p;
	char *body = NULL;
	int bodyLength = 0;
	enum MULTICAST_EVENT_TYPE eventType;
	struct ILibXMLNode *root,*current;
	void *pStack;
	char *ServiceType = NULL;
	int ServiceVersion = -1;
	char *DeviceUDN = NULL;
	char *ServiceID = NULL;
	char *VariableValue;
	int VariableValueLength;
	
	
	p = ILibParsePacketHeader(buffer, 0, bufferLength);
	if (p != NULL)
	{
		if (p->DirectiveLength == 6 && 
		strncasecmp(p->Directive, "NOTIFY", 6) == 0 &&
		ILibGetHeaderLine(p, "NT", 2) != NULL &&
		strcmp(ILibGetHeaderLine(p, "NT", 2), "upnp:event") == 0
		)
		{
			body = ILibGetHeaderLine(p, "USN" ,3);
			if (body != NULL)
			{
				i = ILibString_IndexOf(body, (int)strlen(body), "::", 2);
				DeviceUDN = body + 5; //uuid:
				body[i] = 0;
				ServiceType = body + i + 2; // ::
				i = ILibString_LastIndexOf(ServiceType, (int)strlen(ServiceType), ":", 1);
				ServiceType[i] = 0;
				ServiceVersion = atoi(ServiceType + i + 1);
			}
			
			body = p->Body;
			bodyLength = p->BodyLength;
			if (body == NULL)
			{
				i = ILibString_IndexOf(buffer, bufferLength, "\0\n\r\n", 4);
				if (i > 0)
				{
					body = buffer + i + 4;
					bodyLength = bufferLength - i - 4;
				}
			}
			if (body != NULL)
			{
				LVL = ILibGetHeaderLine(p, "LVL", 3);
				eventType = (enum MULTICAST_EVENT_TYPE)ILibFindEntryInTable(LVL, MULTICAST_EVENT_TYPE_DESCRIPTION);
				
				//
				// Parse the  Body
				//
				root=current=ILibParseXML(body, 0, bodyLength);
				if (ILibProcessXMLNodeList(current) == 0)
				{
					ILibXML_BuildNamespaceLookupTable(root);
					ILibCreateStack(&pStack);
					while(current != NULL)
					{
						current->Name[current->NameLength] = 0;
						if (ILibXML_LookupNamespace(current, current->NSTag, current->NSLength) != NULL &&
						strcmp(ILibXML_LookupNamespace(current, current->NSTag, current->NSLength), "urn:schemas-upnp-org:event-1-0") == 0 &&
						strcasecmp(current->Name, "propertyset") == 0)
						{
							ILibPushStack(&pStack,current);
							current=current->Next;
							while(current != NULL)
							{
								current->Name[current->NameLength] = 0;
								if ( ILibXML_LookupNamespace(current, current->NSTag, current->NSLength) != NULL &&
								strcmp(ILibXML_LookupNamespace(current, current->NSTag, current->NSLength),"urn:schemas-upnp-org:event-1-0") == 0 &&
								strcasecmp(current->Name, "property") == 0)
								{
									ILibPushStack(&pStack, current);
									current = current->Next;
									while(current != NULL)
									{
										// Check the variables
										current->Name[current->NameLength] = 0;
										VariableValueLength = ILibReadInnerXML(current, &VariableValue);
										VariableValue[VariableValueLength] = 0;
										if (UPnPOnEvent_MulticastGeneric != NULL)
										{
											UPnPOnEvent_MulticastGeneric(
											user,
											ServiceType, 
											ServiceVersion, 
											ServiceID,
											DeviceUDN, 
											eventType,
											current->Name, 
											VariableValue
											);
										}
										
										current = current->Peer;
									}
									current = (struct ILibXMLNode*)ILibPopStack(&pStack);
								}
								current = current->Peer;
							}
							current = (struct ILibXMLNode*)ILibPopStack(&pStack);
						}
						current = current->Peer;
					}
				}
				ILibDestructXMLNodeList(root);
			}
		}
		ILibDestructPacket(p);
	}
}
//
//	Internal underlying Initialization, that shouldn't be called explicitely
// 
// <param name="state">State object</param>
// <param name="NotifyCycleSeconds">Cycle duration</param>
// <param name="PortNumber">Port Number</param>
void UPnPInit(struct UPnPDataObject *state, void *chain, const int NotifyCycleSeconds, const unsigned short PortNumber)
{
	int i;
	struct sockaddr_in any4;
	struct sockaddr_in6 any6;
	UNREFERENCED_PARAMETER( PortNumber );
	
	// Setup ANY addresses
	memset(&any4, 0, sizeof(struct sockaddr_in));
	any4.sin_family = AF_INET;
	any4.sin_port = htons(UPNP_PORT);
	memset(&any6, 0, sizeof(struct sockaddr_in6));
	any6.sin6_family = AF_INET6;
	any6.sin6_port = htons(UPNP_PORT);
	
	state->Chain = chain;
	
	// Setup notification timer
	state->NotifyCycleTime = NotifyCycleSeconds;
	gettimeofday(&(state->CurrentTime), NULL);
	(state->NotifyTime).tv_sec = (state->CurrentTime).tv_sec  + (state->NotifyCycleTime / 2);
	
	// Fetch the list of local IPv4 interfaces
	state->AddressListV4Length = ILibGetLocalIPv4AddressList(&(state->AddressListV4), 1);
	
	// Setup the IPv4 sockets
	if ((state->NOTIFY_SEND_socks = (void**)malloc(sizeof(void*)*(state->AddressListV4Length))) == NULL) ILIBCRITICALEXIT(254);
	if ((state->NOTIFY_RECEIVE_socks = (void**)malloc(sizeof(void*)*(state->AddressListV4Length))) == NULL) ILIBCRITICALEXIT(254);
	
	// Setup multicast IPv4 address
	memset(&state->MulticastAddrV4, 0, sizeof(struct sockaddr_in));
	state->MulticastAddrV4.sin_family = AF_INET;
	state->MulticastAddrV4.sin_port = htons(UPNP_PORT);
	ILibInet_pton(AF_INET, UPNP_MCASTv4_GROUP, &(state->MulticastAddrV4.sin_addr));
	
	// Test IPv6 support
	if (ILibDetectIPv6Support())
	{
		// Fetch the list of local IPv6 interfaces
		state->AddressListV6Length = ILibGetLocalIPv6List(&(state->AddressListV6));
		
		// Setup the IPv6 sockets
		if ((state->NOTIFY_SEND_socks6 = (void**)malloc(sizeof(void*)*(state->AddressListV6Length))) == NULL) ILIBCRITICALEXIT(254);
		if ((state->NOTIFY_RECEIVE_socks6 = (void**)malloc(sizeof(void*)*(state->AddressListV6Length))) == NULL) ILIBCRITICALEXIT(254);
		
		// Setup multicast IPv6 address (Site Local)
		memset(&state->MulticastAddrV6SL, 0, sizeof(struct sockaddr_in6));
		state->MulticastAddrV6SL.sin6_family = AF_INET6;
		state->MulticastAddrV6SL.sin6_port = htons(UPNP_PORT);
		ILibInet_pton(AF_INET6, UPNP_MCASTv6_GROUP, &(state->MulticastAddrV6SL.sin6_addr));
		
		// Setup multicast IPv6 address (Link Local)
		memset(&state->MulticastAddrV6LL, 0, sizeof(struct sockaddr_in6));
		state->MulticastAddrV6LL.sin6_family = AF_INET6;
		state->MulticastAddrV6LL.sin6_port = htons(UPNP_PORT);
		ILibInet_pton(AF_INET6, UPNP_MCASTv6_LINK_GROUP, &(state->MulticastAddrV6LL.sin6_addr));
	}
	
	// Iterate through all the current IPv4 addresses
	for (i = 0; i < state->AddressListV4Length; ++i)
	{
		(state->AddressListV4[i]).sin_port = 0; // Bind to ANY port for outbound packets
		state->NOTIFY_SEND_socks[i] = ILibAsyncUDPSocket_CreateEx(
		chain,
		UPNP_MAX_SSDP_HEADER_SIZE,
		(struct sockaddr*)&(state->AddressListV4[i]),
		ILibAsyncUDPSocket_Reuse_SHARED,
		NULL,
		NULL,
		state);
		
		ILibAsyncUDPSocket_SetMulticastTTL(state->NOTIFY_SEND_socks[i], UPNP_SSDP_TTL);
		ILibAsyncUDPSocket_SetMulticastLoopback(state->NOTIFY_SEND_socks[i], 1);
		
		(state->AddressListV4[i]).sin_port = htons(UPNP_PORT); // Bind to UPnP port for inbound packets
		state->NOTIFY_RECEIVE_socks[i] = ILibAsyncUDPSocket_CreateEx(
		state->Chain,
		UPNP_MAX_SSDP_HEADER_SIZE,
		(struct sockaddr*)&any4,
		ILibAsyncUDPSocket_Reuse_SHARED,
		&UPnPSSDPSink,
		NULL,
		state);
		
		ILibAsyncUDPSocket_JoinMulticastGroupV4(state->NOTIFY_RECEIVE_socks[i], (struct sockaddr_in*)&(state->MulticastAddrV4), (struct sockaddr*)&(state->AddressListV4[i]));
		ILibAsyncUDPSocket_SetLocalInterface(state->NOTIFY_RECEIVE_socks[i], (struct sockaddr*)&(state->AddressListV4[i]));
		ILibAsyncUDPSocket_SetMulticastLoopback(state->NOTIFY_RECEIVE_socks[i], 1);
		/*
		state->MulticastEventListener = ILibAsyncUDPSocket_Create(state->Chain, UPNP_MAX_SSDP_HEADER_SIZE, 0, UPNP_MULTICASTEVENT_PORT, ILibAsyncUDPSocket_Reuse_SHARED, &OnUPnPMulticastEvent, NULL, state);
		ILibAsyncUDPSocket_JoinMulticastGroup(
		state->MulticastEventListener,
		state->AddressListV4[i],
		inet_addr(UPNP_MCASTv4_GROUP));
		*/
	}
	
	if (state->AddressListV6Length > 0)
	{
		// Iterate through all the current IPv6 interfaces
		for (i = 0; i < state->AddressListV6Length; ++i)
		{
			(state->AddressListV6[i]).sin6_port = 0;
			state->NOTIFY_SEND_socks6[i] = ILibAsyncUDPSocket_CreateEx(
			chain,
			UPNP_MAX_SSDP_HEADER_SIZE,
			(struct sockaddr*)&(state->AddressListV6[i]),
			ILibAsyncUDPSocket_Reuse_SHARED,
			NULL,
			NULL,
			state);
			
			ILibAsyncUDPSocket_SetMulticastTTL(state->NOTIFY_SEND_socks6[i], UPNP_SSDP_TTL);
			ILibAsyncUDPSocket_SetMulticastLoopback(state->NOTIFY_SEND_socks6[i], 1);
			
			(state->AddressListV6[i]).sin6_port = htons(UPNP_PORT); // Bind to UPnP port for inbound packets
			state->NOTIFY_RECEIVE_socks6[i] = ILibAsyncUDPSocket_CreateEx(
			state->Chain,
			UPNP_MAX_SSDP_HEADER_SIZE,
			(struct sockaddr*)&any6,
			ILibAsyncUDPSocket_Reuse_SHARED,
			&UPnPSSDPSink,
			NULL,
			state);
			
			if (ILibAsyncSocket_IsIPv6LinkLocal((struct sockaddr*)&(state->AddressListV6[i])))
			{
				ILibAsyncUDPSocket_JoinMulticastGroupV6(state->NOTIFY_RECEIVE_socks6[i], &(state->MulticastAddrV6LL), state->AddressListV6[i].sin6_scope_id);
			}
			else
			{
				ILibAsyncUDPSocket_JoinMulticastGroupV6(state->NOTIFY_RECEIVE_socks6[i], &(state->MulticastAddrV6SL), state->AddressListV6[i].sin6_scope_id);
			}
			ILibAsyncUDPSocket_SetMulticastLoopback(state->NOTIFY_RECEIVE_socks6[i], 1);
			ILibAsyncUDPSocket_SetLocalInterface(state->NOTIFY_RECEIVE_socks6[i], (struct sockaddr*)&(state->AddressListV6[i]));
			/*
			state->MulticastEventListener = ILibAsyncUDPSocket_Create(state->Chain, UPNP_MAX_SSDP_HEADER_SIZE, 0, UPNP_MULTICASTEVENT_PORT, ILibAsyncUDPSocket_Reuse_SHARED, &OnUPnPMulticastEvent, NULL, state);
			ILibAsyncUDPSocket_JoinMulticastGroup(
			state->MulticastEventListener,
			state->AddressListV6[i],
			inet_addr(UPNP_MCASTv6_GROUP));
			*/
		}
	}
	UPnPBindUnicastReceiveSockets(state);
}

void UPnPPostMX_Destroy(void *object)
{
	struct MSEARCH_state *mss = (struct MSEARCH_state*)object;
	free(mss->ST);
	free(mss);
}
void UPnPOnPostMX_MSEARCH_SendOK(ILibAsyncUDPSocket_SocketModule socketModule, void *user1, void *user2)
{
	struct MSEARCH_state *mss = (struct MSEARCH_state*)user1;
	UNREFERENCED_PARAMETER( socketModule );
	UNREFERENCED_PARAMETER( user2 );
	
	ILibChain_SafeRemove_SubChain(mss->Chain, mss->SubChain);
	free(mss->ST);
	free(mss);
}

void UPnPPostMX_MSEARCH(void *object)
{
	struct MSEARCH_state *mss = (struct MSEARCH_state*)object;
	void *response_socket;
	void *subChain;
	char *ST = mss->ST;
	int STLength = mss->STLength;
	struct UPnPDataObject *upnp = (struct UPnPDataObject*)mss->upnp;
	int rcode = 0;
	
	subChain = ILibCreateChain();
	
	response_socket = ILibAsyncUDPSocket_CreateEx(
	subChain,
	UPNP_MAX_SSDP_HEADER_SIZE,
	(struct sockaddr*)&(mss->localIPAddress),
	ILibAsyncUDPSocket_Reuse_SHARED,
	NULL,
	UPnPOnPostMX_MSEARCH_SendOK,
	mss);
	
	ILibChain_SafeAdd_SubChain(mss->Chain, subChain);
	mss->SubChain = subChain;
	
	// Search for root device
	if (STLength == 15 && memcmp(ST, "upnp:rootdevice", 15) == 0)
	{
		UPnPBuildSendSsdpResponsePacket(response_socket, upnp, (struct sockaddr*)&(mss->localIPAddress), (struct sockaddr*)&(mss->dest_addr), 0, "::upnp:rootdevice", "upnp:rootdevice", "");
	}
	// Search for everything
	else if (STLength == 8 && memcmp(ST, "ssdp:all", 8) == 0)
	{
		rcode = UPnPBuildSendSsdpResponsePacket(response_socket, upnp, (struct sockaddr*)&(mss->localIPAddress), (struct sockaddr*)&(mss->dest_addr), 0, "::upnp:rootdevice", "upnp:rootdevice", "");
		rcode = UPnPBuildSendSsdpResponsePacket(response_socket, upnp, (struct sockaddr*)&(mss->localIPAddress), (struct sockaddr*)&(mss->dest_addr), 0, "", upnp->UUID, "");
		rcode = UPnPBuildSendSsdpResponsePacket(response_socket, upnp, (struct sockaddr*)&(mss->localIPAddress), (struct sockaddr*)&(mss->dest_addr), 0, "::urn:schemas-upnp-org:device:MediaRenderer:1", "urn:schemas-upnp-org:device:MediaRenderer:1", "");
		rcode = UPnPBuildSendSsdpResponsePacket(response_socket, upnp, (struct sockaddr*)&(mss->localIPAddress), (struct sockaddr*)&(mss->dest_addr), 0, "::urn:schemas-upnp-org:service:AVTransport:1", "urn:schemas-upnp-org:service:AVTransport:1", "");
		rcode = UPnPBuildSendSsdpResponsePacket(response_socket, upnp, (struct sockaddr*)&(mss->localIPAddress), (struct sockaddr*)&(mss->dest_addr), 0, "::urn:schemas-upnp-org:service:ConnectionManager:1", "urn:schemas-upnp-org:service:ConnectionManager:1", "");
		rcode = UPnPBuildSendSsdpResponsePacket(response_socket, upnp, (struct sockaddr*)&(mss->localIPAddress), (struct sockaddr*)&(mss->dest_addr), 0, "::urn:schemas-upnp-org:service:RenderingControl:1", "urn:schemas-upnp-org:service:RenderingControl:1", "");
		
	}
	else if (STLength == (int)strlen(upnp->UUID) && memcmp(ST,upnp->UUID,(int)strlen(upnp->UUID))==0)
	{
		rcode = UPnPBuildSendSsdpResponsePacket(response_socket, upnp, (struct sockaddr*)&(mss->localIPAddress), (struct sockaddr*)&(mss->dest_addr), 0,"",upnp->UUID,"");
	}
	else if (STLength >= 42 && memcmp(ST,"urn:schemas-upnp-org:device:MediaRenderer:",42)==0 && atoi(ST+42)<=1)
	{
		rcode = UPnPBuildSendSsdpResponsePacket(response_socket, upnp, (struct sockaddr*)&(mss->localIPAddress), (struct sockaddr*)&(mss->dest_addr), 0, "::urn:schemas-upnp-org:device:MediaRenderer:1", ST, "");
	}
	else if (STLength >= 41 && memcmp(ST,"urn:schemas-upnp-org:service:AVTransport:",41)==0 && atoi(ST+41)<=1)
	{
		rcode = UPnPBuildSendSsdpResponsePacket(response_socket, upnp, (struct sockaddr*)&(mss->localIPAddress), (struct sockaddr*)&(mss->dest_addr), 0, "::urn:schemas-upnp-org:service:AVTransport:1", ST, "");
	}
	else if (STLength >= 47 && memcmp(ST,"urn:schemas-upnp-org:service:ConnectionManager:",47)==0 && atoi(ST+47)<=1)
	{
		rcode = UPnPBuildSendSsdpResponsePacket(response_socket, upnp, (struct sockaddr*)&(mss->localIPAddress), (struct sockaddr*)&(mss->dest_addr), 0, "::urn:schemas-upnp-org:service:ConnectionManager:1", ST, "");
	}
	else if (STLength >= 46 && memcmp(ST,"urn:schemas-upnp-org:service:RenderingControl:",46)==0 && atoi(ST+46)<=1)
	{
		rcode = UPnPBuildSendSsdpResponsePacket(response_socket, upnp, (struct sockaddr*)&(mss->localIPAddress), (struct sockaddr*)&(mss->dest_addr), 0, "::urn:schemas-upnp-org:service:RenderingControl:1", ST, "");
	}
	
	
	if (rcode == 0)
	{
		ILibChain_SafeRemove_SubChain(mss->Chain, subChain);
		free(mss->ST);
		free(mss);
	}
}

void UPnPProcessMSEARCH(struct UPnPDataObject *upnp, struct packetheader *packet)
{
	char* ST = NULL;
	unsigned long MXVal = 0;
	int STLength = 0, MANOK = 0, MXOK = 0, MX;
	struct packetheader_field_node *node;
	struct MSEARCH_state *mss = NULL;
	
	if (memcmp(packet->DirectiveObj, "*", 1)==0)
	{
		if (memcmp(packet->Version, "1.1", 3)==0)
		{
			node = packet->FirstField;
			while(node!=NULL)
			{
				if (node->FieldLength==2 && strncasecmp(node->Field,"ST",2)==0)
				{
					// This is what is being searched for
					if ((ST = (char*)malloc(1 + node->FieldDataLength)) == NULL) ILIBCRITICALEXIT(254);
					memcpy(ST, node->FieldData, node->FieldDataLength);
					ST[node->FieldDataLength] = 0;
					STLength = node->FieldDataLength;
				}
				else if (node->FieldLength == 3 && strncasecmp(node->Field, "MAN", 3) == 0 && memcmp(node->FieldData, "\"ssdp:discover\"", 15) == 0)
				{
					// This is a required header field
					MANOK = 1;
				}
				else if (node->FieldLength == 2 && strncasecmp(node->Field, "MX", 2) == 0 && ILibGetULong(node->FieldData, node->FieldDataLength, &MXVal) == 0)
				{
					// If the timeout value specified is greater than 10 seconds, just force it down to 10 seconds
					MXOK = 1;
					MXVal = MXVal>10?10:MXVal;
				}
				node = node->NextField;
			}
			if (MANOK != 0 && MXOK != 0)
			{
				if (MXVal == 0)
				{
					MX = 0;
				}
				else
				{
					// The timeout value should be a random number between 0 and the specified value
					MX = (int)(0 + ((unsigned short)rand() % MXVal));
				}
				if ((mss = (struct MSEARCH_state*)malloc(sizeof(struct MSEARCH_state))) == NULL) ILIBCRITICALEXIT(254);
				mss->ST = ST;
				mss->STLength = STLength;
				mss->upnp = upnp;
				memcpy(&(mss->dest_addr), &(packet->Source), sizeof(struct sockaddr_in6));
				memcpy(&(mss->localIPAddress), &(packet->ReceivingAddress), sizeof(struct sockaddr_in6));
				mss->Chain = upnp->Chain;
				
				// Register for a timed callback, so we can respond later
				ILibLifeTime_Add(upnp->WebServerTimer, mss, MX, &UPnPPostMX_MSEARCH, &UPnPPostMX_Destroy);
			}
			else
			{
				free(ST);
			}
		}
	}
}

void UPnPDispatch_AVTransport_GetCurrentTransportActions(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 26 && memcmp(xnode->Name, "GetCurrentTransportActions",26) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 1)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	if (UPnPFP_AVTransport_GetCurrentTransportActions == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_AVTransport_GetCurrentTransportActions((void*)ReaderObject,_InstanceID);
}

void UPnPDispatch_AVTransport_GetDeviceCapabilities(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 21 && memcmp(xnode->Name, "GetDeviceCapabilities",21) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 1)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	if (UPnPFP_AVTransport_GetDeviceCapabilities == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_AVTransport_GetDeviceCapabilities((void*)ReaderObject,_InstanceID);
}

void UPnPDispatch_AVTransport_GetMediaInfo(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 12 && memcmp(xnode->Name, "GetMediaInfo",12) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 1)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	if (UPnPFP_AVTransport_GetMediaInfo == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_AVTransport_GetMediaInfo((void*)ReaderObject,_InstanceID);
}

void UPnPDispatch_AVTransport_GetPositionInfo(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 15 && memcmp(xnode->Name, "GetPositionInfo",15) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 1)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	if (UPnPFP_AVTransport_GetPositionInfo == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_AVTransport_GetPositionInfo((void*)ReaderObject,_InstanceID);
}

void UPnPDispatch_AVTransport_GetTransportInfo(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 16 && memcmp(xnode->Name, "GetTransportInfo",16) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 1)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	if (UPnPFP_AVTransport_GetTransportInfo == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_AVTransport_GetTransportInfo((void*)ReaderObject,_InstanceID);
}

void UPnPDispatch_AVTransport_GetTransportSettings(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 20 && memcmp(xnode->Name, "GetTransportSettings",20) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 1)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	if (UPnPFP_AVTransport_GetTransportSettings == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_AVTransport_GetTransportSettings((void*)ReaderObject,_InstanceID);
}

void UPnPDispatch_AVTransport_Next(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Next",4) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 1)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	if (UPnPFP_AVTransport_Next == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_AVTransport_Next((void*)ReaderObject,_InstanceID);
}

void UPnPDispatch_AVTransport_Pause(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 5 && memcmp(xnode->Name, "Pause",5) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 1)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	if (UPnPFP_AVTransport_Pause == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_AVTransport_Pause((void*)ReaderObject,_InstanceID);
}

void UPnPDispatch_AVTransport_Play(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	char *p_Speed = NULL;
	int p_SpeedLength = 0;
	char* _Speed = "";
	int _SpeedLength;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Play",4) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								else if (xnode->NameLength == 5 && memcmp(xnode->Name, "Speed",5)==0)
								{
									p_SpeedLength = ILibReadInnerXML(xnode, &p_Speed);
									p_Speed[p_SpeedLength]=0;
									OK |= 2;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 3)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	_SpeedLength = ILibInPlaceXmlUnEscape(p_Speed);
	_Speed = p_Speed;
	if (memcmp(_Speed, "1\0",2) != 0
	)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	if (UPnPFP_AVTransport_Play == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_AVTransport_Play((void*)ReaderObject,_InstanceID,_Speed);
}

void UPnPDispatch_AVTransport_Previous(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Previous",8) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 1)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	if (UPnPFP_AVTransport_Previous == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_AVTransport_Previous((void*)ReaderObject,_InstanceID);
}

void UPnPDispatch_AVTransport_Seek(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	char *p_Unit = NULL;
	int p_UnitLength = 0;
	char* _Unit = "";
	int _UnitLength;
	char *p_Target = NULL;
	int p_TargetLength = 0;
	char* _Target = "";
	int _TargetLength;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Seek",4) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								else if (xnode->NameLength == 4 && memcmp(xnode->Name, "Unit",4)==0)
								{
									p_UnitLength = ILibReadInnerXML(xnode, &p_Unit);
									p_Unit[p_UnitLength]=0;
									OK |= 2;
								}
								else if (xnode->NameLength == 6 && memcmp(xnode->Name, "Target",6)==0)
								{
									p_TargetLength = ILibReadInnerXML(xnode, &p_Target);
									p_Target[p_TargetLength]=0;
									OK |= 4;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 7)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	_UnitLength = ILibInPlaceXmlUnEscape(p_Unit);
	_Unit = p_Unit;
	if (memcmp(_Unit, "REL_TIME\0",9) != 0
	&& memcmp(_Unit, "TRACK_NR\0",9) != 0
	)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_TargetLength = ILibInPlaceXmlUnEscape(p_Target);
	_Target = p_Target;
	if (UPnPFP_AVTransport_Seek == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_AVTransport_Seek((void*)ReaderObject,_InstanceID,_Unit,_Target);
}

void UPnPDispatch_AVTransport_SetAVTransportURI(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	char *p_CurrentURI = NULL;
	int p_CurrentURILength = 0;
	char* _CurrentURI = "";
	int _CurrentURILength;
	char *p_CurrentURIMetaData = NULL;
	int p_CurrentURIMetaDataLength = 0;
	char* _CurrentURIMetaData = "";
	int _CurrentURIMetaDataLength;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 17 && memcmp(xnode->Name, "SetAVTransportURI",17) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								else if (xnode->NameLength == 10 && memcmp(xnode->Name, "CurrentURI",10)==0)
								{
									p_CurrentURILength = ILibReadInnerXML(xnode, &p_CurrentURI);
									p_CurrentURI[p_CurrentURILength]=0;
									OK |= 2;
								}
								else if (xnode->NameLength == 18 && memcmp(xnode->Name, "CurrentURIMetaData",18)==0)
								{
									p_CurrentURIMetaDataLength = ILibReadInnerXML(xnode, &p_CurrentURIMetaData);
									p_CurrentURIMetaData[p_CurrentURIMetaDataLength]=0;
									OK |= 4;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 7)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	_CurrentURILength = ILibInPlaceXmlUnEscape(p_CurrentURI);
	_CurrentURI = p_CurrentURI;
	_CurrentURIMetaDataLength = ILibInPlaceXmlUnEscape(p_CurrentURIMetaData);
	_CurrentURIMetaData = p_CurrentURIMetaData;
	if (UPnPFP_AVTransport_SetAVTransportURI == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_AVTransport_SetAVTransportURI((void*)ReaderObject,_InstanceID,_CurrentURI,_CurrentURIMetaData);
}

void UPnPDispatch_AVTransport_SetPlayMode(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	char *p_NewPlayMode = NULL;
	int p_NewPlayModeLength = 0;
	char* _NewPlayMode = "";
	int _NewPlayModeLength;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 11 && memcmp(xnode->Name, "SetPlayMode",11) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								else if (xnode->NameLength == 11 && memcmp(xnode->Name, "NewPlayMode",11)==0)
								{
									p_NewPlayModeLength = ILibReadInnerXML(xnode, &p_NewPlayMode);
									p_NewPlayMode[p_NewPlayModeLength]=0;
									OK |= 2;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 3)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	_NewPlayModeLength = ILibInPlaceXmlUnEscape(p_NewPlayMode);
	_NewPlayMode = p_NewPlayMode;
	if (memcmp(_NewPlayMode, "NORMAL\0",7) != 0
	&& memcmp(_NewPlayMode, "REPEAT_ONE\0",11) != 0
	&& memcmp(_NewPlayMode, "REPEAT_ALL\0",11) != 0
	&& memcmp(_NewPlayMode, "SHUFFLE\0",8) != 0
	&& memcmp(_NewPlayMode, "SHUFFLE_NOREPEAT\0",17) != 0
	)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	if (UPnPFP_AVTransport_SetPlayMode == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_AVTransport_SetPlayMode((void*)ReaderObject,_InstanceID,_NewPlayMode);
}

void UPnPDispatch_AVTransport_Stop(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Stop",4) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 1)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	if (UPnPFP_AVTransport_Stop == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_AVTransport_Stop((void*)ReaderObject,_InstanceID);
}

#define UPnPDispatch_ConnectionManager_GetCurrentConnectionIDs(buffer,offset,bufferLength, session)\
{\
	if (UPnPFP_ConnectionManager_GetCurrentConnectionIDs == NULL)\
	UPnPResponse_Error(session,501,"No Function Handler");\
	else\
	UPnPFP_ConnectionManager_GetCurrentConnectionIDs((void*)session);\
}

void UPnPDispatch_ConnectionManager_GetCurrentConnectionInfo(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	long TempLong;
	int OK = 0;
	char *p_ConnectionID = NULL;
	int p_ConnectionIDLength = 0;
	int _ConnectionID = 0;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 24 && memcmp(xnode->Name, "GetCurrentConnectionInfo",24) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 12 && memcmp(xnode->Name, "ConnectionID",12)==0)
								{
									p_ConnectionIDLength = ILibReadInnerXML(xnode, &p_ConnectionID);
									OK |= 1;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 1)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetLong(p_ConnectionID,p_ConnectionIDLength, &TempLong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_ConnectionID = (int)TempLong;
	if (UPnPFP_ConnectionManager_GetCurrentConnectionInfo == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_ConnectionManager_GetCurrentConnectionInfo((void*)ReaderObject,_ConnectionID);
}

#define UPnPDispatch_ConnectionManager_GetProtocolInfo(buffer,offset,bufferLength, session)\
{\
	if (UPnPFP_ConnectionManager_GetProtocolInfo == NULL)\
	UPnPResponse_Error(session,501,"No Function Handler");\
	else\
	UPnPFP_ConnectionManager_GetProtocolInfo((void*)session);\
}

void UPnPDispatch_RenderingControl_GetMute(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	char *p_Channel = NULL;
	int p_ChannelLength = 0;
	char* _Channel = "";
	int _ChannelLength;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 7 && memcmp(xnode->Name, "GetMute",7) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								else if (xnode->NameLength == 7 && memcmp(xnode->Name, "Channel",7)==0)
								{
									p_ChannelLength = ILibReadInnerXML(xnode, &p_Channel);
									p_Channel[p_ChannelLength]=0;
									OK |= 2;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 3)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	_ChannelLength = ILibInPlaceXmlUnEscape(p_Channel);
	_Channel = p_Channel;
	if (memcmp(_Channel, "Master\0",7) != 0
	)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	if (UPnPFP_RenderingControl_GetMute == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_RenderingControl_GetMute((void*)ReaderObject,_InstanceID,_Channel);
}

void UPnPDispatch_RenderingControl_GetVolume(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	char *p_Channel = NULL;
	int p_ChannelLength = 0;
	char* _Channel = "";
	int _ChannelLength;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 9 && memcmp(xnode->Name, "GetVolume",9) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								else if (xnode->NameLength == 7 && memcmp(xnode->Name, "Channel",7)==0)
								{
									p_ChannelLength = ILibReadInnerXML(xnode, &p_Channel);
									p_Channel[p_ChannelLength]=0;
									OK |= 2;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 3)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	_ChannelLength = ILibInPlaceXmlUnEscape(p_Channel);
	_Channel = p_Channel;
	if (memcmp(_Channel, "Master\0",7) != 0
	)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	if (UPnPFP_RenderingControl_GetVolume == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_RenderingControl_GetVolume((void*)ReaderObject,_InstanceID,_Channel);
}

void UPnPDispatch_RenderingControl_GetVolumeDB(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	char *p_Channel = NULL;
	int p_ChannelLength = 0;
	char* _Channel = "";
	int _ChannelLength;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 11 && memcmp(xnode->Name, "GetVolumeDB",11) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								else if (xnode->NameLength == 7 && memcmp(xnode->Name, "Channel",7)==0)
								{
									p_ChannelLength = ILibReadInnerXML(xnode, &p_Channel);
									p_Channel[p_ChannelLength]=0;
									OK |= 2;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 3)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	_ChannelLength = ILibInPlaceXmlUnEscape(p_Channel);
	_Channel = p_Channel;
	if (memcmp(_Channel, "Master\0",7) != 0
	)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	if (UPnPFP_RenderingControl_GetVolumeDB == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_RenderingControl_GetVolumeDB((void*)ReaderObject,_InstanceID,_Channel);
}

void UPnPDispatch_RenderingControl_GetVolumeDBRange(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	char *p_Channel = NULL;
	int p_ChannelLength = 0;
	char* _Channel = "";
	int _ChannelLength;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 16 && memcmp(xnode->Name, "GetVolumeDBRange",16) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								else if (xnode->NameLength == 7 && memcmp(xnode->Name, "Channel",7)==0)
								{
									p_ChannelLength = ILibReadInnerXML(xnode, &p_Channel);
									p_Channel[p_ChannelLength]=0;
									OK |= 2;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 3)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	_ChannelLength = ILibInPlaceXmlUnEscape(p_Channel);
	_Channel = p_Channel;
	if (memcmp(_Channel, "Master\0",7) != 0
	)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	if (UPnPFP_RenderingControl_GetVolumeDBRange == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_RenderingControl_GetVolumeDBRange((void*)ReaderObject,_InstanceID,_Channel);
}

void UPnPDispatch_RenderingControl_ListPresets(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 11 && memcmp(xnode->Name, "ListPresets",11) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 1)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	if (UPnPFP_RenderingControl_ListPresets == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_RenderingControl_ListPresets((void*)ReaderObject,_InstanceID);
}

void UPnPDispatch_RenderingControl_SelectPreset(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	char *p_PresetName = NULL;
	int p_PresetNameLength = 0;
	char* _PresetName = "";
	int _PresetNameLength;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 12 && memcmp(xnode->Name, "SelectPreset",12) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								else if (xnode->NameLength == 10 && memcmp(xnode->Name, "PresetName",10)==0)
								{
									p_PresetNameLength = ILibReadInnerXML(xnode, &p_PresetName);
									p_PresetName[p_PresetNameLength]=0;
									OK |= 2;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 3)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	_PresetNameLength = ILibInPlaceXmlUnEscape(p_PresetName);
	_PresetName = p_PresetName;
	if (memcmp(_PresetName, "FactoryDefaults\0",16) != 0
	)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	if (UPnPFP_RenderingControl_SelectPreset == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_RenderingControl_SelectPreset((void*)ReaderObject,_InstanceID,_PresetName);
}

void UPnPDispatch_RenderingControl_SetMute(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	char *p_Channel = NULL;
	int p_ChannelLength = 0;
	char* _Channel = "";
	int _ChannelLength;
	char *p_DesiredMute = NULL;
	int p_DesiredMuteLength = 0;
	int _DesiredMute = 0;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 7 && memcmp(xnode->Name, "SetMute",7) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								else if (xnode->NameLength == 7 && memcmp(xnode->Name, "Channel",7)==0)
								{
									p_ChannelLength = ILibReadInnerXML(xnode, &p_Channel);
									p_Channel[p_ChannelLength]=0;
									OK |= 2;
								}
								else if (xnode->NameLength == 11 && memcmp(xnode->Name, "DesiredMute",11)==0)
								{
									p_DesiredMuteLength = ILibReadInnerXML(xnode, &p_DesiredMute);
									OK |= 4;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 7)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	_ChannelLength = ILibInPlaceXmlUnEscape(p_Channel);
	_Channel = p_Channel;
	if (memcmp(_Channel, "Master\0",7) != 0
	)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	OK=0;
	if (p_DesiredMuteLength == 4)
	{
		if (strncasecmp(p_DesiredMute,"true",4) == 0)
		{
			OK = 1;
			_DesiredMute = 1;
		}
	}
	if (p_DesiredMuteLength == 5)
	{
		if (strncasecmp(p_DesiredMute,"false",5) == 0)
		{
			OK = 1;
			_DesiredMute = 0;
		}
	}
	if (p_DesiredMuteLength == 1)
	{
		if (memcmp(p_DesiredMute,"0",1) == 0)
		{
			OK = 1;
			_DesiredMute = 0;
		}
		if (memcmp(p_DesiredMute,"1",1) == 0)
		{
			OK = 1;
			_DesiredMute = 1;
		}
	}
	if (OK == 0)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	if (UPnPFP_RenderingControl_SetMute == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_RenderingControl_SetMute((void*)ReaderObject,_InstanceID,_Channel,_DesiredMute);
}

void UPnPDispatch_RenderingControl_SetVolume(char *buffer, int offset, int bufferLength, struct ILibWebServer_Session *ReaderObject)
{
	unsigned long TempULong;
	int OK = 0;
	char *p_InstanceID = NULL;
	int p_InstanceIDLength = 0;
	unsigned int _InstanceID = 0;
	char *p_Channel = NULL;
	int p_ChannelLength = 0;
	char* _Channel = "";
	int _ChannelLength;
	char *p_DesiredVolume = NULL;
	int p_DesiredVolumeLength = 0;
	unsigned short _DesiredVolume = 0;
	struct ILibXMLNode *xnode = ILibParseXML(buffer, offset, bufferLength);
	struct ILibXMLNode *root = xnode;
	if (ILibProcessXMLNodeList(root)!=0)
	{
		/* The XML is not well formed! */
		ILibDestructXMLNodeList(root);
		UPnPResponse_Error(ReaderObject, 501, "Invalid XML");
		return;
	}
	while(xnode != NULL)
	{
		if (xnode->StartTag != 0 && xnode->NameLength == 8 && memcmp(xnode->Name, "Envelope", 8)==0)
		{
			// Envelope
			xnode = xnode->Next;
			while(xnode != NULL)
			{
				if (xnode->StartTag!=0 && xnode->NameLength == 4 && memcmp(xnode->Name, "Body", 4) == 0)
				{
					// Body
					xnode = xnode->Next;
					while(xnode != NULL)
					{
						if (xnode->StartTag != 0 && xnode->NameLength == 9 && memcmp(xnode->Name, "SetVolume",9) == 0)
						{
							// Inside the interesting part of the SOAP
							xnode = xnode->Next;
							while(xnode != NULL)
							{
								if (xnode->NameLength == 10 && memcmp(xnode->Name, "InstanceID",10)==0)
								{
									p_InstanceIDLength = ILibReadInnerXML(xnode, &p_InstanceID);
									OK |= 1;
								}
								else if (xnode->NameLength == 7 && memcmp(xnode->Name, "Channel",7)==0)
								{
									p_ChannelLength = ILibReadInnerXML(xnode, &p_Channel);
									p_Channel[p_ChannelLength]=0;
									OK |= 2;
								}
								else if (xnode->NameLength == 13 && memcmp(xnode->Name, "DesiredVolume",13)==0)
								{
									p_DesiredVolumeLength = ILibReadInnerXML(xnode, &p_DesiredVolume);
									OK |= 4;
								}
								if (xnode->Peer == NULL)
								{
									xnode = xnode->Parent;
									break;
								}
								else
								{
									xnode = xnode->Peer;
								}
							}
						}
						if (xnode != NULL)
						{
							if (xnode->Peer == NULL)
							{
								xnode = xnode->Parent;
								break;
							}
							else
							{
								xnode = xnode->Peer;
							}
						}
					}
				}
				if (xnode != NULL)
				{
					if (xnode->Peer == NULL)
					{
						xnode = xnode->Parent;
						break;
					}
					else
					{
						xnode = xnode->Peer;
					}
				}
			}
		}
		if (xnode != NULL){xnode = xnode->Peer;}
	}
	ILibDestructXMLNodeList(root);
	if (OK != 7)
	{
		UPnPResponse_Error(ReaderObject, 402, "Illegal value");
		return;
	}
	
	/* Type Checking */
	OK = ILibGetULong(p_InstanceID,p_InstanceIDLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	_InstanceID = (unsigned int)TempULong;
	_ChannelLength = ILibInPlaceXmlUnEscape(p_Channel);
	_Channel = p_Channel;
	if (memcmp(_Channel, "Master\0",7) != 0
	)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	OK = ILibGetULong(p_DesiredVolume,p_DesiredVolumeLength, &TempULong);
	if (OK!=0)
	{
		UPnPResponse_Error(ReaderObject,402,"Illegal value");
		return;
	}
	else
	{
		if (!(TempULong>=(unsigned long)0x0 && TempULong<=(unsigned long)0x64))
		{
			UPnPResponse_Error(ReaderObject,402,"Illegal value");
			return;
		}
		_DesiredVolume = (unsigned short)TempULong;
	}
	if (UPnPFP_RenderingControl_SetVolume == NULL)
	UPnPResponse_Error(ReaderObject,501,"No Function Handler");
	else
	UPnPFP_RenderingControl_SetVolume((void*)ReaderObject,_InstanceID,_Channel,_DesiredVolume);
}



int UPnPProcessPOST(struct ILibWebServer_Session *session, struct packetheader* header, char *bodyBuffer, int offset, int bodyBufferLength)
{
	struct packetheader_field_node *f = header->FirstField;
	char* HOST;
	char* SOAPACTION = NULL;
	int SOAPACTIONLength = 0;
	struct parser_result *r, *r2;
	struct parser_result_field *prf;
	int RetVal = 0;
	
	// Iterate through all the HTTP Headers
	while(f!=NULL)
	{
		if (f->FieldLength == 4 && strncasecmp(f->Field, "HOST", 4) == 0)
		{
			HOST = f->FieldData;
		}
		else if (f->FieldLength == 10 && strncasecmp(f->Field, "SOAPACTION", 10) == 0)
		{
			r = ILibParseString(f->FieldData, 0, f->FieldDataLength, "#", 1);
			SOAPACTION = r->LastResult->data;
			SOAPACTIONLength = r->LastResult->datalength - 1;
			ILibDestructParserResults(r);
		}
		else if (f->FieldLength == 10 && strncasecmp(f->Field, "USER-AGENT", 10) == 0)
		{
			// Check UPnP version of the Control Point which invoked us
			r = ILibParseString(f->FieldData, 0, f->FieldDataLength, " ", 1);
			prf = r->FirstResult;
			while(prf!=NULL)
			{
				if (prf->datalength>5 && memcmp(prf->data, "UPnP/", 5)==0)
				{
					r2 = ILibParseString(prf->data + 5, 0, prf->datalength - 5, ".", 1);
					r2->FirstResult->data[r2->FirstResult->datalength] = 0;
					r2->LastResult->data[r2->LastResult->datalength] = 0;
					if (atoi(r2->FirstResult->data) == 1 && atoi(r2->LastResult->data) > 0)
					{
						session->Reserved9 = 1;
					}
					ILibDestructParserResults(r2);
				}
				prf = prf->NextResult;
			}
			ILibDestructParserResults(r);
		}
		f = f->NextField;
	}
	if (header->DirectiveObjLength==20 && memcmp((header->DirectiveObj)+1,"AVTransport/control",19)==0)
	{
		if (SOAPACTIONLength==26 && memcmp(SOAPACTION,"GetCurrentTransportActions",26)==0)
		{
			UPnPDispatch_AVTransport_GetCurrentTransportActions(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==21 && memcmp(SOAPACTION,"GetDeviceCapabilities",21)==0)
		{
			UPnPDispatch_AVTransport_GetDeviceCapabilities(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==12 && memcmp(SOAPACTION,"GetMediaInfo",12)==0)
		{
			UPnPDispatch_AVTransport_GetMediaInfo(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==15 && memcmp(SOAPACTION,"GetPositionInfo",15)==0)
		{
			UPnPDispatch_AVTransport_GetPositionInfo(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==16 && memcmp(SOAPACTION,"GetTransportInfo",16)==0)
		{
			UPnPDispatch_AVTransport_GetTransportInfo(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==20 && memcmp(SOAPACTION,"GetTransportSettings",20)==0)
		{
			UPnPDispatch_AVTransport_GetTransportSettings(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==4 && memcmp(SOAPACTION,"Next",4)==0)
		{
			UPnPDispatch_AVTransport_Next(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==5 && memcmp(SOAPACTION,"Pause",5)==0)
		{
			UPnPDispatch_AVTransport_Pause(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==4 && memcmp(SOAPACTION,"Play",4)==0)
		{
			UPnPDispatch_AVTransport_Play(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==8 && memcmp(SOAPACTION,"Previous",8)==0)
		{
			UPnPDispatch_AVTransport_Previous(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==4 && memcmp(SOAPACTION,"Seek",4)==0)
		{
			UPnPDispatch_AVTransport_Seek(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==17 && memcmp(SOAPACTION,"SetAVTransportURI",17)==0)
		{
			UPnPDispatch_AVTransport_SetAVTransportURI(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==11 && memcmp(SOAPACTION,"SetPlayMode",11)==0)
		{
			UPnPDispatch_AVTransport_SetPlayMode(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==4 && memcmp(SOAPACTION,"Stop",4)==0)
		{
			UPnPDispatch_AVTransport_Stop(bodyBuffer, offset, bodyBufferLength, session);
		}
		else
		{
			RetVal=1;
		}
	}
	else if (header->DirectiveObjLength==26 && memcmp((header->DirectiveObj)+1,"ConnectionManager/control",25)==0)
	{
		if (SOAPACTIONLength==23 && memcmp(SOAPACTION,"GetCurrentConnectionIDs",23)==0)
		{
			UPnPDispatch_ConnectionManager_GetCurrentConnectionIDs(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==24 && memcmp(SOAPACTION,"GetCurrentConnectionInfo",24)==0)
		{
			UPnPDispatch_ConnectionManager_GetCurrentConnectionInfo(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==15 && memcmp(SOAPACTION,"GetProtocolInfo",15)==0)
		{
			UPnPDispatch_ConnectionManager_GetProtocolInfo(bodyBuffer, offset, bodyBufferLength, session);
		}
		else
		{
			RetVal=1;
		}
	}
	else if (header->DirectiveObjLength==25 && memcmp((header->DirectiveObj)+1,"RenderingControl/control",24)==0)
	{
		if (SOAPACTIONLength==7 && memcmp(SOAPACTION,"GetMute",7)==0)
		{
			UPnPDispatch_RenderingControl_GetMute(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==9 && memcmp(SOAPACTION,"GetVolume",9)==0)
		{
			UPnPDispatch_RenderingControl_GetVolume(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==11 && memcmp(SOAPACTION,"GetVolumeDB",11)==0)
		{
			UPnPDispatch_RenderingControl_GetVolumeDB(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==16 && memcmp(SOAPACTION,"GetVolumeDBRange",16)==0)
		{
			UPnPDispatch_RenderingControl_GetVolumeDBRange(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==11 && memcmp(SOAPACTION,"ListPresets",11)==0)
		{
			UPnPDispatch_RenderingControl_ListPresets(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==12 && memcmp(SOAPACTION,"SelectPreset",12)==0)
		{
			UPnPDispatch_RenderingControl_SelectPreset(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==7 && memcmp(SOAPACTION,"SetMute",7)==0)
		{
			UPnPDispatch_RenderingControl_SetMute(bodyBuffer, offset, bodyBufferLength, session);
		}
		else if (SOAPACTIONLength==9 && memcmp(SOAPACTION,"SetVolume",9)==0)
		{
			UPnPDispatch_RenderingControl_SetVolume(bodyBuffer, offset, bodyBufferLength, session);
		}
		else
		{
			RetVal=1;
		}
	}
	else
	{
		RetVal=1;
	}
	
	return(RetVal);
}
struct SubscriberInfo* UPnPRemoveSubscriberInfo(struct SubscriberInfo **Head, int *TotalSubscribers, char* SID, int SIDLength)
{
	struct SubscriberInfo *info = *Head;
	while(info != NULL)
	{
		if (info->SIDLength == SIDLength && memcmp(info->SID, SID, SIDLength) == 0)
		{
			if (info->Previous) info->Previous->Next = info->Next; else *Head = info->Next;
			if (info->Next) info->Next->Previous = info->Previous;
			break;
		}
		info = info->Next;
	}
	if (info != NULL)
	{
		info->Previous = NULL;
		info->Next = NULL;
		--(*TotalSubscribers);
	}
	return(info);
}

#define UPnPDestructSubscriberInfo(info)\
{\
	free(info->Path);\
	free(info->SID);\
	free(info);\
}

#define UPnPDestructEventObject(EvObject)\
{\
	free(EvObject->PacketBody);\
	free(EvObject);\
}

#define UPnPDestructEventDataObject(EvData)\
{\
	free(EvData);\
}

void UPnPExpireSubscriberInfo(struct UPnPDataObject *d, struct SubscriberInfo *info)
{
	struct SubscriberInfo *t = info;
	while(t->Previous != NULL) { t = t->Previous; }
	if (d->HeadSubscriberPtr_AVTransport==t)
	{
		--(d->NumberOfSubscribers_AVTransport);
	}
	else if (d->HeadSubscriberPtr_ConnectionManager==t)
	{
		--(d->NumberOfSubscribers_ConnectionManager);
	}
	else if (d->HeadSubscriberPtr_RenderingControl==t)
	{
		--(d->NumberOfSubscribers_RenderingControl);
	}
	
	
	if (info->Previous != NULL)
	{
		// This is not the Head
		info->Previous->Next = info->Next;
		if (info->Next != NULL) { info->Next->Previous = info->Previous; }
	}
	else
	{
		// This is the Head
		if (d->HeadSubscriberPtr_AVTransport==info)
		{
			d->HeadSubscriberPtr_AVTransport = info->Next;
			if (info->Next!=NULL)
			{
				info->Next->Previous = NULL;
			}
		}
		else if (d->HeadSubscriberPtr_ConnectionManager==info)
		{
			d->HeadSubscriberPtr_ConnectionManager = info->Next;
			if (info->Next!=NULL)
			{
				info->Next->Previous = NULL;
			}
		}
		else if (d->HeadSubscriberPtr_RenderingControl==info)
		{
			d->HeadSubscriberPtr_RenderingControl = info->Next;
			if (info->Next!=NULL)
			{
				info->Next->Previous = NULL;
			}
		}
		else 
		{
			// Error
			return;
		}
		
	}
	--info->RefCount;
	if (info->RefCount == 0) { UPnPDestructSubscriberInfo(info); }
}

int UPnPSubscriptionExpired(struct SubscriberInfo *info)
{
	int RetVal = 0;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	if ((info->RenewByTime).tv_sec < tv.tv_sec) { RetVal = -1; }
	return(RetVal);
}

void UPnPGetInitialEventBody_AVTransport(struct UPnPDataObject *UPnPObject,char ** body, int *bodylength)
{
	int TempLength;
	TempLength = (int)(25+(int)strlen(UPnPObject->AVTransport_LastChange));
	if ((*body = (char*)malloc(sizeof(char) * TempLength)) == NULL) ILIBCRITICALEXIT(254);
	*bodylength = snprintf(*body, sizeof(char) * TempLength, "LastChange>%s</LastChange",UPnPObject->AVTransport_LastChange);
}
void UPnPGetInitialEventBody_ConnectionManager(struct UPnPDataObject *UPnPObject,char ** body, int *bodylength)
{
	int TempLength;
	TempLength = (int)(177+(int)strlen(UPnPObject->ConnectionManager_SourceProtocolInfo)+(int)strlen(UPnPObject->ConnectionManager_SinkProtocolInfo)+(int)strlen(UPnPObject->ConnectionManager_CurrentConnectionIDs));
	if ((*body = (char*)malloc(sizeof(char) * TempLength)) == NULL) ILIBCRITICALEXIT(254);
	*bodylength = snprintf(*body, sizeof(char) * TempLength, "SourceProtocolInfo>%s</SourceProtocolInfo></e:property><e:property><SinkProtocolInfo>%s</SinkProtocolInfo></e:property><e:property><CurrentConnectionIDs>%s</CurrentConnectionIDs",UPnPObject->ConnectionManager_SourceProtocolInfo,UPnPObject->ConnectionManager_SinkProtocolInfo,UPnPObject->ConnectionManager_CurrentConnectionIDs);
}
void UPnPGetInitialEventBody_RenderingControl(struct UPnPDataObject *UPnPObject,char ** body, int *bodylength)
{
	int TempLength;
	TempLength = (int)(25+(int)strlen(UPnPObject->RenderingControl_LastChange));
	if ((*body = (char*)malloc(sizeof(char) * TempLength)) == NULL) ILIBCRITICALEXIT(254);
	*bodylength = snprintf(*body, sizeof(char) * TempLength, "LastChange>%s</LastChange",UPnPObject->RenderingControl_LastChange);
}


void UPnPProcessUNSUBSCRIBE(struct packetheader *header, struct ILibWebServer_Session *session)
{
	char* SID = NULL;
	int SIDLength = 0;
	struct SubscriberInfo *Info;
	struct packetheader_field_node *f;
	char* packet;
	int packetlength;
	if ((packet = (char*)malloc(50)) == NULL) ILIBCRITICALEXIT(254);
	
	// Iterate through all the HTTP headers
	f = header->FirstField;
	while(f != NULL)
	{
		if (f->FieldLength == 3)
		{
			if (strncasecmp(f->Field, "SID", 3) == 0)
			{
				// Get the Subscription ID
				SID = f->FieldData;
				SIDLength = f->FieldDataLength;
			}
		}
		f = f->NextField;
	}
	sem_wait(&(((struct UPnPDataObject*)session->User)->EventLock));
	if (header->DirectiveObjLength==18 && memcmp(header->DirectiveObj + 1,"AVTransport/event",17)==0)
	{
		Info = UPnPRemoveSubscriberInfo(&(((struct UPnPDataObject*)session->User)->HeadSubscriberPtr_AVTransport),&(((struct UPnPDataObject*)session->User)->NumberOfSubscribers_AVTransport),SID,SIDLength);
		if (Info != NULL)
		{
			--Info->RefCount;
			if (Info->RefCount == 0)
			{
				UPnPDestructSubscriberInfo(Info);
			}
			packetlength = snprintf(packet, 50, "HTTP/1.1 %d %s\r\nContent-Length: 0\r\n\r\n", 200, "OK");
			ILibWebServer_Send_Raw(session, packet, packetlength, 0, 1);
		}
		else
		{
			packetlength = snprintf(packet, 50, "HTTP/1.1 %d %s\r\nContent-Length: 0\r\n\r\n", 412, "Invalid SID");
			ILibWebServer_Send_Raw(session, packet, packetlength, 0, 1);
		}
	}
	else if (header->DirectiveObjLength==24 && memcmp(header->DirectiveObj + 1,"ConnectionManager/event",23)==0)
	{
		Info = UPnPRemoveSubscriberInfo(&(((struct UPnPDataObject*)session->User)->HeadSubscriberPtr_ConnectionManager),&(((struct UPnPDataObject*)session->User)->NumberOfSubscribers_ConnectionManager),SID,SIDLength);
		if (Info != NULL)
		{
			--Info->RefCount;
			if (Info->RefCount == 0)
			{
				UPnPDestructSubscriberInfo(Info);
			}
			packetlength = snprintf(packet, 50, "HTTP/1.1 %d %s\r\nContent-Length: 0\r\n\r\n", 200, "OK");
			ILibWebServer_Send_Raw(session, packet, packetlength, 0, 1);
		}
		else
		{
			packetlength = snprintf(packet, 50, "HTTP/1.1 %d %s\r\nContent-Length: 0\r\n\r\n", 412, "Invalid SID");
			ILibWebServer_Send_Raw(session, packet, packetlength, 0, 1);
		}
	}
	else if (header->DirectiveObjLength==23 && memcmp(header->DirectiveObj + 1,"RenderingControl/event",22)==0)
	{
		Info = UPnPRemoveSubscriberInfo(&(((struct UPnPDataObject*)session->User)->HeadSubscriberPtr_RenderingControl),&(((struct UPnPDataObject*)session->User)->NumberOfSubscribers_RenderingControl),SID,SIDLength);
		if (Info != NULL)
		{
			--Info->RefCount;
			if (Info->RefCount == 0)
			{
				UPnPDestructSubscriberInfo(Info);
			}
			packetlength = snprintf(packet, 50, "HTTP/1.1 %d %s\r\nContent-Length: 0\r\n\r\n", 200, "OK");
			ILibWebServer_Send_Raw(session, packet, packetlength, 0, 1);
		}
		else
		{
			packetlength = snprintf(packet, 50, "HTTP/1.1 %d %s\r\nContent-Length: 0\r\n\r\n", 412, "Invalid SID");
			ILibWebServer_Send_Raw(session, packet, packetlength, 0, 1);
		}
	}
	
	sem_post(&(((struct UPnPDataObject*)session->User)->EventLock));
}

void UPnPTryToSubscribe(char* ServiceName, long Timeout, char* URL, int URLLength, struct ILibWebServer_Session *session)
{
	int *TotalSubscribers = NULL;
	struct SubscriberInfo **HeadPtr = NULL;
	struct SubscriberInfo *NewSubscriber, *TempSubscriber;
	int SIDNumber, rnumber;
	char *SID;
	char *TempString;
	int TempStringLength;
	char *TempString2;
	long TempLong;
	char *packet;
	int packetlength;
	char* path;
	size_t len;
	
	char* escapedURI;
	int escapedURILength;
	
	char *packetbody = NULL;
	int packetbodyLength = 0;
	
	struct parser_result *p;
	struct parser_result *p2;
	
	struct UPnPDataObject *dataObject = (struct UPnPDataObject*)session->User;
	
	if (strncmp(ServiceName,"AVTransport",11)==0)
	{
		TotalSubscribers = &(dataObject->NumberOfSubscribers_AVTransport);
		HeadPtr = &(dataObject->HeadSubscriberPtr_AVTransport);
	}
	if (strncmp(ServiceName,"ConnectionManager",17)==0)
	{
		TotalSubscribers = &(dataObject->NumberOfSubscribers_ConnectionManager);
		HeadPtr = &(dataObject->HeadSubscriberPtr_ConnectionManager);
	}
	if (strncmp(ServiceName,"RenderingControl",16)==0)
	{
		TotalSubscribers = &(dataObject->NumberOfSubscribers_RenderingControl);
		HeadPtr = &(dataObject->HeadSubscriberPtr_RenderingControl);
	}
	
	
	if (*HeadPtr!=NULL)
	{
		NewSubscriber = *HeadPtr;
		while(NewSubscriber != NULL)
		{
			if (UPnPSubscriptionExpired(NewSubscriber) != 0)
			{
				TempSubscriber = NewSubscriber->Next;
				NewSubscriber = UPnPRemoveSubscriberInfo(HeadPtr, TotalSubscribers, NewSubscriber->SID, NewSubscriber->SIDLength);
				UPnPDestructSubscriberInfo(NewSubscriber);
				NewSubscriber = TempSubscriber;
			}
			else
			{
				NewSubscriber = NewSubscriber->Next;
			}
		}
	}
	
	// The Maximum number of subscribers can be bounded
	if (*TotalSubscribers < 10)
	{
		if ((NewSubscriber = (struct SubscriberInfo*)malloc(sizeof(struct SubscriberInfo))) == NULL) ILIBCRITICALEXIT(254);
		memset(NewSubscriber, 0, sizeof(struct SubscriberInfo));
		NewSubscriber->NotLegacy = session->Reserved9;
		
		// The SID must be globally unique, so lets generate it using a bunch of random hex characters
		if ((SID = (char*)malloc(43)) == NULL) ILIBCRITICALEXIT(254);
		memset(SID, 0, 38);
		snprintf(SID, 43, "uuid:");
		for(SIDNumber = 5; SIDNumber <= 12; ++SIDNumber)
		{
			rnumber = rand() % 16;
			snprintf(SID + SIDNumber, 43 - SIDNumber, "%x", rnumber);
		}
		snprintf(SID + SIDNumber, 43 - SIDNumber, "-");
		for(SIDNumber = 14; SIDNumber <= 17; ++SIDNumber)
		{
			rnumber = rand()%16;
			snprintf(SID + SIDNumber, 43 - SIDNumber, "%x", rnumber);
		}
		snprintf(SID + SIDNumber, 43 - SIDNumber, "-");
		for(SIDNumber = 19; SIDNumber <= 22; ++SIDNumber)
		{
			rnumber = rand()%16;
			snprintf(SID + SIDNumber, 43 - SIDNumber, "%x", rnumber);
		}
		snprintf(SID + SIDNumber, 43 - SIDNumber, "-");
		for(SIDNumber = 24; SIDNumber <= 27; ++SIDNumber)
		{
			rnumber = rand()%16;
			snprintf(SID + SIDNumber, 43 - SIDNumber, "%x", rnumber);
		}
		snprintf(SID + SIDNumber, 43 - SIDNumber, "-");
		for(SIDNumber = 29; SIDNumber <= 40; ++SIDNumber)
		{
			rnumber = rand()%16;
			snprintf(SID + SIDNumber, 43 - SIDNumber, "%x", rnumber);
		}
		
		p = ILibParseString(URL, 0, URLLength, "://", 3);
		if (p->NumResults == 1)
		{
			ILibWebServer_Send_Raw(session, "HTTP/1.1 412 Precondition Failed\r\nContent-Length: 0\r\n\r\n", 55, 1, 1);
			ILibDestructParserResults(p);
			return;
		}
		TempString = p->LastResult->data;
		TempStringLength = p->LastResult->datalength;
		ILibDestructParserResults(p);
		p = ILibParseString(TempString, 0, TempStringLength,"/", 1);
		p2 = ILibParseString(p->FirstResult->data, 0, p->FirstResult->datalength, ":", 1);
		if ((TempString2 = (char*)malloc(1 + sizeof(char) * p2->FirstResult->datalength)) == NULL) ILIBCRITICALEXIT(254);
		memcpy(TempString2, p2->FirstResult->data, p2->FirstResult->datalength);
		TempString2[p2->FirstResult->datalength] = '\0';
		NewSubscriber->Address = inet_addr(TempString2);
		if (p2->NumResults == 1)
		{
			NewSubscriber->Port = 80;
			if ((path = (char*)malloc(1+TempStringLength - p2->FirstResult->datalength -1)) == NULL) ILIBCRITICALEXIT(254);
			memcpy(path,TempString + p2->FirstResult->datalength,TempStringLength - p2->FirstResult->datalength -1);
			path[TempStringLength - p2->FirstResult->datalength - 1] = '\0';
			NewSubscriber->Path = path;
			NewSubscriber->PathLength = (int)strlen(path);
		}
		else
		{
			ILibGetLong(p2->LastResult->data,p2->LastResult->datalength,&TempLong);
			NewSubscriber->Port = (unsigned short)TempLong;
			if (TempStringLength == p->FirstResult->datalength)
			{
				if ((path = (char*)malloc(2)) == NULL) ILIBCRITICALEXIT(254);
				memcpy(path, "/", 1);
				path[1] = '\0';
			}
			else
			{
				if ((path = (char*)malloc(1 + TempStringLength - p->FirstResult->datalength - 1)) == NULL) ILIBCRITICALEXIT(254);
				memcpy(path,TempString + p->FirstResult->datalength,TempStringLength - p->FirstResult->datalength - 1);
				path[TempStringLength - p->FirstResult->datalength - 1] = '\0';
			}
			NewSubscriber->Path = path;
			NewSubscriber->PathLength = (int)strlen(path);
		}
		ILibDestructParserResults(p);
		ILibDestructParserResults(p2);
		free(TempString2);
		
		if ((escapedURI = (char*)malloc(ILibHTTPEscapeLength(NewSubscriber->Path))) == NULL) ILIBCRITICALEXIT(254);
		escapedURILength = ILibHTTPEscape(escapedURI, NewSubscriber->Path);
		
		free(NewSubscriber->Path);
		NewSubscriber->Path = escapedURI;
		NewSubscriber->PathLength = escapedURILength;
		
		NewSubscriber->RefCount = 1;
		NewSubscriber->Disposing = 0;
		NewSubscriber->Previous = NULL;
		NewSubscriber->SID = SID;
		NewSubscriber->SIDLength = (int)strlen(SID);
		NewSubscriber->SEQ = 0;
		
		// Determine what the subscription renewal cycle is
		gettimeofday(&(NewSubscriber->RenewByTime),NULL);
		(NewSubscriber->RenewByTime).tv_sec += (int)Timeout;
		
		NewSubscriber->Next = *HeadPtr;
		if (*HeadPtr!=NULL) {(*HeadPtr)->Previous = NewSubscriber;}
		*HeadPtr = NewSubscriber;
		++(*TotalSubscribers);
		LVL3DEBUG(printf("\r\n\r\nSubscribed [%s] %d.%d.%d.%d:%d FOR %d Duration\r\n",NewSubscriber->SID,(NewSubscriber->Address)&0xFF,(NewSubscriber->Address>>8)&0xFF,(NewSubscriber->Address>>16)&0xFF,(NewSubscriber->Address>>24)&0xFF,NewSubscriber->Port,Timeout);)
		LVL3DEBUG(printf("TIMESTAMP: %d <%d>\r\n\r\n",(NewSubscriber->RenewByTime).tv_sec-Timeout,NewSubscriber);)
		
		len = 134 + (int)strlen(SID) + (int)strlen(UPnPPLATFORM) + 4;
		if ((packet = (char*)malloc(len)) == NULL) ILIBCRITICALEXIT(254);
		packetlength = snprintf(packet, len, "HTTP/1.1 200 OK\r\nSERVER: %s, UPnP/1.1, MicroStack/1.0.4144\r\nSID: %s\r\nTIMEOUT: Second-%ld\r\nContent-Length: 0\r\n\r\n",UPnPPLATFORM,SID,Timeout);
		if (strcmp(ServiceName,"AVTransport")==0)
		{
			UPnPGetInitialEventBody_AVTransport(dataObject,&packetbody,&packetbodyLength);
		}
		else if (strcmp(ServiceName,"ConnectionManager")==0)
		{
			UPnPGetInitialEventBody_ConnectionManager(dataObject,&packetbody,&packetbodyLength);
		}
		else if (strcmp(ServiceName,"RenderingControl")==0)
		{
			UPnPGetInitialEventBody_RenderingControl(dataObject,&packetbody,&packetbodyLength);
		}
		
		if (packetbody != NULL)
		{
			ILibWebServer_Send_Raw(session, packet, packetlength, 0, 1);
			UPnPSendEvent_Body(dataObject, packetbody, packetbodyLength, NewSubscriber);
			free(packetbody);
		} 
	}
	else
	{
		// Too many subscribers
		ILibWebServer_Send_Raw(session,"HTTP/1.1 412 Too Many Subscribers\r\nContent-Length: 0\r\n\r\n",56,1,1);
	}
}

void UPnPSubscribeEvents(char* path, int pathlength, char* Timeout, int TimeoutLength, char* URL, int URLLength, struct ILibWebServer_Session* session)
{
	long TimeoutVal;
	char* buffer;
	if ((buffer = (char*)malloc(1 + sizeof(char)*pathlength)) == NULL) ILIBCRITICALEXIT(254);
	
	ILibGetLong(Timeout, TimeoutLength, &TimeoutVal);
	memcpy(buffer, path, pathlength);
	buffer[pathlength] = '\0';
	free(buffer);
	if (TimeoutVal>UPnP_MAX_SUBSCRIPTION_TIMEOUT) { TimeoutVal = UPnP_MAX_SUBSCRIPTION_TIMEOUT; }
	if (pathlength==18 && memcmp(path+1,"AVTransport/event",17)==0)
	{
		UPnPTryToSubscribe("AVTransport",TimeoutVal,URL,URLLength,session);
	}
	else if (pathlength==24 && memcmp(path+1,"ConnectionManager/event",23)==0)
	{
		UPnPTryToSubscribe("ConnectionManager",TimeoutVal,URL,URLLength,session);
	}
	else if (pathlength==23 && memcmp(path+1,"RenderingControl/event",22)==0)
	{
		UPnPTryToSubscribe("RenderingControl",TimeoutVal,URL,URLLength,session);
	}
	else
	{
		ILibWebServer_Send_Raw(session,"HTTP/1.1 412 Invalid Service Name\r\nContent-Length: 0\r\n\r\n",56,1,1);
	}
	
}

void UPnPRenewEvents(char* path, int pathlength, char *_SID,int SIDLength, char* Timeout, int TimeoutLength, struct ILibWebServer_Session *ReaderObject)
{
	struct SubscriberInfo *info = NULL;
	long TimeoutVal;
	struct timeval tv;
	char* packet;
	int packetlength;
	char* SID;
	size_t len;
	
	if ((SID = (char*)malloc(SIDLength + 1)) == NULL) ILIBCRITICALEXIT(254);
	memcpy(SID, _SID, SIDLength);
	SID[SIDLength] = '\0';
	
	LVL3DEBUG(gettimeofday(&tv, NULL);)
	LVL3DEBUG(printf("\r\n\r\nTIMESTAMP: %d\r\n", tv.tv_sec);)
	LVL3DEBUG(printf("SUBSCRIBER [%s] attempting to Renew Events for %s Duration [", SID, Timeout);)
	if (pathlength==18 && memcmp(path+1,"AVTransport/event",17)==0)
	{
		info = ((struct UPnPDataObject*)ReaderObject->User)->HeadSubscriberPtr_AVTransport;
	}
	else if (pathlength==24 && memcmp(path+1,"ConnectionManager/event",23)==0)
	{
		info = ((struct UPnPDataObject*)ReaderObject->User)->HeadSubscriberPtr_ConnectionManager;
	}
	else if (pathlength==23 && memcmp(path+1,"RenderingControl/event",22)==0)
	{
		info = ((struct UPnPDataObject*)ReaderObject->User)->HeadSubscriberPtr_RenderingControl;
	}
	
	
	// Find this SID in the subscriber list, and recalculate the expiration timeout
	while(info != NULL && strcmp(info->SID,SID) != 0)
	{
		info = info->Next;
	}
	if (info != NULL)
	{
		ILibGetLong(Timeout, TimeoutLength, &TimeoutVal);
		if (TimeoutVal>UPnP_MAX_SUBSCRIPTION_TIMEOUT) {TimeoutVal = UPnP_MAX_SUBSCRIPTION_TIMEOUT;}
		
		gettimeofday(&tv,NULL);
		(info->RenewByTime).tv_sec = tv.tv_sec + TimeoutVal;
		
		len = 134 + strlen(SID) + 4;
		if ((packet = (char*)malloc(len)) == NULL) ILIBCRITICALEXIT(254);
		packetlength = snprintf(packet, len, "HTTP/1.1 200 OK\r\nSERVER: %s, UPnP/1.1, MicroStack/1.0.4144\r\nSID: %s\r\nTIMEOUT: Second-%ld\r\nContent-Length: 0\r\n\r\n",UPnPPLATFORM,SID,TimeoutVal);
		ILibWebServer_Send_Raw(ReaderObject, packet, packetlength, 0, 1);
		LVL3DEBUG(printf("OK] {%d} <%d>\r\n\r\n", TimeoutVal, info);)
	}
	else
	{
		LVL3DEBUG(printf("FAILED]\r\n\r\n");)
		ILibWebServer_Send_Raw(ReaderObject, "HTTP/1.1 412 Precondition Failed\r\nContent-Length: 0\r\n\r\n", 55, 1, 1);
	}
	free(SID);
}

void UPnPProcessSUBSCRIBE(struct packetheader *header, struct ILibWebServer_Session *session)
{
	char* SID = NULL;
	int SIDLength = 0;
	char* Timeout = NULL;
	int TimeoutLength = 0;
	char* URL = NULL;
	int URLLength = 0;
	struct parser_result *p;
	struct parser_result *r,*r2;
	struct parser_result_field *prf;
	struct packetheader_field_node *f;
	
	// Iterate through all the HTTP Headers
	f = header->FirstField;
	while(f!=NULL)
	{
		if (f->FieldLength==3 && strncasecmp(f->Field, "SID", 3) == 0)
		{
			// Get the Subscription ID
			SID = f->FieldData;
			SIDLength = f->FieldDataLength;
		}
		else if (f->FieldLength == 8 && strncasecmp(f->Field, "Callback", 8) == 0)
		{
			// Get the Callback URL
			URL = f->FieldData;
			URLLength = f->FieldDataLength;
		}
		else if (f->FieldLength == 7 && strncasecmp(f->Field, "Timeout", 7) == 0)
		{
			// Get the requested timeout value
			Timeout = f->FieldData;
			TimeoutLength = f->FieldDataLength;
		}
		else if (f->FieldLength == 10 && strncasecmp(f->Field, "USER-AGENT", 10) == 0)
		{
			// Check UPnP version of the Control Point which invoked us
			r = ILibParseString(f->FieldData,0,f->FieldDataLength," ",1);
			prf = r->FirstResult;
			while(prf!=NULL)
			{
				if (prf->datalength>5 && memcmp(prf->data, "UPnP/", 5) == 0)
				{
					r2 = ILibParseString(prf->data + 5, 0, prf->datalength - 5, ".", 1);
					r2->FirstResult->data[r2->FirstResult->datalength] = 0;
					r2->LastResult->data[r2->LastResult->datalength] = 0;
					if (atoi(r2->FirstResult->data) == 1 && atoi(r2->LastResult->data) > 0) session->Reserved9 = 1;
					ILibDestructParserResults(r2);
				}
				prf = prf->NextResult;
			}
			ILibDestructParserResults(r);
		}
		f = f->NextField;
	}
	if (Timeout == NULL)
	{
		// It a timeout wasn't specified, force it to a specific value
		Timeout = "7200";
		TimeoutLength = 4;
	}
	else
	{
		p = ILibParseString(Timeout, 0, TimeoutLength, "-", 1);
		if (p->NumResults == 2)
		{
			Timeout = p->LastResult->data;
			TimeoutLength = p->LastResult->datalength;
			if (TimeoutLength == 8 && strncasecmp(Timeout, "INFINITE", 8) == 0)
			{
				// Infinite timeouts will cause problems, so we don't allow it
				Timeout = "7200";
				TimeoutLength = 4;
			}
		}
		else
		{
			Timeout = "7200";
			TimeoutLength = 4;
		}
		ILibDestructParserResults(p);
	}
	if (SID == NULL)
	{
		// If not SID was specified, this is a subscription request
		// Subscribe
		UPnPSubscribeEvents(header->DirectiveObj, header->DirectiveObjLength, Timeout, TimeoutLength, URL, URLLength, session);
	}
	else
	{
		// If a SID was specified, it is a renewal request for an existing subscription
		// Renew
		UPnPRenewEvents(header->DirectiveObj, header->DirectiveObjLength, SID, SIDLength, Timeout, TimeoutLength, session);
	}
}
void UPnPProcessHTTPPacket(struct ILibWebServer_Session *session, struct packetheader* header, char *bodyBuffer, int offset, int bodyBufferLength)
{
	struct UPnPDataObject *dataObject = (struct UPnPDataObject*)session->User;
	#if defined(WIN32) || defined(_WIN32_WCE)
	char *responseHeader = "\r\nCONTENT-TYPE:  text/xml; charset=\"utf-8\"\r\nServer: WINDOWS, UPnP/1.1, MicroStack/1.0.4144";
	#elif defined(__SYMBIAN32__)
	char *responseHeader = "\r\nCONTENT-TYPE:  text/xml; charset=\"utf-8\"\r\nServer: SYMBIAN, UPnP/1.1, MicroStack/1.0.4144";
	#else
	char *responseHeader = "\r\nCONTENT-TYPE:  text/xml; charset=\"utf-8\"\r\nServer: POSIX, UPnP/1.1, MicroStack/1.0.4144";
	#endif
	char *errorTemplate = "HTTP/1.1 %d %s\r\nServer: %s, UPnP/1.1, MicroStack/1.0.4144\r\nContent-Length: 0\r\n\r\n";
	char *errorPacket;
	int errorPacketLength;
	char *buffer;
	
	LVL3DEBUG(errorPacketLength = ILibGetRawPacket(header, &errorPacket);)
	LVL3DEBUG(printf("%s\r\n",errorPacket);)
	LVL3DEBUG(free(errorPacket);)			
	
	
	if (header->DirectiveLength == 4 && memcmp(header->Directive,"HEAD", 4) == 0)
	{
		if (header->DirectiveObjLength == 1 && memcmp(header->DirectiveObj, "/", 1) == 0)
		{
			// A HEAD request for the device description document.
			// We stream the document back, so we don't return content length or anything because the actual response won't have it either
			ILibWebServer_StreamHeader_Raw(session, 200, "OK", responseHeader, 1);
			ILibWebServer_StreamBody(session, NULL, 0, ILibAsyncSocket_MemoryOwnership_STATIC, 1);
		}
		else if (header->DirectiveObjLength==21 && memcmp((header->DirectiveObj)+1,"AVTransport/scpd.xml",20)==0)
		{
			ILibWebServer_StreamHeader_Raw(session,200,"OK",responseHeader,1);
			ILibWebServer_StreamBody(session,NULL,0,ILibAsyncSocket_MemoryOwnership_STATIC,1);
		}
		else if (header->DirectiveObjLength==27 && memcmp((header->DirectiveObj)+1,"ConnectionManager/scpd.xml",26)==0)
		{
			ILibWebServer_StreamHeader_Raw(session,200,"OK",responseHeader,1);
			ILibWebServer_StreamBody(session,NULL,0,ILibAsyncSocket_MemoryOwnership_STATIC,1);
		}
		else if (header->DirectiveObjLength==26 && memcmp((header->DirectiveObj)+1,"RenderingControl/scpd.xml",25)==0)
		{
			ILibWebServer_StreamHeader_Raw(session,200,"OK",responseHeader,1);
			ILibWebServer_StreamBody(session,NULL,0,ILibAsyncSocket_MemoryOwnership_STATIC,1);
		}
		
		else
		{
			// A HEAD request for something we don't have
			if ((errorPacket = (char*)malloc(128)) == NULL) ILIBCRITICALEXIT(254);
			errorPacketLength = snprintf(errorPacket, 128, errorTemplate, 404, "File Not Found", UPnPPLATFORM);
			ILibWebServer_Send_Raw(session, errorPacket, errorPacketLength, 0, 1);
		}
	}
	else if (header->DirectiveLength == 3 && memcmp(header->Directive, "GET", 3) == 0)
	{
		if (header->DirectiveObjLength == 1 && memcmp(header->DirectiveObj,"/", 1) == 0)
		{
			// A GET Request for the device description document, so lets stream it back to the client
			ILibWebServer_StreamHeader_Raw(session, 200, "OK", responseHeader, 1);
			ILibWebServer_StreamBody(session, dataObject->DeviceDescription, dataObject->DeviceDescriptionLength, 1, 1);
		}
		else if (header->DirectiveObjLength==21 && memcmp((header->DirectiveObj)+1,"AVTransport/scpd.xml",20)==0)
		{
			buffer = ILibDecompressString((unsigned char*)UPnPAVTransportDescription,UPnPAVTransportDescriptionLength,UPnPAVTransportDescriptionLengthUX);
			ILibWebServer_Send_Raw(session,buffer,UPnPAVTransportDescriptionLengthUX,0,1);
		}
		else if (header->DirectiveObjLength==27 && memcmp((header->DirectiveObj)+1,"ConnectionManager/scpd.xml",26)==0)
		{
			buffer = ILibDecompressString((unsigned char*)UPnPConnectionManagerDescription,UPnPConnectionManagerDescriptionLength,UPnPConnectionManagerDescriptionLengthUX);
			ILibWebServer_Send_Raw(session,buffer,UPnPConnectionManagerDescriptionLengthUX,0,1);
		}
		else if (header->DirectiveObjLength==26 && memcmp((header->DirectiveObj)+1,"RenderingControl/scpd.xml",25)==0)
		{
			buffer = ILibDecompressString((unsigned char*)UPnPRenderingControlDescription,UPnPRenderingControlDescriptionLength,UPnPRenderingControlDescriptionLengthUX);
			ILibWebServer_Send_Raw(session,buffer,UPnPRenderingControlDescriptionLengthUX,0,1);
		}
		
		else
		{
			// A GET Request for something we don't have
			if ((errorPacket = (char*)malloc(128)) == NULL) ILIBCRITICALEXIT(254);
			errorPacketLength = snprintf(errorPacket, 128, errorTemplate, 404, "File Not Found", UPnPPLATFORM);
			ILibWebServer_Send_Raw(session, errorPacket, errorPacketLength, 0, 1);
		}
	}
	else if (header->DirectiveLength == 4 && memcmp(header->Directive,"POST",4) == 0)
	{
		// Defer Control to the POST Handler
		if (UPnPProcessPOST(session, header, bodyBuffer, offset, bodyBufferLength) != 0)
		{
			// A POST for an action that doesn't exist
			UPnPResponse_Error(session, 401, "Invalid Action");
		}
	}
	else if (header->DirectiveLength == 9 && memcmp(header->Directive, "SUBSCRIBE" ,9) == 0)
	{
		// Subscription Handler
		UPnPProcessSUBSCRIBE(header,session);
	}
	else if (header->DirectiveLength == 11 && memcmp(header->Directive, "UNSUBSCRIBE", 11) == 0)
	{
		// UnSubscribe Handler
		UPnPProcessUNSUBSCRIBE(header,session);
	}	else
	{
		// The client tried something we didn't expect/support
		if ((errorPacket = (char*)malloc(128)) == NULL) ILIBCRITICALEXIT(254);
		errorPacketLength = snprintf(errorPacket, 128, errorTemplate, 400, "Bad Request", UPnPPLATFORM);
		ILibWebServer_Send_Raw(session, errorPacket, errorPacketLength, ILibAsyncSocket_MemoryOwnership_CHAIN, 1);
	}
}
void UPnPFragmentedSendNotify_Destroy(void *data);
void UPnPMasterPreSelect(void* object, void *socketset, void *writeset, void *errorset, int* blocktime)
{
	int i;
	struct UPnPDataObject *UPnPObject = (struct UPnPDataObject*)object;	
	struct UPnPFragmentNotifyStruct *f;
	int timeout;
	UNREFERENCED_PARAMETER( socketset );
	UNREFERENCED_PARAMETER( writeset );
	UNREFERENCED_PARAMETER( errorset );
	UNREFERENCED_PARAMETER( blocktime );
	
	if (UPnPObject->InitialNotify == 0)
	{
		// The initial "HELLO" packets were not sent yet, so lets send them
		UPnPObject->InitialNotify = -1;
		
		// In case we were interrupted, we need to flush out the caches of
		// all the control points by sending a "byebye" first, to insure
		// control points don't ignore our "hello" packets thinking they are just
		// periodic re-advertisements.
		UPnPSendByeBye(UPnPObject);
		
		// PacketNumber 0 is the controller, for the rest of the packets. Send
		// one of these to send out an advertisement "group"
		if ((f = (struct UPnPFragmentNotifyStruct*)malloc(sizeof(struct UPnPFragmentNotifyStruct))) == NULL) ILIBCRITICALEXIT(254);
		f->packetNumber = 0;
		f->upnp = UPnPObject;
		
		// We need to inject some delay in these packets to space them out,
		// otherwise we could overflow the inbound buffer of the recipient, causing them
		// to lose packets. And UPnP/1.0 control points are not as robust as UPnP/1.1 control points,
		// so they need all the help they can get ;)
		timeout = (int)(0 + ((unsigned short)rand() % (500)));
		do { f->upnp->InitialNotify = rand(); } while (f->upnp->InitialNotify == 0);
		
		// Register for the timed callback, to actually send the packet
		ILibLifeTime_AddEx(f->upnp->WebServerTimer, f, timeout, &UPnPFragmentedSendNotify, &UPnPFragmentedSendNotify_Destroy);
	}
	
	if (UPnPObject->UpdateFlag != 0)
	{
		// Somebody told us that we should recheck our IP Address table, as one of them may have changed
		UPnPObject->UpdateFlag = 0;
		
		// Release all of our UPnP/1.1 unicast sockets. We'll re-initialise them when we iterate through all the current IP Addresses
		UPnPFreeUnicastReceiveSockets(UPnPObject);
		ILibChain_SafeRemove(UPnPObject->Chain, UPnPObject->MulticastEventListener);
		// Clear Sockets
		// Iterate through all the currently bound IPv4 addresses and release the sockets
		if (UPnPObject->AddressListV4 != NULL)
		{
			for (i = 0; i < UPnPObject->AddressListV4Length; ++i) ILibChain_SafeRemove(UPnPObject->Chain, UPnPObject->NOTIFY_SEND_socks[i]);
			free(UPnPObject->NOTIFY_SEND_socks);
			for (i = 0; i < UPnPObject->AddressListV4Length; ++i) ILibChain_SafeRemove(UPnPObject->Chain, UPnPObject->NOTIFY_RECEIVE_socks[i]);
			free(UPnPObject->NOTIFY_RECEIVE_socks);
			free(UPnPObject->AddressListV4);
		}
		if (UPnPObject->AddressListV6 != NULL)
		{
			for (i = 0; i < UPnPObject->AddressListV6Length; ++i) ILibChain_SafeRemove(UPnPObject->Chain, UPnPObject->NOTIFY_SEND_socks6[i]);
			free(UPnPObject->NOTIFY_SEND_socks6);
			for (i = 0; i < UPnPObject->AddressListV6Length; ++i) ILibChain_SafeRemove(UPnPObject->Chain, UPnPObject->NOTIFY_RECEIVE_socks6[i]);
			free(UPnPObject->NOTIFY_RECEIVE_socks6);
			free(UPnPObject->AddressListV6);
		}
		
		// Fetch a current list of ip addresses
		UPnPObject->AddressListV4Length = ILibGetLocalIPv4AddressList(&(UPnPObject->AddressListV4), 1);
		
		// Re-Initialize our SEND socket
		if ((UPnPObject->NOTIFY_SEND_socks = (void**)malloc(sizeof(void*)*(UPnPObject->AddressListV4Length))) == NULL) ILIBCRITICALEXIT(254);
		if ((UPnPObject->NOTIFY_RECEIVE_socks = (void**)malloc(sizeof(void*)*(UPnPObject->AddressListV4Length))) == NULL) ILIBCRITICALEXIT(254);
		
		// Test IPv6 support
		if (ILibDetectIPv6Support())
		{
			// Fetch the list of local IPv6 interfaces
			UPnPObject->AddressListV6Length = ILibGetLocalIPv6List(&(UPnPObject->AddressListV6));
			
			// Setup the IPv6 sockets
			if ((UPnPObject->NOTIFY_SEND_socks6 = (void**)malloc(sizeof(void*)*(UPnPObject->AddressListV6Length))) == NULL) ILIBCRITICALEXIT(254);
			if ((UPnPObject->NOTIFY_RECEIVE_socks6 = (void**)malloc(sizeof(void*)*(UPnPObject->AddressListV6Length))) == NULL) ILIBCRITICALEXIT(254);
		}
		
		// Iterate through all the current IP Addresses
		for (i = 0; i < UPnPObject->AddressListV4Length; ++i)
		{
			(UPnPObject->AddressListV4[i]).sin_port = 0; // Bind to ANY port for outbound packets
			UPnPObject->NOTIFY_SEND_socks[i] = ILibAsyncUDPSocket_CreateEx(
			UPnPObject->Chain,
			UPNP_MAX_SSDP_HEADER_SIZE,
			(struct sockaddr*)&(UPnPObject->AddressListV4[i]),
			ILibAsyncUDPSocket_Reuse_SHARED,
			NULL,
			NULL,
			UPnPObject);
			
			ILibAsyncUDPSocket_SetMulticastTTL(UPnPObject->NOTIFY_SEND_socks[i], UPNP_SSDP_TTL);
			ILibAsyncUDPSocket_SetMulticastLoopback(UPnPObject->NOTIFY_SEND_socks[i], 1);
			
			(UPnPObject->AddressListV4[i]).sin_port = htons(UPNP_PORT); // Bind to UPnP port for inbound packets
			UPnPObject->NOTIFY_RECEIVE_socks[i] = ILibAsyncUDPSocket_CreateEx(
			UPnPObject->Chain,
			UPNP_MAX_SSDP_HEADER_SIZE,
			(struct sockaddr*)&(UPnPObject->AddressListV4[i]),
			ILibAsyncUDPSocket_Reuse_SHARED,
			&UPnPSSDPSink,
			NULL,
			UPnPObject);
			
			ILibAsyncUDPSocket_JoinMulticastGroupV4(UPnPObject->NOTIFY_RECEIVE_socks[i], (struct sockaddr_in*)&(UPnPObject->MulticastAddrV4), (struct sockaddr*)&(UPnPObject->AddressListV4[i]));
			ILibAsyncUDPSocket_SetMulticastLoopback(UPnPObject->NOTIFY_RECEIVE_socks[i], 1);
			/*
			UPnPObject->MulticastEventListener = ILibAsyncUDPSocket_Create(UPnPObject->Chain, UPNP_MAX_SSDP_HEADER_SIZE, 0, UPNP_MULTICASTEVENT_PORT, ILibAsyncUDPSocket_Reuse_SHARED, &OnUPnPMulticastEvent, NULL, UPnPObject);
			ILibAsyncUDPSocket_JoinMulticastGroup(UPnPObject->MulticastEventListener, UPnPObject->AddressList[i], inet_addr(UPNP_MCASTv4_GROUP));
			*/
		}
		// Re-initialise our UPnP/1.1 unicast sockets
		UPnPBindUnicastReceiveSockets(UPnPObject);
		
		if (UPnPObject->AddressListV6Length > 0)
		{
			// Iterate through all the current IPv6 interfaces
			for (i = 0; i < UPnPObject->AddressListV6Length; ++i)
			{
				(UPnPObject->AddressListV6[i]).sin6_port = 0;
				UPnPObject->NOTIFY_SEND_socks6[i] = ILibAsyncUDPSocket_CreateEx(
				UPnPObject->Chain,
				UPNP_MAX_SSDP_HEADER_SIZE,
				(struct sockaddr*)&(UPnPObject->AddressListV6[i]),
				ILibAsyncUDPSocket_Reuse_SHARED,
				NULL,
				NULL,
				UPnPObject);
				
				ILibAsyncUDPSocket_SetMulticastTTL(UPnPObject->NOTIFY_SEND_socks6[i], UPNP_SSDP_TTL);
				ILibAsyncUDPSocket_SetMulticastLoopback(UPnPObject->NOTIFY_SEND_socks6[i], 1);
				
				(UPnPObject->AddressListV6[i]).sin6_port = htons(UPNP_PORT); // Bind to UPnP port for inbound packets
				UPnPObject->NOTIFY_RECEIVE_socks6[i] = ILibAsyncUDPSocket_CreateEx(
				UPnPObject->Chain,
				UPNP_MAX_SSDP_HEADER_SIZE,
				(struct sockaddr*)&(UPnPObject->AddressListV6[i]),
				ILibAsyncUDPSocket_Reuse_SHARED,
				&UPnPSSDPSink,
				NULL,
				UPnPObject);
				
				if (ILibAsyncSocket_IsIPv6LinkLocal((struct sockaddr*)&(UPnPObject->AddressListV6[i])))
				{
					ILibAsyncUDPSocket_JoinMulticastGroupV6(UPnPObject->NOTIFY_RECEIVE_socks6[i], &(UPnPObject->MulticastAddrV6LL), UPnPObject->AddressListV6[i].sin6_scope_id);
				}
				else
				{
					ILibAsyncUDPSocket_JoinMulticastGroupV6(UPnPObject->NOTIFY_RECEIVE_socks6[i], &(UPnPObject->MulticastAddrV6SL), UPnPObject->AddressListV6[i].sin6_scope_id);
				}
				ILibAsyncUDPSocket_SetMulticastLoopback(UPnPObject->NOTIFY_RECEIVE_socks6[i], 1);
				/*
				UPnPObject->MulticastEventListener = ILibAsyncUDPSocket_Create(UPnPObject->Chain, UPNP_MAX_SSDP_HEADER_SIZE, 0, UPNP_MULTICASTEVENT_PORT, ILibAsyncUDPSocket_Reuse_SHARED, &OnUPnPMulticastEvent, NULL, UPnPObject);
				ILibAsyncUDPSocket_JoinMulticastGroup(UPnPObject->MulticastEventListener, UPnPObject->AddressList[i], inet_addr(UPNP_MCASTv6_GROUP));
				*/
			}
		}
		
		// Iterate through all the packet types, and re-broadcast
		for (i = 1; i <= 4; ++i)
		{
			if ((f = (struct UPnPFragmentNotifyStruct*)malloc(sizeof(struct UPnPFragmentNotifyStruct))) == NULL) ILIBCRITICALEXIT(254);
			f->packetNumber = i;
			f->upnp = UPnPObject;
			
			// Inject some random delay, to spread these packets out, to help prevent the inbound buffer of the recipient from overflowing, causing dropped packets.
			timeout = (int)(0 + ((unsigned short)rand() % (500)));
			ILibLifeTime_AddEx(f->upnp->WebServerTimer, f, timeout, &UPnPFragmentedSendNotify, &UPnPFragmentedSendNotify_Destroy);
		}
	}
}

void UPnPFragmentedSendNotify_Destroy(void *data)
{
	free(data);
}

void UPnPFragmentedSendNotify(void *data)
{
	int i,i2;
	int subsetRange;
	int timeout, timeout2;
	struct UPnPFragmentNotifyStruct *f;
	struct UPnPFragmentNotifyStruct *FNS = (struct UPnPFragmentNotifyStruct*)data;
	
	if (FNS->packetNumber == 0)
	{				
		subsetRange = 5000 / 5; // Make sure all our packets will get out within 5 seconds
		
		// Send the first "group"
		for (i2 = 0; i2 <= 4; ++i2)
		{
			if ((f = (struct UPnPFragmentNotifyStruct*)malloc(sizeof(struct UPnPFragmentNotifyStruct))) == NULL) ILIBCRITICALEXIT(254);
			f->packetNumber = i2 + 1;
			f->upnp = FNS->upnp;
			timeout2 = (rand() % subsetRange);
			ILibLifeTime_AddEx(FNS->upnp->WebServerTimer, f, timeout2, &UPnPFragmentedSendNotify, &UPnPFragmentedSendNotify_Destroy);
		}
		
		// Now Repeat this "group" after 7 seconds, to insure there is no overlap
		for (i2 = 0; i2 <= 4; ++i2)
		{
			if ((f = (struct UPnPFragmentNotifyStruct*)malloc(sizeof(struct UPnPFragmentNotifyStruct))) == NULL) ILIBCRITICALEXIT(254);
			f->packetNumber = i2 + 1;
			f->upnp = FNS->upnp;
			timeout2 = 7000 + (rand() % subsetRange);
			ILibLifeTime_AddEx(FNS->upnp->WebServerTimer, f, timeout2, &UPnPFragmentedSendNotify, &UPnPFragmentedSendNotify_Destroy);
		}
		
		// Calculate the next transmission window and spread the packets
		timeout = (int)((FNS->upnp->NotifyCycleTime / 4) + ((unsigned short)rand() % (FNS->upnp->NotifyCycleTime / 2 - FNS->upnp->NotifyCycleTime / 4)));
		ILibLifeTime_Add(FNS->upnp->WebServerTimer, FNS, timeout, &UPnPFragmentedSendNotify, &UPnPFragmentedSendNotify_Destroy);
	}
	
	for (i = 0; i < FNS->upnp->AddressListV4Length; ++i)
	{
		switch(FNS->packetNumber)
		{
			case 1:
			UPnPBuildSendSsdpNotifyPacket(FNS->upnp->NOTIFY_SEND_socks[i], FNS->upnp, (struct sockaddr*)&(FNS->upnp->AddressListV4[i]), 0, "::upnp:rootdevice", "upnp:rootdevice", "");
			break;
			case 2:
			UPnPBuildSendSsdpNotifyPacket(FNS->upnp->NOTIFY_SEND_socks[i], FNS->upnp, (struct sockaddr*)&(FNS->upnp->AddressListV4[i]), 0, "", "uuid:", FNS->upnp->UDN);
			break;
			case 3:
			UPnPBuildSendSsdpNotifyPacket(FNS->upnp->NOTIFY_SEND_socks[i], FNS->upnp, (struct sockaddr*)&(FNS->upnp->AddressListV4[i]), 0, "::urn:schemas-upnp-org:device:MediaRenderer:1", "urn:schemas-upnp-org:device:MediaRenderer:1", "");
			break;
			case 4:
			UPnPBuildSendSsdpNotifyPacket(FNS->upnp->NOTIFY_SEND_socks[i], FNS->upnp, (struct sockaddr*)&(FNS->upnp->AddressListV4[i]), 0, "::urn:schemas-upnp-org:service:AVTransport:1", "urn:schemas-upnp-org:service:AVTransport:1", "");
			break;
			case 5:
			UPnPBuildSendSsdpNotifyPacket(FNS->upnp->NOTIFY_SEND_socks[i], FNS->upnp, (struct sockaddr*)&(FNS->upnp->AddressListV4[i]), 0, "::urn:schemas-upnp-org:service:ConnectionManager:1", "urn:schemas-upnp-org:service:ConnectionManager:1", "");
			break;
			case 6:
			UPnPBuildSendSsdpNotifyPacket(FNS->upnp->NOTIFY_SEND_socks[i], FNS->upnp, (struct sockaddr*)&(FNS->upnp->AddressListV4[i]), 0, "::urn:schemas-upnp-org:service:RenderingControl:1", "urn:schemas-upnp-org:service:RenderingControl:1", "");
			break;
			
		}
	}
	
	for (i = 0; i < FNS->upnp->AddressListV6Length; ++i)
	{
		switch(FNS->packetNumber)
		{
			case 1:
			UPnPBuildSendSsdpNotifyPacket(FNS->upnp->NOTIFY_SEND_socks6[i], FNS->upnp, (struct sockaddr*)&(FNS->upnp->AddressListV6[i]), 0, "::upnp:rootdevice", "upnp:rootdevice", "");
			break;
			case 2:
			UPnPBuildSendSsdpNotifyPacket(FNS->upnp->NOTIFY_SEND_socks6[i], FNS->upnp, (struct sockaddr*)&(FNS->upnp->AddressListV6[i]), 0, "", "uuid:", FNS->upnp->UDN);
			break;
			case 3:
			UPnPBuildSendSsdpNotifyPacket(FNS->upnp->NOTIFY_SEND_socks6[i], FNS->upnp, (struct sockaddr*)&(FNS->upnp->AddressListV6[i]), 0, "::urn:schemas-upnp-org:device:MediaRenderer:1", "urn:schemas-upnp-org:device:MediaRenderer:1", "");
			break;
			case 4:
			UPnPBuildSendSsdpNotifyPacket(FNS->upnp->NOTIFY_SEND_socks6[i], FNS->upnp, (struct sockaddr*)&(FNS->upnp->AddressListV6[i]), 0, "::urn:schemas-upnp-org:service:AVTransport:1", "urn:schemas-upnp-org:service:AVTransport:1", "");
			break;
			case 5:
			UPnPBuildSendSsdpNotifyPacket(FNS->upnp->NOTIFY_SEND_socks6[i], FNS->upnp, (struct sockaddr*)&(FNS->upnp->AddressListV6[i]), 0, "::urn:schemas-upnp-org:service:ConnectionManager:1", "urn:schemas-upnp-org:service:ConnectionManager:1", "");
			break;
			case 6:
			UPnPBuildSendSsdpNotifyPacket(FNS->upnp->NOTIFY_SEND_socks6[i], FNS->upnp, (struct sockaddr*)&(FNS->upnp->AddressListV6[i]), 0, "::urn:schemas-upnp-org:service:RenderingControl:1", "urn:schemas-upnp-org:service:RenderingControl:1", "");
			break;
			
		}
	}
	
	if (FNS->packetNumber != 0) free(FNS);
}


void UPnPSendNotify(const struct UPnPDataObject *upnp)
{
	int i, i2;
	for (i=0;i<upnp->AddressListV4Length;++i)
	{
		for (i2=0; i2<2; i2++)
		{
			UPnPBuildSendSsdpNotifyPacket(upnp->NOTIFY_SEND_socks[i], upnp, (struct sockaddr*)&(upnp->AddressListV4[i]), 0, "::upnp:rootdevice", "upnp:rootdevice", "");
			UPnPBuildSendSsdpNotifyPacket(upnp->NOTIFY_SEND_socks[i], upnp, (struct sockaddr*)&(upnp->AddressListV4[i]), 0, "", "uuid:", upnp->UDN);
			UPnPBuildSendSsdpNotifyPacket(upnp->NOTIFY_SEND_socks[i], upnp, (struct sockaddr*)&(upnp->AddressListV4[i]), 0, "::urn:schemas-upnp-org:device:MediaRenderer:1", "urn:schemas-upnp-org:device:MediaRenderer:1", "");
			UPnPBuildSendSsdpNotifyPacket(upnp->NOTIFY_SEND_socks[i], upnp, (struct sockaddr*)&(upnp->AddressListV4[i]), 0, "::urn:schemas-upnp-org:service:AVTransport:1", "urn:schemas-upnp-org:service:AVTransport:1", "");
			UPnPBuildSendSsdpNotifyPacket(upnp->NOTIFY_SEND_socks[i], upnp, (struct sockaddr*)&(upnp->AddressListV4[i]), 0, "::urn:schemas-upnp-org:service:ConnectionManager:1", "urn:schemas-upnp-org:service:ConnectionManager:1", "");
			UPnPBuildSendSsdpNotifyPacket(upnp->NOTIFY_SEND_socks[i], upnp, (struct sockaddr*)&(upnp->AddressListV4[i]), 0, "::urn:schemas-upnp-org:service:RenderingControl:1", "urn:schemas-upnp-org:service:RenderingControl:1", "");
			
		}
	}
	for (i=0;i<upnp->AddressListV6Length;++i)
	{
		for (i2=0; i2<2; i2++)
		{
			UPnPBuildSendSsdpNotifyPacket(upnp->NOTIFY_SEND_socks6[i], upnp, (struct sockaddr*)&(upnp->AddressListV6[i]), 0, "::upnp:rootdevice", "upnp:rootdevice", "");
			UPnPBuildSendSsdpNotifyPacket(upnp->NOTIFY_SEND_socks6[i], upnp, (struct sockaddr*)&(upnp->AddressListV6[i]), 0, "", "uuid:", upnp->UDN);
			UPnPBuildSendSsdpNotifyPacket(upnp->NOTIFY_SEND_socks6[i], upnp, (struct sockaddr*)&(upnp->AddressListV6[i]), 0, "::urn:schemas-upnp-org:device:MediaRenderer:1", "urn:schemas-upnp-org:device:MediaRenderer:1", "");
			UPnPBuildSendSsdpNotifyPacket(upnp->NOTIFY_SEND_socks6[i], upnp, (struct sockaddr*)&(upnp->AddressListV6[i]), 0, "::urn:schemas-upnp-org:service:AVTransport:1", "urn:schemas-upnp-org:service:AVTransport:1", "");
			UPnPBuildSendSsdpNotifyPacket(upnp->NOTIFY_SEND_socks6[i], upnp, (struct sockaddr*)&(upnp->AddressListV6[i]), 0, "::urn:schemas-upnp-org:service:ConnectionManager:1", "urn:schemas-upnp-org:service:ConnectionManager:1", "");
			UPnPBuildSendSsdpNotifyPacket(upnp->NOTIFY_SEND_socks6[i], upnp, (struct sockaddr*)&(upnp->AddressListV6[i]), 0, "::urn:schemas-upnp-org:service:RenderingControl:1", "urn:schemas-upnp-org:service:RenderingControl:1", "");
			
		}
	}
}

int UPnPBuildSendSsdpByeByePacket(void* module, const struct UPnPDataObject *upnp, struct sockaddr* target, char* mcastgroup, char* USNex, char* NT, char* NTex, int DeviceID)
{
	int len;
	
	if (DeviceID == 0)
	{
		len = snprintf(ILibScratchPad, sizeof(ILibScratchPad), "NOTIFY * HTTP/1.1\r\nCONFIGID.UPNP.ORG: %d\r\nSEARCHPORT.UPNP.ORG: %u\r\nBOOTID.UPNP.ORG: %d\r\nMAXVERSION.UPNP.ORG: %d\r\nHOST: %s:1900\r\nNTS: ssdp:byebye\r\nUSN: uuid:%s%s\r\nNT: %s%s\r\nContent-Length: 0\r\n\r\n", upnp->ConfigID, upnp->UnicastReceiveSocketPortNumber, upnp->InitialNotify, 1, mcastgroup, upnp->UDN, USNex, NT, NTex);
	}
	else
	{
		if (memcmp(NT, "uuid:", 5) == 0)
		{
			len = snprintf(ILibScratchPad, sizeof(ILibScratchPad), "NOTIFY * HTTP/1.1\r\nCONFIGID.UPNP.ORG: %d\r\nSEARCHPORT.UPNP.ORG: %u\r\nBOOTID.UPNP.ORG: %d\r\nMAXVERSION.UPNP.ORG: %d\r\nHOST: %s:1900\r\nNTS: ssdp:byebye\r\nUSN: uuid:%s_%d%s\r\nNT: %s%s_%d\r\nContent-Length: 0\r\n\r\n", upnp->ConfigID, upnp->UnicastReceiveSocketPortNumber, upnp->InitialNotify, 1, mcastgroup, upnp->UDN, DeviceID, USNex, NT, NTex, DeviceID);
		}
		else
		{
			len = snprintf(ILibScratchPad, sizeof(ILibScratchPad), "NOTIFY * HTTP/1.1\r\nCONFIGID.UPNP.ORG: %d\r\nSEARCHPORT.UPNP.ORG: %u\r\nBOOTID.UPNP.ORG: %d\r\nMAXVERSION.UPNP.ORG: %d\r\nHOST: %s:1900\r\nNTS: ssdp:byebye\r\nUSN: uuid:%s_%d%s\r\nNT: %s%s\r\nContent-Length: 0\r\n\r\n", upnp->ConfigID, upnp->UnicastReceiveSocketPortNumber, upnp->InitialNotify, 1, mcastgroup, upnp->UDN, DeviceID, USNex, NT, NTex);
		}
	}
	return ILibAsyncUDPSocket_SendTo(module, target, ILibScratchPad, len, ILibAsyncSocket_MemoryOwnership_USER);
}

void UPnPSendByeBye(const struct UPnPDataObject *upnp)
{
	int i, i2;
	struct sockaddr* t1;
	char* t2;
	int TempVal = 0;
	
	for (i=0; i<upnp->AddressListV4Length; ++i)
	{	
		if (upnp->InitialNotify != -1) TempVal = upnp->InitialNotify;  
		for (i2=0; i2<2; i2++)
		{
			UPnPBuildSendSsdpByeByePacket(upnp->NOTIFY_SEND_socks[i], upnp, (struct sockaddr*)&(upnp->MulticastAddrV4), UPNP_MCASTv4_GROUP, "::upnp:rootdevice", "upnp:rootdevice", "", 0);
			UPnPBuildSendSsdpByeByePacket(upnp->NOTIFY_SEND_socks[i], upnp, (struct sockaddr*)&(upnp->MulticastAddrV4), UPNP_MCASTv4_GROUP, "", "uuid:", upnp->UDN, 0);
			UPnPBuildSendSsdpByeByePacket(upnp->NOTIFY_SEND_socks[i], upnp, (struct sockaddr*)&(upnp->MulticastAddrV4), UPNP_MCASTv4_GROUP, "::urn:schemas-upnp-org:device:MediaRenderer:1", "urn:schemas-upnp-org:device:MediaRenderer:1", "", 0);
			UPnPBuildSendSsdpByeByePacket(upnp->NOTIFY_SEND_socks[i], upnp, (struct sockaddr*)&(upnp->MulticastAddrV4), UPNP_MCASTv4_GROUP, "::urn:schemas-upnp-org:service:AVTransport:1", "urn:schemas-upnp-org:service:AVTransport:1", "", 0);
			UPnPBuildSendSsdpByeByePacket(upnp->NOTIFY_SEND_socks[i], upnp, (struct sockaddr*)&(upnp->MulticastAddrV4), UPNP_MCASTv4_GROUP, "::urn:schemas-upnp-org:service:ConnectionManager:1", "urn:schemas-upnp-org:service:ConnectionManager:1", "", 0);
			UPnPBuildSendSsdpByeByePacket(upnp->NOTIFY_SEND_socks[i], upnp, (struct sockaddr*)&(upnp->MulticastAddrV4), UPNP_MCASTv4_GROUP, "::urn:schemas-upnp-org:service:RenderingControl:1", "urn:schemas-upnp-org:service:RenderingControl:1", "", 0);
			
		}
	}
	
	for (i=0; i<upnp->AddressListV6Length; ++i)
	{	
		if (ILibAsyncSocket_IsIPv6LinkLocal((struct sockaddr*)&(upnp->AddressListV6[i])))
		{
			t1 = (struct sockaddr*)&(upnp->MulticastAddrV6LL);
			t2 = UPNP_MCASTv6_LINK_GROUPB;
		}
		else
		{
			t1 = (struct sockaddr*)&(upnp->MulticastAddrV6SL);
			t2 = UPNP_MCASTv6_GROUPB;
		}
		
		for (i2=0; i2<2; i2++)
		{
			UPnPBuildSendSsdpByeByePacket(upnp->NOTIFY_SEND_socks6[i], upnp, t1, t2, "::upnp:rootdevice", "upnp:rootdevice", "", 0);
			UPnPBuildSendSsdpByeByePacket(upnp->NOTIFY_SEND_socks6[i], upnp, t1, t2, "", "uuid:", upnp->UDN, 0);
			UPnPBuildSendSsdpByeByePacket(upnp->NOTIFY_SEND_socks6[i], upnp, t1, t2, "::urn:schemas-upnp-org:device:MediaRenderer:1", "urn:schemas-upnp-org:device:MediaRenderer:1", "", 0);
			UPnPBuildSendSsdpByeByePacket(upnp->NOTIFY_SEND_socks6[i], upnp, t1, t2, "::urn:schemas-upnp-org:service:AVTransport:1", "urn:schemas-upnp-org:service:AVTransport:1", "", 0);
			UPnPBuildSendSsdpByeByePacket(upnp->NOTIFY_SEND_socks6[i], upnp, t1, t2, "::urn:schemas-upnp-org:service:ConnectionManager:1", "urn:schemas-upnp-org:service:ConnectionManager:1", "", 0);
			UPnPBuildSendSsdpByeByePacket(upnp->NOTIFY_SEND_socks6[i], upnp, t1, t2, "::urn:schemas-upnp-org:service:RenderingControl:1", "urn:schemas-upnp-org:service:RenderingControl:1", "", 0);
			
		}
	}
}

/*! \fn UPnPResponse_Error(const UPnPSessionToken UPnPToken, const int ErrorCode, const char* ErrorMsg)
\brief Responds to the client invocation with a SOAP Fault
\param UPnPToken UPnP token
\param ErrorCode Fault Code
\param ErrorMsg Error Detail
*/
void UPnPResponse_Error(const UPnPSessionToken UPnPToken, const int ErrorCode, const char* ErrorMsg)
{
	char* body;
	int bodylength;
	char* head;
	int headlength;
	int len = 395 + (int)strlen(ErrorMsg);
	
	if ((body = (char*)malloc(len)) == NULL) ILIBCRITICALEXIT(254);
	bodylength = snprintf(body, len, "<s:Envelope\r\n xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><s:Fault><faultcode>s:Client</faultcode><faultstring>UPnPError</faultstring><detail><UPnPError xmlns=\"urn:schemas-upnp-org:control-1-0\"><errorCode>%d</errorCode><errorDescription>%s</errorDescription></UPnPError></detail></s:Fault></s:Body></s:Envelope>",ErrorCode,ErrorMsg);
	if ((head = (char*)malloc(59)) == NULL) ILIBCRITICALEXIT(254);
	headlength = snprintf(head, 59, "HTTP/1.1 500 Internal\r\nContent-Length: %d\r\n\r\n",bodylength);
	ILibWebServer_Send_Raw((struct ILibWebServer_Session*)UPnPToken, head, headlength, 0, 0);
	ILibWebServer_Send_Raw((struct ILibWebServer_Session*)UPnPToken, body, bodylength, 0, 1);
}

/*! \fn UPnPGetLocalInterfaceToHost(const UPnPSessionToken UPnPToken)
\brief When a UPnP request is dispatched, this method determines which ip address actually received this request
\param UPnPToken UPnP token
\returns IP Address
*/
/*
int UPnPGetLocalInterfaceToHost(const UPnPSessionToken UPnPToken)
{
	return(ILibWebServer_GetLocalInterface((struct ILibWebServer_Session*)UPnPToken));
}
*/

void UPnPResponseGeneric(const UPnPMicroStackToken UPnPToken, const char* ServiceURI, const char* MethodName, const char* Params)
{
	int RVAL = 0;
	char* packet;
	int packetlength;
	struct ILibWebServer_Session *session = (struct ILibWebServer_Session*)UPnPToken;
	size_t len = 239 + strlen(ServiceURI) + strlen(Params) + (strlen(MethodName) * 2);
	
	if ((packet = (char*)malloc(len)) == NULL) ILIBCRITICALEXIT(254);
	packetlength = snprintf(packet, len, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n<s:Envelope s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\"><s:Body><u:%sResponse xmlns:u=\"%s\">%s</u:%sResponse></s:Body></s:Envelope>",MethodName,ServiceURI,Params,MethodName);
	LVL3DEBUG(printf("SendBody: %s\r\n", packet);)
	#if defined(WIN32) || defined(_WIN32_WCE)
	RVAL=ILibWebServer_StreamHeader_Raw(session, 200, "OK", "\r\nEXT:\r\nCONTENT-TYPE: text/xml; charset=\"utf-8\"\r\nSERVER: WINDOWS, UPnP/1.0, MicroStack/1.0.4144", 1);
	#elif defined(__SYMBIAN32__)
	RVAL=ILibWebServer_StreamHeader_Raw(session, 200, "OK", "\r\nEXT:\r\nCONTENT-TYPE: text/xml; charset=\"utf-8\"\r\nSERVER: SYMBIAN, UPnP/1.0, MicroStack/1.0.4144", 1);
	#else
	RVAL=ILibWebServer_StreamHeader_Raw(session, 200, "OK", "\r\nEXT:\r\nCONTENT-TYPE: text/xml; charset=\"utf-8\"\r\nSERVER: POSIX, UPnP/1.0, MicroStack/1.0.4144", 1);
	#endif
	if (RVAL!=ILibAsyncSocket_SEND_ON_CLOSED_SOCKET_ERROR && RVAL != ILibWebServer_SEND_RESULTED_IN_DISCONNECT)
	{
		RVAL=ILibWebServer_StreamBody(session, packet, packetlength, 0, 1);
	}
}

/*! \fn UPnPResponse_AVTransport_GetCurrentTransportActions(const UPnPSessionToken UPnPToken, const char* unescaped_Actions)
\brief Response Method for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> GetCurrentTransportActions
\param UPnPToken MicroStack token
\param unescaped_Actions Value of argument Actions \b     Note: Automatically Escaped
*/
void UPnPResponse_AVTransport_GetCurrentTransportActions(const UPnPSessionToken UPnPToken, const char* unescaped_Actions)
{
	char* body;
	char *Actions = (char*)malloc(1+ILibXmlEscapeLength(unescaped_Actions));
	
	ILibXmlEscape(Actions, unescaped_Actions);
	if ((body = (char*)malloc(20+strlen(Actions))) == NULL) ILIBCRITICALEXIT(254);
	snprintf(body, 20+strlen(Actions), "<Actions>%s</Actions>", Actions);
	UPnPResponseGeneric(UPnPToken, "urn:schemas-upnp-org:service:AVTransport:1", "GetCurrentTransportActions", body);
	free(body);
	free(Actions);
}

/*! \fn UPnPResponse_AVTransport_GetDeviceCapabilities(const UPnPSessionToken UPnPToken, const char* unescaped_PlayMedia, const char* unescaped_RecMedia, const char* unescaped_RecQualityModes)
\brief Response Method for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> GetDeviceCapabilities
\param UPnPToken MicroStack token
\param unescaped_PlayMedia Value of argument PlayMedia \b     Note: Automatically Escaped
\param unescaped_RecMedia Value of argument RecMedia \b     Note: Automatically Escaped
\param unescaped_RecQualityModes Value of argument RecQualityModes \b     Note: Automatically Escaped
*/
void UPnPResponse_AVTransport_GetDeviceCapabilities(const UPnPSessionToken UPnPToken, const char* unescaped_PlayMedia, const char* unescaped_RecMedia, const char* unescaped_RecQualityModes)
{
	char* body;
	char *PlayMedia = (char*)malloc(1+ILibXmlEscapeLength(unescaped_PlayMedia));
	char *RecMedia = (char*)malloc(1+ILibXmlEscapeLength(unescaped_RecMedia));
	char *RecQualityModes = (char*)malloc(1+ILibXmlEscapeLength(unescaped_RecQualityModes));
	
	ILibXmlEscape(PlayMedia, unescaped_PlayMedia);
	ILibXmlEscape(RecMedia, unescaped_RecMedia);
	ILibXmlEscape(RecQualityModes, unescaped_RecQualityModes);
	if ((body = (char*)malloc(80+strlen(PlayMedia)+strlen(RecMedia)+strlen(RecQualityModes))) == NULL) ILIBCRITICALEXIT(254);
	snprintf(body, 80+strlen(PlayMedia)+strlen(RecMedia)+strlen(RecQualityModes), "<PlayMedia>%s</PlayMedia><RecMedia>%s</RecMedia><RecQualityModes>%s</RecQualityModes>", PlayMedia, RecMedia, RecQualityModes);
	UPnPResponseGeneric(UPnPToken, "urn:schemas-upnp-org:service:AVTransport:1", "GetDeviceCapabilities", body);
	free(body);
	free(PlayMedia);
	free(RecMedia);
	free(RecQualityModes);
}

/*! \fn UPnPResponse_AVTransport_GetMediaInfo(const UPnPSessionToken UPnPToken, const unsigned int NrTracks, const char* unescaped_MediaDuration, const char* unescaped_CurrentURI, const char* unescaped_CurrentURIMetaData, const char* unescaped_NextURI, const char* unescaped_NextURIMetaData, const char* unescaped_PlayMedium, const char* unescaped_RecordMedium, const char* unescaped_WriteStatus)
\brief Response Method for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> GetMediaInfo
\param UPnPToken MicroStack token
\param NrTracks Value of argument NrTracks
\param unescaped_MediaDuration Value of argument MediaDuration \b     Note: Automatically Escaped
\param unescaped_CurrentURI Value of argument CurrentURI \b     Note: Automatically Escaped
\param unescaped_CurrentURIMetaData Value of argument CurrentURIMetaData \b     Note: Automatically Escaped
\param unescaped_NextURI Value of argument NextURI \b     Note: Automatically Escaped
\param unescaped_NextURIMetaData Value of argument NextURIMetaData \b     Note: Automatically Escaped
\param unescaped_PlayMedium Value of argument PlayMedium \b     Note: Automatically Escaped
\param unescaped_RecordMedium Value of argument RecordMedium \b     Note: Automatically Escaped
\param unescaped_WriteStatus Value of argument WriteStatus \b     Note: Automatically Escaped
*/
void UPnPResponse_AVTransport_GetMediaInfo(const UPnPSessionToken UPnPToken, const unsigned int NrTracks, const char* unescaped_MediaDuration, const char* unescaped_CurrentURI, const char* unescaped_CurrentURIMetaData, const char* unescaped_NextURI, const char* unescaped_NextURIMetaData, const char* unescaped_PlayMedium, const char* unescaped_RecordMedium, const char* unescaped_WriteStatus)
{
	char* body;
	char *MediaDuration = (char*)malloc(1+ILibXmlEscapeLength(unescaped_MediaDuration));
	char *CurrentURI = (char*)malloc(1+ILibXmlEscapeLength(unescaped_CurrentURI));
	char *CurrentURIMetaData = (char*)malloc(1+ILibXmlEscapeLength(unescaped_CurrentURIMetaData));
	char *NextURI = (char*)malloc(1+ILibXmlEscapeLength(unescaped_NextURI));
	char *NextURIMetaData = (char*)malloc(1+ILibXmlEscapeLength(unescaped_NextURIMetaData));
	char *PlayMedium = (char*)malloc(1+ILibXmlEscapeLength(unescaped_PlayMedium));
	char *RecordMedium = (char*)malloc(1+ILibXmlEscapeLength(unescaped_RecordMedium));
	char *WriteStatus = (char*)malloc(1+ILibXmlEscapeLength(unescaped_WriteStatus));
	
	ILibXmlEscape(MediaDuration, unescaped_MediaDuration);
	ILibXmlEscape(CurrentURI, unescaped_CurrentURI);
	ILibXmlEscape(CurrentURIMetaData, unescaped_CurrentURIMetaData);
	ILibXmlEscape(NextURI, unescaped_NextURI);
	ILibXmlEscape(NextURIMetaData, unescaped_NextURIMetaData);
	ILibXmlEscape(PlayMedium, unescaped_PlayMedium);
	ILibXmlEscape(RecordMedium, unescaped_RecordMedium);
	ILibXmlEscape(WriteStatus, unescaped_WriteStatus);
	if ((body = (char*)malloc(265+strlen(MediaDuration)+strlen(CurrentURI)+strlen(CurrentURIMetaData)+strlen(NextURI)+strlen(NextURIMetaData)+strlen(PlayMedium)+strlen(RecordMedium)+strlen(WriteStatus))) == NULL) ILIBCRITICALEXIT(254);
	snprintf(body, 265+strlen(MediaDuration)+strlen(CurrentURI)+strlen(CurrentURIMetaData)+strlen(NextURI)+strlen(NextURIMetaData)+strlen(PlayMedium)+strlen(RecordMedium)+strlen(WriteStatus), "<NrTracks>%u</NrTracks><MediaDuration>%s</MediaDuration><CurrentURI>%s</CurrentURI><CurrentURIMetaData>%s</CurrentURIMetaData><NextURI>%s</NextURI><NextURIMetaData>%s</NextURIMetaData><PlayMedium>%s</PlayMedium><RecordMedium>%s</RecordMedium><WriteStatus>%s</WriteStatus>", NrTracks, MediaDuration, CurrentURI, CurrentURIMetaData, NextURI, NextURIMetaData, PlayMedium, RecordMedium, WriteStatus);
	UPnPResponseGeneric(UPnPToken, "urn:schemas-upnp-org:service:AVTransport:1", "GetMediaInfo", body);
	free(body);
	free(MediaDuration);
	free(CurrentURI);
	free(CurrentURIMetaData);
	free(NextURI);
	free(NextURIMetaData);
	free(PlayMedium);
	free(RecordMedium);
	free(WriteStatus);
}

/*! \fn UPnPResponse_AVTransport_GetPositionInfo(const UPnPSessionToken UPnPToken, const unsigned int Track, const char* unescaped_TrackDuration, const char* unescaped_TrackMetaData, const char* unescaped_TrackURI, const char* unescaped_RelTime, const char* unescaped_AbsTime, const int RelCount, const int AbsCount)
\brief Response Method for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> GetPositionInfo
\param UPnPToken MicroStack token
\param Track Value of argument Track
\param unescaped_TrackDuration Value of argument TrackDuration \b     Note: Automatically Escaped
\param unescaped_TrackMetaData Value of argument TrackMetaData \b     Note: Automatically Escaped
\param unescaped_TrackURI Value of argument TrackURI \b     Note: Automatically Escaped
\param unescaped_RelTime Value of argument RelTime \b     Note: Automatically Escaped
\param unescaped_AbsTime Value of argument AbsTime \b     Note: Automatically Escaped
\param RelCount Value of argument RelCount
\param AbsCount Value of argument AbsCount
*/
void UPnPResponse_AVTransport_GetPositionInfo(const UPnPSessionToken UPnPToken, const unsigned int Track, const char* unescaped_TrackDuration, const char* unescaped_TrackMetaData, const char* unescaped_TrackURI, const char* unescaped_RelTime, const char* unescaped_AbsTime, const int RelCount, const int AbsCount)
{
	char* body;
	char *TrackDuration = (char*)malloc(1+ILibXmlEscapeLength(unescaped_TrackDuration));
	char *TrackMetaData = (char*)malloc(1+ILibXmlEscapeLength(unescaped_TrackMetaData));
	char *TrackURI = (char*)malloc(1+ILibXmlEscapeLength(unescaped_TrackURI));
	char *RelTime = (char*)malloc(1+ILibXmlEscapeLength(unescaped_RelTime));
	char *AbsTime = (char*)malloc(1+ILibXmlEscapeLength(unescaped_AbsTime));
	
	ILibXmlEscape(TrackDuration, unescaped_TrackDuration);
	ILibXmlEscape(TrackMetaData, unescaped_TrackMetaData);
	ILibXmlEscape(TrackURI, unescaped_TrackURI);
	ILibXmlEscape(RelTime, unescaped_RelTime);
	ILibXmlEscape(AbsTime, unescaped_AbsTime);
	if ((body = (char*)malloc(212+strlen(TrackDuration)+strlen(TrackMetaData)+strlen(TrackURI)+strlen(RelTime)+strlen(AbsTime))) == NULL) ILIBCRITICALEXIT(254);
	snprintf(body, 212+strlen(TrackDuration)+strlen(TrackMetaData)+strlen(TrackURI)+strlen(RelTime)+strlen(AbsTime), "<Track>%u</Track><TrackDuration>%s</TrackDuration><TrackMetaData>%s</TrackMetaData><TrackURI>%s</TrackURI><RelTime>%s</RelTime><AbsTime>%s</AbsTime><RelCount>%d</RelCount><AbsCount>%d</AbsCount>", Track, TrackDuration, TrackMetaData, TrackURI, RelTime, AbsTime, RelCount, AbsCount);
	UPnPResponseGeneric(UPnPToken, "urn:schemas-upnp-org:service:AVTransport:1", "GetPositionInfo", body);
	free(body);
	free(TrackDuration);
	free(TrackMetaData);
	free(TrackURI);
	free(RelTime);
	free(AbsTime);
}

/*! \fn UPnPResponse_AVTransport_GetTransportInfo(const UPnPSessionToken UPnPToken, const char* unescaped_CurrentTransportState, const char* unescaped_CurrentTransportStatus, const char* unescaped_CurrentSpeed)
\brief Response Method for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> GetTransportInfo
\param UPnPToken MicroStack token
\param unescaped_CurrentTransportState Value of argument CurrentTransportState \b     Note: Automatically Escaped
\param unescaped_CurrentTransportStatus Value of argument CurrentTransportStatus \b     Note: Automatically Escaped
\param unescaped_CurrentSpeed Value of argument CurrentSpeed \b     Note: Automatically Escaped
*/
void UPnPResponse_AVTransport_GetTransportInfo(const UPnPSessionToken UPnPToken, const char* unescaped_CurrentTransportState, const char* unescaped_CurrentTransportStatus, const char* unescaped_CurrentSpeed)
{
	char* body;
	char *CurrentTransportState = (char*)malloc(1+ILibXmlEscapeLength(unescaped_CurrentTransportState));
	char *CurrentTransportStatus = (char*)malloc(1+ILibXmlEscapeLength(unescaped_CurrentTransportStatus));
	char *CurrentSpeed = (char*)malloc(1+ILibXmlEscapeLength(unescaped_CurrentSpeed));
	
	ILibXmlEscape(CurrentTransportState, unescaped_CurrentTransportState);
	ILibXmlEscape(CurrentTransportStatus, unescaped_CurrentTransportStatus);
	ILibXmlEscape(CurrentSpeed, unescaped_CurrentSpeed);
	if ((body = (char*)malloc(126+strlen(CurrentTransportState)+strlen(CurrentTransportStatus)+strlen(CurrentSpeed))) == NULL) ILIBCRITICALEXIT(254);
	snprintf(body, 126+strlen(CurrentTransportState)+strlen(CurrentTransportStatus)+strlen(CurrentSpeed), "<CurrentTransportState>%s</CurrentTransportState><CurrentTransportStatus>%s</CurrentTransportStatus><CurrentSpeed>%s</CurrentSpeed>", CurrentTransportState, CurrentTransportStatus, CurrentSpeed);
	UPnPResponseGeneric(UPnPToken, "urn:schemas-upnp-org:service:AVTransport:1", "GetTransportInfo", body);
	free(body);
	free(CurrentTransportState);
	free(CurrentTransportStatus);
	free(CurrentSpeed);
}

/*! \fn UPnPResponse_AVTransport_GetTransportSettings(const UPnPSessionToken UPnPToken, const char* unescaped_PlayMode, const char* unescaped_RecQualityMode)
\brief Response Method for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> GetTransportSettings
\param UPnPToken MicroStack token
\param unescaped_PlayMode Value of argument PlayMode \b     Note: Automatically Escaped
\param unescaped_RecQualityMode Value of argument RecQualityMode \b     Note: Automatically Escaped
*/
void UPnPResponse_AVTransport_GetTransportSettings(const UPnPSessionToken UPnPToken, const char* unescaped_PlayMode, const char* unescaped_RecQualityMode)
{
	char* body;
	char *PlayMode = (char*)malloc(1+ILibXmlEscapeLength(unescaped_PlayMode));
	char *RecQualityMode = (char*)malloc(1+ILibXmlEscapeLength(unescaped_RecQualityMode));
	
	ILibXmlEscape(PlayMode, unescaped_PlayMode);
	ILibXmlEscape(RecQualityMode, unescaped_RecQualityMode);
	if ((body = (char*)malloc(55+strlen(PlayMode)+strlen(RecQualityMode))) == NULL) ILIBCRITICALEXIT(254);
	snprintf(body, 55+strlen(PlayMode)+strlen(RecQualityMode), "<PlayMode>%s</PlayMode><RecQualityMode>%s</RecQualityMode>", PlayMode, RecQualityMode);
	UPnPResponseGeneric(UPnPToken, "urn:schemas-upnp-org:service:AVTransport:1", "GetTransportSettings", body);
	free(body);
	free(PlayMode);
	free(RecQualityMode);
}

/*! \fn UPnPResponse_AVTransport_Next(const UPnPSessionToken UPnPToken)
\brief Response Method for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> Next
\param UPnPToken MicroStack token
*/
void UPnPResponse_AVTransport_Next(const UPnPSessionToken UPnPToken)
{
	UPnPResponseGeneric(UPnPToken,"urn:schemas-upnp-org:service:AVTransport:1","Next","");
}

/*! \fn UPnPResponse_AVTransport_Pause(const UPnPSessionToken UPnPToken)
\brief Response Method for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> Pause
\param UPnPToken MicroStack token
*/
void UPnPResponse_AVTransport_Pause(const UPnPSessionToken UPnPToken)
{
	UPnPResponseGeneric(UPnPToken,"urn:schemas-upnp-org:service:AVTransport:1","Pause","");
}

/*! \fn UPnPResponse_AVTransport_Play(const UPnPSessionToken UPnPToken)
\brief Response Method for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> Play
\param UPnPToken MicroStack token
*/
void UPnPResponse_AVTransport_Play(const UPnPSessionToken UPnPToken)
{
	UPnPResponseGeneric(UPnPToken,"urn:schemas-upnp-org:service:AVTransport:1","Play","");
}

/*! \fn UPnPResponse_AVTransport_Previous(const UPnPSessionToken UPnPToken)
\brief Response Method for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> Previous
\param UPnPToken MicroStack token
*/
void UPnPResponse_AVTransport_Previous(const UPnPSessionToken UPnPToken)
{
	UPnPResponseGeneric(UPnPToken,"urn:schemas-upnp-org:service:AVTransport:1","Previous","");
}

/*! \fn UPnPResponse_AVTransport_Seek(const UPnPSessionToken UPnPToken)
\brief Response Method for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> Seek
\param UPnPToken MicroStack token
*/
void UPnPResponse_AVTransport_Seek(const UPnPSessionToken UPnPToken)
{
	UPnPResponseGeneric(UPnPToken,"urn:schemas-upnp-org:service:AVTransport:1","Seek","");
}

/*! \fn UPnPResponse_AVTransport_SetAVTransportURI(const UPnPSessionToken UPnPToken)
\brief Response Method for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> SetAVTransportURI
\param UPnPToken MicroStack token
*/
void UPnPResponse_AVTransport_SetAVTransportURI(const UPnPSessionToken UPnPToken)
{
	UPnPResponseGeneric(UPnPToken,"urn:schemas-upnp-org:service:AVTransport:1","SetAVTransportURI","");
}

/*! \fn UPnPResponse_AVTransport_SetPlayMode(const UPnPSessionToken UPnPToken)
\brief Response Method for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> SetPlayMode
\param UPnPToken MicroStack token
*/
void UPnPResponse_AVTransport_SetPlayMode(const UPnPSessionToken UPnPToken)
{
	UPnPResponseGeneric(UPnPToken,"urn:schemas-upnp-org:service:AVTransport:1","SetPlayMode","");
}

/*! \fn UPnPResponse_AVTransport_Stop(const UPnPSessionToken UPnPToken)
\brief Response Method for AVTransport >> urn:schemas-upnp-org:service:AVTransport:1 >> Stop
\param UPnPToken MicroStack token
*/
void UPnPResponse_AVTransport_Stop(const UPnPSessionToken UPnPToken)
{
	UPnPResponseGeneric(UPnPToken,"urn:schemas-upnp-org:service:AVTransport:1","Stop","");
}

/*! \fn UPnPResponse_ConnectionManager_GetCurrentConnectionIDs(const UPnPSessionToken UPnPToken, const char* unescaped_ConnectionIDs)
\brief Response Method for ConnectionManager >> urn:schemas-upnp-org:service:ConnectionManager:1 >> GetCurrentConnectionIDs
\param UPnPToken MicroStack token
\param unescaped_ConnectionIDs Value of argument ConnectionIDs \b     Note: Automatically Escaped
*/
void UPnPResponse_ConnectionManager_GetCurrentConnectionIDs(const UPnPSessionToken UPnPToken, const char* unescaped_ConnectionIDs)
{
	char* body;
	char *ConnectionIDs = (char*)malloc(1+ILibXmlEscapeLength(unescaped_ConnectionIDs));
	
	ILibXmlEscape(ConnectionIDs, unescaped_ConnectionIDs);
	if ((body = (char*)malloc(32+strlen(ConnectionIDs))) == NULL) ILIBCRITICALEXIT(254);
	snprintf(body, 32+strlen(ConnectionIDs), "<ConnectionIDs>%s</ConnectionIDs>", ConnectionIDs);
	UPnPResponseGeneric(UPnPToken, "urn:schemas-upnp-org:service:ConnectionManager:1", "GetCurrentConnectionIDs", body);
	free(body);
	free(ConnectionIDs);
}

/*! \fn UPnPResponse_ConnectionManager_GetCurrentConnectionInfo(const UPnPSessionToken UPnPToken, const int RcsID, const int AVTransportID, const char* unescaped_ProtocolInfo, const char* unescaped_PeerConnectionManager, const int PeerConnectionID, const char* unescaped_Direction, const char* unescaped_Status)
\brief Response Method for ConnectionManager >> urn:schemas-upnp-org:service:ConnectionManager:1 >> GetCurrentConnectionInfo
\param UPnPToken MicroStack token
\param RcsID Value of argument RcsID
\param AVTransportID Value of argument AVTransportID
\param unescaped_ProtocolInfo Value of argument ProtocolInfo \b     Note: Automatically Escaped
\param unescaped_PeerConnectionManager Value of argument PeerConnectionManager \b     Note: Automatically Escaped
\param PeerConnectionID Value of argument PeerConnectionID
\param unescaped_Direction Value of argument Direction \b     Note: Automatically Escaped
\param unescaped_Status Value of argument Status \b     Note: Automatically Escaped
*/
void UPnPResponse_ConnectionManager_GetCurrentConnectionInfo(const UPnPSessionToken UPnPToken, const int RcsID, const int AVTransportID, const char* unescaped_ProtocolInfo, const char* unescaped_PeerConnectionManager, const int PeerConnectionID, const char* unescaped_Direction, const char* unescaped_Status)
{
	char* body;
	char *ProtocolInfo = (char*)malloc(1+ILibXmlEscapeLength(unescaped_ProtocolInfo));
	char *PeerConnectionManager = (char*)malloc(1+ILibXmlEscapeLength(unescaped_PeerConnectionManager));
	char *Direction = (char*)malloc(1+ILibXmlEscapeLength(unescaped_Direction));
	char *Status = (char*)malloc(1+ILibXmlEscapeLength(unescaped_Status));
	
	ILibXmlEscape(ProtocolInfo, unescaped_ProtocolInfo);
	ILibXmlEscape(PeerConnectionManager, unescaped_PeerConnectionManager);
	ILibXmlEscape(Direction, unescaped_Direction);
	ILibXmlEscape(Status, unescaped_Status);
	if ((body = (char*)malloc(233+strlen(ProtocolInfo)+strlen(PeerConnectionManager)+strlen(Direction)+strlen(Status))) == NULL) ILIBCRITICALEXIT(254);
	snprintf(body, 233+strlen(ProtocolInfo)+strlen(PeerConnectionManager)+strlen(Direction)+strlen(Status), "<RcsID>%d</RcsID><AVTransportID>%d</AVTransportID><ProtocolInfo>%s</ProtocolInfo><PeerConnectionManager>%s</PeerConnectionManager><PeerConnectionID>%d</PeerConnectionID><Direction>%s</Direction><Status>%s</Status>", RcsID, AVTransportID, ProtocolInfo, PeerConnectionManager, PeerConnectionID, Direction, Status);
	UPnPResponseGeneric(UPnPToken, "urn:schemas-upnp-org:service:ConnectionManager:1", "GetCurrentConnectionInfo", body);
	free(body);
	free(ProtocolInfo);
	free(PeerConnectionManager);
	free(Direction);
	free(Status);
}

/*! \fn UPnPResponse_ConnectionManager_GetProtocolInfo(const UPnPSessionToken UPnPToken, const char* unescaped_Source, const char* unescaped_Sink)
\brief Response Method for ConnectionManager >> urn:schemas-upnp-org:service:ConnectionManager:1 >> GetProtocolInfo
\param UPnPToken MicroStack token
\param unescaped_Source Value of argument Source \b     Note: Automatically Escaped
\param unescaped_Sink Value of argument Sink \b     Note: Automatically Escaped
*/
void UPnPResponse_ConnectionManager_GetProtocolInfo(const UPnPSessionToken UPnPToken, const char* unescaped_Source, const char* unescaped_Sink)
{
	char* body;
	char *Source = (char*)malloc(1+ILibXmlEscapeLength(unescaped_Source));
	char *Sink = (char*)malloc(1+ILibXmlEscapeLength(unescaped_Sink));
	
	ILibXmlEscape(Source, unescaped_Source);
	ILibXmlEscape(Sink, unescaped_Sink);
	if ((body = (char*)malloc(31+strlen(Source)+strlen(Sink))) == NULL) ILIBCRITICALEXIT(254);
	snprintf(body, 31+strlen(Source)+strlen(Sink), "<Source>%s</Source><Sink>%s</Sink>", Source, Sink);
	UPnPResponseGeneric(UPnPToken, "urn:schemas-upnp-org:service:ConnectionManager:1", "GetProtocolInfo", body);
	free(body);
	free(Source);
	free(Sink);
}

/*! \fn UPnPResponse_RenderingControl_GetMute(const UPnPSessionToken UPnPToken, const int CurrentMute)
\brief Response Method for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> GetMute
\param UPnPToken MicroStack token
\param CurrentMute Value of argument CurrentMute
*/
void UPnPResponse_RenderingControl_GetMute(const UPnPSessionToken UPnPToken, const int CurrentMute)
{
	char* body;
	
	if ((body = (char*)malloc(29)) == NULL) ILIBCRITICALEXIT(254);
	snprintf(body, 29, "<CurrentMute>%d</CurrentMute>", (CurrentMute!=0?1:0));
	UPnPResponseGeneric(UPnPToken, "urn:schemas-upnp-org:service:RenderingControl:1", "GetMute", body);
	free(body);
}

/*! \fn UPnPResponse_RenderingControl_GetVolume(const UPnPSessionToken UPnPToken, const unsigned short CurrentVolume)
\brief Response Method for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> GetVolume
\param UPnPToken MicroStack token
\param CurrentVolume Value of argument CurrentVolume
*/
void UPnPResponse_RenderingControl_GetVolume(const UPnPSessionToken UPnPToken, const unsigned short CurrentVolume)
{
	char* body;
	
	if ((body = (char*)malloc(38)) == NULL) ILIBCRITICALEXIT(254);
	snprintf(body, 38, "<CurrentVolume>%u</CurrentVolume>", CurrentVolume);
	UPnPResponseGeneric(UPnPToken, "urn:schemas-upnp-org:service:RenderingControl:1", "GetVolume", body);
	free(body);
}

/*! \fn UPnPResponse_RenderingControl_GetVolumeDB(const UPnPSessionToken UPnPToken, const short CurrentVolume)
\brief Response Method for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> GetVolumeDB
\param UPnPToken MicroStack token
\param CurrentVolume Value of argument CurrentVolume
*/
void UPnPResponse_RenderingControl_GetVolumeDB(const UPnPSessionToken UPnPToken, const short CurrentVolume)
{
	char* body;
	
	if ((body = (char*)malloc(38)) == NULL) ILIBCRITICALEXIT(254);
	snprintf(body, 38, "<CurrentVolume>%d</CurrentVolume>", CurrentVolume);
	UPnPResponseGeneric(UPnPToken, "urn:schemas-upnp-org:service:RenderingControl:1", "GetVolumeDB", body);
	free(body);
}

/*! \fn UPnPResponse_RenderingControl_GetVolumeDBRange(const UPnPSessionToken UPnPToken, const short MinValue, const short MaxValue)
\brief Response Method for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> GetVolumeDBRange
\param UPnPToken MicroStack token
\param MinValue Value of argument MinValue
\param MaxValue Value of argument MaxValue
*/
void UPnPResponse_RenderingControl_GetVolumeDBRange(const UPnPSessionToken UPnPToken, const short MinValue, const short MaxValue)
{
	char* body;
	
	if ((body = (char*)malloc(55)) == NULL) ILIBCRITICALEXIT(254);
	snprintf(body, 55, "<MinValue>%d</MinValue><MaxValue>%d</MaxValue>", MinValue, MaxValue);
	UPnPResponseGeneric(UPnPToken, "urn:schemas-upnp-org:service:RenderingControl:1", "GetVolumeDBRange", body);
	free(body);
}

/*! \fn UPnPResponse_RenderingControl_ListPresets(const UPnPSessionToken UPnPToken, const char* unescaped_CurrentPresetNameList)
\brief Response Method for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> ListPresets
\param UPnPToken MicroStack token
\param unescaped_CurrentPresetNameList Value of argument CurrentPresetNameList \b     Note: Automatically Escaped
*/
void UPnPResponse_RenderingControl_ListPresets(const UPnPSessionToken UPnPToken, const char* unescaped_CurrentPresetNameList)
{
	char* body;
	char *CurrentPresetNameList = (char*)malloc(1+ILibXmlEscapeLength(unescaped_CurrentPresetNameList));
	
	ILibXmlEscape(CurrentPresetNameList, unescaped_CurrentPresetNameList);
	if ((body = (char*)malloc(48+strlen(CurrentPresetNameList))) == NULL) ILIBCRITICALEXIT(254);
	snprintf(body, 48+strlen(CurrentPresetNameList), "<CurrentPresetNameList>%s</CurrentPresetNameList>", CurrentPresetNameList);
	UPnPResponseGeneric(UPnPToken, "urn:schemas-upnp-org:service:RenderingControl:1", "ListPresets", body);
	free(body);
	free(CurrentPresetNameList);
}

/*! \fn UPnPResponse_RenderingControl_SelectPreset(const UPnPSessionToken UPnPToken)
\brief Response Method for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> SelectPreset
\param UPnPToken MicroStack token
*/
void UPnPResponse_RenderingControl_SelectPreset(const UPnPSessionToken UPnPToken)
{
	UPnPResponseGeneric(UPnPToken,"urn:schemas-upnp-org:service:RenderingControl:1","SelectPreset","");
}

/*! \fn UPnPResponse_RenderingControl_SetMute(const UPnPSessionToken UPnPToken)
\brief Response Method for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> SetMute
\param UPnPToken MicroStack token
*/
void UPnPResponse_RenderingControl_SetMute(const UPnPSessionToken UPnPToken)
{
	UPnPResponseGeneric(UPnPToken,"urn:schemas-upnp-org:service:RenderingControl:1","SetMute","");
}

/*! \fn UPnPResponse_RenderingControl_SetVolume(const UPnPSessionToken UPnPToken)
\brief Response Method for RenderingControl >> urn:schemas-upnp-org:service:RenderingControl:1 >> SetVolume
\param UPnPToken MicroStack token
*/
void UPnPResponse_RenderingControl_SetVolume(const UPnPSessionToken UPnPToken)
{
	UPnPResponseGeneric(UPnPToken,"urn:schemas-upnp-org:service:RenderingControl:1","SetVolume","");
}


void UPnPSendEventSink(
void *WebReaderToken,
int IsInterrupt,
struct packetheader *header,
char *buffer,
int *p_BeginPointer,
int EndPointer,
int done,
void *subscriber,
void *upnp,
int *PAUSE)	
{
	UNREFERENCED_PARAMETER( WebReaderToken );
	UNREFERENCED_PARAMETER( IsInterrupt );
	UNREFERENCED_PARAMETER( buffer );
	UNREFERENCED_PARAMETER( p_BeginPointer );
	UNREFERENCED_PARAMETER( EndPointer );
	UNREFERENCED_PARAMETER( PAUSE );
	
	if (done != 0 && ((struct SubscriberInfo*)subscriber)->Disposing == 0)
	{
		sem_wait(&(((struct UPnPDataObject*)upnp)->EventLock));
		--((struct SubscriberInfo*)subscriber)->RefCount;
		if (((struct SubscriberInfo*)subscriber)->RefCount == 0)
		{
			LVL3DEBUG(printf("\r\n\r\nSubscriber at [%s] %d.%d.%d.%d:%d was/did UNSUBSCRIBE while trying to send event\r\n\r\n", ((struct SubscriberInfo*)subscriber)->SID, (((struct SubscriberInfo*)subscriber)->Address&0xFF),((((struct SubscriberInfo*)subscriber)->Address>>8)&0xFF),((((struct SubscriberInfo*)subscriber)->Address>>16)&0xFF), ((((struct SubscriberInfo*)subscriber)->Address>>24)&0xFF), ((struct SubscriberInfo*)subscriber)->Port);)
			UPnPDestructSubscriberInfo(((struct SubscriberInfo*)subscriber));
		}
		else if (header == NULL)
		{
			LVL3DEBUG(printf("\r\n\r\nCould not deliver event for [%s] %d.%d.%d.%d:%d UNSUBSCRIBING\r\n\r\n", ((struct SubscriberInfo*)subscriber)->SID, (((struct SubscriberInfo*)subscriber)->Address&0xFF),((((struct SubscriberInfo*)subscriber)->Address>>8)&0xFF), ((((struct SubscriberInfo*)subscriber)->Address>>16)&0xFF), ((((struct SubscriberInfo*)subscriber)->Address>>24)&0xFF), ((struct SubscriberInfo*)subscriber)->Port);)
			// Could not send Event, so unsubscribe the subscriber
			((struct SubscriberInfo*)subscriber)->Disposing = 1;
			UPnPExpireSubscriberInfo(upnp, subscriber);
		}
		sem_post(&(((struct UPnPDataObject*)upnp)->EventLock));
	}
}

void UPnPSendEvent_Body(void *upnptoken, char *body, int bodylength, struct SubscriberInfo *info)
{
	struct UPnPDataObject* UPnPObject = (struct UPnPDataObject*)upnptoken;
	struct sockaddr_in dest;
	int packetLength;
	char *packet;
	int ipaddr;
	int len;
	
	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = info->Address;
	dest.sin_port = htons(info->Port);
	dest.sin_family = AF_INET;
	ipaddr = info->Address;
	
	len = info->PathLength + bodylength + 483;
	if ((packet = (char*)malloc(len)) == NULL) ILIBCRITICALEXIT(254);
	packetLength = snprintf(packet, len, "NOTIFY %s HTTP/1.1\r\nSERVER: %s, UPnP/1.1, MicroStack/1.0.4144\r\nHOST: %s:%d\r\nContent-Type: text/xml; charset=\"utf-8\"\r\nNT: upnp:event\r\nNTS: upnp:propchange\r\nSID: %s\r\nSEQ: %d\r\nContent-Length: %d\r\n\r\n<?xml version=\"1.0\" encoding=\"utf-8\"?><e:propertyset xmlns:e=\"urn:schemas-upnp-org:event-1-0\"><e:property><%s></e:property></e:propertyset>",info->Path,UPnPPLATFORM,inet_ntoa(dest.sin_addr),info->Port,info->SID,info->SEQ,bodylength+137,body);
	++info->SEQ;
	
	++info->RefCount;
	ILibWebClient_PipelineRequestEx(UPnPObject->EventClient, (struct sockaddr*)(&dest), packet, packetLength, 0, NULL, 0, 0, &UPnPSendEventSink, info, upnptoken);
}

void UPnPSendEvent(void *upnptoken, char* body, const int bodylength, const char* eventname)
{
	struct SubscriberInfo *info = NULL;
	struct UPnPDataObject* UPnPObject = (struct UPnPDataObject*)upnptoken;
	struct sockaddr_in dest;
	LVL3DEBUG(struct timeval tv;)
	
	if (UPnPObject == NULL)
	{
		free(body);
		return;
	}
	sem_wait(&(UPnPObject->EventLock));
	if (strncmp(eventname,"AVTransport",11)==0)
	{
		info = UPnPObject->HeadSubscriberPtr_AVTransport;
	}
	if (strncmp(eventname,"ConnectionManager",17)==0)
	{
		info = UPnPObject->HeadSubscriberPtr_ConnectionManager;
	}
	if (strncmp(eventname,"RenderingControl",16)==0)
	{
		info = UPnPObject->HeadSubscriberPtr_RenderingControl;
	}
	
	memset(&dest, 0, sizeof(dest));
	while(info != NULL)
	{
		if (!UPnPSubscriptionExpired(info))
		{
			UPnPSendEvent_Body(upnptoken, body, bodylength, info);
		}
		else
		{
			// Remove Subscriber
			LVL3DEBUG(gettimeofday(&tv, NULL);)
			LVL3DEBUG(printf("\r\n\r\nTIMESTAMP: %d\r\n", tv.tv_sec);)
			LVL3DEBUG(printf("Did not renew [%s] %d.%d.%d.%d:%d UNSUBSCRIBING <%d>\r\n\r\n", ((struct SubscriberInfo*)info)->SID, (((struct SubscriberInfo*)info)->Address&0xFF), ((((struct SubscriberInfo*)info)->Address>>8)&0xFF),((((struct SubscriberInfo*)info)->Address>>16)&0xFF), ((((struct SubscriberInfo*)info)->Address>>24)&0xFF), ((struct SubscriberInfo*)info)->Port, info);)
		}
		info = info->Next;
	}
	sem_post(&(UPnPObject->EventLock));
}
/*! \fn UPnPSetState_AVTransport_LastChange(UPnPMicroStackToken upnptoken, char* val)
\brief Sets the state of LastChange << urn:schemas-upnp-org:service:AVTransport:1 << AVTransport \par
\b Note: Must be called at least once prior to start
\param upnptoken The MicroStack token
\param val The new value of the state variable
*/
void UPnPSetState_AVTransport_LastChange(UPnPMicroStackToken upnptoken, char* val)
{
	struct UPnPDataObject *UPnPObject = (struct UPnPDataObject*)upnptoken;
	char* body;
	int bodylength;
	char* valstr;
	if ((valstr = (char*)malloc(ILibXmlEscapeLength(val) + 1)) == NULL) ILIBCRITICALEXIT(254);
	ILibXmlEscape(valstr, val);
	if (UPnPObject->AVTransport_LastChange != NULL) free(UPnPObject->AVTransport_LastChange);
	UPnPObject->AVTransport_LastChange = valstr;
	bodylength = 30 + (int)strlen(valstr);
	if ((body = (char*)malloc(bodylength)) == NULL) ILIBCRITICALEXIT(254);
	bodylength = snprintf(body, bodylength, "%s>%s</%s", "LastChange", valstr, "LastChange");
	UPnPSendEvent(upnptoken, body, bodylength, "AVTransport");
	free(body);
}

/*! \fn UPnPSetState_ConnectionManager_SourceProtocolInfo(UPnPMicroStackToken upnptoken, char* val)
\brief Sets the state of SourceProtocolInfo << urn:schemas-upnp-org:service:ConnectionManager:1 << ConnectionManager \par
\b Note: Must be called at least once prior to start
\param upnptoken The MicroStack token
\param val The new value of the state variable
*/
void UPnPSetState_ConnectionManager_SourceProtocolInfo(UPnPMicroStackToken upnptoken, char* val)
{
	struct UPnPDataObject *UPnPObject = (struct UPnPDataObject*)upnptoken;
	char* body;
	int bodylength;
	char* valstr;
	if ((valstr = (char*)malloc(ILibXmlEscapeLength(val) + 1)) == NULL) ILIBCRITICALEXIT(254);
	ILibXmlEscape(valstr, val);
	if (UPnPObject->ConnectionManager_SourceProtocolInfo != NULL) free(UPnPObject->ConnectionManager_SourceProtocolInfo);
	UPnPObject->ConnectionManager_SourceProtocolInfo = valstr;
	bodylength = 46 + (int)strlen(valstr);
	if ((body = (char*)malloc(bodylength)) == NULL) ILIBCRITICALEXIT(254);
	bodylength = snprintf(body, bodylength, "%s>%s</%s", "SourceProtocolInfo", valstr, "SourceProtocolInfo");
	UPnPSendEvent(upnptoken, body, bodylength, "ConnectionManager");
	free(body);
}

/*! \fn UPnPSetState_ConnectionManager_SinkProtocolInfo(UPnPMicroStackToken upnptoken, char* val)
\brief Sets the state of SinkProtocolInfo << urn:schemas-upnp-org:service:ConnectionManager:1 << ConnectionManager \par
\b Note: Must be called at least once prior to start
\param upnptoken The MicroStack token
\param val The new value of the state variable
*/
void UPnPSetState_ConnectionManager_SinkProtocolInfo(UPnPMicroStackToken upnptoken, char* val)
{
	struct UPnPDataObject *UPnPObject = (struct UPnPDataObject*)upnptoken;
	char* body;
	int bodylength;
	char* valstr;
	if ((valstr = (char*)malloc(ILibXmlEscapeLength(val) + 1)) == NULL) ILIBCRITICALEXIT(254);
	ILibXmlEscape(valstr, val);
	if (UPnPObject->ConnectionManager_SinkProtocolInfo != NULL) free(UPnPObject->ConnectionManager_SinkProtocolInfo);
	UPnPObject->ConnectionManager_SinkProtocolInfo = valstr;
	bodylength = 42 + (int)strlen(valstr);
	if ((body = (char*)malloc(bodylength)) == NULL) ILIBCRITICALEXIT(254);
	bodylength = snprintf(body, bodylength, "%s>%s</%s", "SinkProtocolInfo", valstr, "SinkProtocolInfo");
	UPnPSendEvent(upnptoken, body, bodylength, "ConnectionManager");
	free(body);
}

/*! \fn UPnPSetState_ConnectionManager_CurrentConnectionIDs(UPnPMicroStackToken upnptoken, char* val)
\brief Sets the state of CurrentConnectionIDs << urn:schemas-upnp-org:service:ConnectionManager:1 << ConnectionManager \par
\b Note: Must be called at least once prior to start
\param upnptoken The MicroStack token
\param val The new value of the state variable
*/
void UPnPSetState_ConnectionManager_CurrentConnectionIDs(UPnPMicroStackToken upnptoken, char* val)
{
	struct UPnPDataObject *UPnPObject = (struct UPnPDataObject*)upnptoken;
	char* body;
	int bodylength;
	char* valstr;
	if ((valstr = (char*)malloc(ILibXmlEscapeLength(val) + 1)) == NULL) ILIBCRITICALEXIT(254);
	ILibXmlEscape(valstr, val);
	if (UPnPObject->ConnectionManager_CurrentConnectionIDs != NULL) free(UPnPObject->ConnectionManager_CurrentConnectionIDs);
	UPnPObject->ConnectionManager_CurrentConnectionIDs = valstr;
	bodylength = 50 + (int)strlen(valstr);
	if ((body = (char*)malloc(bodylength)) == NULL) ILIBCRITICALEXIT(254);
	bodylength = snprintf(body, bodylength, "%s>%s</%s", "CurrentConnectionIDs", valstr, "CurrentConnectionIDs");
	UPnPSendEvent(upnptoken, body, bodylength, "ConnectionManager");
	free(body);
}

/*! \fn UPnPSetState_RenderingControl_LastChange(UPnPMicroStackToken upnptoken, char* val)
\brief Sets the state of LastChange << urn:schemas-upnp-org:service:RenderingControl:1 << RenderingControl \par
\b Note: Must be called at least once prior to start
\param upnptoken The MicroStack token
\param val The new value of the state variable
*/
void UPnPSetState_RenderingControl_LastChange(UPnPMicroStackToken upnptoken, char* val)
{
	struct UPnPDataObject *UPnPObject = (struct UPnPDataObject*)upnptoken;
	char* body;
	int bodylength;
	char* valstr;
	if ((valstr = (char*)malloc(ILibXmlEscapeLength(val) + 1)) == NULL) ILIBCRITICALEXIT(254);
	ILibXmlEscape(valstr, val);
	if (UPnPObject->RenderingControl_LastChange != NULL) free(UPnPObject->RenderingControl_LastChange);
	UPnPObject->RenderingControl_LastChange = valstr;
	bodylength = 30 + (int)strlen(valstr);
	if ((body = (char*)malloc(bodylength)) == NULL) ILIBCRITICALEXIT(254);
	bodylength = snprintf(body, bodylength, "%s>%s</%s", "LastChange", valstr, "LastChange");
	UPnPSendEvent(upnptoken, body, bodylength, "RenderingControl");
	free(body);
}



void UPnPDestroyMicroStack(void *object)
{
	struct UPnPDataObject *upnp = (struct UPnPDataObject*)object;
	struct SubscriberInfo  *sinfo,*sinfo2;	UPnPSendByeBye(upnp);
	UPnPFreeUnicastReceiveSockets(upnp);
	sem_destroy(&(upnp->EventLock));
	free(upnp->AVTransport_LastChange);
	free(upnp->ConnectionManager_SourceProtocolInfo);
	free(upnp->ConnectionManager_SinkProtocolInfo);
	free(upnp->ConnectionManager_CurrentConnectionIDs);
	free(upnp->RenderingControl_LastChange);
	
	if (upnp->AddressListV4 != NULL) free(upnp->AddressListV4);
	if (upnp->AddressListV6 != NULL) free(upnp->AddressListV6);
	if (upnp->NOTIFY_SEND_socks != NULL) free(upnp->NOTIFY_SEND_socks);
	if (upnp->NOTIFY_RECEIVE_socks != NULL) free(upnp->NOTIFY_RECEIVE_socks);
	if (upnp->NOTIFY_SEND_socks6 != NULL) free(upnp->NOTIFY_SEND_socks6);
	if (upnp->NOTIFY_RECEIVE_socks6 != NULL) free(upnp->NOTIFY_RECEIVE_socks6);
	free(upnp->UUID);
	free(upnp->Serial);
	free(upnp->DeviceDescription);
	sinfo = upnp->HeadSubscriberPtr_AVTransport;
	while(sinfo!=NULL)
	{
		sinfo2 = sinfo->Next;
		UPnPDestructSubscriberInfo(sinfo);
		sinfo = sinfo2;
	}
	sinfo = upnp->HeadSubscriberPtr_ConnectionManager;
	while(sinfo!=NULL)
	{
		sinfo2 = sinfo->Next;
		UPnPDestructSubscriberInfo(sinfo);
		sinfo = sinfo2;
	}
	sinfo = upnp->HeadSubscriberPtr_RenderingControl;
	while(sinfo!=NULL)
	{
		sinfo2 = sinfo->Next;
		UPnPDestructSubscriberInfo(sinfo);
		sinfo = sinfo2;
	}
	
}

int UPnPGetLocalPortNumber(UPnPSessionToken token)
{
	return(ILibWebServer_GetPortNumber(((struct ILibWebServer_Session*)token)->Parent));
}

void UPnPSessionReceiveSink(
struct ILibWebServer_Session *sender,
int InterruptFlag,
struct packetheader *header,
char *bodyBuffer,
int *beginPointer,
int endPointer,
int done)
{
	char *txt;
	if (header != NULL && sender->User3 == NULL && done == 0)
	{
		sender->User3 = (void*)~0;
		txt = ILibGetHeaderLine(header,"Expect",6);
		if (txt!=NULL)
		{
			if (strcasecmp(txt,"100-Continue")==0)
			{
				// Expect Continue
				ILibWebServer_Send_Raw(sender,"HTTP/1.1 100 Continue\r\n\r\n",25,ILibAsyncSocket_MemoryOwnership_STATIC,0);
			}
			else
			{
				// Don't understand
				ILibWebServer_Send_Raw(sender,"HTTP/1.1 417 Expectation Failed\r\n\r\n",35,ILibAsyncSocket_MemoryOwnership_STATIC,1);
				ILibWebServer_DisconnectSession(sender);
				return;
			}
		}
	}
	if (header != NULL && done !=0 && InterruptFlag == 0)
	{
		UPnPProcessHTTPPacket(sender, header, bodyBuffer, beginPointer == NULL?0:*beginPointer, endPointer);
		if (beginPointer!=NULL) {*beginPointer = endPointer;}
	}
}
void UPnPSessionSink(struct ILibWebServer_Session *SessionToken, void *user)
{
	SessionToken->OnReceive = &UPnPSessionReceiveSink;
	SessionToken->User = user;
}

void UPnPSetTag(const UPnPMicroStackToken token, void *UserToken)
{
	((struct UPnPDataObject*)token)->User = UserToken;
}

void *UPnPGetTag(const UPnPMicroStackToken token)
{
	return(((struct UPnPDataObject*)token)->User);
}

UPnPMicroStackToken UPnPGetMicroStackTokenFromSessionToken(const UPnPSessionToken token)
{
	return(((struct ILibWebServer_Session*)token)->User);
}

UPnPMicroStackToken UPnPCreateMicroStack(void *Chain, const char* FriendlyName, const char* UDN, const char* SerialNumber, const int NotifyCycleSeconds, const unsigned short PortNum)

{
	struct UPnPDataObject* RetVal;
	char* DDT;	struct timeval tv;
	size_t len;
	if ((RetVal = (struct UPnPDataObject*)malloc(sizeof(struct UPnPDataObject))) == NULL) ILIBCRITICALEXIT(254);
	
	gettimeofday(&tv,NULL);
	srand((int)tv.tv_sec);
	
	// Complete State Reset
	memset(RetVal, 0, sizeof(struct UPnPDataObject));
	
	RetVal->ForceExit = 0;
	RetVal->PreSelect = &UPnPMasterPreSelect;
	RetVal->PostSelect = NULL;
	RetVal->Destroy = &UPnPDestroyMicroStack;
	RetVal->InitialNotify = 0;
	if (UDN != NULL)
	{
		len = (int)strlen(UDN) + 6;
		if ((RetVal->UUID = (char*)malloc(len)) == NULL) ILIBCRITICALEXIT(254);
		snprintf(RetVal->UUID, len, "uuid:%s", UDN);
		RetVal->UDN = RetVal->UUID + 5;
	}
	if (SerialNumber != NULL)
	{
		len = strlen(SerialNumber) + 1;
		if (len > 20) len = 20;
		if ((RetVal->Serial = (char*)malloc(len)) == NULL) ILIBCRITICALEXIT(254);
		memcpy(RetVal->Serial, SerialNumber, len);
		RetVal->Serial[len - 1] = 0;
	}
	
	len = 10 + UPnPDeviceDescriptionTemplateLengthUX+ (int)strlen(FriendlyName)  + (((int)strlen(RetVal->Serial) + (int)strlen(RetVal->UUID)) * 1);
	if ((RetVal->DeviceDescription = (char*)malloc(len)) == NULL) ILIBCRITICALEXIT(254);
	
	RetVal->WebServerTimer = ILibCreateLifeTime(Chain);
	RetVal->HTTPServer = ILibWebServer_Create(Chain, UPNP_HTTP_MAXSOCKETS, PortNum, &UPnPSessionSink, RetVal);
	RetVal->WebSocketPortNumber = (int)ILibWebServer_GetPortNumber(RetVal->HTTPServer);
	
	
	RetVal->ConfigID = RetVal->WebSocketPortNumber;	
	
	ILibAddToChain(Chain, RetVal);
	UPnPInit(RetVal ,Chain, NotifyCycleSeconds, PortNum);
	
	RetVal->EventClient = ILibCreateWebClient(5, Chain);
	RetVal->UpdateFlag = 0;
	
	DDT = ILibDecompressString((unsigned char*)UPnPDeviceDescriptionTemplate, UPnPDeviceDescriptionTemplateLength, UPnPDeviceDescriptionTemplateLengthUX);
	RetVal->DeviceDescriptionLength = snprintf(RetVal->DeviceDescription, len, DDT, RetVal->ConfigID, FriendlyName, RetVal->Serial, RetVal->UDN);
	
	free(DDT);
	
	sem_init(&(RetVal->EventLock), 0, 1);
	return(RetVal);
}









