using System;
using ReactiveRoutingApp.ViewModel;
using ReactiveUI;

namespace ReactiveRoutingApp.View;

public class AppViewLocator : ReactiveUI.IViewLocator
{
    public IViewFor ResolveView<T>(T? viewModel, string? contract = null) =>
        viewModel switch
        {
            FirstViewModel vm => new FirstView() { DataContext = vm },
            _ => throw new ArgumentOutOfRangeException(nameof(viewModel))
        };
}
