using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace HardwareSupplies
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainWindow : Window
    {
        public HardwareItem[] HardwareItems { get; set; }

        public MainWindow()
        {
            this.InitializeComponent();

            PopulateItems();
        }

        private void PopulateItems()
        {
            HardwareItems = new[]
            {
                new HardwareItem { id = 1, name = "Wood Screw", category
                = "Screws", cost = 0.02M, price = 0.10M, quantity = 504 },
                new HardwareItem { id = 2, name = "Sheet Metal Screw",
                category = "Screws", cost = 0.03M, price = 0.15M, quantity = 655
                },
                new HardwareItem { id = 3, name = "Drywall Screw",
                category = "Screws", cost = 0.02M, price = 0.11M, quantity = 421
                },
                new HardwareItem { id = 4, name = "Galvanized Nail",
                category = "Nails", cost = 0.04M, price = 0.16M, quantity = 5620
                },
                new HardwareItem { id = 5, name = "Framing Nail",
                category = "Nails", cost = 0.06M, price = 0.20M, quantity =
                12000 },
                new HardwareItem { id = 6, name = "Finishing Nail 2 inch", category = "Nails", cost = 0.02M, price = 0.11M, quantity
                = 1405 },
                new HardwareItem { id = 7, name = "Finishing Nail 1 inch", category = "Nails", cost = 0.01M, price = 0.10M, quantity
                = 1110 },
                new HardwareItem { id = 8, name = "Light Switch - White", category = "Electrical", cost = 0.25M, price = 1.99M,
                quantity = 78 },
                new HardwareItem { id = 9, name = "Outlet - White",
                category = "Electrical", cost = 0.21M, price = 1.99M, quantity =
                56 },
                new HardwareItem { id = 10, name = "Outlet - Beige",
                category = "Electrical", cost = 0.21M, price = 1.99M, quantity =
                90 },
                new HardwareItem { id = 11, name = "Wire Ties", category
                = "Electrical", cost = 0.50M, price = 4.99M, quantity = 125 },
                new HardwareItem { id = 12, name = "Switch Plate - White", category = "Electrical", cost = 0.21M, price = 2.49M,
                quantity = 200 }
            };
        }
    }
}
