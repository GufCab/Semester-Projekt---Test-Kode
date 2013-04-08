using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using OpenSource.UPnP;
using OpenSource.DeviceBuilder;


namespace CP_Sink
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static CpRenderingControl _renderingControl;
        private static CpConnectionManager _connectionManagerControl;
        private static CpAVTransport _avTransport;

        public MainWindow()
        {
            InitializeComponent();

            MediaRendererDiscovery disco = new MediaRendererDiscovery();
            disco.OnAddedDevice += new MediaRendererDiscovery.DiscoveryHandler(AddSink);
            disco.OnRemovedDevice += new MediaRendererDiscovery.DiscoveryHandler(RemoveSink);
            
            disco.Start();
            
        }

        private static void AddSink(MediaRendererDiscovery sender, UPnPDevice d)
        {
            //Console.WriteLine("Added Device: " + d.FriendlyName);
            MessageBox.Show("Sink detected: " + d.FriendlyName);
            _renderingControl = new CpRenderingControl(d.GetServices(CpRenderingControl.SERVICE_NAME)[0]);
            _connectionManagerControl = new CpConnectionManager(d.GetServices(CpConnectionManager.SERVICE_NAME)[0]);
            _avTransport = new CpAVTransport(d.GetServices(CpAVTransport.SERVICE_NAME)[0]);
            
            //RenderingControl._subscribe(300);
        }

        private static void RemoveSink(MediaRendererDiscovery sender, UPnPDevice d)
        {
            Console.WriteLine("Removed Device: " + d.FriendlyName);
        }

        private void btnPlayInvoke_Click(object sender, RoutedEventArgs e)
        {
            _avTransport.Play(0, CpAVTransport.Enum_TransportPlaySpeed._1);
        }
    }
}
