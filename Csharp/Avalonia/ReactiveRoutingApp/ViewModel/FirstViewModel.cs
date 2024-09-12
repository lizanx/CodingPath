using System;
using ReactiveUI;

namespace ReactiveRoutingApp.ViewModel;

public class FirstViewModel : ReactiveObject, IRoutableViewModel
{
    public IScreen HostScreen { get; }

    public string UrlPathSegment { get; } = Guid.NewGuid().ToString().Substring(0, 5);

    public FirstViewModel(IScreen screen)
    {
        HostScreen = screen;
    }
}
