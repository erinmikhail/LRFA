#include "include.h"
#include <string.h>

void runAllTests(void) {
  StatusCode test_status;

  printf("=== Testing myMemchr ===\n");
  const char *test_str = "Hello World";
  void *result_ptr = NULL;
  test_status = myMemchr(test_str, 'W', 11, &result_ptr);
  printf("Search 'W': %s\n", (test_status == OK && strcmp(result_ptr, "World") == 0) ? "PASS" : "FAIL");
  
  test_status = myMemchr(test_str, 'z', 11, &result_ptr);
  printf("Search 'z': %s\n", (test_status == NOT_FOUND) ? "PASS" : "FAIL");
  printf("\n");

  printf("=== Testing myMemcmp ===\n");
  int cmp_result;
  test_status = myMemcmp("abc", "abd", 3, &cmp_result);
  printf("Compare 'abc' and 'abd': %s\n", (test_status == OK && cmp_result < 0) ? "PASS" : "FAIL");
  
  test_status = myMemcmp("abc", "abc", 3, &cmp_result);
  printf("Compare 'abc' and 'abc': %s\n", (test_status == OK && cmp_result == 0) ? "PASS" : "FAIL");
  printf("\n");

  printf("=== Testing myMemcpy ===\n");
  char buffer[10] = "";
  test_status = myMemcpy(buffer, "test", 5);
  printf("Copy 'test': %s\n", (test_status == OK && strcmp(buffer, "test") == 0) ? "PASS" : "FAIL");
  printf("\n");

  printf("=== Testing myMemset ===\n");
  char data[] = "aaaaa";
  myMemset(data, 'b', 3);
  printf("Set to 'b': %s\n", (strcmp(data, "bbbaa") == 0) ? "PASS" : "FAIL");
  printf("\n");

  printf("=== Testing myStrncat ===\n");
  char dest[20] = "Hello ";
  myStrncat(dest, "World!", 3);
  printf("Concatenate 3 chars: %s\n", (strcmp(dest, "Hello Wor") == 0) ? "PASS" : "FAIL");
  printf("\n");

  printf("=== Testing myStrchr ===\n");
  char *char_ptr;
  myStrchr("test", 's', &char_ptr);
  printf("Search 's': %s\n", (char_ptr != NULL && strcmp(char_ptr, "st") == 0) ? "PASS" : "FAIL");
  printf("\n");

  printf("=== Testing myStrncmp ===\n");
  int str_cmp_result;
  myStrncmp("test", "tesT", 4, &str_cmp_result);
  printf("Compare 'test' and 'tesT': %s\n", (str_cmp_result > 0) ? "PASS" : "FAIL");
  printf("\n");

  printf("=== Testing myStrncpy ===\n");
  char copy_buf[10];
  myStrncpy(copy_buf, "abc", 5);
  printf("Copy short string: %s\n", (copy_buf[0] == 'a' && copy_buf[3] == '\0') ? "PASS" : "FAIL");
  printf("\n");

  printf("=== Testing myStrcspn ===\n");
  size_t span_len;
  myStrcspn("find the char", " tc", &span_len);
  printf("Length without ' tc': %s\n", (span_len == 4) ? "PASS" : "FAIL");
  printf("\n");

  printf("=== Testing myStrerror ===\n");
  char *err_msg;
  myStrerror(2, &err_msg);
  printf("Error #2: %s\n", (err_msg != NULL) ? "PASS" : "FAIL");
  printf("\n");

  printf("=== Testing myStrlen ===\n");
  size_t str_len;
  myStrlen("hello", &str_len);
  printf("Length of 'hello': %s\n", (str_len == 5) ? "PASS" : "FAIL");
  printf("\n");

  printf("=== Testing myStrpbrk ===\n");
  char *found_pos;
  myStrpbrk("hello world", "xr w", &found_pos);
  printf("Find any of 'xr w': %s\n", (found_pos != NULL) ? "PASS" : "FAIL");
  printf("\n");

  printf("=== Testing myStrrchr ===\n");
  char *last_char;
  myStrrchr("hello world", 'l', &last_char);
  printf("Find last 'l': %s\n", (last_char != NULL && strcmp(last_char, "ld") == 0) ? "PASS" : "FAIL");
  printf("\n");

  printf("=== Testing myStrstr ===\n");
  char *substr;
  test_status = myStrstr("this is a test", "is a", &substr);
  printf("Find substring 'is a': %s\n", (test_status == OK && substr != NULL) ? "PASS" : "FAIL");
  printf("\n");

  printf("=== Testing myStrtok ===\n");
  char text[] = "token1,token2.token3";
  char *token;
  int token_count = 0;
  
  myStrtok(text, ",.", &token);
  if (token != NULL && strcmp(token, "token1") == 0) token_count++;
  myStrtok(NULL, ",.", &token);
  if (token != NULL && strcmp(token, "token2") == 0) token_count++;
  myStrtok(NULL, ",.", &token);
  if (token != NULL && strcmp(token, "token3") == 0) token_count++;
  
  printf("Tokenize string: %s\n", (token_count == 3) ? "PASS" : "FAIL");
  printf("\n");

  printf("=== ALL TESTS COMPLETED ===\n");
}