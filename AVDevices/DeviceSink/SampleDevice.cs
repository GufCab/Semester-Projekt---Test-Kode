// UPnP .NET Framework Device Stack, Device Module
// Device Builder Build#1.0.4144.25068

using System;
using OpenSource.UPnP;
using OpenSource.DeviceBuilder;

namespace OpenSource.DeviceBuilder
{
	/// <summary>
	/// Summary description for SampleDevice.
	/// </summary>
	class SampleDevice
	{
		private UPnPDevice device;
		
		public SampleDevice()
		{
			device = UPnPDevice.CreateRootDevice(1800,1.0,"\\");
			
			device.FriendlyName = "Media Renderer (Casper-laptop)";
			device.Manufacturer = "OpenSource";
			device.ManufacturerURL = "http://opentools.homeip.net/";
			device.ModelName = "AV Renderer";
			device.ModelDescription = "Media Renderer Device";
			device.HasPresentation = false;
			device.DeviceURN = "urn:schemas-upnp-org:device:MediaRenderer:1";
			OpenSource.DeviceBuilder.DvAVTransport AVTransport = new OpenSource.DeviceBuilder.DvAVTransport();
			AVTransport.External_GetCurrentTransportActions = new OpenSource.DeviceBuilder.DvAVTransport.Delegate_GetCurrentTransportActions(AVTransport_GetCurrentTransportActions);
			AVTransport.External_GetDeviceCapabilities = new OpenSource.DeviceBuilder.DvAVTransport.Delegate_GetDeviceCapabilities(AVTransport_GetDeviceCapabilities);
			AVTransport.External_GetMediaInfo = new OpenSource.DeviceBuilder.DvAVTransport.Delegate_GetMediaInfo(AVTransport_GetMediaInfo);
			AVTransport.External_GetPositionInfo = new OpenSource.DeviceBuilder.DvAVTransport.Delegate_GetPositionInfo(AVTransport_GetPositionInfo);
			AVTransport.External_GetTransportInfo = new OpenSource.DeviceBuilder.DvAVTransport.Delegate_GetTransportInfo(AVTransport_GetTransportInfo);
			AVTransport.External_GetTransportSettings = new OpenSource.DeviceBuilder.DvAVTransport.Delegate_GetTransportSettings(AVTransport_GetTransportSettings);
			AVTransport.External_Next = new OpenSource.DeviceBuilder.DvAVTransport.Delegate_Next(AVTransport_Next);
			AVTransport.External_Pause = new OpenSource.DeviceBuilder.DvAVTransport.Delegate_Pause(AVTransport_Pause);
			AVTransport.External_Play = new OpenSource.DeviceBuilder.DvAVTransport.Delegate_Play(AVTransport_Play);
			AVTransport.External_Previous = new OpenSource.DeviceBuilder.DvAVTransport.Delegate_Previous(AVTransport_Previous);
			AVTransport.External_Seek = new OpenSource.DeviceBuilder.DvAVTransport.Delegate_Seek(AVTransport_Seek);
			AVTransport.External_SetAVTransportURI = new OpenSource.DeviceBuilder.DvAVTransport.Delegate_SetAVTransportURI(AVTransport_SetAVTransportURI);
			AVTransport.External_SetPlayMode = new OpenSource.DeviceBuilder.DvAVTransport.Delegate_SetPlayMode(AVTransport_SetPlayMode);
			AVTransport.External_Stop = new OpenSource.DeviceBuilder.DvAVTransport.Delegate_Stop(AVTransport_Stop);
			device.AddService(AVTransport);
			OpenSource.DeviceBuilder.DvConnectionManager ConnectionManager = new OpenSource.DeviceBuilder.DvConnectionManager();
			ConnectionManager.External_GetCurrentConnectionIDs = new OpenSource.DeviceBuilder.DvConnectionManager.Delegate_GetCurrentConnectionIDs(ConnectionManager_GetCurrentConnectionIDs);
			ConnectionManager.External_GetCurrentConnectionInfo = new OpenSource.DeviceBuilder.DvConnectionManager.Delegate_GetCurrentConnectionInfo(ConnectionManager_GetCurrentConnectionInfo);
			ConnectionManager.External_GetProtocolInfo = new OpenSource.DeviceBuilder.DvConnectionManager.Delegate_GetProtocolInfo(ConnectionManager_GetProtocolInfo);
			device.AddService(ConnectionManager);
			OpenSource.DeviceBuilder.DvRenderingControl RenderingControl = new OpenSource.DeviceBuilder.DvRenderingControl();
			RenderingControl.External_GetBlueVideoBlackLevel = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetBlueVideoBlackLevel(RenderingControl_GetBlueVideoBlackLevel);
			RenderingControl.External_GetBlueVideoGain = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetBlueVideoGain(RenderingControl_GetBlueVideoGain);
			RenderingControl.External_GetBrightness = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetBrightness(RenderingControl_GetBrightness);
			RenderingControl.External_GetColorTemperature = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetColorTemperature(RenderingControl_GetColorTemperature);
			RenderingControl.External_GetContrast = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetContrast(RenderingControl_GetContrast);
			RenderingControl.External_GetGreenVideoBlackLevel = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetGreenVideoBlackLevel(RenderingControl_GetGreenVideoBlackLevel);
			RenderingControl.External_GetGreenVideoGain = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetGreenVideoGain(RenderingControl_GetGreenVideoGain);
			RenderingControl.External_GetHorizontalKeystone = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetHorizontalKeystone(RenderingControl_GetHorizontalKeystone);
			RenderingControl.External_GetLoudness = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetLoudness(RenderingControl_GetLoudness);
			RenderingControl.External_GetMute = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetMute(RenderingControl_GetMute);
			RenderingControl.External_GetRedVideoBlackLevel = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetRedVideoBlackLevel(RenderingControl_GetRedVideoBlackLevel);
			RenderingControl.External_GetRedVideoGain = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetRedVideoGain(RenderingControl_GetRedVideoGain);
			RenderingControl.External_GetSharpness = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetSharpness(RenderingControl_GetSharpness);
			RenderingControl.External_GetVerticalKeystone = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetVerticalKeystone(RenderingControl_GetVerticalKeystone);
			RenderingControl.External_GetVolume = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetVolume(RenderingControl_GetVolume);
			RenderingControl.External_GetVolumeDB = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetVolumeDB(RenderingControl_GetVolumeDB);
			RenderingControl.External_GetVolumeDBRange = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_GetVolumeDBRange(RenderingControl_GetVolumeDBRange);
			RenderingControl.External_ListPresets = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_ListPresets(RenderingControl_ListPresets);
			RenderingControl.External_SelectPreset = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SelectPreset(RenderingControl_SelectPreset);
			RenderingControl.External_SetBlueVideoBlackLevel = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetBlueVideoBlackLevel(RenderingControl_SetBlueVideoBlackLevel);
			RenderingControl.External_SetBlueVideoGain = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetBlueVideoGain(RenderingControl_SetBlueVideoGain);
			RenderingControl.External_SetBrightness = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetBrightness(RenderingControl_SetBrightness);
			RenderingControl.External_SetColorTemperature = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetColorTemperature(RenderingControl_SetColorTemperature);
			RenderingControl.External_SetContrast = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetContrast(RenderingControl_SetContrast);
			RenderingControl.External_SetGreenVideoBlackLevel = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetGreenVideoBlackLevel(RenderingControl_SetGreenVideoBlackLevel);
			RenderingControl.External_SetGreenVideoGain = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetGreenVideoGain(RenderingControl_SetGreenVideoGain);
			RenderingControl.External_SetHorizontalKeystone = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetHorizontalKeystone(RenderingControl_SetHorizontalKeystone);
			RenderingControl.External_SetLoudness = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetLoudness(RenderingControl_SetLoudness);
			RenderingControl.External_SetMute = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetMute(RenderingControl_SetMute);
			RenderingControl.External_SetRedVideoBlackLevel = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetRedVideoBlackLevel(RenderingControl_SetRedVideoBlackLevel);
			RenderingControl.External_SetRedVideoGain = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetRedVideoGain(RenderingControl_SetRedVideoGain);
			RenderingControl.External_SetSharpness = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetSharpness(RenderingControl_SetSharpness);
			RenderingControl.External_SetVerticalKeystone = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetVerticalKeystone(RenderingControl_SetVerticalKeystone);
			RenderingControl.External_SetVolume = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetVolume(RenderingControl_SetVolume);
			RenderingControl.External_SetVolumeDB = new OpenSource.DeviceBuilder.DvRenderingControl.Delegate_SetVolumeDB(RenderingControl_SetVolumeDB);
			device.AddService(RenderingControl);
			
			// Setting the initial value of evented variables
			AVTransport.Evented_LastChange = "Sample String";
			ConnectionManager.Evented_SourceProtocolInfo = "Sample String";
			ConnectionManager.Evented_SinkProtocolInfo = "Sample String";
			ConnectionManager.Evented_CurrentConnectionIDs = "Sample String";
			RenderingControl.Evented_LastChange = "Sample String";
		}
		
