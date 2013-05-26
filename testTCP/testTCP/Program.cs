using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UPnP_Device;

namespace testTCP
{
    class Program
    {
        static void Main(string[] args)
        {
            TCPReceiver tcpReceiver = new TCPReceiver("127.0.0.1", 1000);
            //TCPUtillity util = new TCPUtillity();

            Console.Read();

            tcpReceiver.receive();
        }
    }
}
