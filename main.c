#include "cipher.h"
#include "tests.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define VALID 1
#define INVALID 0
#define MAX_L_TEXT 1024
#define BASE 10
#define NUM_OF_CIPHER_ARGS 5
#define NUM_OF_TEST_ARGS 2
#define INVALID_FILE "The given file is invalid.\n"
#define CIPHER_TEST "Usage: cipher test\n"
#define NUM_OF_ARGS "The program receives 1 or 4 arguments only.\n"
#define COMMAND "The given command is invalid.\n"
#define OFFSET "The given shift value is invalid.\n"
#define ABC 26

//declarations


int mod (long num);

/**
 *
 * @param s - command string
 * @return 0 if command is invalid, 1 if command is "encode"/ "decode"
 */
int check_command_validation (char s[]);

/**
 *
 * @param argv
 * @return 1 if all arguments are valid, o otherwise
 */
int five_args (char *argv[]);

/**
 *
 * @param argv
 * @return 1 if the command is valid, o otherwise
 */
int two_args (char *argv[]);

/**
 *
 * @param s -offset string
 * @return 0 if k is invalid, 1 if k is an int
 */
int check_k_validation (const char s[]);

/**
 *
 * @param file_loc - string of the source file location
 * @return 0 if the location does`t exist or can`t be open' 1 otherwise
 */
int check_source_file_v (char file_loc[]);

/**
 *
 * @param file_loc - string of the target file location
 * @return 0 if the location does`t exist, 1 otherwise
 */
int check_target_file_v (char file_loc[]);

/**
 *
 * @param source_loc - string of the source file location
 * @param command -string of the command
 * @param k -int of the offset
 * @param target_loc - string of the target file location
 */
int cipher_files (char source_loc[], char command[], int k, char target_loc[]);

/**
 *
 * @return 1 if all test passed, 0 otherwise
 */
int run_tests ();

int check_command_validation (char s[])
{
  if ((strcmp (s, "encode") != 0) && (strcmp (s, "decode") != 0))
    {
      fprintf (stderr, COMMAND);
      return INVALID;
    }
  return VALID;
}

int check_k_validation (const char s[])
{
  // check if the first char is a number or sign
  if (s[0] != '-' && (s[0] < '0' || s[0] > '9'))
    {
      fprintf (stderr, OFFSET);
      return INVALID;
    }

  //checking that all chars are numbers
  for (int i = 1; s[i] != '\0'; ++i)
    {
      if (s[i] < '0' || s[i] > '9')
        {
          fprintf (stderr, OFFSET);
          return INVALID;
        }
    }
  return VALID;
}

int check_source_file_v (char file_loc[])
{
  FILE *source = fopen (file_loc, "r");
  if (source == NULL)
    {
      fprintf (stderr, INVALID_FILE);
      return INVALID;
    }
  else
    {
      return VALID;
    }
}

int check_target_file_v (char file_loc[])
{
  FILE *source = fopen (file_loc, "w");
  if (source == NULL)
    {
      fprintf (stderr, INVALID_FILE);
      return INVALID;
    }
  else
    {
      return VALID;
    }
}

int cipher_files (char source_loc[], char command[], int k, char target_loc[])
{
  FILE *source = fopen (source_loc, "r");
  FILE *target = fopen (target_loc, "w");
  char str[MAX_L_TEXT];
  while (fgets (str, MAX_L_TEXT, source) != NULL)
    {
      if (strcmp (command, "encode") == 0)
        {
          encode (str, k);
        }

      if (strcmp (command, "decode") == 0)
        {
          decode (str, k);
        }

      fputs (str, target);
    }
  fclose (source);
  fclose (target);
  return VALID;
}

int run_tests ()
{
  int passed_all = test_encode_non_cyclic_lower_case_positive_k () +
                   test_encode_cyclic_lower_case_special_char_positive_k () +
                   test_encode_non_cyclic_lower_case_special_char_negative_k ()
                   +
                   test_encode_cyclic_lower_case_negative_k () +
                   test_encode_cyclic_upper_case_positive_k () +
                   test_decode_non_cyclic_lower_case_positive_k () +
                   test_decode_cyclic_lower_case_special_char_positive_k () +
                   test_decode_non_cyclic_lower_case_special_char_negative_k ()
                   +
                   test_decode_cyclic_lower_case_negative_k () +
                   test_decode_cyclic_upper_case_positive_k ();
  if (passed_all != 0)
    {
      return INVALID;
    }
  else
    {
      return VALID;
    }
}

int five_args (char *argv[])
{
// check command
  if (!check_command_validation (argv[1]))
    {
      return INVALID;
    }

  //check offset
  if (!check_k_validation (argv[2]))
    {
      return INVALID;
    }
  //converting offset to int
  long k = strtol (argv[2], NULL, BASE);
  int mod_k = mod (k);
  //check files validation
  if ((check_source_file_v (argv[3]) != 1) ||
      (check_target_file_v (argv[4]) != 1))
    {
      return INVALID;
    }

  // all arguments are fine
  //encrypt/ decrypt files
  cipher_files (argv[3], argv[1], mod_k, argv[4]);
  return VALID;
}

int two_args (char *argv[])
{
  if (strcmp (argv[1], "test") != 0)
    {
      fprintf (stderr, CIPHER_TEST);
      return INVALID;
    }
  else
    {
      if (!run_tests ())
        {
          return INVALID;
        }
    }
  return VALID;
}

int main (int argc, char *argv[])
{
  if (argc == NUM_OF_CIPHER_ARGS)
    {
      if (!five_args (argv))
        {
          return EXIT_FAILURE;
        }
    }

  else if (argc == NUM_OF_TEST_ARGS)
    {
      if (!two_args (argv))
        {
          return EXIT_FAILURE;
        }
    }
  else
    {
      fprintf (stderr, NUM_OF_ARGS);
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}

int mod (long num)
{
  return (int) (num % ABC + ABC) % ABC;
}