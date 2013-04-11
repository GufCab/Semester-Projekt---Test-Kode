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
        //moved outside scope to keep it alive
        private MediaRendererDiscovery disco;

        public MainWindow()
        {
            InitializeComponent();

            disco = new MediaRendererDiscovery();
            disco.OnAddedDevice += new MediaRendererDiscovery.DiscoveryHandler(AddSink);
            disco.OnRemovedDevice += new MediaRendererDiscovery.DiscoveryHandler(RemoveSink);
            
            disco.Start();
        }

        private void AddSink(MediaRendererDiscovery sender, UPnPDevice d)
        {
            MessageBox.Show("Sink detected: " + d.FriendlyName);

            try
            {
                _avTransport = new CpAVTransport(d.GetServices(CpAVTransport.SERVICE_NAME)[0]);
                
                _avTransport.OnStateVariable_LastChange += new CpAVTransport.StateVariableModifiedHandler_LastChange(Eventer);
            }
            catch (Exception m)
            {
                MessageBox.Show("Couldn't initialize AVTransport: " + m.Message);
            }

            try
            {
                _connectionManagerControl = new CpConnectionManager(d.GetServices(CpConnectionManager.SERVICE_NAME)[0]);
            }
            catch (Exception m)
            {
                MessageBox.Show("Couldn't initialize ConnectionManager: " + m.Message);
            }

            try
            {
                _renderingControl = new CpRenderingControl(d.GetServices(CpRenderingControl.SERVICE_NAME)[0]);
            }
            catch (Exception m)
            {
                MessageBox.Show("Couldn't initialize RenderingControl: " + m.Message);
            }

            //MessageBox.Show(d.DeviceURN);

            //RenderingControl._subscribe(300);
            
        }



        private static void RemoveSink(MediaRendererDiscovery sender, UPnPDevice d)
        {
            Console.WriteLine("Removed Device: " + d.FriendlyName);
        }

        private void btnPlayInvoke_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                _avTransport.Play(0, CpAVTransport.Enum_TransportPlaySpeed._1);
            }
            catch (Exception m)
            {
                MessageBox.Show(m.Message);
                
            }
        }

        private void btnPauseInvoke_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                _avTransport.Pause(0);
            }
            catch (Exception m)
            {
                MessageBox.Show(m.Message);
            }
        }

        private void btnStopInvoke_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                _avTransport.Stop(0);
            }
            catch (Exception m)
            {
                MessageBox.Show(m.Message);
            }
        }

        private void btnNextInvoke_Click(object sender, RoutedEventArgs e)
        {
            //lbxMsgOut.Items.Add("This is some string");
            
            try
            {
                _avTransport.Next(0);
            }
            catch (Exception m)
            {
                MessageBox.Show(m.Message);
            }
             
        }

        private void btnPreviousInvoke_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                _avTransport.Previous(0);
            }
            catch (Exception m)
            {
                MessageBox.Show(m.Message);
            }
        }

        private void btnVolume_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                _avTransport.SetAVTransportURI(0, "rtsp://192.168.1.100/Jump.mp3", "SomeXML");
            }
            catch (Exception m)
            {
                MessageBox.Show(m.Message);
            }
        }

        private void btnSetTransportURI_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                _avTransport.SetAVTransportURI(0, "rtsp://192.168.1.100/Jump.mp3", "SomeXML");
            }
            catch (Exception m)
            {
                MessageBox.Show(m.Message);
            }
        }

        private void btnSubscribe_Click(object sender, RoutedEventArgs e)
        {
            _avTransport._subscribe(300);
        }
        
        public void Eventer(CpAVTransport sender, string d)
        {
            //MessageBox.Show("Got a new event: " + d);
            lbxMsgOut.Items.Add("New Event: " + d);
        }
    }
}
