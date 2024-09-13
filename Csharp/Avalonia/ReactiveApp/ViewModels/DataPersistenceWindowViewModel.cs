using System.Reactive;
using System.Runtime.Serialization;
using System.Threading.Tasks;
using ReactiveUI;

namespace ReactiveApp.ViewModels;

[DataContract]
public class DataPersistenceWindowViewModel : ReactiveObject
{
    private string _searchQuery = string.Empty;

    [DataMember]
    public string SearchQuery
    {
        get => _searchQuery;
        set => this.RaiseAndSetIfChanged(ref _searchQuery, value);
    }
    
    [IgnoreDataMember]
    public ReactiveCommand<Unit, Unit> SearchCommand { get; }

    public DataPersistenceWindowViewModel()
    {
        var canSearch = this.WhenAnyValue(x => x.SearchQuery, query => !string.IsNullOrWhiteSpace(query));
        SearchCommand = ReactiveCommand.CreateFromTask(() => Task.Delay(1000), canSearch);
    }
}