#include "include.h"

#if defined(__linux__)
#define MAX_ERRNO 133
const char *const ERROR_LIST[MAX_ERRNO + 1] = {
    "Success", "Operation not permitted", "No such file or directory",
    "No such process", "Interrupted system call", "Input/output error",
    "No such device or address", "Argument list too long", "Exec format error",
    "Bad file descriptor", "No child processes", "Resource temporarily unavailable",
    "Cannot allocate memory", "Permission denied", "Bad address",
    "Block device required", "Device or resource busy", "File exists",
    "Invalid cross-device link", "No such device", "Not a directory",
    "Is a directory", "Invalid argument", "Too many open files in system",
    "Too many open files", "Inappropriate ioctl for device", "Text file busy",
    "File too large", "No space left on device", "Illegal seek",
    "Read-only file system", "Too many links", "Broken pipe",
    "Numerical argument out of domain", "Numerical result out of range",
    "Resource deadlock avoided", "File name too long", "No record locks available",
    "Function not implemented", "Directory not empty", "Too many symbolic links encountered",
    "Unknown error 41", "No message of desired type", "Identifier removed",
    "Channel number out of range", "Level 2 not synchronized", "Level 3 halted",
    "Level 3 reset", "Link number out of range", "Protocol driver not attached",
    "No CSI structure available", "Level 2 halted", "Invalid exchange",
    "Invalid request descriptor", "Exchange full", "No anode",
    "Invalid request code", "Invalid slot", "Unknown error 58",
    "Bad font file format", "Device not a stream", "No data available",
    "Timer expired", "Out of streams resources", "Machine is not on the network",
    "Package not installed", "Object is remote", "Link has been severed",
    "Advertise error", "Srmount error", "Communication error on send",
    "Protocol error", "Multihop attempted", "RFS specific error",
    "Bad message", "Value too large for defined data type", "Name not unique on network",
    "File descriptor in bad state", "Remote address changed",
    "Can not access a needed shared library", "Accessing a corrupted shared library",
    ".lib section in a.out corrupted", "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly", "Illegal byte sequence",
    "Interrupted system call should be restarted", "Streams pipe error",
    "Too many users", "Socket operation on non-socket", "Destination address required",
    "Message too long", "Protocol wrong type for socket", "Protocol not available",
    "Protocol not supported", "Socket type not supported", "Operation not supported",
    "Protocol family not supported", "Address family not supported by protocol",
    "Address already in use", "Cannot assign requested address", "Network is down",
    "Network is unreachable", "Network dropped connection on reset",
    "Software caused connection abort", "Connection reset by peer",
    "No buffer space available", "Transport endpoint is already connected",
    "Transport endpoint is not connected", "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice", "Connection timed out",
    "Connection refused", "Host is down", "No route to host",
    "Operation already in progress", "Operation now in progress",
    "Stale file handle", "Structure needs cleaning", "Not a XENIX named type file",
    "No XENIX semaphores available", "Is a named type file", "Remote I/O error",
    "Quota exceeded", "No medium found", "Wrong medium type", "Operation canceled",
    "Required key not available", "Key has expired", "Key has been revoked",
    "Key was rejected by service", "Owner died", "State not recoverable",
    "Operation not possible due to RF-kill", "Memory page has hardware error"
};
#else
#define MAX_ERRNO 0
const char *const ERROR_LIST[MAX_ERRNO + 1] = {"Windows OS"};
#endif

void printErrors(StatusCode status) {
  switch (status) {
  case INVALID_INPUT:
    printf("Invalid input\n");
    break;
  case NOT_FOUND:
    printf("Not found\n");
    break;
  default:
    break;
  }
}

StatusCode myMemchr(const void *memory, int search_char, size_t bytes_count, void **found_position) {
  if (memory == NULL || found_position == NULL) {
    return INVALID_INPUT;
  }

  const unsigned char *byte_ptr = (const unsigned char *)memory;
  unsigned char target_byte = (unsigned char)search_char;

  for (size_t index = 0; index < bytes_count; index++) {
    if (byte_ptr[index] == target_byte) {
      *found_position = (void *)(byte_ptr + index);
      return OK;
    }
  }

  *found_position = NULL;
  return NOT_FOUND;
}

