using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using XMLReader;

namespace UDPSend
{
    class Program
    {
        static void Main(string[] args)
        {
            XMLWriterPi writer = new XMLWriterPi();
            string s = writer.testXMLConverter();

            UdpClient udpclient = new UdpClient();

            IPAddress multicastaddress = IPAddress.Parse("239.255.255.250");
            udpclient.JoinMulticastGroup(multicastaddress);
            IPEndPoint remoteep = new IPEndPoint(multicastaddress, 1900);

            Byte[] buffer = null;

            Console.WriteLine("Press ENTER to start sending messages");
            Console.ReadLine();

            string i = "M-SEARCH * HTTP/1.1\nHOST: 239.255.255.250:1900\nST:urn:schemas-upnp-org:device:MediaRenderer:1\nMAN:\"ssdp:discover\"\nMX: 2\r\n";
            StringBuilder stringBuilder = new StringBuilder(i);
            stringBuilder.Append(s);
            i = stringBuilder.ToString();
            
            Console.WriteLine(i);

            buffer = Encoding.UTF8.GetBytes(i);
            udpclient.Send(buffer, buffer.Length, remoteep);
            Console.WriteLine("Sent " + i);

            Console.WriteLine("All Done! Press ENTER to quit.");
            Console.ReadLine();
        }
    }
}
