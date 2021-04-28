/**
Encryption and Decryption functions

(Read jabcode.h in src/jabcode to understand jab_data)
**/

#include "jabcode.h"
#include "encryption.h"

/**
* @brief encrypt data using given key
* @param key the private key for encryption
* @param data the data to be encrypted
* @return the encrypted data
**/
jab_data* RG_encrypt(jab_data* key,jab_data* data){
    // Encrypt enc_data -> data using enc_data -> key
    return data;
}

/**
* @brief decrypt data using the given key
* @param key the public key for decryption
* @param data the data to be decrypted
* @return the decrypted data
**/
jab_data* RG_decrypt(jab_data* key,jab_data* data){
    return data;
}

/**
* @brief generate a signature for the given data
* @param data the data whose signature is to be found
* @return the signature
**/
jab_data* RG_sign(jab_data* data){
    return data;
}