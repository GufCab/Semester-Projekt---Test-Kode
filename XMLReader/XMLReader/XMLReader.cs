using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using System.Xml;

namespace XMLReader
{
    public class XMLReader
    {
        public string reader(string xml)
        {
            var xmlDocument = new XmlDocument();
            //xmlDocument.Load("SomeXML.xml");
            xmlDocument.LoadXml(xml);

            XmlNodeList nodeList = xmlDocument.GetElementsByTagName("container");

            foreach (XmlElement elm in nodeList)
            {
                Console.Write(elm.GetAttribute("id") + ": ");
                var y = elm.InnerXml;
                XmlNodeList titleList = elm.GetElementsByTagName("dc:title");
                
                Console.WriteLine(titleList[0].InnerText);
            }

            return xml;
        }
    }
}
