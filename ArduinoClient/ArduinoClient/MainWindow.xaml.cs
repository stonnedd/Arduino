using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Windows;

namespace ArduinoClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow
    {
        private Socket _sender;
        public MainWindow()
        {
            InitializeComponent();
        }

        private void ButtonClick(object sender, RoutedEventArgs e)
        {
            ConnectSocketClient();
        }

        private void ConnectSocketClient()
        {
            var bytes = new byte[1024];
            var adreess = new IPEndPoint(IPAddress.Parse("192.168.1.177"), 23);
             _sender = new Socket(AddressFamily.InterNetwork,
                SocketType.Stream, ProtocolType.Tcp);
            
          
            // Connect the socket to the remote endpoint. Catch any errors.
            try
            {
                _sender.Connect(adreess);

                MessageBox.Show("Socket connected to {0}",
                    _sender.RemoteEndPoint.ToString());
                
                
                //int bytesRec = _sender.Receive(bytes);
                //MessageBox.Show("Echoed test = {0}",
                //    Encoding.ASCII.GetString(bytes, 0, bytesRec));
                //_sender.Shutdown(SocketShutdown.Both);
               // _sender.Close();

            }
            catch (ArgumentNullException ane)
            {
                MessageBox.Show("ArgumentNullException : {0}", ane.ToString());
            }


        }

        private void Led1Click(object sender, RoutedEventArgs e)
        {
            SendData("1");
        }

        private void Led2Click(object sender, RoutedEventArgs e)
        {
            SendData("2");
        }

        private void Led3Click(object sender, RoutedEventArgs e)
        {
            SendData("3");
        }

        private void SendData(String sData)
        {
            
            var msg = Encoding.ASCII.GetBytes(sData);
            _sender.Send(msg);
            
           
        }
    }
}
