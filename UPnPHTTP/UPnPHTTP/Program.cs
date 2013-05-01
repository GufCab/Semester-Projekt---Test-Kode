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

        public static int port = 1900;
        public static IPAddress ip = new IPAddress(0xeffffffa);    //ip: 239.255.255.250
        //Find converter here: http://www.ipaddresslocation.org/convertip.php

        static void Main(string[] args)
        {
            if (HttpListener.IsSupported)
                Console.WriteLine("Supported");
            
            HttpListener listener = new HttpListener();

            listener.Prefixes.Add(string.Format("http://239.255.255.250:1900/"));
            
            Console.WriteLine("Start listening...");

            try
            {
                listener.Start();
                Console.WriteLine("...");

                HttpListenerContext context = listener.GetContext();
                HttpListenerRequest request = context.Request;

                Console.WriteLine("New connection received");

                Console.WriteLine(context);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                Console.WriteLine(e.Message);
                
            }




            Console.ReadLine();

            /* NOT IN USE. SAVED FOR LATER
            serverSocket = new TcpListener(ip, port);

            serverSocket.Start();

            TcpClient con = serverSocket.AcceptTcpClient();
            
            NetworkStream net = con.GetStream();
             * */
        }
    }
}
