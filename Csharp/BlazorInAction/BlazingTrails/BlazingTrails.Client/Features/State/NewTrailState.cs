using BlazingTrails.Shared.Features.ManageTrails.Shared;

namespace BlazingTrails.Client.Features.State;

public class NewTrailState
{
    private TrailDto _unsavedNewTrail = new();

    public TrailDto GetTrail() => _unsavedNewTrail;
    public void SaveTrail(TrailDto newTrail) => _unsavedNewTrail = newTrail;
    public void ClearTrail() => _unsavedNewTrail = new();
}
