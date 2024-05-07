using BlazingTrails.Shared.Features.ManageTrails.Shared;

namespace BlazingTrails.Client.Features.State;

public class AppState
{
    public NewTrailState NewTrailState { get; }

    public AppState()
    {
        NewTrailState = new();
    }
}
