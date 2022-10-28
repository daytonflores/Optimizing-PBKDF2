# PES-Assignment-5
 Code for Assign 5 for PRES, ECEN 5813-001B, Fall 2022

# Time Analysis During time_pbkdf2_hmac_isha()

## Original

### pbkdf2_hmac_isha()

- During time_pbkdf2_hmac_isha(), the function pbkdf2_hmac_isha() is invoked from 1 separate line:

| Count | Total Time | Average Time Per Invocation | Caller                | Invocation Details |
| ----- | ---------- | --------------------------- | --------------------- | ------------------ |
| 1     | 8742.0 ms  | 8742.000 ms                 | time_pbkdf2_hmac_isha | Unconditional      |

### F()

- During time_pbkdf2_hmac_isha(), the function F() is invoked from 1 separate line:

| Count | Total Time | Average Time Per Invocation | Caller           | Invocation Details       |
| ----- | ---------- | --------------------------- | ---------------- | ------------------------ |
| 42    | 9482.0 ms  | 225.762 ms                  | pbkdf2_hmac_isha | For int i=0; i<l; i++    |

### hmac_isha()

- During time_pbkdf2_hmac_isha(), the function hmac_isha() is invoked from 2 separate lines:

| Count | Total Time | Average Time Per Invocation | Caller         | Invocation Details       |
| ----- | ---------- | --------------------------- | -------------- | ------------------------ |
| 42    | 28.1 ms    | 0.669 ms                    | F              | Unconditional            |
| 13285 | 9124.9 ms  | 0.687 ms                    | F              | For int j=1; j<iter; j++ |

### ISHAReset()

- During time_pbkdf2_hmac_isha(), the function ISHAReset() is invoked from 3 separate lines:

| Count | Total Time | Average Time Per Invocation | Caller    | Invocation Details         |
| ----- | ---------- | --------------------------- | --------- | -------------------------- |
| 0     | 0.0 ms     | 0.000 ms                    | hmac_isha | If key_len > ISHA_BLOCKLEN |
| 13330 | 24.8 ms    | 0.002 ms                    | hmac_isha | Inner ISHA                 |
| 13330 | 27.1 ms    | 0.002 ms                    | hmac_isha | Outer ISHA                 |

### ISHAInput()

- During time_pbkdf2_hmac_isha(), the function ISHAInput() is invoked from 5 separate lines:

| Count | Total Time | Average Time Per Invocation | Caller    | Invocation Details         |
| ----- | ---------- | --------------------------- | --------- | -------------------------- |
| 0     | 0.0 ms     | 0.000 ms                    | hmac_isha | If key_len > ISHA_BLOCKLEN |
| 13330 | 2171.9 ms  | 0.163 ms                    | hmac_isha | Inner ISHA - ipad          |
| 13330 | 444.8 ms   | 0.033 ms                    | hmac_isha | Inner ISHA - msg           |
| 13330 | 2171.7 ms  | 0.163 ms                    | hmac_isha | Outer ISHA - opad          |
| 13330 | 444.6 ms   | 0.033 ms                    | hmac_isha | Outer ISHA - inner_digest  |

### ISHAResult()

- During time_pbkdf2_hmac_isha(), the function ISHAResult() is invoked from 3 separate lines:

| Count | Total Time | Average Time Per Invocation | Caller    | Invocation Details         |
| ----- | ---------- | --------------------------- | --------- | -------------------------- |
| 0     | 0.0 ms     | 0.000 ms                    | hmac_isha | If key_len > ISHA_BLOCKLEN |
| 13330 | 1183.9 ms  | 0.089 ms                    | hmac_isha | Inner ISHA                 |
| 13330 | 1183.6 ms  | 0.089 ms                    | hmac_isha | Outer ISHA                 |

### ISHAPadMessage()

- During time_pbkdf2_hmac_isha(), the function ISHAPadMessage() is invoked from 1 separate line:

| Count | Total Time | Average Time Per Invocation | Caller     | Invocation Details |
| ----- | ---------- | --------------------------- | ---------- | ------------------ |
| 26668 | 2066.9 ms  | 0.078 ms                    | ISHAResult | If !ctx->Computed  |

### ISHAProcessMessageBlock()

- During time_pbkdf2_hmac_isha(), the function ISHAProcessMessageBlock() is invoked from 3 separate lines:

| Count | Total Time | Average Time Per Invocation | Caller         | Invocation Details   |
| ----- | ---------- | --------------------------- | -------------- | -------------------- |
| 26666 | 1574.6 ms  | 0.059 ms                    | ISHAInput      | If ctx->MB_Idx == 64 |
| 2     | 2.0 ms     | 1.000 ms                    | ISHAPadMessage | If ctx->MB_Idx > 55  |
| 26668 | 1536.5 ms  | 0.058 ms                    | ISHAPadMessage | Unconditional        |
