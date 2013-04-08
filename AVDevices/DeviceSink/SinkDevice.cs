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


            //Add stack to device (and network)
            device.AddService(AVTransport);
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
