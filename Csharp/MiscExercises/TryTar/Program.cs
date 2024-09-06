// Package directory and compress it.
using System.Formats.Tar;
using System.IO.Compression;

string sourceDir = "./Data";
string dstFile = "./Tar/Data.tar.gz";
using (var fs = new FileStream(dstFile, FileMode.Create, FileAccess.Write))
{
    using (var gs = new GZipStream(fs, CompressionMode.Compress))
    {
        await TarFile.CreateFromDirectoryAsync(sourceDir, gs, includeBaseDirectory: true);
    }
}

// Decompress tar.gz file and unpackage it.
string sourceFile = "./Tar/Data.tar.gz";
string dstDir = "./Tar";
using (var fs = new FileStream(sourceFile, FileMode.Open, FileAccess.Read))
{
    using (var gs = new GZipStream(fs, CompressionMode.Decompress))
    {
        await TarFile.ExtractToDirectoryAsync(gs, dstDir, overwriteFiles: true);
    }
}

// Loop through each entry in the tar file without extraction.
// Extract a single file in tar.gz
string dstSingleFile = "./Tar/Single/Cars.json";
using (var fs = new FileStream(sourceFile, FileMode.Open, FileAccess.Read))
{
    using (var gs = new GZipStream(fs, CompressionMode.Decompress))
    {
        using (var reader = new TarReader(gs, leaveOpen: true))
        {
            while (reader.GetNextEntry() is TarEntry entry)
            {
                Console.WriteLine(
                    "[TarEntry] Name: {0}, Length: {1}, "
                        + "ModificationTime: {2}, Checksum: {3}"
                        + "\n  Mode: {4}",
                    entry.Name,
                    entry.Length,
                    entry.ModificationTime,
                    entry.Checksum,
                    entry.Mode
                );
                if (Path.GetFileName(entry.Name) == "Cars.json")
                {
                    Console.WriteLine(
                        "Found matched single file {0} in {1}",
                        entry.Name,
                        sourceFile
                    );
                    entry.ExtractToFile(dstSingleFile, overwrite: true);
                }
            }
        }
    }
}
