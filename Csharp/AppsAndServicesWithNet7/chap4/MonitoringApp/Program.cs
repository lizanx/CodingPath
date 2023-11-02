using System.Text;
using Packt.Shared;

WriteLine("Processing. Please wait...");

// Test large array memory usage.
/*
Recorder.Start();

int[] largeArrayOfInts = Enumerable.Range(start: 0, count: 10_000).ToArray();

Thread.Sleep(Random.Shared.Next(3, 5) * 1000);

Recorder.Stop();
*/

// Test string usage.
int[] numbers = Enumerable.Range(start: 0, count: 10_000).ToArray();

SectionTitle("Using StringBuilder");
Recorder.Start();
StringBuilder builder = new();
foreach (int n in numbers)
{
    builder.Append(n);
    builder.Append(", ");
}
Recorder.Stop();
WriteLine();

SectionTitle("Using string with +");
Recorder.Start();
string s = string.Empty;
foreach (int n in numbers)
{
    s += n.ToString() + ", ";
}
Recorder.Stop();

