# PES-Assignment-5
 Code for Assign 5 for PRES, ECEN 5813-001B, Fall 2022

# Time Analysis During time_pbkdf2_hmac_isha()

## Original

### ISHAReset()

- During time_pbkdf2_hmac_isha(), the function ISHAReset() is invoked from 3 separate lines:

| Count | Caller    | Invocation Details         | Average Time Per Invocation |
| ----- | --------- | -------------------------- | --------------------------- |
| 0     | hmac_isha | If key_len > ISHA_BLOCKLEN | 0.00 us                     |
| 13330 | hmac_isha | Inner ISHA                 | 1.84 us                     |
| 13330 | hmac_isha | Outer ISHA                 | 2.05 us                     |

### ISHAInput()

- During time_pbkdf2_hmac_isha(), the function ISHAInput() is invoked from 5 separate lines:

| Count | Caller    | Invocation Details         | Average Time Per Invocation |
| ----- | --------- | -------------------------- | --------------------------- |
| 0     | hmac_isha | If key_len > ISHA_BLOCKLEN | 0.00 us                     |
| 13330 | hmac_isha | Inner ISHA - ipad          | 16.29 us                    |
| 13330 | hmac_isha | Inner ISHA - msg           | 3.33 us                     |
| 13330 | hmac_isha | Outer ISHA - opad          | 16.29 us                    |
| 13330 | hmac_isha | Outer ISHA - inner_digest  | 3.33 us                     |

### ISHAResult()

- During time_pbkdf2_hmac_isha(), the function ISHAResult() is invoked from 3 separate lines:

| Count | Caller    | Invocation Details         | Average Time Per Invocation |
| ----- | --------- | -------------------------- | --------------------------- |
| 0     | hmac_isha | If key_len > ISHA_BLOCKLEN | 0.00 us                     |
| 13330 | hmac_isha | Inner ISHA                 | 8.88 us                     |
| 13330 | hmac_isha | Outer ISHA                 | 8.88 us                     |

### ISHAPadMessage()

- During time_pbkdf2_hmac_isha(), the function ISHAPadMessage() is invoked from 1 separate line:

| Count | Caller     | Invocation Details | Average Time Per Invocation |
| ----- | ---------- | ------------------ | --------------------------- |
| 26668 | ISHAResult | If !ctx->Computed  | 7.75 us                     |

### ISHAProcessMessageBlock()

- During time_pbkdf2_hmac_isha(), the function ISHAProcessMessageBlock() is invoked from 3 separate lines:

| Count | Caller         | Invocation Details   | Average Time Per Invocation |
| ----- | -------------- | -------------------- | --------------------------- |
| 26666 | ISHAInput      | If ctx->MB_Idx == 64 | 5.89 us                     |
| 2     | ISHAPadMessage | If ctx->MB_Idx > 55  | 1.00 us                     |
| 26666 | ISHAPadMessage | Unconditional        | 5.77 us                     |

### hmac_isha()

- During time_pbkdf2_hmac_isha(), the function hmac_isha() is invoked from 2 separate lines:

| Count | Caller         | Invocation Details       | Average Time Per Invocation |
| ----- | -------------- | ------------------------ | --------------------------- |
| 42    | F              | Unconditional            | 66.9 us                     |
| 13285 | F              | For int j=1; j<iter; j++ | 68.7 us                     |

### F()

- During time_pbkdf2_hmac_isha(), the function F() is invoked from 1 separate line:

| Count | Caller           | Invocation Details       | Average Time Per Invocation |
| ----- | ---------------- | ------------------------ | --------------------------- |
| 42    | pbkdf2_hmac_isha | For int i=0; i<l; i++    | 22575.95 us                 |

### pbkdf2_hmac_isha()

- During time_pbkdf2_hmac_isha(), the function pbkdf2_hmac_isha() is invoked from 1 separate line:

| Count | Caller                | Invocation Details | Average Time Per Invocation |
| ----- | --------------------- | ------------------ | --------------------------- |
| 1     | time_pbkdf2_hmac_isha | Unconditional      | 8742000 us                  |
