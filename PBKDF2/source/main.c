/*
 * PBKDF2_Optimization.c
 *
 * Application entry point, and test timing
 * 
 * Author: Howdy Pierce, howdy.pierce@colorado.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "pbkdf2.h"
#include "pbkdf2_test.h"
#include "ticktime.h"

volatile int Count_0 = 0;
volatile int Count_1 = 0;
volatile int Count_2 = 0;
volatile int Count_3 = 0;
volatile int Count_4 = 0;
volatile int Count_5 = 0;
volatile int Count_6 = 0;
volatile int Count_7 = 0;
volatile int Count_8 = 0;
volatile int Count_9 = 0;

volatile ticktime_t Duration_0 = 0;
volatile ticktime_t Duration_1 = 0;
volatile ticktime_t Duration_2 = 0;
volatile ticktime_t Duration_3 = 0;
volatile ticktime_t Duration_4 = 0;
volatile ticktime_t Duration_5 = 0;
volatile ticktime_t Duration_6 = 0;
volatile ticktime_t Duration_7 = 0;
volatile ticktime_t Duration_8 = 0;
volatile ticktime_t Duration_9 = 0;

/*
 * Times a single call to the pbkdf2_hmac_isha function, and prints
 * the resulting duration
 */
static void time_pbkdf2_hmac_isha()
{
  const char *pass = "Boulder";
  const char *salt = "Buffaloes";
  int iterations = 4096;
  size_t dk_len = 48;
  int passlen, saltlen;
  uint8_t act_result[512];
  uint8_t exp_result[512];
  const char *exp_result_hex = "7577B5FFB058195DE3978773B472E92D0216873EE1A2"\
    "170157C2054EDC41E58D7F949050253F8CE1D55E6B86E62AED3F";
    
  ticktime_t duration = 0;

  assert(dk_len <= sizeof(act_result));

  hexstr_to_bytes(exp_result, exp_result_hex, dk_len);passlen = strlen(pass);
  saltlen = strlen(salt);

  reset_timer();
  pbkdf2_hmac_isha((const uint8_t *)pass, passlen, (const uint8_t *)salt, saltlen,
      iterations, dk_len, act_result);
  duration = get_timer();

  if (cmp_bin(act_result, exp_result, dk_len)) {
    printf("%s: %u iterations took %u msec\r\n", __FUNCTION__,
        iterations, duration/10);
  } else {
    printf("FAILURE on timed test\r\n");
  }
}


/*
 * Run all the validity checks; exit on failure
 */
static void run_tests()
{
  bool success = true;

  success &= test_isha();
  success &= test_hmac_isha();
  success &= test_pbkdf2_hmac_isha();

  if (success)
    return;

  printf("TEST FAILURES EXIST ... exiting\r\n");

  exit(-1);
}


/*
 * Application entry point.
 */
int main(void) {

  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
  /* Init FSL debug console. */
  BOARD_InitDebugConsole();
#endif

  init_ticktime();

  printf("Running validity tests...\r\n");
  run_tests();
  printf("All tests passed!\r\n");

  printf("Running timing test...\r\n");
  time_pbkdf2_hmac_isha();

  printf("Count_0 = %d\r\n", Count_0);
  printf("Count_1 = %d\r\n", Count_1);
  printf("Count_2 = %d\r\n", Count_2);
  printf("Count_3 = %d\r\n", Count_3);
  printf("Count_4 = %d\r\n", Count_4);
  printf("Count_5 = %d\r\n", Count_5);
  printf("Count_6 = %d\r\n", Count_6);
  printf("Count_7 = %d\r\n", Count_7);
  printf("Count_8 = %d\r\n", Count_8);
  printf("Count_9 = %d\r\n", Count_9);

  printf("Duration_0 = %d\r\n", Duration_0);
  printf("Duration_1 = %d\r\n", Duration_1);
  printf("Duration_2 = %d\r\n", Duration_2);
  printf("Duration_3 = %d\r\n", Duration_3);
  printf("Duration_4 = %d\r\n", Duration_4);
  printf("Duration_5 = %d\r\n", Duration_5);
  printf("Duration_6 = %d\r\n", Duration_6);
  printf("Duration_7 = %d\r\n", Duration_7);
  printf("Duration_8 = %d\r\n", Duration_8);
  printf("Duration_9 = %d\r\n", Duration_9);

  return 0 ;
}
