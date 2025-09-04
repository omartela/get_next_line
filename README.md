# Get Next Line

A C function that reads a text file line by line, regardless of the size of the text file or the length of the lines. This project is part of the 42 School curriculum and focuses on memory management, file I/O, and efficient buffer handling.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Function Specification](#function-specification)
- [Implementation Details](#implementation-details)
- [Testing](#testing)
- [Project Files](#project-files)
- [Technical Requirements](#technical-requirements)
- [Examples](#examples)
- [Author](#author)

## Description

`get_next_line` is a function that allows you to read a text file line by line. Each call to the function returns the next line from the file descriptor, including the terminating `\n` character (except for the last line if it doesn't end with a newline).

This implementation handles:
- Files with lines of any length
- Multiple file descriptors simultaneously  
- Memory management without leaks
- Various edge cases (empty files, single characters, no final newline, etc.)

## Features

- ✅ **Memory Efficient**: Uses a configurable buffer size for optimal memory usage
- ✅ **Line Length Agnostic**: Handles lines of any length, from single characters to very long lines
- ✅ **Edge Case Handling**: Properly handles empty files, files without trailing newlines, and other edge cases
- ✅ **Memory Safe**: No memory leaks, proper cleanup on errors
- ✅ **Configurable Buffer**: Buffer size can be defined at compile time

## Installation

### Prerequisites
- GCC or any C compiler
- Make (optional)
- UNIX-like operating system (Linux, macOS)

### Compilation

```bash
# Basic compilation with default buffer size (3)
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o get_next_line

# Compilation with custom buffer size
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1024 get_next_line.c get_next_line_utils.c main.c -o get_next_line

# For library use (without main.c)
gcc -Wall -Wextra -Werror -c get_next_line.c get_next_line_utils.c
```

## Usage

### Basic Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("example.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);  // Don't forget to free each line!
    }
    
    close(fd);
    return 0;
}
```

### Command Line Usage

The included test program allows you to test the function from the command line:

```bash
# Test with a file
./get_next_line test.txt

# Test with standard input
echo -e "line1\nline2\nline3" | ./get_next_line /dev/stdin
```

## Function Specification

```c
char *get_next_line(int fd);
```

### Parameters
- `fd`: File descriptor to read from

### Return Value
- **Success**: Returns a string containing the next line from the file, including the `\n` character (if present)
- **End of file**: Returns `NULL` when there's nothing more to read
- **Error**: Returns `NULL` on error (invalid file descriptor, memory allocation failure, etc.)

### Important Notes
- The caller is responsible for freeing the returned string
- The function maintains state between calls using static variables
- Each line includes the terminating `\n` character, except possibly the last line

## Implementation Details

### Core Algorithm
1. **Buffer Reading**: Reads data in chunks using the defined `BUFFER_SIZE`
2. **Stash Management**: Maintains a static "stash" to store partial lines between reads
3. **Line Extraction**: Extracts complete lines when a newline character is found
4. **Memory Management**: Efficiently manages memory allocation and deallocation

### Key Functions

- `get_next_line(int fd)`: Main function that returns the next line
- `copy_buffer_to_stash()`: Appends buffer content to the stash
- `extract_line()`: Extracts a line from the stash up to the newline
- `check_nl()`: Checks if the stash contains a newline character
- `calc_len()`: Calculates string length
- `ft_strdup()`: Custom string duplication function

### Memory Management Strategy
- Uses static variables to maintain state between function calls
- Implements proper cleanup to prevent memory leaks
- Handles allocation failures gracefully

## Testing

The project includes test files and a main program for testing:

### Test Files
- `test.txt`: Contains various test cases including long lines, special characters, and edge cases
- `1char.txt`: Single character file for minimal testing

### Running Tests

```bash
# Compile and test
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o get_next_line

# Test with different files
./get_next_line test.txt
./get_next_line 1char.txt

# Test with different buffer sizes
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o get_next_line_small
./get_next_line_small test.txt
```

### Test Cases Covered
- ✅ Empty files
- ✅ Single character files
- ✅ Files without trailing newlines
- ✅ Very long lines (exceeding buffer size)
- ✅ Files with only newlines
- ✅ Mixed content with special characters
- ✅ Multiple consecutive reads

## Project Files

| File | Description |
|------|-------------|
| `get_next_line.c` | Main implementation of the get_next_line function |
| `get_next_line_utils.c` | Utility functions for string manipulation and memory management |
| `get_next_line.h` | Header file with function prototypes and definitions |
| `main.c` | Test program demonstrating usage |
| `test.txt` | Comprehensive test file with various edge cases |
| `1char.txt` | Minimal test file with single character |

## Technical Requirements

### 42 School Requirements
- ✅ Function must be written in C
- ✅ Must follow 42 coding standards (Norminette)
- ✅ No global variables allowed
- ✅ Buffer size must be configurable at compile time
- ✅ Must handle file descriptors correctly
- ✅ Memory management must be leak-free

### Compilation Flags
- `-Wall -Wextra -Werror`: Strict compilation with all warnings as errors
- `-D BUFFER_SIZE=n`: Defines the buffer size at compile time

### Buffer Size Considerations
- Minimum: 1 (for testing edge cases)
- Typical: 1024, 4096, or 8192 for performance
- Maximum: Limited by `INT_MAX` and available memory

## Examples

### Example 1: Reading a Configuration File

```c
#include "get_next_line.h"
#include <fcntl.h>

int read_config(const char *filename) {
    int fd = open(filename, O_RDONLY);
    char *line;
    int line_number = 1;
    
    if (fd < 0) {
        perror("Cannot open config file");
        return -1;
    }
    
    while ((line = get_next_line(fd)) != NULL) {
        printf("Line %d: %s", line_number++, line);
        free(line);
    }
    
    close(fd);
    return 0;
}
```

### Example 2: Processing Large Files

```c
#include "get_next_line.h"
#include <fcntl.h>

int process_large_file(const char *filename) {
    int fd = open(filename, O_RDONLY);
    char *line;
    size_t total_lines = 0;
    size_t total_chars = 0;
    
    if (fd < 0) return -1;
    
    while ((line = get_next_line(fd)) != NULL) {
        total_lines++;
        total_chars += strlen(line);
        
        // Process line here...
        
        free(line);
    }
    
    printf("Processed %zu lines, %zu characters\n", total_lines, total_chars);
    close(fd);
    return 0;
}
```

## Author

**Omar Tela** - [omartela](https://github.com/omartela)
- 42 School Student (Hive Helsinki)
- Email: omartela@student.hive.fi

This project was completed as part of the 42 School curriculum, which focuses on peer-to-peer learning and hands-on coding experience without traditional lectures or courses.

---

*This README was created to provide comprehensive documentation for the get_next_line project. If you find any issues or have suggestions for improvement, please feel free to contribute!*
