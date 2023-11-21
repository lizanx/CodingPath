1. AES.
2. RSA.
3. A rainbow attack uses a table of precalculated hashes of passwords. When a database
of password hashes is stolen, the attacker can compare against the rainbow table hashes quickly
and determine the original passwords.
4. Smaller block size is better for encryption algorithms.
5. A cryptographic hash is a fixed-size output that results from an input of arbitrary size
being processed by a hash function. Hash functions are one-way, which means that the only
way to recreate the original input is to brute-force all possible inputs and compare the results.
6. Combine hashing algorithm and asymmetric encryption to ensure data integrity.
7. 
- Symmetric: the same key is used for both encryption and decryption.
- Asymmetric: public key is used for encryption, private key is used for decryption.
8. First letter of names of algorithm creators.
9. Because the password is stored as hashed data, which means different users with  
the same password have the same hashed data and it's easy to be attacked.  
Salt is added to ensure that the hashed data of even the same password differ.  
To slow down rainbow dictionary attacks.
10. It's too weak, collisions have been found.
