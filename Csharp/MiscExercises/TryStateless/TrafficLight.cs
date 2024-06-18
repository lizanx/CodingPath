using Stateless;

namespace TryStateless;

class TrafficLight
{
    private readonly StateMachine<Color, Trigger> _light;

    public TrafficLight(TrafficLight.Color color)
    {
        _light = new (color);

        _light.Configure(Color.Green)
            .Permit(Trigger.TimeExpiring, Color.Yellow)
            .OnEntry(static () =>
                {
                    Console.WriteLine($"Traffic Light: 🟢");
                    Console.WriteLine("😁 You can go now!");
                })
            .OnExit(static () =>
                {
                    Console.WriteLine($"🏃💨 Hurry up! Green light is gone.");
                });
        _light.Configure(Color.Yellow)
            .Permit(Trigger.TimeExpiring, Color.Red)
            .OnEntry(static () => Console.WriteLine($"Traffic Light: 🟡"));
        _light.Configure(Color.Red)
            .Permit(Trigger.TimeExpiring, Color.Green)
            .OnEntry(static () =>
                {
                    Console.WriteLine($"Traffic Light: 🔴");
                    Console.WriteLine("🚫 Stop! You must wait now.");
                });
    }

    public void Next()
    {
        _light.Fire(Trigger.TimeExpiring);
    }

    public enum Color
    {
        Red,
        Green,
        Yellow
    }

    public enum Trigger
    {
        TimeExpiring
    }
}
