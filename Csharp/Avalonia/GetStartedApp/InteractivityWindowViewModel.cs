using System.Diagnostics;

namespace GetStartedApp;

public class InteractivityWindowViewModel
{
    public string CounterText { get; set; } = "Counting not started yet.";

    public bool HandleButtonClick()
    {
        Debug.WriteLine("Command issued!");
        return true;
    }
}
