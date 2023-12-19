﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel; // ObservableCollection<T>

namespace Northwind.Maui.Client;
public class CustomerListViewModel :
    ObservableCollection<CustomerDetailViewModel>
{
    public void AddSampleData(bool clearList = true)
    {
        if (clearList)
        {
            Clear();
        }
        Add(new CustomerDetailViewModel
        {
            CustomerId = "ALFKI",
            CompanyName = "Alfreds Futterkiste",
            ContactName = "Maria Anders",
            City = "Berlin",
            Country = "Germany",
            Phone = "030-0074321"
        });
        Add(new CustomerDetailViewModel
        {
            CustomerId = "FRANK",
            CompanyName = "Frankenversand",
            ContactName = "Peter Franken",
            City = "München",
            Country = "Germany",
            Phone = "089-0877310"
        });
        Add(new CustomerDetailViewModel
        {
            CustomerId = "SEVES",
            CompanyName = "Seven Seas Imports",
            ContactName = "Hari Kumar",
            City = "London",
            Country = "UK",
            Phone = "(171) 555-1717"
        });
    }
}
