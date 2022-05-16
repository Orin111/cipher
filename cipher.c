#include "cipher.h"

#define ABC 26 //number of letters in the ABC
/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.


// See full documentation in header file
void encode (char s[], int k)
{
  for (int i = 0; s[i] != '\0'; ++i)
    {
      char ch_start = 'a';
      if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
        {
          if (s[i] <= 'Z')
            {
              ch_start = 'A';
            }
          s[i] = (char) (((s[i] - ch_start + k) % ABC + ABC) % ABC + ch_start);

        }

    }
}

// See full documentation in header file
void decode (char s[], int k)
{
  encode (s, -k);
}