# PES-Assignment-5
 Code for Assign 5 for PRES, ECEN 5813-001B, Fall 2022

# Function Call Tree
<pre>
main()
 |
 *-----> time_pbkdf2_hmac_isha()
                   |
                   *-----> pbkdf2_hmac_isha()
                                 |
                                 *-----> F()
                                         | 
                                         *-----> hmac_isha()
                                                     |
                                                     *-----> ISHAReset()
                                                     |
                                                     *-----> ISHAInput()
                                                     |           |
                                                     |           *-----> ISHAProcessMessageBlock()
                                                     |
                                                     *-----> ISHAResult()
                                                                 |
                                                                 *-----> ISHAPadMessage()
                                                                               |
                                                                               *-----> ISHAProcessMessageBlock()
</pre>

# Entire Program
- Build Configuration            : Release
- Optimization                   : -O0
- Target                         : Program flash action using PEMicro probes
- Total Size Before Optimization : 19708
- Total Size After Optimization  : 
- Timing Test Before Optimization: 8752 ms
- Timing Test After Optimization : 5735 ms

# pbkdf2_hmac_isha()
- Size Before Optimization: 0x00000108
- Size After Optimization: 
- Changes:
	- None
- During time_pbkdf2_hmac_isha(), the function pbkdf2_hmac_isha() is invoked from 1 separate line:

| Count | Total Time Before Optimization (Deep : Surface) | Total Time After Optimization (Deep : Surface) | Caller                | Invocation Details         |
| ----- | ----------------------------------------------- | ---------------------------------------------- | --------------------- | -------------------------- |
| 1     | 8752 ms : 0 ms                                  | 8752 ms : 0 ms                                 | time_pbkdf2_hmac_isha | Unconditional              |

# F()
- Size Before Optimization: 0x000001b8
- Size After Optimization: 
- Changes:
	- Defined iterator i as register storage
	- Used same iterator i in all loops (other than loop using iterator j) rather than having each loop declare its own iterator i
- During time_pbkdf2_hmac_isha(), the function F() is invoked from 1 separate line:

| Count | Total Time Before Optimization (Deep : Surface) | Total Time After Optimization (Deep : Surface) | Caller                | Invocation Details         |
| ----- | ----------------------------------------------- | ---------------------------------------------- | --------------------- | -------------------------- |
| 3     | 8752 ms : 362 ms                                | 7261 ms : 137 ms                               | pbkdf2_hmac_isha      | For int i=0; i<l; i++      |

# hmac_isha()
- Size Before Optimization: 0x00000184
- Size After Optimization: 0x00000112
- Changes:
	- Removed if(key_len > ISHA_BLOCKLEN) conditional since code does not ever go into this branch. This introduces limitation of catching case where key_len > ISHA_BLOCKLEN
	- Combined for(i=0; i<key_len; i++) and for(i=key_len; i<ISHA_BLOCKLEN; i++) loops and added a conditional within loop itself
	- Combined both for(i=0; i<ISHA_BLOCKLEN; i++) loops
	- Removed keypad array and assigned directly to ipad + opad
	- Defined iterator i as register storage
- During time_pbkdf2_hmac_isha(), the function hmac_isha() is invoked from 2 separate lines:

| Count | Total Time Before Optimization (Deep : Surface) | Total Time After Optimization (Deep : Surface) | Caller                | Invocation Details         |
| ----- | ----------------------------------------------- | ---------------------------------------------- | --------------------- | -------------------------- |
| 3     | 2    ms : 0    ms                               | 1    ms : 0   ms                               | F                     | Unconditional              |
| 12285 | 8461 ms : 1428 ms                               | 7137 ms : 402 ms                               | F                     | For int j=1; j<iter; j++   |

# ISHAReset()
- Size Before Optimization: 0x00000060
- Size After Optimization: 
- Changes:
	- Removed ctx->corrupted flag
- During time_pbkdf2_hmac_isha(), the function ISHAReset() is invoked from 3 separate lines:

| Count | Total Time Before Optimization (Deep : Surface) | Total Time After Optimization (Deep : Surface) | Caller                | Invocation Details         |
| ----- | ----------------------------------------------- | ---------------------------------------------- | --------------------- | -------------------------- |
| 0     | 0  ms : 0  ms                                   | N/A                                            | hmac_isha             | If key_len > ISHA_BLOCKLEN |
| 12288 | 28 ms : 28 ms                                   | 28 ms : 28 ms                                  | hmac_isha             | Inner ISHA                 |
| 12288 | 28 ms : 28 ms                                   | 28 ms : 28 ms                                  | hmac_isha             | Outer ISHA                 |

