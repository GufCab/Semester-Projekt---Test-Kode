using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.IO;
using Playback;

namespace XMLReader
{
    class Program
    {
        static void Main(string[] args)
        {
            Track t = new Track();
            t.Path = "Music/Van Halen/";
            
            //finds my ip address
            IPHostEntry host;
            string localIP = "?";
            host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (IPAddress ip in host.AddressList)
            {
                if (ip.AddressFamily.ToString() == "InterNetwork")
                {
                    localIP = ip.ToString();
                }
            }

            t.DeviceIP = localIP;
            t.FileName = "Jump.mp3";
            t.Protocol = "rtsp://";
            t.Title = "Jump";
            t.Duration = 240;
            t.Artist = "Van Halen";
            t.Album = "1984";
            t.Genre = "Pop";

            List<ITrack> trackList = new List<ITrack>();
            trackList.Add(t);
            trackList.Add(t);
            trackList.Add(t);
            trackList.Add(t);

            XMLWriterPi writer = new XMLWriterPi();
            //writer.testXMLConverter();
            string s = writer.XMLConverter(trackList);
            //Console.WriteLine(s);

            var doc = new XmlDocument();
            //doc.Load("CreatedXML.xml");
            doc.Load("SomeXML.xml");

            var reader = new XMLReader();
            List<Result> list = reader.containerReader(doc.OuterXml);

            var doc1 = new XmlDocument();
            doc1.Load("CreatedXML.xml");
            list.AddRange(reader.itemReader(doc1.OuterXml));

            foreach (Result result in list)
            {
                Console.WriteLine(result.ContainerRes + " " + result.type + " " + result.id + " " + result.partenID);
            }

            writer.testXMLConverter();

            Console.Read();
        }
    }
}
