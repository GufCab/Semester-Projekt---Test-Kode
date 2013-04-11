using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using OpenSource.UPnP;
using OpenSource.DeviceBuilder;

namespace DeviceSink
{
    class SinkDevice
    {
        private UPnPDevice device;

        public SinkDevice()
        {
            //Creates root device
            device = UPnPDevice.CreateRootDevice(1800, 1.0 , "\\");

            //Device information:
            device.FriendlyName = "Caspers homemade Renderer";
            device.Manufacturer = "Awesome Casper";
            device.DeviceURN = "urn:schemas-upnp-org:device:MediaRenderer:1";
            
            //Create stacks
            DvAVTransport AVTransport = new DvAVTransport();
            DvConnectionManager connectionManager = new DvConnectionManager();
            DvRenderingControl renderingControl = new DvRenderingControl();

            //Add stacks to device (and network visibility)
            device.AddService(AVTransport);
            device.AddService(connectionManager);
            device.AddService(renderingControl);

            AVTransport.Evented_LastChange = "Sample string";
        }

        public void Start()
        {
            device.StartDevice();
        }

        public void Stop()
        {
            device.StopDevice();
        }

    }
}
