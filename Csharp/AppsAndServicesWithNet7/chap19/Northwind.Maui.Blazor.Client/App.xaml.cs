﻿using Northwind.Maui.Blazor.Client.Views;

namespace Northwind.Maui.Blazor.Client
{
    public partial class App : Application
    {
        public App()
        {
            InitializeComponent();

            MainPage = new AppShell();
        }
    }
}