		public void Start()
		{
			device.StartDevice();
		}
		
		public void Stop()
		{
			device.StopDevice();
		}
		
		public void AVTransport_GetCurrentTransportActions(System.UInt32 InstanceID, out System.String Actions)
		{
			Actions = "Sample String";
			Console.WriteLine("AVTransport_GetCurrentTransportActions(" + InstanceID.ToString() + ")");
		}
		
		public void AVTransport_GetDeviceCapabilities(System.UInt32 InstanceID, out System.String PlayMedia, out System.String RecMedia, out System.String RecQualityModes)
		{
			PlayMedia = "Sample String";
			RecMedia = "Sample String";
			RecQualityModes = "Sample String";
			Console.WriteLine("AVTransport_GetDeviceCapabilities(" + InstanceID.ToString() + ")");
		}
		
		public void AVTransport_GetMediaInfo(System.UInt32 InstanceID, out System.UInt32 NrTracks, out System.String MediaDuration, out System.String CurrentURI, out System.String CurrentURIMetaData, out System.String NextURI, out System.String NextURIMetaData, out DvAVTransport.Enum_PlaybackStorageMedium PlayMedium, out DvAVTransport.Enum_RecordStorageMedium RecordMedium, out DvAVTransport.Enum_RecordMediumWriteStatus WriteStatus)
		{
			NrTracks = 0;
			MediaDuration = "Sample String";
			CurrentURI = "Sample String";
			CurrentURIMetaData = "Sample String";
			NextURI = "Sample String";
			NextURIMetaData = "Sample String";
			PlayMedium = DvAVTransport.Enum_PlaybackStorageMedium.UNKNOWN;
			RecordMedium = DvAVTransport.Enum_RecordStorageMedium.UNKNOWN;
			WriteStatus = DvAVTransport.Enum_RecordMediumWriteStatus.WRITABLE;
			Console.WriteLine("AVTransport_GetMediaInfo(" + InstanceID.ToString() + ")");
		}
		
