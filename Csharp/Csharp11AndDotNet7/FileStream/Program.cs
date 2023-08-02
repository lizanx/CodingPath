using static System.IO.Directory;
using static System.IO.Path;
using static System.Environment;
using System.Xml;
using System.Formats.Tar;


// SectionTitle("* Handling cross-platform environments and filesystems");
// WriteLine("{0,-33} {1}", arg0: "Path.PathSeparator",
//     arg1: PathSeparator);
// WriteLine("{0,-33} {1}", arg0: "Path.DirectorySeparatorChar",
//     arg1: DirectorySeparatorChar);
// WriteLine("{0,-33} {1}", arg0: "Directory.GetCurrentDirectory()",
//     arg1: GetCurrentDirectory());
// WriteLine("{0,-33} {1}", arg0: "Environment.CurrentDirectory",
//     arg1: CurrentDirectory);
// WriteLine("{0,-33} {1}", arg0: "Environment.SystemDirectory",
//     arg1: SystemDirectory);
// WriteLine("{0,-33} {1}", arg0: "Path.GetTempPath()",
//     arg1: GetTempPath());

// WriteLine("GetFolderPath(SpecialFolder");
// WriteLine("{0,-33} {1}", arg0: " .System)",
//     arg1: GetFolderPath(SpecialFolder.System));
// WriteLine("{0,-33} {1}", arg0: " .ApplicationData)",
//     arg1: GetFolderPath(SpecialFolder.ApplicationData));
// WriteLine("{0,-33} {1}", arg0: " .MyDocuments)",
//     arg1: GetFolderPath(SpecialFolder.MyDocuments));
// WriteLine("{0,-33} {1}", arg0: " .Personal)",
//     arg1: GetFolderPath(SpecialFolder.Personal));


// SectionTitle("Managing drives");
// WriteLine("{0,-30} | {1,-10} | {2,-7} | {3,18} | {4,18}",
//     "NAME", "TYPE", "FORMAT", "SIZE (BYTES)", "FREE SPACE");
// foreach (DriveInfo drv in DriveInfo.GetDrives())
// {
//     if (drv.IsReady)
//     {
//         WriteLine("{0,-30} | {1,-10} | {2,-7} | {3,18:N0} | {4,18:N0}",
//             drv.Name, drv.DriveType, drv.DriveFormat, drv.TotalSize, drv.AvailableFreeSpace);
//     }
//     else
//     {
//         WriteLine($"{drv.Name, -30} of type {drv.DriveType, -10} is not ready.");
//     }
// }

// SectionTitle("Manage directories");
// string newFolder = Combine(GetCurrentDirectory(), "NewFolder");
// WriteLine($"{newFolder} exists? {Path.Exists(newFolder)}");
// WriteLine("Creating it...");
// CreateDirectory(newFolder);
// WriteLine($"{newFolder} exists? {Path.Exists(newFolder)}");
// WriteLine($"Confirm to delete folder {newFolder} :");
// // ReadLine();
// WriteLine($"Deleting {newFolder}...");
// Delete(newFolder, recursive: true);
// WriteLine($"{newFolder} exists? {Path.Exists(newFolder)}");

// SectionTitle("Manage files");
// string outFolder = Combine(CurrentDirectory, "OutputFolder");
// if (!Path.Exists(outFolder))
// {
//     CreateDirectory(outFolder);
// }
// string textFile = Combine(outFolder, "tmp.txt");
// string backupFile = Combine(outFolder, "tmp.backup");
// // var textWriter = File.CreateText(textFile);
// // textWriter.WriteLine("Hello, C#!");
// // textWriter.Close();
// // File.Copy(textFile, backupFile);
// // var backupReader = File.OpenText(backupFile);
// // WriteLine(backupReader.ReadToEnd());
// // backupReader.Close();

// FileInfo info = new(backupFile);
// WriteLine($"File length: {info.Length} bytes");
// WriteLine($"Last access time: {info.LastAccessTime}");
// WriteLine($"Read only: {info.IsReadOnly}");

// string[] Callsigns = new[]
// {
//     "Husker", "Starbuck", "Apollo", "Boomer",
//     "Bulldog", "Athena", "Helo", "Racetrack"
// };
// string xmlFile = Combine(CurrentDirectory, "stream.xml");
// using (FileStream fs = File.Create(xmlFile))
// {
//     using (XmlWriter xmlWriter = XmlWriter.Create(fs, new XmlWriterSettings { Indent = true }))
//     {
//         xmlWriter.WriteStartDocument();
//         xmlWriter.WriteStartElement("callsigns");
//         foreach (string callsign in Callsigns)
//         {
//             xmlWriter.WriteElementString("callsign", callsign);
//         }
//         xmlWriter.WriteEndElement();
//         xmlWriter.WriteEndDocument();
//     }
// }


SectionTitle("Manage tar files");
string srcDir = Combine(CurrentDirectory, "C");
string dstDir = Combine(CurrentDirectory, "extractDir");
string archiveFile = Combine(CurrentDirectory, "C-archive.tar");
if (!Directory.Exists(srcDir))
{
    Error($"{srcDir} doesn't exist.");
    return;
}
if (File.Exists(archiveFile))
{
    File.Delete(archiveFile);
}
WriteLine("Archiving...");
// using (FileStream tarStream = File.Create(archiveFile))
// {
    TarFile.CreateFromDirectory(srcDir, archiveFile, true);
// }
WriteLine($"Successfully archived to file {archiveFile}");
if (!File.Exists(archiveFile))
{
    Error($"{archiveFile} doesn't exist.");
    return;
}
WriteLine("Unarchiving...");
if (!Directory.Exists(dstDir))
{
    Directory.CreateDirectory(dstDir);
}
// using (FileStream tarStream = File.Create(archiveFile))
// {
    TarFile.ExtractToDirectory(archiveFile, dstDir, true);
// }
WriteLine($"Successfully unarchived to dir {dstDir}");
foreach (var dir in Directory.GetDirectories(dstDir))
{
    Info($"In dir: {dir}");
    foreach (var file in Directory.GetFiles(dir))
    {
        Info($"\tExtracted file: {Path.GetFileName(file)}");
    }
}
