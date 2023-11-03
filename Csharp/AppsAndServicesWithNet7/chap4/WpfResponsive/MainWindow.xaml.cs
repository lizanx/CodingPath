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
using System.Diagnostics;
using Microsoft.Data.SqlClient;

namespace WpfResponsive
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private const string connectionString =
            "Data Source=.;" +
            "Initial Catalog=Northwind;" +
            "Integrated Security=true;" +
            "Encrypt=false;" +
            "MultipleActiveResultSets=true;";
        private const string sql =
            "WAITFOR DELAY '00:00:05';" +
            "SELECT EmployeeId, FirstName, LastName FROM Employees";

        public MainWindow()
        {
            InitializeComponent();
        }
    }
}
