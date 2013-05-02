using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using XMLReader;
using System.Threading;


namespace UDPSend
{
    internal class Program
    {
        private static readonly IPAddress multicastIp = IPAddress.Parse("239.255.255.250");
        private static readonly int multicastPort = 1900;

        public static string UUID { get; private set; }
        public static Guid g = Guid.NewGuid();

        #region Send multicast

        private static UdpClient sendClient;
        private static IPEndPoint remoteep;
        private static Byte[] sendBuffer;

        public static void SetupMulticastSender()
        {
            sendClient = new UdpClient();

            sendClient.JoinMulticastGroup(multicastIp);

            remoteep = new IPEndPoint(multicastIp, multicastPort);
        }

        public static void SendMulticast(string s)
        {
            sendBuffer = Encoding.UTF8.GetBytes(s);
            sendClient.Send(sendBuffer, sendBuffer.Length, remoteep);
        }

        #endregion

        #region Receiver multicast

        private static UdpClient recClient;
        private static IPEndPoint recIPep;
        private static Byte[] recBuffer;

        public static void SetupMulticastReceiver()
        {
            recClient = new UdpClient();

            recIPep = new IPEndPoint(IPAddress.Any, multicastPort);
            recClient.Client.Bind(recIPep);

            recClient.JoinMulticastGroup(multicastIp);
        }

        //Blocks until reception
        public static string ReceiveMulticast()
        {
            Byte[] data = recClient.Receive(ref recIPep);
            string strData = Encoding.UTF8.GetString(data);

            return strData;
        }

        #endregion

        /*
        public enum Directive
        { NOTIFY, "POST", "GET", MSEARCH="M-SEARCH"};
        */

        public static List<string> HTTPNotifygenerator(int cacheexpire, string locationip, List<string> NTs)
        {
            int i = 0;
            List<string> slist = new List<string>();
            
            string id = "uuid:" + UUID;

            slist.Add("NOTIFY * HTTP/1.1\r\n" +
                    "HOST: " + multicastIp.ToString() + ":" + multicastPort + "\r\n" +
                    "CACHE-CONTROL: max-age=" + cacheexpire + "\r\n" +
                    "LOCATION: " + locationip + "\r\n" +
                    "SERVER: Windows NT/5.0, UPnP/1.1\r\n" +
                    "NT: " + id + "\r\n" +
                    "NTS: ssdp:alive\r\n" +
                    "USN: " + id + "\r\n" +
                    "Content-Length: 0" + "\r\n");

            foreach(string f in NTs)
            {
                slist.Add("NOTIFY * HTTP/1.1\n" +
                      "HOST: " + multicastIp.ToString() + ":" + multicastPort + "\r\n" +
                      "CACHE-CONTROL: max-age=" + cacheexpire + "\r\n" +
                      "LOCATION: " + locationip + "\r\n" +
                      "SERVER: Windows NT/5.0, UPnP/1.1\r\n" +
                      "NT: " + f + "\r\n" +
                      "NTS: ssdp:alive\n" +
                      "USN: " + UUID + "::" + f + "\r\n" + 
                      "Content-Length: 0" + "\r\n");
            }

            return slist;
        }

        public static string GetOwnIp()
        {
            //finds my ip address
            string localIP = "";
            IPHostEntry host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (IPAddress ip in host.AddressList)
            {
                if (ip.AddressFamily.ToString() == "InterNetwork")
                {
                    localIP = ip.ToString();
                }
            }
            return localIP;
        }

        #region M-SEARCH header saved for later use
        string i = "M-SEARCH * HTTP/1.1\n" +
           "HOST: 239.255.255.250:1900\n" +
           "ST:urn:schemas-upnp-org:device:MediaRenderer:1\n" +
           "MAN:\"ssdp:discover\"\n" +
           "MX: 2" +
           "\r\n";
        #endregion

        static void Main(string[] args)
        {
            //Initial setup:
            SetupMulticastSender();
            //SetupMulticastReceiver();

            UUID = g.ToString();
            string ownip = "http://" + GetOwnIp();

            Console.WriteLine("Press ENTER to start sending messages");
            Console.ReadLine();

            List<string> NTs = new List<string>();
            NTs.Add("upnp:rootdevice");
            NTs.Add("urn:schemas-upnp-org:device:MediaServer:1");
            NTs.Add("urn:schemas-upnp-org:service:ContentDirectory:1");
            NTs.Add("urn:schemas-upnp-org:service:ConnectionManager:1");

            List<string> notify = HTTPNotifygenerator(1800, ownip, NTs);

            for (int l = 0; l < 4; l++)
            {
                foreach (string s in notify)
                {
                    SendMulticast(s);
                    Console.WriteLine(s);
                }
                Thread.Sleep(66);
            }


            Console.ReadLine();
        }
    }
}
