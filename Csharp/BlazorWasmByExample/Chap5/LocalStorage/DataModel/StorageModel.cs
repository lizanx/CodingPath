namespace LocalStorage.DataModel;

public class StorageModel
{
    public string Value { get; set; } = string.Empty;

    public int Length { get; set; }
    
    public DateTime CreatedAt { get; set; }

    public override string ToString() =>
        $"[Value: {Value}, Length: {Length}, CreationTime: {CreatedAt}]";
}