# ISHAInput()
- Size Before Optimization: 0x000000ae
- Size After Optimization: 
- Changes:
	- Stored length into register iterator i and replaced all instances of length with iterator i
	- Removed ctx->corrupted flag
	- Incremented message_length in-line
- During time_pbkdf2_hmac_isha(), the function ISHAInput() is invoked from 5 separate lines:

| Count | Total Time Before Optimization (Deep : Surface) | Total Time After Optimization (Deep : Surface) | Caller                | Invocation Details         |
| ----- | ----------------------------------------------- | ---------------------------------------------- | --------------------- | -------------------------- |
| 0     | 0    ms : 0    ms                               | N/A                                            | hmac_isha             | If key_len > ISHA_BLOCKLEN |
| 12288 | 1996 ms : 1250 ms                               |  ms :  ms                              | hmac_isha             | Inner ISHA - ipad          |
| 12288 | 417  ms : 399  ms                               |   ms :   ms                              | hmac_isha             | Inner ISHA - msg           |
| 12288 | 2000 ms : 1249 ms                               |  ms :  ms                              | hmac_isha             | Outer ISHA - opad          |
| 12288 | 417  ms : 409  ms                               |   ms :   ms                              | hmac_isha             | Outer ISHA - inner_digest  |

# ISHAResult()
- Size Before Optimization: 0x000000c0
- Size After Optimization: 0x000000a0
- Changes:
	- Replaced all instances of (i/4) with (t >> 2)
	- Removed ctx->corrupted flag
- During time_pbkdf2_hmac_isha(), the function ISHAResult() is invoked from 3 separate lines:

| Count | Total Time Before Optimization (Deep : Surface) | Total Time After Optimization (Deep : Surface) | Caller                | Invocation Details         |
| ----- | ----------------------------------------------- | ---------------------------------------------- | --------------------- | -------------------------- |
| 0     | 0    ms : 0   ms                                | N/A                                            | hmac_isha             | If key_len > ISHA_BLOCKLEN |
| 12288 | 1089 ms : 148 ms                                | 745 ms : 125 ms                               | hmac_isha             | Inner ISHA                 |
| 12288 | 1089 ms : 148 ms                                | 745 ms : 125 ms                               | hmac_isha             | Outer ISHA                 |

# ISHAPadMessage()
- Size Before Optimization: 0x0000010e
- Size After Optimization: 0x000000f2
- Changes:
	- Removed while(ctx->MB_Idx < 56) loops out of if/else and put it after since it is unconditional
- During time_pbkdf2_hmac_isha(), the function ISHAPadMessage() is invoked from 1 separate line:

| Count | Total Time Before Optimization (Deep : Surface) | Total Time After Optimization (Deep : Surface) | Caller                | Invocation Details         |
| ----- | ----------------------------------------------- | ---------------------------------------------- | --------------------- | -------------------------- |
| 24576 | 1902 ms : 472 ms                                | 1794 ms : 494 ms                               | ISHAResult            | If !ctx->Computed          |

# ISHAProcessMessageBlock
- Size Before Optimization: 0x00000152
- Size After Optimization: 0x0000013e
- Changes:
	- Replaced all instances of (t * 4) with (t << 2)
	- Combined both for(t = 0; t < 16; t++) loops
	- Defined iterator t as register storage
	- Removed W array and assigned directly into temp. This may decrease readability but increases performance
- During time_pbkdf2_hmac_isha(), the function ISHAProcessMessageBlock() is invoked from 3 separate lines:

| Count | Total Time Before Optimization (Deep : Surface) | Total Time After Optimization (Deep : Surface) | Caller                | Invocation Details         |
| ----- | ----------------------------------------------- | ---------------------------------------------- | --------------------- | -------------------------- |
| 24576 | 1404 ms : 1404 ms                               | 853 ms : 853 ms                                | ISHAInput             | If ctx->MB_Idx == 64       |
| 0     | 0    ms : 0    ms                               | 0   ms : 0   ms                                | ISHAPadMessage        | If ctx->MB_Idx > 55        |
| 24576 | 1462 ms : 1462 ms                               | 851 ms : 851 ms                                | ISHAPadMessage        | Unconditional              |
