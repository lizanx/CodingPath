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

    private static Dictionary<string, User> Users = new();

    public static string? PublicKey;

    public static string GenerateSignature(string data)
    {
        byte[] dataBytes = Encoding.Unicode.GetBytes(data);
        SHA256 sha = SHA256.Create();

        byte[] hashedData = sha.ComputeHash(dataBytes);
        RSA rsa = RSA.Create();

        PublicKey = rsa.ToXmlString(includePrivateParameters: false);

        return ToBase64String(
            rsa.SignHash(hashedData, HashAlgorithmName.SHA256, RSASignaturePadding.Pkcs1)
        );
    }

    public static bool ValidateSignature(string data, string signature)
    {
        if (PublicKey is null)
        {
            return false;
        }

        byte[] dataBytes = Encoding.Unicode.GetBytes(data);
        SHA256 sha = SHA256.Create();

        byte[] hashedData = sha.ComputeHash(dataBytes);
        byte[] signatureBytes = FromBase64String(signature);

        RSA rsa = RSA.Create();
        rsa.FromXmlString(PublicKey);

        return rsa.VerifyHash(
            hashedData, signatureBytes,
            HashAlgorithmName.SHA256, RSASignaturePadding.Pkcs1
        );
    }

    public static User Register(string username, string password)
    {
        RandomNumberGenerator rng = RandomNumberGenerator.Create();
        byte[] saltBytes = new byte[16];
        rng.GetBytes(saltBytes);
        string saltText = ToBase64String(saltBytes);

        string saltedHashedPassword = SaltAndHashPassword(password, saltText);

        User user = new(username, saltText, saltedHashedPassword);

        Users.Add(user.Name, user);

        return user;
    }

    public static bool CheckPassword(string username, string password)
    {
        if (!Users.ContainsKey(username))
        {
            return false;
        }

        User u = Users[username];

        return CheckPassword(password, u.Salt, u.SaltedHashedPassword);
    }

    public static bool CheckPassword(string password, string salt, string hashedPassword)
    {
        return hashedPassword == SaltAndHashPassword(password, salt);
    }

    public static string SaltAndHashPassword(string password, string salt)
    {
        using SHA256 sha = SHA256.Create();
        string saltedPassword = password + salt;
        return ToBase64String(
            sha.ComputeHash(
                Encoding.Unicode.GetBytes(saltedPassword)
            )
        );
    }

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
