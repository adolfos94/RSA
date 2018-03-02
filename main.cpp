//
//  main.cpp
//  RSA
//
//  Created by Adolfo Solís on 2/28/18.
//  Copyright © 2018 Adolfo Solís. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <gmp.h>
#include <gmpxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, const char * argv[]) {
    
    //Keysize
    mp_bitcnt_t keysize = 4096;
    
    // Padding
    //(keysize / 8) - 11 = 245 bytes
    
    // Seed Timer - Random
    clock_t timer;
    timer = clock();
    
    // Creando Variables
    mpz_t p, q, n, t, e, d, ec, dc;
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_init(t);
    mpz_init(e);
    mpz_init(d);
    mpz_init(ec);
    mpz_init(dc);
    
    // Valores aleatorios para P y Q
    gmp_randstate_t randState;
    gmp_randinit_mt(randState);
    gmp_randseed_ui(randState, timer);
    mpz_urandomb(p,randState,keysize);
    mpz_urandomb(q,randState,keysize);
    
    
    // Primos P y Q
    mpz_nextprime(p,p);
    mpz_nextprime(q,q);
    
    // n = P * Q
    mpz_mul(n,p,q);
    
    // t = lcm(p-1,q-1)
    mpz_sub_ui(p,p,1);
    mpz_sub_ui(q,q,1);
    mpz_lcm(t,p,q);
    
    // e
    unsigned long _e = 786433;
    while(mpz_gcd_ui(NULL, t, _e) != 1){
        _e += 2;
    }
    mpz_set_si(e, _e);
    
    
    // modinv d
    mpz_invert(d,e,t);
    
    // Mensaje
    const char *plaintext = "ADOLFO";
    mpz_import(dc, strlen(plaintext), 1, 1, 0, 0, plaintext);
    
    gmp_printf("Mensaje: %s\n", plaintext);
    std::cout << "Length: " << strlen(plaintext) << std::endl;
    
    // Encryption
    mpz_powm(ec, dc, e, n);
    gmp_printf("Encoded:   %Zd\n", ec);
    
    // Decryption
    
    mpz_powm(dc, ec, d, n);
    gmp_printf("Decoded:   %Zd\n", dc);
    
    // Mensaje Decodificado
    char buffer[strlen(plaintext)];
    mpz_export(buffer, NULL, 1, 1, 0, 0, dc);
    std::cout << "Mensaje Decodificado: " << buffer;
    
    std::cout << "\n";
    return 0;
}
