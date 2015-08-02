/*
   The MIT License (MIT)

   Copyright (c) <year> <copyright holders>

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_OUTPUT    ("file.out")
#define DEFAULT_INPUT     ("file.in")
#define DEFAULT_AUXILIARY ("file.aux")

typedef struct options_set options_set;

struct options_set {
  const char *output_file;
  const char *input_file;
  const char *aux_file;
  int         num_option;
  int         num_value;
  int         log_flag;
};

static void print_usage(struct option *, const char *);
static options_set *ptr_options_init(int argc, char **argv);
static void init_options(struct options_set *, int, char **);
static void program(struct options_set *ptr_opt_set);
static int  log_flag;

int main(int argc, char **argv);
int main (int argc, char **argv)
{

  options_set opt_set;
  init_options(&opt_set,argc,argv);

  program(&opt_set);

  return 0;
}

static void print_usage(struct option *long_option, const char *prog_name)
{
  int opt_index;

  printf("Usage: %s",prog_name);

  for ( opt_index = 0 ; opt_index < 7 ; opt_index++ ) {

    printf(" --%s",long_option[opt_index].name);

    if ( !long_option[opt_index].flag && long_option[opt_index].val ) {
      printf(" (-%c)",long_option[opt_index].val);
    }

    if ( long_option[opt_index].has_arg )
      printf(" <value>");
  }

  printf("\n");
}

static void init_options(struct options_set *ptr_opt_set, int argc, char **argv)
{
  int cmd_line_opt;

  static struct option long_options[] =
  {
    /* These options set a flag. */
    {"log", no_argument,       &log_flag, 1},
    {"help", no_argument, 0, 0},
    /* These options don't set a flag.
       We distinguish them by their indices. */
    {"num",  required_argument, 0, 'n'},
    {"output-file",  required_argument, 0, 'o'},
    {"input-file",    required_argument, 0, 'i'},
    {"aux-file",    required_argument, 0, 'p'},
    {0, 0, 0, 0}
  };

  ptr_opt_set->output_file = NULL;
  ptr_opt_set->input_file  = NULL;
  ptr_opt_set->aux_file    = NULL;
  ptr_opt_set->num_option  = 0;
  ptr_opt_set->num_value   = 1; /* default value when option not supplied */
  ptr_opt_set->log_flag    = 0;

  while (1)
    {
      /* getopt_long stores the option index here. */
      int option_index = 0;

      cmd_line_opt = getopt_long (argc, argv, "o:i:p:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if ( cmd_line_opt == -1 )
        break;

      ptr_opt_set->log_flag = log_flag;

      switch ( cmd_line_opt )
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if ( long_options[option_index].flag != 0 )
            break;

          if ( !strcmp(long_options[option_index].name,"help") ) {
            print_usage(long_options,argv[0]);
            exit(0);
          }

          if ( !strcmp(long_options[option_index].name,"num") ) {
            ptr_opt_set->num_option = 1;
            ptr_opt_set->num_value = atoi(optarg);
          }

          if ( !strcmp(long_options[option_index].name,"output-file") )
            ptr_opt_set->output_file = optarg;

          if ( !strcmp(long_options[option_index].name,"input-file") )
            ptr_opt_set->input_file = optarg;

          if ( !strcmp(long_options[option_index].name,"aux-file") )
            ptr_opt_set->aux_file = optarg;

          break;

        case 'n':
          ptr_opt_set->num_option = 1;
          ptr_opt_set->num_value = atoi(optarg);
          break;

        case 'o':
          ptr_opt_set->output_file = optarg;
          break;

        case 'i':
          ptr_opt_set->input_file = optarg;
          break;

        case 'p':
          ptr_opt_set->aux_file = optarg;
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          print_usage(long_options,argv[0]);
          exit (1);
        }
    }

  /* Print any remaining command line arguments (not options). */
  if ( optind < argc )
    {
      printf("error: unknown option:\n");
      print_usage(long_options,argv[0]);
      exit (1);
    }

  if ( ptr_opt_set->num_value < 1 ) {
    printf("error: --num argument must be greater than 0:\n");
    print_usage(long_options,argv[0]);
    exit(1);
  }

  if ( !ptr_opt_set->input_file ) {
    printf("error: --input-file argument not optional:\n");
    print_usage(long_options,argv[0]);
    exit(1);
  }

}

static void program(options_set *ptr_opt_set)
{

  printf("hello world\n");

}
