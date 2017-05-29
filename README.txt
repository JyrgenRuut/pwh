Basic Password handler made in c++ (NOT to be used for real passwords) for use on Windows platforms by Jürgen Ruut

###Basic overview###
The program is meant to take a Master Password and a site name (or "key") and make a SHA1 hash from the pair, generating a password onto your clipboard for pasting where-ever needed.
The program also has a way to save a few preferences/restrictions, namely if the password is required to have at least one non-capital letter and if the length of the password must be less than 40.

I must stress this again, SHA1 is no longer considered secure, and the program is missing functionality for salting the hashes, meaning all that this program should really be used for is simply generating seemingly random strings of hex letters from a "master Password" - "Key" pair. 


:Documentation not present... date of arrival unknown: