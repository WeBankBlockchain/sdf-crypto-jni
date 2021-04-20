/*
    This file is part of FISCO-BCOS.

    FISCO-BCOS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FISCO-BCOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FISCO-BCOS.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file SDFCryptoProvider.h
 * @author maggiewu
 * @date 2021-02-01
 */
#pragma once
#include "libsdf/swsds.h"
#include <stdio.h>
#include <cstdlib>
#include <list>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
namespace dev
{
class KeyPair;
namespace crypto
{
enum AlgorithmType : uint32_t
{
    SM2 = 0x00020100,      // SGD_SM2_1
    SM3 = 0x00000001,      // SGD_SM3
    SM4_CBC = 0x00002002,  // SGD_SM4_CBC
};
class Key
{
public:
    unsigned char * PublicKey() const { return m_publicKey; }
    unsigned char * PrivateKey() const { return m_privateKey; }
    int PublicKeyLen() const { return m_publicKeyLen; }
    int PrivateKeyLen() const { return m_privateKeyLen; }
    unsigned int Identifier() const { return m_keyIndex; };
    char * Password() const { return m_keyPassword; };
    bool IsInternalKey() const { return m_isInternalKey; }
    Key(void){};
    Key(unsigned char* privateKey,int privateKeyLen, unsigned char* publicKey, int publicKeyLen)
    {
        m_privateKey = privateKey;
        m_privateKeyLen = privateKeyLen;
        m_publicKey = publicKey;
        m_publicKeyLen = publicKeyLen;
    };
    Key(const unsigned int keyIndex, char *& password)
    {
        m_keyIndex = keyIndex;
        m_keyPassword = password;
        m_isInternalKey = true;
    };
    Key(const unsigned int keyIndex)
    {
        m_keyIndex = keyIndex;
        m_isInternalKey = true;
    };
    void setPrivateKey(unsigned char* privateKey, unsigned int len)
    {
        m_privateKey = (unsigned char*)malloc(len * sizeof(char));
        memcpy(m_privateKey, privateKey, len);
        m_privateKeyLen = len;
    };
    void setPublicKey(unsigned char* publicKey, unsigned int len)
    {
        m_publicKey = (unsigned char*)malloc(len * sizeof(char));
        memcpy(m_publicKey, publicKey, len);
        m_publicKeyLen = len;
    };

private:
    unsigned int m_keyIndex;
    char * m_keyPassword;
    unsigned char * m_privateKey;
    unsigned char * m_publicKey;
    int m_privateKeyLen;
    int m_publicKeyLen;
    bool m_isInternalKey = false;
};

/*
class SessionPool
{
public:
    SessionPool(int size, void * deviceHandle);
    virtual ~SessionPool();
    void * GetSession();
    void ReturnSession(void * session);


private:
    void * m_deviceHandle;
    size_t m_size;
    std::list<void *> m_pool;
};
*/

/**
 *  SDFCryptoProvider suply SDF function calls
 *  Singleton
 */
/*class SDFCryptoProvider
{
private:
    void * m_deviceHandle;
    SessionPool* m_sessionPool;
    SDFCryptoProvider();
    ~SDFCryptoProvider();
    SDFCryptoProvider(const SDFCryptoProvider&);
    SDFCryptoProvider& operator=(const SDFCryptoProvider&);
    // std::mutex mut;

public:
    *//**
     * Return the instance
     *//*
    static SDFCryptoProvider& GetInstance();

    *//**
     * Generate key
     * Return error code
     *//*
    unsigned int KeyGen(AlgorithmType algorithm, Key* key);

    *//**
     * Sign
     *//*
    unsigned int Sign(Key const& key, AlgorithmType algorithm, unsigned char const* digest,
        unsigned int const digestLen, unsigned char* signature, unsigned int* signatureLen);

    *//**
     * Verify signature
     *//*
    unsigned int Verify(Key const& key, AlgorithmType algorithm, unsigned char const* digest,
        unsigned int const digestLen, unsigned char const* signature,
        unsigned int const signatureLen, bool* result);

    *//**
     * Make hash
     *//*
    unsigned int Hash(Key* key, AlgorithmType algorithm, unsigned char const* message,
        unsigned int const messageLen, unsigned char*  digest, unsigned int* digestLen);

    *//**
     * Encrypt
     *//*
    unsigned int Encrypt(Key const& key, AlgorithmType algorithm, unsigned char const* plantext,
        unsigned int const plantextLen, unsigned char* cyphertext, unsigned int* cyphertextLen);

    *//**
     * Decrypt
     *//*
    unsigned int Decrypt(Key const& key, AlgorithmType algorithm, unsigned char const* cyphertext,
        unsigned int const cyphertextLen, unsigned char* plantext, unsigned int* plantextLen);

    *//**
     * Make sm3 hash with z value
     *//*
    unsigned int HashWithZ(Key* key, AlgorithmType algorithm, unsigned char const* zValue,
        unsigned int const zValueLen, unsigned char const* message, unsigned int const messageLen,
        unsigned char* digest, unsigned int* digestLen);

    *//**
     *  Get public key of an internal key
     *//*
    unsigned int ExportInternalPublicKey(Key & key, AlgorithmType algorithm);
    
    static char * GetErrorMessage(unsigned int code);
};*/

struct SDFCryptoResult{
    char * signature;
    char * publicKey;
    char * privateKey;
    bool result;
    char * hash;
    char * sdfErrorMessage;
};

SDFCryptoResult KeyGen(AlgorithmType algorithm);
SDFCryptoResult Sign(char * privateKey, AlgorithmType algorithm, char const* digest);
SDFCryptoResult SignWithInternalKey(unsigned int keyIndex, char * password, AlgorithmType algorithm, char const* digest);
SDFCryptoResult Verify(char * publicKey, AlgorithmType algorithm, char const* digest, char const* signature);
SDFCryptoResult VerifyWithInternalKey(unsigned int keyIndex, AlgorithmType algorithm, char const* digest,char const* signature);
SDFCryptoResult Hash(char * key, AlgorithmType algorithm, char const* message);
SDFCryptoResult ExportInternalPublicKey(unsigned int keyIndex, AlgorithmType algorithm);


/*SDFCryptoResult HashWithZ(char * key, AlgorithmType algorithm, char const* message);
SDFCryptoResult makeResult(char * signature,char * publicKey,char * privateKey,bool result,char * hash,unsigned int code,char*);
char * toHex(unsigned char *data, int len);
std::vector<uint8_t> fromHex(char * hexString);
int fromHexChar(char _i);
unsigned int getHexByteLen(char * hexString);
int PrintData(char*,unsigned char*,unsigned int, unsigned int);
int SearchData(unsigned char *, unsigned int , unsigned int);*/
}  // namespace crypto
}  // namespace dev