		public void AVTransport_GetPositionInfo(System.UInt32 InstanceID, out System.UInt32 Track, out System.String TrackDuration, out System.String TrackMetaData, out System.String TrackURI, out System.String RelTime, out System.String AbsTime, out System.Int32 RelCount, out System.Int32 AbsCount)
		{
			Track = 0;
			TrackDuration = "Sample String";
			TrackMetaData = "Sample String";
			TrackURI = "Sample String";
			RelTime = "Sample String";
			AbsTime = "Sample String";
			RelCount = 0;
			AbsCount = 0;
			Console.WriteLine("AVTransport_GetPositionInfo(" + InstanceID.ToString() + ")");
		}
		
		public void AVTransport_GetTransportInfo(System.UInt32 InstanceID, out DvAVTransport.Enum_TransportState CurrentTransportState, out DvAVTransport.Enum_TransportStatus CurrentTransportStatus, out DvAVTransport.Enum_TransportPlaySpeed CurrentSpeed)
		{
			CurrentTransportState = DvAVTransport.Enum_TransportState.STOPPED;
			CurrentTransportStatus = DvAVTransport.Enum_TransportStatus.OK;
			CurrentSpeed = DvAVTransport.Enum_TransportPlaySpeed._1;
			Console.WriteLine("AVTransport_GetTransportInfo(" + InstanceID.ToString() + ")");
		}
		
