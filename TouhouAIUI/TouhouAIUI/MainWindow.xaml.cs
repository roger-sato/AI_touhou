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

        TouhouAILogic.MainProc main_proc;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void SendKeyPre()
        {
            Interaction.AppActivate(p.Id);
            System.Threading.Thread.Sleep(100);
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
        
        private void GetProcess_Click(object sender, RoutedEventArgs e)
        {
            p = Process.GetProcessesByName("th15")[0];
        }
        
        private void Test_Click(object sender, RoutedEventArgs e)
        {
            Interaction.AppActivate(p.Id);
            System.Threading.Thread.Sleep(100);

            Timer timer = new Timer();

            timer.Tick += new EventHandler(MyProc);
            timer.Interval = 30;
            timer.Start();

        }

        private void MyProc(object sender, EventArgs e)
        {
           main_proc.Test();
            
        }

        private void mach_Click(object sender, RoutedEventArgs e)
        {
            main_proc.Test();
        }

        private void Init_Click(object sender, RoutedEventArgs e)
        {
            main_proc = new TouhouAILogic.MainProc();

            main_proc.Init(Process.GetProcessesByName("th15")[0].MainWindowHandle);
        }

        private void ScreenShot_Click(object sender, RoutedEventArgs e)
        { 
            Timer timer = new Timer();

            timer.Tick += new EventHandler(ScreenShot_event);
            timer.Interval = 100;
            timer.Start();
        }

        private void ScreenShot_event(object sender, EventArgs e)
        {
            main_proc.ScreenShot();
        }

    }
}
