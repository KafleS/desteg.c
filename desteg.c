/* Name : Suman Kafle
CS 241
lab 9 desteg.c*/

#include <stdio.h>
#include <stdlib.h>

/**********************************************************************/
/* Take the array of the bytes
   function to save the 2 bits from each of the bytes of their last 2 bitsinto the int*/
/**********************************************************************/
int modifier(unsigned char bytes[])
{
  int n = 0;
  n |= bytes[0] & 0x03;
  n |= (bytes[1] & 0x03) << 2;
  n |= (bytes[2] & 0x03) << 4;
  n |= (bytes[3] & 0x03) << 6;
  return n;
}

/**********************************************************************/
/* Take 4 bytes from an unsigned char array and assemble them into an */
/* int where the first element of the array is the least significant  */
/* byte of the int.                                                   */
/**********************************************************************/
int getIntFromArray(unsigned char bytes[])
{
    int n =
          bytes[0] |
          bytes[1] << 8 |
          bytes[2] << 16 |
      bytes[3] << 24;
    return n;
}

/* Copy a bitmap file without red */
int main(int argc, char** argv)
{
  char* infilename = argv[1];
  unsigned char header[54];
  FILE* in = fopen(infilename, "rb");
  int pixelDataSize;
  int output;
  int i;

  /* read header into array */
  fread(header, 1, 54, in);

  /* is this really a bitmap? */
  if(header[0] != 'B' || header[1] != 'M')
    {
      printf("Input file is not a bitmap\n");
    }

  /* Is the header size what we expect? */
  if(getIntFromArray(&header[10]) != 54)
    {
      printf("Unexpected header size\n");
    }

  /* How many bits per pixel? Expecting 24*/
  if(!(header[28] == 24 && header[29] == 0))
    {
      printf("Unexpected number of bits/pixel\n");
    }

  pixelDataSize = getIntFromArray(&header[34]);

  /* Read RGB data from original */
  for(i = 0; i < pixelDataSize/4; ++i)
    {
      unsigned char bytes[4];

      /* color order is BGR */
      fread(bytes, 1, 4, in);

      output = modifier(bytes);

      /* if the output is not equal to zero the outvalue value is printed */
      if(output != 0)
	{
	  printf("%c", output);
	}

      /* break the loop*/
      else
	{
	  break;
	}
    }

  fclose(in);
  return 0;
}
