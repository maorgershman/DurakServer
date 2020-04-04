using System;
using System.Diagnostics;
using System.IO;
using System.Windows;

namespace DurakServerLauncher
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static string DurakServerExePath
        {
            get
            {
                var solutionPath = Directory.GetParent(Directory.GetCurrentDirectory()).FullName;

                return string.Format(@"{0}\Binaries\DurakServer.exe", solutionPath);
            }
        }

        public MainWindow()
        {
            InitializeComponent();
        }

        private void GenerateRandomSeed()
        {
            uint number = (uint)(new Random().Next(int.MinValue, int.MaxValue) + (uint)int.MaxValue);
            textBoxSeed.Text = "0x" + Convert.ToString(number, 16).PadLeft("ffffffff".Length, '0');
        }

        private bool CheckSeed()
        {
            var seed = textBoxSeed.Text.ToLower();
            
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

            textBoxSeed.Text = seed; // Switch all to lower case
            
            return true;
        }

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
                try
                {
                    var variation = comboBoxVariation.Text.ToLower();
                    var players = integerUpDownPlayers.Text;
                    var seed = textBoxSeed.Text;
                    var args = string.Format("{0} {1} {2}", variation, players, seed);

                    Process.Start(DurakServerExePath, args);
                    Close();
                }
                catch (Exception)
                {
                    MessageBox.Show(string.Format("Unable to start process at: '{0}'", DurakServerExePath), 
                        "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }
    }
}
