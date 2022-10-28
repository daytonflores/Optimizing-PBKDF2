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

