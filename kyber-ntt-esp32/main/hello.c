
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "params.h"   
#include "ntt.h"      
#include "poly.h"     
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define PRINT_COEFFS 32  

static int16_t poly_a[KYBER_N];
static int16_t poly_b[KYBER_N];
static int16_t poly_res[KYBER_N];

// PRINT_COEFFS coef and checksum (sum mod q)
static void print_summary(const char *label, int16_t *p)
{
    unsigned long sum = 0;
    printf("%s (first %d coeffs):\n", label, PRINT_COEFFS);
    for (int i = 0; i < PRINT_COEFFS; i++) {
        printf("%6d ", p[i]);
        if ((i + 1) % 8 == 0) printf("\n");
    }
    if (PRINT_COEFFS % 8) printf("\n");
    for (int i = 0; i < KYBER_N; i++) {
        int v = p[i] % KYBER_Q;
        if (v < 0) v += KYBER_Q;
        sum += (unsigned long)v;
    }
    printf("%s checksum (sum of all coeffs mod %d) = %lu\n\n", 
           label, KYBER_Q, sum % KYBER_Q);
}

void app_main(void)
{
    printf("\n=== kyber NTT/INTT test esp32 ===\n");

    for (int i = 0; i < KYBER_N; i++) {
        poly_a[i] = (int16_t)((i * 17 + 3) % KYBER_Q);
        poly_b[i] = (int16_t)((i * 29 + 5) % KYBER_Q);
        poly_res[i] = 0;
    }

    print_summary("A (time domain, before NTT)", poly_a);
    print_summary("B (time domain, before NTT)", poly_b);

    printf("Applying NTT to A and B\n");
    ntt(poly_a);
    ntt(poly_b);

    print_summary("A (NTT domain)", poly_a);
    print_summary("B (NTT domain)", poly_b);

    printf("Pointwise multiplication in NTT domain...\n");
    for (int i = 0; i < KYBER_N / 2; i++) {
        basemul(&poly_res[2*i], &poly_a[2*i], &poly_b[2*i], zetas[i]);
    }

    print_summary("Res (NTT domain, after basemul)", poly_res);

    printf("Applying inverse NTT (INTT)\n");
    invntt(poly_res);

    print_summary("Res (time domain, product)", poly_res);

    printf("=== end NTT test ===\n\n");

    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

