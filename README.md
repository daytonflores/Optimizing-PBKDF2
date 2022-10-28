# PES-Assignment-5
 Code for Assign 5 for PRES, ECEN 5813-001B, Fall 2022

# Time Analysis During time_pbkdf2_hmac_isha()

## Original

### ISHAReset()

- During time_pbkdf2_hmac_isha(), the function ISHAReset() is invoked from 3 separate lines:

| Count | Caller    | Invocation Details         | Average Time Per Invocation |
| ----- | --------- | -------------------------- | --------------------------- |
| 0     | hmac_isha | If key_len > ISHA_BLOCKLEN | 0 us                        |
| 13330 | hmac_isha | Inner ISHA                 | 1.84 us                     |
| 13330 | hmac_isha | Outer ISHA                 | 2.05 us                     |
