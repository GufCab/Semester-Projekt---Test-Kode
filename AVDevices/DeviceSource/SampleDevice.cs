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
			
			device.FriendlyName = "Media Server (CASPER-LAPTOP)";
			device.Manufacturer = "OpenSource";
			device.ManufacturerURL = "";
			device.ModelName = "Media Server";
			device.ModelDescription = "Provides content through UPnP ContentDirectory service";
			device.ModelNumber = "0.765";
			device.HasPresentation = false;
			device.DeviceURN = "urn:schemas-upnp-org:device:MediaServer:1";
			
            DvConnectionManager ConnectionManager = new DvConnectionManager();

            ConnectionManager.External_GetCurrentConnectionIDs = ConnectionManager_GetCurrentConnectionIDs;
		    ConnectionManager.External_GetCurrentConnectionInfo = ConnectionManager_GetCurrentConnectionInfo;
			//ConnectionManager.External_GetProtocolInfo = ConnectionManager_GetProtocolInfo;
			
            device.AddService(ConnectionManager);
			

            DvContentDirectory ContentDirectory = new DvContentDirectory();
			
            ContentDirectory.External_Browse = new OpenSource.DeviceBuilder.DvContentDirectory.Delegate_Browse(ContentDirectory_Browse);
			ContentDirectory.External_CreateObject = new OpenSource.DeviceBuilder.DvContentDirectory.Delegate_CreateObject(ContentDirectory_CreateObject);
			ContentDirectory.External_CreateReference = new OpenSource.DeviceBuilder.DvContentDirectory.Delegate_CreateReference(ContentDirectory_CreateReference);
			ContentDirectory.External_DeleteResource = new OpenSource.DeviceBuilder.DvContentDirectory.Delegate_DeleteResource(ContentDirectory_DeleteResource);
			ContentDirectory.External_DestroyObject = new OpenSource.DeviceBuilder.DvContentDirectory.Delegate_DestroyObject(ContentDirectory_DestroyObject);
			ContentDirectory.External_ExportResource = new OpenSource.DeviceBuilder.DvContentDirectory.Delegate_ExportResource(ContentDirectory_ExportResource);
			ContentDirectory.External_GetSearchCapabilities = new OpenSource.DeviceBuilder.DvContentDirectory.Delegate_GetSearchCapabilities(ContentDirectory_GetSearchCapabilities);
			ContentDirectory.External_GetSortCapabilities = new OpenSource.DeviceBuilder.DvContentDirectory.Delegate_GetSortCapabilities(ContentDirectory_GetSortCapabilities);
			ContentDirectory.External_GetSystemUpdateID = new OpenSource.DeviceBuilder.DvContentDirectory.Delegate_GetSystemUpdateID(ContentDirectory_GetSystemUpdateID);
			ContentDirectory.External_GetTransferProgress = new OpenSource.DeviceBuilder.DvContentDirectory.Delegate_GetTransferProgress(ContentDirectory_GetTransferProgress);
			ContentDirectory.External_ImportResource = new OpenSource.DeviceBuilder.DvContentDirectory.Delegate_ImportResource(ContentDirectory_ImportResource);
			ContentDirectory.External_Search = new OpenSource.DeviceBuilder.DvContentDirectory.Delegate_Search(ContentDirectory_Search);
			ContentDirectory.External_StopTransferResource = new OpenSource.DeviceBuilder.DvContentDirectory.Delegate_StopTransferResource(ContentDirectory_StopTransferResource);
			ContentDirectory.External_UpdateObject = new OpenSource.DeviceBuilder.DvContentDirectory.Delegate_UpdateObject(ContentDirectory_UpdateObject);
			
            device.AddService(ContentDirectory);
			
			// Setting the initial value of evented variables
			ConnectionManager.Evented_SourceProtocolInfo = "Sample String";
			ConnectionManager.Evented_SinkProtocolInfo = "Sample String";
			ConnectionManager.Evented_CurrentConnectionIDs = "Sample String";
			ContentDirectory.Evented_ContainerUpdateIDs = "Sample String";
			ContentDirectory.Evented_SystemUpdateID = 0;
			ContentDirectory.Evented_TransferIDs = "Sample String";
		}
		
		public void Start()
		{
			device.StartDevice();
		}
		
		public void Stop()
		{
			device.StopDevice();
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
		
		public void ContentDirectory_Browse(System.String ObjectID, DvContentDirectory.Enum_A_ARG_TYPE_BrowseFlag BrowseFlag, System.String Filter, System.UInt32 StartingIndex, System.UInt32 RequestedCount, System.String SortCriteria, out System.String Result, out System.UInt32 NumberReturned, out System.UInt32 TotalMatches, out System.UInt32 UpdateID)
		{
			Result = "Noget nyt";
			NumberReturned = 1;
			TotalMatches = 2;
			UpdateID = 3;
			Console.WriteLine("ContentDirectory_Browse(" + ObjectID.ToString() + BrowseFlag.ToString() + Filter.ToString() + StartingIndex.ToString() + RequestedCount.ToString() + SortCriteria.ToString() + ")");
		}
		
		public void ContentDirectory_CreateObject(System.String ContainerID, System.String Elements, out System.String ObjectID, out System.String Result)
		{
			ObjectID = "Sample String";
			Result = "Sample String";
			Console.WriteLine("ContentDirectory_CreateObject(" + ContainerID.ToString() + Elements.ToString() + ")");
		}
		
		public void ContentDirectory_CreateReference(System.String ContainerID, System.String ObjectID, out System.String NewID)
		{
			NewID = "Sample String";
			Console.WriteLine("ContentDirectory_CreateReference(" + ContainerID.ToString() + ObjectID.ToString() + ")");
		}
		
		public void ContentDirectory_DeleteResource(System.Uri ResourceURI)
		{
			Console.WriteLine("ContentDirectory_DeleteResource(" + ResourceURI.ToString() + ")");
		}
		
		public void ContentDirectory_DestroyObject(System.String ObjectID)
		{
			Console.WriteLine("ContentDirectory_DestroyObject(" + ObjectID.ToString() + ")");
		}
		
		public void ContentDirectory_ExportResource(System.Uri SourceURI, System.Uri DestinationURI, out System.UInt32 TransferID)
		{
			TransferID = 0;
			Console.WriteLine("ContentDirectory_ExportResource(" + SourceURI.ToString() + DestinationURI.ToString() + ")");
		}
		
		public void ContentDirectory_GetSearchCapabilities(out System.String SearchCaps)
		{
			SearchCaps = "Sample String";
			Console.WriteLine("ContentDirectory_GetSearchCapabilities(" + ")");
		}
		
		public void ContentDirectory_GetSortCapabilities(out System.String SortCaps)
		{
			SortCaps = "Sample String";
			Console.WriteLine("ContentDirectory_GetSortCapabilities(" + ")");
		}
		
		public void ContentDirectory_GetSystemUpdateID(out System.UInt32 Id)
		{
			Id = 0;
			Console.WriteLine("ContentDirectory_GetSystemUpdateID(" + ")");
		}
		
		public void ContentDirectory_GetTransferProgress(System.UInt32 TransferID, out DvContentDirectory.Enum_A_ARG_TYPE_TransferStatus TransferStatus, out System.String TransferLength, out System.String TransferTotal)
		{
			TransferStatus = DvContentDirectory.Enum_A_ARG_TYPE_TransferStatus.COMPLETED;
			TransferLength = "Sample String";
			TransferTotal = "Sample String";
			Console.WriteLine("ContentDirectory_GetTransferProgress(" + TransferID.ToString() + ")");
		}
		
		public void ContentDirectory_ImportResource(System.Uri SourceURI, System.Uri DestinationURI, out System.UInt32 TransferID)
		{
			TransferID = 0;
			Console.WriteLine("ContentDirectory_ImportResource(" + SourceURI.ToString() + DestinationURI.ToString() + ")");
		}
		
		public void ContentDirectory_Search(System.String ContainerID, System.String SearchCriteria, System.String Filter, System.UInt32 StartingIndex, System.UInt32 RequestedCount, System.String SortCriteria, out System.String Result, out System.UInt32 NumberReturned, out System.UInt32 TotalMatches, out System.UInt32 UpdateID)
		{
			Result = "Sample String";
			NumberReturned = 0;
			TotalMatches = 0;
			UpdateID = 0;
			Console.WriteLine("ContentDirectory_Search(" + ContainerID.ToString() + SearchCriteria.ToString() + Filter.ToString() + StartingIndex.ToString() + RequestedCount.ToString() + SortCriteria.ToString() + ")");
		}
		
		public void ContentDirectory_StopTransferResource(System.UInt32 TransferID)
		{
			Console.WriteLine("ContentDirectory_StopTransferResource(" + TransferID.ToString() + ")");
		}
		
		public void ContentDirectory_UpdateObject(System.String ObjectID, System.String CurrentTagValue, System.String NewTagValue)
		{
			Console.WriteLine("ContentDirectory_UpdateObject(" + ObjectID.ToString() + CurrentTagValue.ToString() + NewTagValue.ToString() + ")");
		}
		
	}
}

