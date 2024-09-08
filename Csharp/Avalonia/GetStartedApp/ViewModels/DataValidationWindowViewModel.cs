using System;
using System.ComponentModel.DataAnnotations;
using CommunityToolkit.Mvvm.ComponentModel;

namespace GetStartedApp.ViewModels;

public partial class DataValidationWindowViewModel : ObservableObject
{
    public string Email
    {
        get => _email;
        set
        {
            if (!value.Contains('@'))
                throw new ArgumentException($"Invalid email: {value}");
            SetProperty(ref _email, value);
        }
    }
    
    private string _email = string.Empty;
}