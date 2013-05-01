using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Net;
using System.IO;

namespace UPnPHTTP
{
    class Program
    {
        static public TcpListener serverSocket;
        private static UdpClient cli;

        public static int port = 1900;
        public static IPAddress ip = IPAddress.Parse("239.255.255.250"); 
            //0xeffffffa);    //ip: 239.255.255.250
        //Find converter here: http://www.ipaddresslocation.org/convertip.php

        static void Main(string[] args)
        {
            //Tutorial: http://www.jarloo.com/c-udp-multicasting-tutorial/
            cli = new UdpClient();

            IPEndPoint ipep = new IPEndPoint(IPAddress.Any, 1900);


            cli.Client.Bind(ipep);

            cli.JoinMulticastGroup(ip);

            while (true)
            {
                Byte[] data = cli.Receive(ref ipep);
                string strData = Encoding.UTF8.GetString(data);
                Console.WriteLine(strData);
            }

            /*
            Byte[] buffer = null;

            Console.WriteLine("Press ENTER to start sending messages");
            Console.ReadLine();

            for (int i = 0; i <= 8000; i++)
            {
                buffer = Encoding.Unicode.GetBytes(i.ToString());
                cli.Send(buffer, buffer.Length, ipep);
                Console.WriteLine("Sent " + i);
            }

            Console.WriteLine("All Done! Press ENTER to quit.");
            Console.ReadLine();
            */
            /*
            //Tutorial: http://www.codeproject.com/Articles/1705/IP-Multicasting-in-C
            Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);


            IPEndPoint ipep = new IPEndPoint(IPAddress.Any, 1900);
            s.Bind(ipep);

            s.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.AddMembership, new MulticastOption(ip, IPAddress.Any));

            

            byte[] b = new byte[10000];

            s.Receive(b);
            string str = System.Text.Encoding.ASCII.GetString(b, 0, b.Length);
            
            Console.WriteLine(str);

            //For receive:

            //s.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.AddMembership, new MulticastOption(ip));

            //s.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.MulticastTimeToLive, 2);
            */

            /*
            if (HttpListener.IsSupported)
                Console.WriteLine("Supported");
            
            HttpListener listener = new HttpListener();

            listener.Prefixes.Add("http://127.0.0.1:1900/");
            
            Console.WriteLine("Start listening...");

            try
            {
                listener.Start();
                Console.WriteLine("...");

                HttpListenerContext context = listener.GetContext();
 

                Console.WriteLine("New connection received");

                HttpListenerRequest request = context.Request;
                // Obtain a response object.
                HttpListenerResponse response = context.Response;
                // Construct a response. 
                string responseString = "<HTML><BODY> Hello world!</BODY></HTML>";
                byte[] buffer = System.Text.Encoding.UTF8.GetBytes(responseString);
                // Get a response stream and write the response to it.
                response.ContentLength64 = buffer.Length;
                System.IO.Stream output = response.OutputStream;
                output.Write(buffer, 0, buffer.Length);
                // You must close the output stream.
                output.Close();
                listener.Stop();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                Console.WriteLine(e.Message);
                
            }

            /*
            byte[] buffer = new byte[1000000];

            serverSocket = new TcpListener(ip, port);

            serverSocket.Start();

            TcpClient con = serverSocket.AcceptTcpClient();

            NetworkStream net = con.GetStream();
            Console.WriteLine("Connection established");

            //Receive TCP Connection:
            #region Receive
            net.Flush();
            net.Read(buffer, 0, (int) con.ReceiveBufferSize);
            string inString = System.Text.Encoding.ASCII.GetString(buffer);	
            #endregion

            Console.WriteLine(inString);
            */


            Console.ReadLine();

            

            
        }
    }
}
