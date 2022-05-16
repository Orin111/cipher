#include <string.h>
#include "tests.h"
#include "cipher.h"

#define K_1 3
#define K_2 2
#define K_3 -1
#define K_4 -3
#define K_5 29

// See full documentation in header file
int test_encode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  encode (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_special_char_positive_k ()
{
    char in[] = "it`s a zebra!";
    char out[] = "kv`u c bgdtc!";
    encode (in, K_2);
    return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_non_cyclic_lower_case_special_char_negative_k ()
{
    char in[] = "hi, you!";
    char out[] = "gh, xnt!";
    encode (in, K_3);
    return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_negative_k ()
{
    char in[] = "daniel is stupid";
    char out[] = "axkfbi fp pqrmfa";
    encode (in, K_4);
    return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_upper_case_positive_k ()
{
    char in[] = "FIX THE CODE";
    char out[] = "ILA WKH FRGH";
    encode (in, K_5);
    return strcmp (in, out) != 0;
}






// See full documentation in header file
int test_decode_non_cyclic_lower_case_positive_k ()
{
    char in[] = "huuru";
    char out[] = "error";
    decode (in, K_1);
    return strcmp (in, out) != 0;
}


// See full documentation in header file
int test_decode_cyclic_lower_case_special_char_positive_k ()
{
    char in[] = "bgdtc ku jgtg!";
  char out[] = "zebra is here!";
    decode (in, K_2);
    return strcmp (in, out) != 0;
}


// See full documentation in header file
int test_decode_non_cyclic_lower_case_special_char_negative_k ()
{
    char in[] = "lntrd*";
    char out[] = "mouse*";
    decode (in, K_3);
    return strcmp (in, out) != 0;
}



// See full documentation in header file
int test_decode_cyclic_lower_case_negative_k ()
{
    char in[] = "obixu uu";
    char out[] = "relax xx";
    decode (in, K_4);
    return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_upper_case_positive_k ()
{
    char in[] = "CHEUD";
    char out[] = "ZEBRA";
    decode (in, K_5);
    return strcmp (in, out) != 0;
}