StatusCode myMemcmp(const void *first_memory, const void *second_memory, size_t bytes_count, int *comparison_result) {
  if (first_memory == NULL || second_memory == NULL || comparison_result == NULL) {
    return INVALID_INPUT;
  }

  const unsigned char *first_ptr = (const unsigned char *)first_memory;
  const unsigned char *second_ptr = (const unsigned char *)second_memory;

  for (size_t index = 0; index < bytes_count; index++) {
    if (first_ptr[index] != second_ptr[index]) {
      *comparison_result = first_ptr[index] - second_ptr[index];
      return OK;
    }
  }

  *comparison_result = 0;
  return OK;
}

StatusCode myMemcpy(void *destination, const void *source, size_t bytes_count) {
  if (destination == NULL || source == NULL) {
    return INVALID_INPUT;
  }

  unsigned char *dest_ptr = (unsigned char *)destination;
  const unsigned char *src_ptr = (const unsigned char *)source;

  for (size_t index = 0; index < bytes_count; index++) {
    dest_ptr[index] = src_ptr[index];
  }

  return OK;
}

StatusCode myMemset(void *memory_block, int fill_value, size_t bytes_count) {
  if (memory_block == NULL) {
    return INVALID_INPUT;
  }

  unsigned char *block_ptr = (unsigned char *)memory_block;
  unsigned char fill_byte = (unsigned char)fill_value;

  for (size_t index = 0; index < bytes_count; index++) {
    block_ptr[index] = fill_byte;
  }

  return OK;
}

StatusCode myStrncat(char *destination, const char *source, size_t max_chars) {
  if (destination == NULL || source == NULL) {
    return INVALID_INPUT;
  }

  char *dest_end = destination;
  while (*dest_end != '\0') {
    dest_end++;
  }

  size_t copied_chars = 0;
  while (copied_chars < max_chars && *source != '\0') {
    *dest_end++ = *source++;
    copied_chars++;
  }

  *dest_end = '\0';
  return OK;
}

StatusCode myStrchr(const char *string, int character, char **found_ptr) {
  if (string == NULL || found_ptr == NULL) {
    return INVALID_INPUT;
  }

  char search_char = (char)character;
  const char *current_pos = string;

  while (*current_pos != '\0') {
    if (*current_pos == search_char) {
      *found_ptr = (char *)current_pos;
      return OK;
    }
    current_pos++;
  }

  if (search_char == '\0') {
    *found_ptr = (char *)current_pos;
    return OK;
  }

  *found_ptr = NULL;
  return NOT_FOUND;
}

StatusCode myStrncmp(const char *first_str, const char *second_str, size_t max_chars, int *result_value) {
  if (first_str == NULL || second_str == NULL || result_value == NULL) {
    return INVALID_INPUT;
  }

  if (max_chars == 0) {
    *result_value = 0;
    return OK;
  }

  size_t char_index = 0;
  while (char_index < max_chars && first_str[char_index] != '\0' && 
         first_str[char_index] == second_str[char_index]) {
    char_index++;
  }

  if (char_index == max_chars) {
    *result_value = 0;
  } else {
    *result_value = (unsigned char)first_str[char_index] - (unsigned char)second_str[char_index];
  }

  return OK;
}

StatusCode myStrncpy(char *destination, const char *source, size_t max_chars) {
  if (destination == NULL || source == NULL) {
    return INVALID_INPUT;
  }

  size_t index;
  for (index = 0; index < max_chars && source[index] != '\0'; index++) {
    destination[index] = source[index];
  }

  for (; index < max_chars; index++) {
    destination[index] = '\0';
  }

  return OK;
}

StatusCode myStrcspn(const char *main_string, const char *reject_chars, size_t *span_length) {
  if (main_string == NULL || reject_chars == NULL || span_length == NULL) {
    return INVALID_INPUT;
  }

  size_t count = 0;
  const char *main_ptr = main_string;

  while (*main_ptr != '\0') {
    const char *reject_ptr = reject_chars;
    int found = 0;

    while (*reject_ptr != '\0') {
      if (*main_ptr == *reject_ptr) {
        found = 1;
        break;
      }
      reject_ptr++;
    }

    if (found) {
      break;
    }

    count++;
    main_ptr++;
  }

  *span_length = count;
  return OK;
}

