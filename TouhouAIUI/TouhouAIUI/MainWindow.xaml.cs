using System.Windows;
using System.Windows.Forms;
//using Microsoft.Win32;
using Microsoft.VisualBasic;
using System.Runtime.InteropServices;
using System;
using System.Diagnostics;


namespace TouhouAIUI
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        private OpenFileDialog ofd;
        System.Diagnostics.Process p;

        TouhouAILogic.MainProc main_proc = new TouhouAILogic.MainProc();

        public MainWindow()
        {
            InitializeComponent();
            
        }

        private void SendKeyPre()
        {
            Interaction.AppActivate(p.Id);
            System.Threading.Thread.Sleep(30);
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            p = System.Diagnostics.Process.Start(ofd.FileName);

            //念のため待つ。
            p.WaitForInputIdle();

            //ウィンドウハンドルが取得できるか、
            //生成したプロセスが終了するまで待ってみる。
            while (p.MainWindowHandle == IntPtr.Zero &&
            p.HasExited == false)
            {
                System.Threading.Thread.Sleep(1);
                p.Refresh();
            }
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            ofd = new OpenFileDialog();
            ofd.FileName = "";
            ofd.DefaultExt = "*.*";
            ofd.ShowDialog();
        }

        private void Up_Click(object sender, RoutedEventArgs e)
        {
            SendKeyPre();
            main_proc.Up();
        }

        private void Enter_Click(object sender, RoutedEventArgs e)
        {
            SendKeyPre();
            main_proc.Enter();
        }

        private void Right_Click(object sender, RoutedEventArgs e)
        {
            SendKeyPre();
            main_proc.Right();
        }

        private void Left_Click(object sender, RoutedEventArgs e)
        {
            SendKeyPre();
            main_proc.Left();
        }

        private void Down_Click(object sender, RoutedEventArgs e)
        {
            SendKeyPre();
            main_proc.Down();
        }

        private void GetProcess_Click(object sender, RoutedEventArgs e)
        {
            p = Process.GetProcessesByName("th15")[0];
        }
        
        private void Test_Click(object sender, RoutedEventArgs e)
        {
            // SendKeyPre();
            //Test.Content = main_proc.Test(p.MainWindowHandle);
            Test.Content = main_proc.Test(Process.GetProcessesByName("th15")[0].MainWindowHandle);
        }

        private void mach_Click(object sender, RoutedEventArgs e)
        {
            main_proc.Mach();
        }
    }
}
