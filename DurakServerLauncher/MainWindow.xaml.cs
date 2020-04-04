using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace DurakServerLauncher
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void GenerateRandomSeed()
        {
            var random = new Random();
            uint number = (uint)(random.Next(int.MinValue, int.MaxValue) + (uint)int.MaxValue);
            textBoxDeckSeed.Text = "0x" + Convert.ToString(number, 16);
        }

        private void windowLauncher_Loaded(object sender, RoutedEventArgs e)
        {
            GenerateRandomSeed();
        }

        private void buttonGenerateNewSeed_Click(object sender, RoutedEventArgs e)
        {
            GenerateRandomSeed();
        }
    }
}
