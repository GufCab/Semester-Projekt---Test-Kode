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

namespace CP_Source
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static CpConnectionManager ConnectionManager;
        private static CpContentDirectory ContentDirectory;

        public MainWindow()
        {
            InitializeComponent();

            MediaServerDiscovery disco = new MediaServerDiscovery();
            disco.OnAddedDevice += new MediaServerDiscovery.DiscoveryHandler(AddSink);
            disco.OnRemovedDevice += new MediaServerDiscovery.DiscoveryHandler(RemoveSink);

            disco.Start();
        }

        private static void AddSink(MediaServerDiscovery sender, UPnPDevice d)
        {
            //Console.WriteLine("Added Device: " + d.FriendlyName);

            // To interace with a service, instantiate the appropriate wrapper class on the appropriate service
            // Traverse the device heirarchy to the correct device, and invoke 'GetServices', passing in the static field 'SERVICE_NAME'
            // of the appropriate wrapper class. This method returns an array of all services with this service type. For most purposes,
            // there will only be one service, in which case you can use array index 0.
            // Save a reference to this instance of the wrapper class for later use.

            ConnectionManager = new CpConnectionManager(d.GetServices(CpConnectionManager.SERVICE_NAME)[0]);
            ContentDirectory = new CpContentDirectory(d.GetServices(CpContentDirectory.SERVICE_NAME)[0]);

            // To subscribe to Events, call the '_subscribe' method of the wrapper class. The only parameter is
            // the duration of the event. A good value is 300 seconds.
            //ConnectionManager._subscribe(300);

            // The wrapper class exposes all the evented state variables through events in the form 'OnStateVariable_xx', where xx is the variable name.

            // The wrapper class exposes methods in two formats. Asyncronous and Syncronous. The Async method calls are exposed simply
            // by the name of the method. The Syncronous version is the same, except with the word, 'Sync_' prepended to the name.
            // Asyncronous responses to th async method calls are dispatched through the event in the format, 'OnResult_x' where x is the method name.

            // Note: All arguments are automatically type checked. Allowed Values are abstracted through enumerations, that are defined in the wrapper class.
            // To access the list of allowed values or ranges for a given device, refer to the property 'Values_XXX' for a list of the allowed values for a
            // given state variable. Similarly, refer to the properties 'HasMaximum_XXX', 'HasMinimum_XXX', 'Maximum_XXX', and 'Minimum_XXX' where XXX is the variable name, for the Max/Min values.

            // To determine if a given service implements a particular StateVariable or Method, use the properties, 'HasStateVariableXXX' and 'HasActionXXX' where XXX is the method/variable name.
        }
        private static void RemoveSink(MediaServerDiscovery sender, UPnPDevice d)
        {
            Console.WriteLine("Removed Device: " + d.FriendlyName);
        }
    }
}
