using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.IO;

namespace XMLReader
{
    class Program
    {
        static void Main(string[] args)
        {
            var doc = new XmlDocument();
            doc.Load("SomeXML.xml");

            var reader = new XMLReader();
            reader.reader(doc.OuterXml);

            Console.Read();
        }
    }
}