		public void AVTransport_GetTransportSettings(System.UInt32 InstanceID, out DvAVTransport.Enum_CurrentPlayMode PlayMode, out DvAVTransport.Enum_CurrentRecordQualityMode RecQualityMode)
		{
			PlayMode = DvAVTransport.Enum_CurrentPlayMode.NORMAL;
			RecQualityMode = DvAVTransport.Enum_CurrentRecordQualityMode._0_EP;
			Console.WriteLine("AVTransport_GetTransportSettings(" + InstanceID.ToString() + ")");
		}
		
		public void AVTransport_Next(System.UInt32 InstanceID)
		{
			Console.WriteLine("AVTransport_Next(" + InstanceID.ToString() + ")");
		}
		
		public void AVTransport_Pause(System.UInt32 InstanceID)
		{
			Console.WriteLine("AVTransport_Pause(" + InstanceID.ToString() + ")");
		}
		
		public void AVTransport_Play(System.UInt32 InstanceID, DvAVTransport.Enum_TransportPlaySpeed Speed)
		{
			Console.WriteLine("AVTransport_Play(" + InstanceID.ToString() + Speed.ToString() + ")");
		}
		
		public void AVTransport_Previous(System.UInt32 InstanceID)
		{
			Console.WriteLine("AVTransport_Previous(" + InstanceID.ToString() + ")");
		}
		
		public void AVTransport_Seek(System.UInt32 InstanceID, DvAVTransport.Enum_A_ARG_TYPE_SeekMode Unit, System.String Target)
		{
			Console.WriteLine("AVTransport_Seek(" + InstanceID.ToString() + Unit.ToString() + Target.ToString() + ")");
		}
		
		public void AVTransport_SetAVTransportURI(System.UInt32 InstanceID, System.String CurrentURI, System.String CurrentURIMetaData)
		{
			Console.WriteLine("AVTransport_SetAVTransportURI(" + InstanceID.ToString() + CurrentURI.ToString() + CurrentURIMetaData.ToString() + ")");
		}
		
		public void AVTransport_SetPlayMode(System.UInt32 InstanceID, DvAVTransport.Enum_CurrentPlayMode NewPlayMode)
		{
			Console.WriteLine("AVTransport_SetPlayMode(" + InstanceID.ToString() + NewPlayMode.ToString() + ")");
		}
		
		public void AVTransport_Stop(System.UInt32 InstanceID)
		{
			Console.WriteLine("AVTransport_Stop(" + InstanceID.ToString() + ")");
		}
		
		public void ConnectionManager_GetCurrentConnectionIDs(out System.String ConnectionIDs)
		{
			ConnectionIDs = "Sample String";
			Console.WriteLine("ConnectionManager_GetCurrentConnectionIDs(" + ")");
		}
		
		public void ConnectionManager_GetCurrentConnectionInfo(System.Int32 ConnectionID, out System.Int32 RcsID, out System.Int32 AVTransportID, out System.String ProtocolInfo, out System.String PeerConnectionManager, out System.Int32 PeerConnectionID, out DvConnectionManager.Enum_A_ARG_TYPE_Direction Direction, out DvConnectionManager.Enum_A_ARG_TYPE_ConnectionStatus Status)
		{
			RcsID = 0;
			AVTransportID = 0;
			ProtocolInfo = "Sample String";
			PeerConnectionManager = "Sample String";
			PeerConnectionID = 0;
			Direction = DvConnectionManager.Enum_A_ARG_TYPE_Direction.INPUT;
			Status = DvConnectionManager.Enum_A_ARG_TYPE_ConnectionStatus.OK;
			Console.WriteLine("ConnectionManager_GetCurrentConnectionInfo(" + ConnectionID.ToString() + ")");
		}
		
