using BlazingTrails.Shared.Features.ManageTrails.Shared;
using Blazored.LocalStorage;

namespace BlazingTrails.Client.Features.State;

public class AppState
{
    public NewTrailState NewTrailState { get; }
    public FavoriteTrailsState FavoriteTrailsState { get; }
    private bool _isInitialized;

    public AppState(ILocalStorageService localStorageService)
    {
        NewTrailState = new();
        FavoriteTrailsState = new(localStorageService);
    }

    public async Task Initialize()
    {
        if (!_isInitialized)
        {
            await FavoriteTrailsState.Initialize();

            _isInitialized = true;
        }
    }
}
