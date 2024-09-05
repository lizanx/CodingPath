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
