# simple-gnu-utils

A lightweight implementation of the GNU `cat` and `grep` utilities, written in C to provide essential functionality with minimal code.

---

## Features

### `cat`
Outputs file contents to standard output.

Supported options:
- `-b` : number non-empty output lines
- `-e` : display `$` at end of each line and make non-printing characters visible (equivalent to `-vE`)
- `-E` : display `$` at end of each line
- `-n` : number all output lines
- `-s` : suppress repeated empty output lines
- `-t` : display tab characters as `^I` and make non-printing characters visible (equivalent to `-vT`)
- `-T` : display tab characters as `^I`
- `-v` : make non-printing characters visible

### `grep`
Searches for patterns in files using basic regular expressions.

Supported options:
- `-e` : specify a pattern
- `-i` : case-insensitive matching
- `-v` : invert match
- `-c` : print only a count of matching lines per file
- `-l` : print only names of files with matches
- `-n` : prefix each matching line with the line number
- `-h` : suppress the prefixing of file names on output
- `-s` : suppress error messages about nonexistent or unreadable files
- `-f` : obtain patterns from a file
- `-o` : show only matching parts of lines

---

## Build

```bash
git clone https://github.com/mayrlex/simple-gnu-utils.git
cd simple-gnu-utils
make
```

### Build individually

```bash
make cat    # Build cat utility
make grep   # Build grep utility
```

---

## Usage

### `cat`

```bash
./gcat <OPTION>... <FILE>...
```

Example:

```bash
./gcat -n file.txt
```

### `grep`

```bash
./ggrep <OPTION>... PATTERN <FILE>...
```

Example:

```bash
./ggrep -i "lorem" file.txt
```

---

## Tests
Run unit tests:

```bash
make test-cat
make test-grep
```

---

## Makefile commands

- make — build all utilities
- make cat — build only cat
- make grep — build only grep
- make test-cat — run tests for cat
- make test-grep — run tests for grep
- make clang — format code using clang-format
- make clang-check — check code formatting without modifying files
- make clean — remove build artifacts
- make rebuild — clean and build