		public void ConnectionManager_GetProtocolInfo(out System.String Source, out System.String Sink)
		{
			Source = "Sample String";
			Sink = "Sample String";
			Console.WriteLine("ConnectionManager_GetProtocolInfo(" + ")");
		}
		
		public void RenderingControl_GetBlueVideoBlackLevel(System.UInt32 InstanceID, out System.UInt16 CurrentBlueVideoBlackLevel)
		{
			CurrentBlueVideoBlackLevel = 0;
			Console.WriteLine("RenderingControl_GetBlueVideoBlackLevel(" + InstanceID.ToString() + ")");
		}
		
		public void RenderingControl_GetBlueVideoGain(System.UInt32 InstanceID, out System.UInt16 CurrentBlueVideoGain)
		{
			CurrentBlueVideoGain = 0;
			Console.WriteLine("RenderingControl_GetBlueVideoGain(" + InstanceID.ToString() + ")");
		}
		
		public void RenderingControl_GetBrightness(System.UInt32 InstanceID, out System.UInt16 CurrentBrightness)
		{
			CurrentBrightness = 0;
			Console.WriteLine("RenderingControl_GetBrightness(" + InstanceID.ToString() + ")");
		}
		
		public void RenderingControl_GetColorTemperature(System.UInt32 InstanceID, out System.UInt16 CurrentColorTemperature)
		{
			CurrentColorTemperature = 0;
			Console.WriteLine("RenderingControl_GetColorTemperature(" + InstanceID.ToString() + ")");
		}
		
		public void RenderingControl_GetContrast(System.UInt32 InstanceID, out System.UInt16 CurrentContrast)
		{
			CurrentContrast = 0;
			Console.WriteLine("RenderingControl_GetContrast(" + InstanceID.ToString() + ")");
		}
		
		public void RenderingControl_GetGreenVideoBlackLevel(System.UInt32 InstanceID, out System.UInt16 CurrentGreenVideoBlackLevel)
		{
			CurrentGreenVideoBlackLevel = 0;
			Console.WriteLine("RenderingControl_GetGreenVideoBlackLevel(" + InstanceID.ToString() + ")");
		}
		
		public void RenderingControl_GetGreenVideoGain(System.UInt32 InstanceID, out System.UInt16 CurrentGreenVideoGain)
		{
			CurrentGreenVideoGain = 0;
			Console.WriteLine("RenderingControl_GetGreenVideoGain(" + InstanceID.ToString() + ")");
		}
		
		public void RenderingControl_GetHorizontalKeystone(System.UInt32 InstanceID, out System.Int16 CurrentHorizontalKeystone)
		{
			CurrentHorizontalKeystone = 0;
			Console.WriteLine("RenderingControl_GetHorizontalKeystone(" + InstanceID.ToString() + ")");
		}
		
		public void RenderingControl_GetLoudness(System.UInt32 InstanceID, DvRenderingControl.Enum_A_ARG_TYPE_Channel Channel, out System.Boolean CurrentLoudness)
		{
			CurrentLoudness = false;
			Console.WriteLine("RenderingControl_GetLoudness(" + InstanceID.ToString() + Channel.ToString() + ")");
		}
		
		public void RenderingControl_GetMute(System.UInt32 InstanceID, DvRenderingControl.Enum_A_ARG_TYPE_Channel Channel, out System.Boolean CurrentMute)
		{
			CurrentMute = false;
			Console.WriteLine("RenderingControl_GetMute(" + InstanceID.ToString() + Channel.ToString() + ")");
		}
		
		public void RenderingControl_GetRedVideoBlackLevel(System.UInt32 InstanceID, out System.UInt16 CurrentRedVideoBlackLevel)
		{
			CurrentRedVideoBlackLevel = 0;
			Console.WriteLine("RenderingControl_GetRedVideoBlackLevel(" + InstanceID.ToString() + ")");
		}
		
