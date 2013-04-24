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
    class XMLReader
    {
        string reader(string xml)
        {
            //XDocument xmlDoc = new XDocument(new StringReader(xml));

            //var title = xmlDoc.Element(ns + "DIDL-Lite").Elements(ns + "container");
            //var x = xmlDoc.Element(ns + "DIDL-Lite").Elements(ns + "container");

            //Output.Text = x.Attributes("[id]").ToString();

            XmlDocument xmlDocument = new XmlDocument();
            xmlDocument.LoadXml(xml);
            XmlNodeList nodeList = xmlDocument.SelectNodes()

        }
    }
}
