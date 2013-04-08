// UPnP .NET Framework Device Stack, Core Module
// Device Builder Build#1.0.4144.25068

using System;
using DeviceSink;
using OpenSource.UPnP;
using OpenSource.DeviceBuilder;

namespace OpenSource.DeviceBuilder
{
	/// <summary>
	/// Summary description for Main.
	/// </summary>
	class SampleDeviceMain
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			// Starting UPnP Device
			System.Console.WriteLine("UPnP .NET Framework Stack");
			System.Console.WriteLine("Device Builder Build#1.0.4144.25068");
			SinkDevice device = new SinkDevice();
			device.Start();
			System.Console.WriteLine("Press return to stop device.");
			System.Console.ReadLine();
			device.Stop();
		}
	}
}