StatusCode myStrerror(int error_number, char **error_message) {
  if (error_message == NULL) {
    return INVALID_INPUT;
  }

  static char custom_error[50];

  if (error_number >= 0 && error_number <= MAX_ERRNO) {
    *error_message = (char *)ERROR_LIST[error_number];
  } else {
    snprintf(custom_error, sizeof(custom_error), "Unknown error: %d", error_number);
    *error_message = custom_error;
  }

  return OK;
}

StatusCode myStrlen(const char *string, size_t *length_result) {
  if (string == NULL || length_result == NULL) {
    return INVALID_INPUT;
  }

  size_t count = 0;
  while (string[count] != '\0') {
    count++;
  }

  *length_result = count;
  return OK;
}

StatusCode myStrpbrk(const char *main_string, const char *char_set, char **found_char) {
  if (main_string == NULL || char_set == NULL || found_char == NULL) {
    return INVALID_INPUT;
  }

  for (const char *main_ptr = main_string; *main_ptr != '\0'; main_ptr++) {
    for (const char *set_ptr = char_set; *set_ptr != '\0'; set_ptr++) {
      if (*main_ptr == *set_ptr) {
        *found_char = (char *)main_ptr;
        return OK;
      }
    }
  }

  *found_char = NULL;
  return NOT_FOUND;
}

StatusCode myStrrchr(const char *string, int character, char **last_occurrence) {
  if (string == NULL || last_occurrence == NULL) {
    return INVALID_INPUT;
  }

  char search_char = (char)character;
  const char *last_pos = NULL;
  const char *current = string;

  while (*current != '\0') {
    if (*current == search_char) {
      last_pos = current;
    }
    current++;
  }

  if (search_char == '\0') {
    *last_occurrence = (char *)current;
    return OK;
  }

  if (last_pos != NULL) {
    *last_occurrence = (char *)last_pos;
    return OK;
  }

  *last_occurrence = NULL;
  return NOT_FOUND;
}

StatusCode myStrstr(const char *haystack, const char *needle, char **substring_start) {
  if (haystack == NULL || needle == NULL || substring_start == NULL) {
    return INVALID_INPUT;
  }

  if (*needle == '\0') {
    *substring_start = (char *)haystack;
    return OK;
  }

  for (const char *h_ptr = haystack; *h_ptr != '\0'; h_ptr++) {
    const char *h_temp = h_ptr;
    const char *n_temp = needle;

    while (*h_temp != '\0' && *n_temp != '\0' && *h_temp == *n_temp) {
      h_temp++;
      n_temp++;
    }

    if (*n_temp == '\0') {
      *substring_start = (char *)h_ptr;
      return OK;
    }
  }

  *substring_start = NULL;
  return NOT_FOUND;
}

static int is_delimiter(char ch, const char *delimiters) {
  while (*delimiters != '\0') {
    if (ch == *delimiters) {
      return 1;
    }
    delimiters++;
  }
  return 0;
}

StatusCode myStrtok(char *input_string, const char *delimiters, char **token_ptr) {
  if (delimiters == NULL || token_ptr == NULL) {
    return INVALID_INPUT;
  }

  static char *next_token = NULL;
  char *token_start = (input_string != NULL) ? input_string : next_token;

  if (token_start == NULL) {
    *token_ptr = NULL;
    return NOT_FOUND;
  }

  while (*token_start != '\0' && is_delimiter(*token_start, delimiters)) {
    token_start++;
  }

  if (*token_start == '\0') {
    next_token = NULL;
    *token_ptr = NULL;
    return NOT_FOUND;
  }

  char *token_end = token_start;
  while (*token_end != '\0' && !is_delimiter(*token_end, delimiters)) {
    token_end++;
  }

  if (*token_end != '\0') {
    *token_end = '\0';
    next_token = token_end + 1;
  } else {
    next_token = token_end;
  }

  *token_ptr = token_start;
  return OK;
}