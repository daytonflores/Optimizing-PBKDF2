/*
 * isha.c
 *
 * A completely insecure and bad hashing algorithm, based loosely on
 * SHA-1 (which is itself no longer considered a good hashing
 * algorithm)
 *
 * Based on code for sha1 processing from Paul E. Jones, available at
 * https://www.packetizer.com/security/sha1/
 */

#include "isha.h"
#include "ticktime.h"

/*
 * circular shift macro
 */
#define ISHACircularShift(bits,word) \
  ((((word) << (bits)) & 0xFFFFFFFF) | ((word) >> (32-(bits))))

extern volatile int Count_0;
extern volatile int Count_1;
extern volatile int Count_2;
extern volatile int Count_3;
extern volatile int Count_4;
extern volatile int Count_5;
extern volatile int Count_6;
extern volatile int Count_7;
extern volatile int Count_8;
extern volatile int Count_9;

extern volatile ticktime_t Duration_0;
extern volatile ticktime_t Duration_1;
extern volatile ticktime_t Duration_2;
extern volatile ticktime_t Duration_3;
extern volatile ticktime_t Duration_4;
extern volatile ticktime_t Duration_5;
extern volatile ticktime_t Duration_6;
extern volatile ticktime_t Duration_7;
extern volatile ticktime_t Duration_8;
extern volatile ticktime_t Duration_9;

/*  
 * Processes the next 512 bits of the message stored in the MBlock
 * array.
 *
 * Parameters:
 *   ctx         The ISHAContext (in/out)
 */
static void ISHAProcessMessageBlock(ISHAContext *ctx)
{
  uint32_t temp; 
  int t;
  uint32_t W[16];
  uint32_t A, B, C, D, E;

  A = ctx->MD[0];
  B = ctx->MD[1];
  C = ctx->MD[2];
  D = ctx->MD[3];
  E = ctx->MD[4];

  for(t = 0; t < 16; t++)
  {
    W[t] = ((uint32_t) ctx->MBlock[(t << 2)]) << 24;
    W[t] |= ((uint32_t) ctx->MBlock[(t << 2) + 1]) << 16;
    W[t] |= ((uint32_t) ctx->MBlock[(t << 2) + 2]) << 8;
    W[t] |= ((uint32_t) ctx->MBlock[(t << 2) + 3]);

    temp = ISHACircularShift(5,A) + ((B & C) | ((~B) & D)) + E + W[t];
    temp &= 0xFFFFFFFF;
    E = D;
    D = C;
    C = ISHACircularShift(30,B);
    B = A;
    A = temp;
  }

  ctx->MD[0] = (ctx->MD[0] + A) & 0xFFFFFFFF;
  ctx->MD[1] = (ctx->MD[1] + B) & 0xFFFFFFFF;
  ctx->MD[2] = (ctx->MD[2] + C) & 0xFFFFFFFF;
  ctx->MD[3] = (ctx->MD[3] + D) & 0xFFFFFFFF;
  ctx->MD[4] = (ctx->MD[4] + E) & 0xFFFFFFFF;

  ctx->MB_Idx = 0;
}


/*  
 * The message must be padded to an even 512 bits.  The first padding
 * bit must be a '1'.  The last 64 bits represent the length of the
 * original message.  All bits in between should be 0. This function
 * will pad the message according to those rules by filling the MBlock
 * array accordingly. It will also call ISHAProcessMessageBlock()
 * appropriately. When it returns, it can be assumed that the message
 * digest has been computed.
 *
 * Parameters:
 *   ctx         The ISHAContext (in/out)
 */
static void ISHAPadMessage(ISHAContext *ctx)
{
  /*
   *  Check to see if the current message block is too small to hold
   *  the initial padding bits and length.  If so, we will pad the
   *  block, process it, and then continue padding into a second
   *  block.
   */
  if (ctx->MB_Idx > 55)
  {
    ctx->MBlock[ctx->MB_Idx++] = 0x80;
    while(ctx->MB_Idx < 64)
    {
      ctx->MBlock[ctx->MB_Idx++] = 0;
    }

    ISHAProcessMessageBlock(ctx);
  }
  else
  {
    ctx->MBlock[ctx->MB_Idx++] = 0x80;

  }

  while(ctx->MB_Idx < 56)
  {
    ctx->MBlock[ctx->MB_Idx++] = 0;
  }
  /*
   *  Store the message length as the last 8 octets
   */
  ctx->MBlock[56] = (ctx->Length_High >> 24) & 0xFF;
  ctx->MBlock[57] = (ctx->Length_High >> 16) & 0xFF;
  ctx->MBlock[58] = (ctx->Length_High >> 8) & 0xFF;
  ctx->MBlock[59] = (ctx->Length_High) & 0xFF;
  ctx->MBlock[60] = (ctx->Length_Low >> 24) & 0xFF;
  ctx->MBlock[61] = (ctx->Length_Low >> 16) & 0xFF;
  ctx->MBlock[62] = (ctx->Length_Low >> 8) & 0xFF;
  ctx->MBlock[63] = (ctx->Length_Low) & 0xFF;

  ISHAProcessMessageBlock(ctx);
}


void ISHAReset(ISHAContext *ctx)
{
  ctx->Length_Low  = 0;
  ctx->Length_High = 0;
  ctx->MB_Idx      = 0;

  ctx->MD[0]       = 0x67452301;
  ctx->MD[1]       = 0xEFCDAB89;
  ctx->MD[2]       = 0x98BADCFE;
  ctx->MD[3]       = 0x10325476;
  ctx->MD[4]       = 0xC3D2E1F0;

  ctx->Computed    = 0;
  ctx->Corrupted   = 0;
}


void ISHAResult(ISHAContext *ctx, uint8_t *digest_out)
{
  if (ctx->Corrupted)
  {
    return;
  }

  if (!ctx->Computed)
  {
    ISHAPadMessage(ctx);
    ctx->Computed = 1;
  }

  for (int i=0; i<20; i+=4) {
    digest_out[i]   = (ctx->MD[i >> 2] & 0xff000000) >> 24;
    digest_out[i+1] = (ctx->MD[i >> 2] & 0x00ff0000) >> 16;
    digest_out[i+2] = (ctx->MD[i >> 2] & 0x0000ff00) >> 8;
    digest_out[i+3] = (ctx->MD[i >> 2] & 0x000000ff);
  }

  return;
}


void ISHAInput(ISHAContext *ctx, const uint8_t *message_array, size_t length)
{
  if (!length)
  {
    return;
  }

  if (ctx->Computed || ctx->Corrupted)
  {
    ctx->Corrupted = 1;
    return;
  }

  while(length-- && !ctx->Corrupted)
  {
    ctx->MBlock[ctx->MB_Idx++] = (*message_array & 0xFF);

    ctx->Length_Low += 8;
    /* Force it to 32 bits */
    ctx->Length_Low &= 0xFFFFFFFF;
    if (ctx->Length_Low == 0)
    {
      ctx->Length_High++;
      /* Force it to 32 bits */
      ctx->Length_High &= 0xFFFFFFFF;
      if (ctx->Length_High == 0)
      {
        /* Message is too long */
        ctx->Corrupted = 1;
      }
    }

    if (ctx->MB_Idx == 64)
    {
      ISHAProcessMessageBlock(ctx);
    }

    message_array++;
  }
}


