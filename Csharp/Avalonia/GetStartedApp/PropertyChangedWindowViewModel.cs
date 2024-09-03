using System.ComponentModel;

namespace GetStartedApp;

public class PropertyChangedWindowViewModel : INotifyPropertyChanged
{
    private int _clickCounter;

    public int ClickCounter
    {
        get => _clickCounter;
        set
        {
            _clickCounter = value;
            OnPropertyChanged(nameof(ClickCounter));
        }
    }
    
    public event PropertyChangedEventHandler? PropertyChanged;

    protected virtual void OnPropertyChanged(string propertyName)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}