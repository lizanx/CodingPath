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
