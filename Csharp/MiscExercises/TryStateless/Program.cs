
using System.Security.Cryptography;
using TryStateless;

var trafficLight = new TrafficLight(TrafficLight.Color.Red);

Console.WriteLine("Simulation of traffic lights:(Press any key to move to next state, 'q' for quit)");

while (true)
{
    var keyInfo = Console.ReadKey();
    if (keyInfo.Key == ConsoleKey.Q)
    {
        Console.WriteLine("🔚 Exit simulation.");
        break;
    }
    trafficLight.Next();
}
