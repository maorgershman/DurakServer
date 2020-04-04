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
            uint number = (uint)(new Random().Next(int.MinValue, int.MaxValue) + (uint)int.MaxValue);
            textBoxDeckSeed.Text = "0x" + Convert.ToString(number, 16).PadLeft("ffffffff".Length, '0');
        }

        private bool CheckSeed()
        {
            var seed = textBoxDeckSeed.Text.ToLower();
            
            if (seed.Length != "0xffffffff".Length)
            {
                return false;
            }

            if (!(seed[0] == '0' && seed[1] == 'x'))
            {
                return false;
            }

            for (int i = "0x".Length; i < seed.Length; i++)
            {
                char c = seed[i];
                if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')))
                {
                    return false;
                }
            }

            textBoxDeckSeed.Text = seed; // Switch all to lower case
            
            return true;
        }

        //

        private void windowLauncher_Loaded(object sender, RoutedEventArgs e)
        {
            GenerateRandomSeed();
        }

        private void buttonGenerateNewSeed_Click(object sender, RoutedEventArgs e)
        {
            GenerateRandomSeed();
        }

        private void buttonRun_Click(object sender, RoutedEventArgs e)
        {
            if (!CheckSeed())
            {
                MessageBox.Show("Invalid seed!", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
            else
            {
                MessageBox.Show("Preparing to launch!", "Success", MessageBoxButton.OK, MessageBoxImage.Information);
                // TODO!
            }
        }
    }
}
