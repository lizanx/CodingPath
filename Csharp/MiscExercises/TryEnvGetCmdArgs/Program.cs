// args doesn't contain extra arguments other passed in terminal.
Console.WriteLine("### Command line arguments from parameter of Main ###");
foreach (string arg in args)
{
    Console.WriteLine(arg);
}

Console.WriteLine();

// envArgs contains an extra argument for program name(may include path) as first argument
Console.WriteLine("### Command line arguments from Env.GetCmdLineArgs ###");
var envArgs = Environment.GetCommandLineArgs();
foreach (string arg in envArgs)
{
    Console.WriteLine(arg);
}

Console.WriteLine();

Console.WriteLine("### Show information you can get via Environment class ###");
ShowEnvironmentDetails();

static void ShowEnvironmentDetails()
{
    Console.WriteLine("OS Version: {0}", Environment.OSVersion);
    Console.WriteLine(".NET Version: {0}", Environment.Version);
    foreach (string drive in Environment.GetLogicalDrives())
    {
        Console.WriteLine("Drive: {0}", drive);
    }
    Console.WriteLine("Is 64-bit OS: {0}", Environment.Is64BitOperatingSystem);
    Console.WriteLine("Is 64-bit process: {0}", Environment.Is64BitProcess);
    Console.WriteLine("Number of CPU cores: {0}", Environment.ProcessorCount);
    Console.WriteLine("Machine name: {0}", Environment.MachineName);
    Console.WriteLine("User name: {0}", Environment.UserName);
    Console.WriteLine("Current process ID: {0}", Environment.ProcessId);
    Console.WriteLine("System dir path: {0}", Environment.SystemDirectory);
}
