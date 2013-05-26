using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UPnP_Device;

namespace send
{
    class Program
    {
        static void Main(string[] args)
        {
            TCPReceiver soc = new TCPReceiver("127.0.0.1", 1000);
            TCPUtillity utillity = new TCPUtillity();
            
            Console.Read();

            utillity.TCPSend(soc.networkStream, "hej med jer");
        }
    }
}
