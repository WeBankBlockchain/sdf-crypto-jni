package com.webank.wedpr.crypto.hsm;

import com.webank.wedpr.crypto.hsm.sdf.AlgorithmType;
import com.webank.wedpr.crypto.hsm.sdf.SDF;
import com.webank.wedpr.crypto.hsm.sdf.SDFCryptoResult;
import com.webank.wedpr.crypto.hsm.utils.Hex;

public class Main {
    public static void main(String[] arg) {
        byte[] message =
                new byte[] {
                    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61,
                    0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62,
                    0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63,
                    0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
                    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64
                };
        byte[] stdResult =
                new byte[] {
                    (byte) 0xde,
                    (byte) 0xbe,
                    (byte) 0x9f,
                    (byte) 0xf9,
                    0x22,
                    0x75,
                    (byte) 0xb8,
                    (byte) 0xa1,
                    0x38,
                    0x60,
                    0x48,
                    (byte) 0x89,
                    (byte) 0xc1,
                    (byte) 0x8e,
                    0x5a,
                    0x4d,
                    0x6f,
                    (byte) 0xdb,
                    0x70,
                    (byte) 0xe5,
                    0x38,
                    0x7e,
                    0x57,
                    0x65,
                    0x29,
                    0x3d,
                    (byte) 0xcb,
                    (byte) 0xa3,
                    (byte) 0x9c,
                    0x0c,
                    0x57,
                    0x32
                };
        SDFCryptoResult hashResult = SDF.Hash(null, AlgorithmType.SM3, Hex.toHexString(message));
        System.out.println("*********Hash*********");
        if (hashResult.getSdfErrorMessage() != null) {
            System.out.println(hashResult.getSdfErrorMessage());
        } else {
            System.out.println(hashResult.getHash());
            System.out.println(Hex.toHexString(stdResult));
        }

        System.out.println("*********KeyGen*********");
        SDFCryptoResult keGenResult = SDF.KeyGen(AlgorithmType.SM2);
        if (keGenResult.getSdfErrorMessage() != null) {
            System.out.println(keGenResult.getSdfErrorMessage());
        } else {
            System.out.println(keGenResult.getPrivateKey());
            System.out.println(keGenResult.getPublicKey());
        }

        System.out.println("*********Sign*********");
        SDFCryptoResult signResult =
                SDF.Sign(keGenResult.getPrivateKey(), AlgorithmType.SM2, hashResult.getHash());
        if (signResult.getSdfErrorMessage() != null) {
            System.out.println(signResult.getSdfErrorMessage());
        } else {
            System.out.println(signResult.getSignature());
        }

        System.out.println("*********Verify*********");
        SDFCryptoResult verifyResult =
                SDF.Verify(
                        keGenResult.getPublicKey(),
                        AlgorithmType.SM2,
                        hashResult.getHash(),
                        signResult.getSignature());
        if (verifyResult.getSdfErrorMessage() != null) {
            System.out.println(verifyResult.getSdfErrorMessage());
        } else {
            System.out.println(verifyResult.getResult());
        }

        System.out.println("*********SignWithInnerKey*********");
        SDFCryptoResult signInResult =
                SDF.SignWithInternalKey(1, "123456", AlgorithmType.SM2, hashResult.getHash());
        if (signInResult.getSdfErrorMessage() != null) {
            System.out.println(signInResult.getSdfErrorMessage());
        } else {
            System.out.println(signInResult.getSignature());
        }

        System.out.println("*********VerifyWithInnerKey*********");
        SDFCryptoResult verifyInResult =
                SDF.VerifyWithInternalKey(
                        1, AlgorithmType.SM2, hashResult.getHash(), signInResult.getSignature());
        if (verifyInResult.getSdfErrorMessage() != null) {
            System.out.println(verifyInResult.getSdfErrorMessage());
        } else {
            System.out.println(verifyInResult.getResult());
        }

        System.out.println("*********GetInternalPublicKey*********");
        SDFCryptoResult exportKeyResult = SDF.ExportInternalPublicKey(1, AlgorithmType.SM2);
        if (exportKeyResult.getSdfErrorMessage() != null) {
            System.out.println(exportKeyResult.getSdfErrorMessage());
        } else {
            System.out.println(exportKeyResult.getPublicKey());
        }
    }
}
