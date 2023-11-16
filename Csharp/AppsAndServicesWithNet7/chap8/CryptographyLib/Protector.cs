using System.Diagnostics; // Stopwach
using System.Security.Cryptography; // Aes, Rfc2898DeriveBytes, etc.
using System.Text; // Encoding

using static System.Convert; // ToBase64String, FromBase64String

namespace Packt.Shared;

public static class Protector
{
    // salt must be at least 8 bytes, we'll use 16 bytes
    private static readonly byte[] salt = Encoding.Unicode.GetBytes("7BANANAS");
    
    // Default iterations for Rfc2898DeriveBytes is 1000.
    // Iterations should be high enough to take at least 100ms to
    // generate a Key and IV on the target machine.
    private static readonly int iterations = 500_000;

    public static string Encrypt(string plainText, string password)
    {
        byte[] encryptedBytes;
        byte[] plainBytes = Encoding.Unicode.GetBytes(plainText);

        using (Aes aes = Aes.Create())
        {
            Stopwatch timer = Stopwatch.StartNew();

            using (Rfc2898DeriveBytes pbkdf2 = new(
                password, salt, iterations, HashAlgorithmName.SHA256))
            {
                WriteLine("PBKDF2 algorithm: {0}, Iteration count: {1:N0}",
                    pbkdf2.HashAlgorithm, pbkdf2.IterationCount);
                
                aes.Key = pbkdf2.GetBytes(32); // set a 256-bit key
                aes.IV = pbkdf2.GetBytes(16); // set a 128-bit IV
            }

            timer.Stop();

            WriteLine("{0:N0}ms to generate Key and IV.", timer.ElapsedMilliseconds);

            WriteLine("Encryption algorithm: {0}-{1}, {2} mode with {3} padding.",
                "AES", aes.KeySize, aes.Mode, aes.Padding);
            
            using (MemoryStream ms = new())
            {
                using (ICryptoTransform transformer = aes.CreateEncryptor())
                {
                    using (CryptoStream cs = new(ms, transformer, CryptoStreamMode.Write))
                    {
                        cs.Write(plainBytes, 0, plainBytes.Length);

                        if (!cs.HasFlushedFinalBlock)
                        {
                            cs.FlushFinalBlock();
                        }
                    }
                }

                encryptedBytes = ms.ToArray();
            }
        }

        return ToBase64String(encryptedBytes);
    }

    public static string Decrypt(string cipherText, string password)
    {
        byte[] plainBytes;
        byte[] cryptoBytes = FromBase64String(cipherText);

        using (Aes aes = Aes.Create())
        {
            using (Rfc2898DeriveBytes pbkdf2 = new(
                password, salt, iterations, HashAlgorithmName.SHA256))
            {
                aes.Key = pbkdf2.GetBytes(32);
                aes.IV = pbkdf2.GetBytes(16);
            }

            using (MemoryStream ms = new())
            {
                using (ICryptoTransform transformer = aes.CreateDecryptor())
                {
                    using (CryptoStream cs = new(ms, transformer, CryptoStreamMode.Write))
                    {
                        cs.Write(cryptoBytes, 0, cryptoBytes.Length);

                        if (!cs.HasFlushedFinalBlock)
                        {
                            cs.FlushFinalBlock();
                        }
                    }
                }

                plainBytes = ms.ToArray();
            }
        }

        return Encoding.Unicode.GetString(plainBytes);
    }
}
