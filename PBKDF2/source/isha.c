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

#include <string.h>

#include "isha.h"
#include "ticktime.h"

/*
 * circular shift macro
 */
#define ISHACircularShift(bits,word) \
  ((((word) << (bits)) & 0xFFFFFFFF) | ((word) >> (32-(bits))))

#define MAX_MESSAGE_BLOCK_BYTES (64)

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
  register int t;
  uint32_t A, B, C, D, E;

  A = ctx->MD[0];
  B = ctx->MD[1];
  C = ctx->MD[2];
  D = ctx->MD[3];
  E = ctx->MD[4];

  for(t = 0; t < 16; t++)
  {

    temp = ISHACircularShift(5,A) + ((B & C) | ((~B) & D)) + E +
    		(((uint32_t) ctx->MBlock[(t << 2)]) << 24
            | ((uint32_t) ctx->MBlock[(t << 2) + 1]) << 16
            | ((uint32_t) ctx->MBlock[(t << 2) + 2]) << 8
            | ((uint32_t) ctx->MBlock[(t << 2) + 3]));

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

  ctx->MBlock[56] = 0;
  ctx->MBlock[57] = 0;
  ctx->MBlock[58] = 0;
  ctx->MBlock[59] = 0;
  ctx->MBlock[60] = ((ctx->Length_Bytes << 3) >> 24) & 0xFF;
  ctx->MBlock[61] = ((ctx->Length_Bytes << 3) >> 16) & 0xFF;
  ctx->MBlock[62] = ((ctx->Length_Bytes << 3) >> 8) & 0xFF;
  ctx->MBlock[63] = ((ctx->Length_Bytes << 3)) & 0xFF;

  ISHAProcessMessageBlock(ctx);
}


void ISHAReset(ISHAContext *ctx)
{
  ctx->Length_Bytes = 0;
  ctx->MB_Idx      = 0;

  ctx->MD[0]       = 0x67452301;
  ctx->MD[1]       = 0xEFCDAB89;
  ctx->MD[2]       = 0x98BADCFE;
  ctx->MD[3]       = 0x10325476;
  ctx->MD[4]       = 0xC3D2E1F0;

  ctx->Computed    = 0;
}


void ISHAResult(ISHAContext *ctx, uint8_t *digest_out)
{
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
  register size_t i = length;

  if (!i)
  {
    return;
  }

  if (ctx->Computed)
  {
    return;
  }

  /*
   *  If pending block to be copied overflows past 64 bytes, copy the pending block
   *  and then process the message block
   */
  while(ctx->MB_Idx + i > MAX_MESSAGE_BLOCK_BYTES)
  {
	memcpy(ctx->MBlock + ctx->MB_Idx, message_array, MAX_MESSAGE_BLOCK_BYTES - ctx->MB_Idx);
	i -= MAX_MESSAGE_BLOCK_BYTES - ctx->MB_Idx;
	message_array += MAX_MESSAGE_BLOCK_BYTES - ctx->MB_Idx;
	ctx->Length_Bytes += MAX_MESSAGE_BLOCK_BYTES - ctx->MB_Idx;
	ctx->MB_Idx = MAX_MESSAGE_BLOCK_BYTES - ctx->MB_Idx;
	ISHAProcessMessageBlock(ctx);
  }

  /*
   *  If pending block after all multiples of 64-byte sized blocks have
   *  been copied, memcpy the remaining message bytes
   */
  if(i > 0)
  {
	memcpy(ctx->MBlock + ctx->MB_Idx, message_array, i);
	ctx->MB_Idx += i;
	message_array += i;
	ctx->Length_Bytes += i;
	i = 0;
  }
}