		public void RenderingControl_GetRedVideoGain(System.UInt32 InstanceID, out System.UInt16 CurrentRedVideoGain)
		{
			CurrentRedVideoGain = 0;
			Console.WriteLine("RenderingControl_GetRedVideoGain(" + InstanceID.ToString() + ")");
		}
		
		public void RenderingControl_GetSharpness(System.UInt32 InstanceID, out System.UInt16 CurrentSharpness)
		{
			CurrentSharpness = 0;
			Console.WriteLine("RenderingControl_GetSharpness(" + InstanceID.ToString() + ")");
		}
		
		public void RenderingControl_GetVerticalKeystone(System.UInt32 InstanceID, out System.Int16 CurrentVerticalKeystone)
		{
			CurrentVerticalKeystone = 0;
			Console.WriteLine("RenderingControl_GetVerticalKeystone(" + InstanceID.ToString() + ")");
		}
		
		public void RenderingControl_GetVolume(System.UInt32 InstanceID, DvRenderingControl.Enum_A_ARG_TYPE_Channel Channel, out System.UInt16 CurrentVolume)
		{
			CurrentVolume = 0;
			Console.WriteLine("RenderingControl_GetVolume(" + InstanceID.ToString() + Channel.ToString() + ")");
		}
		
		public void RenderingControl_GetVolumeDB(System.UInt32 InstanceID, DvRenderingControl.Enum_A_ARG_TYPE_Channel Channel, out System.Int16 CurrentVolume)
		{
			CurrentVolume = 0;
			Console.WriteLine("RenderingControl_GetVolumeDB(" + InstanceID.ToString() + Channel.ToString() + ")");
		}
		
		public void RenderingControl_GetVolumeDBRange(System.UInt32 InstanceID, DvRenderingControl.Enum_A_ARG_TYPE_Channel Channel, out System.Int16 MinValue, out System.Int16 MaxValue)
		{
			MinValue = 0;
			MaxValue = 0;
			Console.WriteLine("RenderingControl_GetVolumeDBRange(" + InstanceID.ToString() + Channel.ToString() + ")");
		}
		
		public void RenderingControl_ListPresets(System.UInt32 InstanceID, out System.String CurrentPresetNameList)
		{
			CurrentPresetNameList = "Sample String";
			Console.WriteLine("RenderingControl_ListPresets(" + InstanceID.ToString() + ")");
		}
		
		public void RenderingControl_SelectPreset(System.UInt32 InstanceID, DvRenderingControl.Enum_A_ARG_TYPE_PresetName PresetName)
		{
			Console.WriteLine("RenderingControl_SelectPreset(" + InstanceID.ToString() + PresetName.ToString() + ")");
		}
		
		public void RenderingControl_SetBlueVideoBlackLevel(System.UInt32 InstanceID, System.UInt16 DesiredBlueVideoBlackLevel)
		{
			Console.WriteLine("RenderingControl_SetBlueVideoBlackLevel(" + InstanceID.ToString() + DesiredBlueVideoBlackLevel.ToString() + ")");
		}
		
		public void RenderingControl_SetBlueVideoGain(System.UInt32 InstanceID, System.UInt16 DesiredBlueVideoGain)
		{
			Console.WriteLine("RenderingControl_SetBlueVideoGain(" + InstanceID.ToString() + DesiredBlueVideoGain.ToString() + ")");
		}
		
		public void RenderingControl_SetBrightness(System.UInt32 InstanceID, System.UInt16 DesiredBrightness)
		{
			Console.WriteLine("RenderingControl_SetBrightness(" + InstanceID.ToString() + DesiredBrightness.ToString() + ")");
		}
		
		public void RenderingControl_SetColorTemperature(System.UInt32 InstanceID, System.UInt16 DesiredColorTemperature)
		{
			Console.WriteLine("RenderingControl_SetColorTemperature(" + InstanceID.ToString() + DesiredColorTemperature.ToString() + ")");
		}
		
