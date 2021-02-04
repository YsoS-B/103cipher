# 103cipher
Chiffré et déchiffré un mesage avec la matrice d'une clé

# The Usage
OPTION: 0 to cipher et 1 to decipher

./103cipher [MESSAGE] [KEY] [OPTION]

# Mode d'emploi

./103cipher "hello" "key" 0  
Decrypted message:  
Key matrix:  
107	101  
121	0  

Encrypted message:  
23349 10504 24624 10908 11877 11211  

./103cipher "h23349 10504 24624 10908 11877 11211" "key" 1  
Key matrix:  
0.0	0.008  
0.01	-0.009  

Decrypted message:  
hello
# 103cipher.

# Etudiants D'Epitech , Attention au -42.
