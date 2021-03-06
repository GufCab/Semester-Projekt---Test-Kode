using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Containers
{
    public interface ITrack
    {
        string Title { get; set; }
        string Artist { get; set; }
        string Album { get; set; }
        string Genre { get; set; }
        string Duration { get; set; }

        string Path { get; set; }       //mappestruktur ifht live555
        string DeviceIP { get; set; }
        string FileName { get; set; }   //ex Jump.mp3
        string Protocol { get; set; }   //ex rtsp://
        string ParentID { get; set; }
    }

    public class Track: ITrack
    {
        public string DeviceIP { get; set; }
        public string Path { get; set; }
        public string FileName { get; set; }
        public string Protocol { get; set; }
        public string ParentID { get; set; }

        public string Title { get; set; }
        public string Duration { get; set; }
        public string Artist { get; set; }
        public string Album { get; set; }
        public string Genre { get; set; }
    }
}