		public void RenderingControl_SetContrast(System.UInt32 InstanceID, System.UInt16 DesiredContrast)
		{
			Console.WriteLine("RenderingControl_SetContrast(" + InstanceID.ToString() + DesiredContrast.ToString() + ")");
		}
		
		public void RenderingControl_SetGreenVideoBlackLevel(System.UInt32 InstanceID, System.UInt16 DesiredGreenVideoBlackLevel)
		{
			Console.WriteLine("RenderingControl_SetGreenVideoBlackLevel(" + InstanceID.ToString() + DesiredGreenVideoBlackLevel.ToString() + ")");
		}
		
		public void RenderingControl_SetGreenVideoGain(System.UInt32 InstanceID, System.UInt16 DesiredGreenVideoGain)
		{
			Console.WriteLine("RenderingControl_SetGreenVideoGain(" + InstanceID.ToString() + DesiredGreenVideoGain.ToString() + ")");
		}
		
		public void RenderingControl_SetHorizontalKeystone(System.UInt32 InstanceID, System.Int16 DesiredHorizontalKeystone)
		{
			Console.WriteLine("RenderingControl_SetHorizontalKeystone(" + InstanceID.ToString() + DesiredHorizontalKeystone.ToString() + ")");
		}
		
		public void RenderingControl_SetLoudness(System.UInt32 InstanceID, DvRenderingControl.Enum_A_ARG_TYPE_Channel Channel, System.Boolean DesiredLoudness)
		{
			Console.WriteLine("RenderingControl_SetLoudness(" + InstanceID.ToString() + Channel.ToString() + DesiredLoudness.ToString() + ")");
		}
		
		public void RenderingControl_SetMute(System.UInt32 InstanceID, DvRenderingControl.Enum_A_ARG_TYPE_Channel Channel, System.Boolean DesiredMute)
		{
			Console.WriteLine("RenderingControl_SetMute(" + InstanceID.ToString() + Channel.ToString() + DesiredMute.ToString() + ")");
		}
		
		public void RenderingControl_SetRedVideoBlackLevel(System.UInt32 InstanceID, System.UInt16 DesiredRedVideoBlackLevel)
		{
			Console.WriteLine("RenderingControl_SetRedVideoBlackLevel(" + InstanceID.ToString() + DesiredRedVideoBlackLevel.ToString() + ")");
		}
		
		public void RenderingControl_SetRedVideoGain(System.UInt32 InstanceID, System.UInt16 DesiredRedVideoGain)
		{
			Console.WriteLine("RenderingControl_SetRedVideoGain(" + InstanceID.ToString() + DesiredRedVideoGain.ToString() + ")");
		}
		
		public void RenderingControl_SetSharpness(System.UInt32 InstanceID, System.UInt16 DesiredSharpness)
		{
			Console.WriteLine("RenderingControl_SetSharpness(" + InstanceID.ToString() + DesiredSharpness.ToString() + ")");
		}
		
		public void RenderingControl_SetVerticalKeystone(System.UInt32 InstanceID, System.Int16 DesiredVerticalKeystone)
		{
			Console.WriteLine("RenderingControl_SetVerticalKeystone(" + InstanceID.ToString() + DesiredVerticalKeystone.ToString() + ")");
		}
		
		public void RenderingControl_SetVolume(System.UInt32 InstanceID, DvRenderingControl.Enum_A_ARG_TYPE_Channel Channel, System.UInt16 DesiredVolume)
		{
			Console.WriteLine("RenderingControl_SetVolume(" + InstanceID.ToString() + Channel.ToString() + DesiredVolume.ToString() + ")");
		}
		
		public void RenderingControl_SetVolumeDB(System.UInt32 InstanceID, DvRenderingControl.Enum_A_ARG_TYPE_Channel Channel, System.Int16 DesiredVolume)
		{
			Console.WriteLine("RenderingControl_SetVolumeDB(" + InstanceID.ToString() + Channel.ToString() + DesiredVolume.ToString() + ")");
		}
		
	}
}

