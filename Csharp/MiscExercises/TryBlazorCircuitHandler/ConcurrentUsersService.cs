namespace TryBlazorCircuitHandler;

public class ConcurrentUsersService
{
    public int UserCount
    {
        get => _userCount;
        set
        {
            _userCount = value;
            OnUsersChanged?.Invoke(_userCount);
        }
    }

    public event Action<int>? OnUsersChanged;

    private int _userCount;
}
