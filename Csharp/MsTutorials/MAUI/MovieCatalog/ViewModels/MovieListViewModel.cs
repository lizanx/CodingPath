using CommunityToolkit.Mvvm.ComponentModel;
using System.Collections.ObjectModel;
using System.Windows.Input;

namespace MovieCatalog.ViewModels;

public class MovieListViewModel: ObservableObject
{
    public ObservableCollection<MovieViewModel> Movies { get; set; }

    public ICommand DeleteMovieCommand { get; private set; }

    public MovieViewModel SelectedMovie
    {
        get => _selectedMoview;
        set => SetProperty(ref _selectedMoview, value);
    }

    private MovieViewModel _selectedMoview;

    public MovieListViewModel()
    {
        Movies = [];
        SelectedMovie = default!;
        DeleteMovieCommand = new Command<MovieViewModel>(DeleteMovie);
    }

    public async Task RefreshMovies()
    {
        IEnumerable<Models.Movie> moviesData = await Models.MoviesDatabase.GetMovies();

        foreach (Models.Movie movie in moviesData)
            Movies.Add(new MovieViewModel(movie));
    }

    public void DeleteMovie(MovieViewModel movie) =>
        Movies.Remove(movie);
}
