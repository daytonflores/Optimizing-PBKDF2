# PES-Assignment-5
 Code for Assign 5 for PRES, ECEN 5813-001B, Fall 2022

# pbkdf2_hmac_isha()

## Original
- Size: 0x00000128
- During time_pbkdf2_hmac_isha(), the function pbkdf2_hmac_isha() is invoked from 1 separate line:

| Count | Total Time | Average Time Per Invocation | Caller                | Invocation Details |
| ----- | ---------- | --------------------------- | --------------------- | ------------------ |
| 1     | 8742.0 ms  | 8742.000 ms                 | time_pbkdf2_hmac_isha | Unconditional      |

## Modified
- Size: 0x00000128
- During time_pbkdf2_hmac_isha(), the function pbkdf2_hmac_isha() is invoked from 1 separate line:

| Count | Total Time | Average Time Per Invocation | Caller                | Invocation Details |
| ----- | ---------- | --------------------------- | --------------------- | ------------------ |
| 1     | 8495.0 ms  | 8495.000 ms                 | time_pbkdf2_hmac_isha | Unconditional      |

# F()

## Original
- Size: 0x000001d0
- During time_pbkdf2_hmac_isha(), the function F() is invoked from 1 separate line:

| Count | Total Time | Average Time Per Invocation | Caller           | Invocation Details       |
| ----- | ---------- | --------------------------- | ---------------- | ------------------------ |
| 42    | 9482.0 ms  | 225.762 ms                  | pbkdf2_hmac_isha | For int i=0; i<l; i++    |

## Modified


# hmac_isha()

## Original
- Size: 0x00000184
- During time_pbkdf2_hmac_isha(), the function hmac_isha() is invoked from 2 separate lines:

| Count | Total Time | Average Time Per Invocation | Caller         | Invocation Details       |
| ----- | ---------- | --------------------------- | -------------- | ------------------------ |
| 42    | 28.1 ms    | 0.669 ms                    | F              | Unconditional            |
| 13285 | 9124.9 ms  | 0.687 ms                    | F              | For int j=1; j<iter; j++ |

## Modified


# ISHAReset()

## Original
- Size: 0x00000060
- During time_pbkdf2_hmac_isha(), the function ISHAReset() is invoked from 3 separate lines:

| Count | Total Time | Average Time Per Invocation | Caller    | Invocation Details         |
| ----- | ---------- | --------------------------- | --------- | -------------------------- |
| 0     | 0.0 ms     | 0.000 ms                    | hmac_isha | If key_len > ISHA_BLOCKLEN |
| 13330 | 24.8 ms    | 0.002 ms                    | hmac_isha | Inner ISHA                 |
| 13330 | 27.1 ms    | 0.002 ms                    | hmac_isha | Outer ISHA                 |

## Modified


# ISHAInput()

## Original
- Size: 0x000000ae
- During time_pbkdf2_hmac_isha(), the function ISHAInput() is invoked from 5 separate lines:

| Count | Total Time | Average Time Per Invocation | Caller    | Invocation Details         |
| ----- | ---------- | --------------------------- | --------- | -------------------------- |
| 0     | 0.0 ms     | 0.000 ms                    | hmac_isha | If key_len > ISHA_BLOCKLEN |
| 13330 | 2171.9 ms  | 0.163 ms                    | hmac_isha | Inner ISHA - ipad          |
| 13330 | 444.8 ms   | 0.033 ms                    | hmac_isha | Inner ISHA - msg           |
| 13330 | 2171.7 ms  | 0.163 ms                    | hmac_isha | Outer ISHA - opad          |
| 13330 | 444.6 ms   | 0.033 ms                    | hmac_isha | Outer ISHA - inner_digest  |

## Modified


# ISHAResult()

## Original
- Size: 0x000000c0
- During time_pbkdf2_hmac_isha(), the function ISHAResult() is invoked from 3 separate lines:

| Count | Total Time | Average Time Per Invocation | Caller    | Invocation Details         |
| ----- | ---------- | --------------------------- | --------- | -------------------------- |
| 0     | 0.0 ms     | 0.000 ms                    | hmac_isha | If key_len > ISHA_BLOCKLEN |
| 13330 | 1183.9 ms  | 0.089 ms                    | hmac_isha | Inner ISHA                 |
| 13330 | 1183.6 ms  | 0.089 ms                    | hmac_isha | Outer ISHA                 |

## Modified
- Size: 0x000000a0
- Changes made:
	- Replaced all instances of (i/4) with (t >> 2)
- During time_pbkdf2_hmac_isha(), the function ISHAResult() is invoked from 3 separate lines:

| Count | Total Time | Average Time Per Invocation | Caller    | Invocation Details         |
| ----- | ---------- | --------------------------- | --------- | -------------------------- |
| 0     | 0.0 ms     | 0.000 ms                    | hmac_isha | If key_len > ISHA_BLOCKLEN |
| 13330 | 1099.0 ms  | 0.082 ms                    | hmac_isha | Inner ISHA                 |
| 13330 | 1106.3 ms  | 0.083 ms                    | hmac_isha | Outer ISHA                 |

# ISHAPadMessage()

## Original
- Size: 0x0000010e
- During time_pbkdf2_hmac_isha(), the function ISHAPadMessage() is invoked from 1 separate line:

| Count | Total Time | Average Time Per Invocation | Caller     | Invocation Details |
| ----- | ---------- | --------------------------- | ---------- | ------------------ |
| 26668 | 2066.9 ms  | 0.078 ms                    | ISHAResult | If !ctx->Computed  |

## Modified
- Size: 0x000000f2
- Changes made:
	- Removed while(ctx->MB_Idx < 56) loops out of if/else and put it after since it is unconditional
- During time_pbkdf2_hmac_isha(), the function ISHAPadMessage() is invoked from 1 separate line:

| Count | Total Time | Average Time Per Invocation | Caller     | Invocation Details |
| ----- | ---------- | --------------------------- | ---------- | ------------------ |
| 26668 | 2066.9 ms  | 0.078 ms                    | ISHAResult | If !ctx->Computed  |

# ISHAProcessMessageBlock()

## Original
- Size: 0x00000152
- During time_pbkdf2_hmac_isha(), the function ISHAProcessMessageBlock() is invoked from 3 separate lines:

| Count | Total Time | Average Time Per Invocation | Caller         | Invocation Details   |
| ----- | ---------- | --------------------------- | -------------- | -------------------- |
| 26666 | 1574.6 ms  | 0.059 ms                    | ISHAInput      | If ctx->MB_Idx == 64 |
| 2     | 2.0 ms     | 1.000 ms                    | ISHAPadMessage | If ctx->MB_Idx > 55  |
| 26668 | 1536.5 ms  | 0.058 ms                    | ISHAPadMessage | Unconditional        |

## Modified
- Size: 0x0000013e
- Changes made:
	- Replaced all instances of (t * 4) with (t << 2)
	- Combined both for(t = 0; t < 16; t++) loops
- During time_pbkdf2_hmac_isha(), the function ISHAProcessMessageBlock() is invoked from 3 separate lines:

| Count | Total Time | Average Time Per Invocation | Caller         | Invocation Details   |
| ----- | ---------- | --------------------------- | -------------- | -------------------- |
| 26666 | 1443.9 ms  | 0.054 ms                    | ISHAInput      | If ctx->MB_Idx == 64 |
| 2     | 1.0 ms     | 0.500 ms                    | ISHAPadMessage | If ctx->MB_Idx > 55  |
| 26668 | 1445.0 ms  | 0.054 ms                    | ISHAPadMessage | Unconditional        |
