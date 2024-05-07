using BlazingTrails.Client.Features.Home.Shared;
using BlazingTrails.Shared.Features.ManageTrails.Shared;
using Blazored.LocalStorage;
using BlazingTrails.Client.Features.Shared;

namespace BlazingTrails.Client.Features.State;

public class FavoriteTrailsState(ILocalStorageService localStorageService)
{
    public IReadOnlyList<Trail> FavoriteTrails => _favoriteTrails.AsReadOnly();
    public event Action? OnChange;
    private const string FavouriteTrailsKey = "favoriteTrails";
    private bool _isInitialized;
    private List<Trail> _favoriteTrails = [];
    private readonly ILocalStorageService _localStorageService = localStorageService;

    public async Task Initialize()
    {
        if (!_isInitialized)
        {
            _favoriteTrails = await _localStorageService.GetItemAsync<List<Trail>>(FavouriteTrailsKey) ?? [];
            _isInitialized = true;
            NotifyStateHasChanged();
        }
    }

    public async Task AddFavorite(Trail trail)
    {
        if (IsFavorite(trail))
        {
            return;
        }

        _favoriteTrails.Add(trail);
        await _localStorageService.SetItemAsync(FavouriteTrailsKey, _favoriteTrails);
        NotifyStateHasChanged();
    }

    public async Task RemoveFavorite(Trail trail)
    {
        var existingTrail = _favoriteTrails.SingleOrDefault(t => t.Id == trail.Id);
        if (existingTrail == null)
        {
            return;
        }
        _favoriteTrails.Remove(existingTrail);
        await _localStorageService.SetItemAsync(FavouriteTrailsKey, _favoriteTrails);
        NotifyStateHasChanged();
    }

    public bool IsFavorite(Trail trail) =>
        _favoriteTrails.Any(t => t.Id == trail.Id);

    private void NotifyStateHasChanged() =>
        OnChange?.Invoke();
}
