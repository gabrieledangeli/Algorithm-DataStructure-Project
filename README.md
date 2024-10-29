# **Text Editor with Undo and Redo**
## **Algorithms and Principles of Computer Science, Politecnico di Milano 2018-2019**

This repository contains the code for the **Algorithms and Principles of Computer Science** project at **Politecnico di Milano** written by **Gabriele D'Angeli**. 

The project involves implementing a text editor that supports multiple undo and redo operations, inspired by the interface of the traditional `ed` editor.

## Project Description

The editor treats a document as a sequence of numbered lines. Through a series of text-based commands, users can:

- Modify (`c` command) specific lines of text.
- Delete (`d` command) one or more lines.
- Print (`p` command) specific lines.
- Undo (`u` command) or redo (`r` command) multiple modifications.
- Quit the editor (`q` command).

### Undo and Redo Functionality

The editor allows users to undo (`u`) and redo (`r`) a specified number of actions, supporting flexible management of changes. The command sequence is designed to provide a highly customizable workflow.

### Limitations

The editor is implemented in C (2011 version) without the use of external libraries, except for the standard library. It is assumed that all input commands are valid.

## Usage

1. **Compilation**: Use a C11-compatible compiler. Example:
   ```bash
   gcc -o editor editor.c
   ```
2. **Execution**: The editor accepts commands via `stdin`. Example:
   ```bash
   ./editor < input.txt
   ```

## Command Example

```plaintext
1,2c
first line
second line
.
1,3p
2u
q
```

### Example Output

The output displays the specified lines, following the logic of undo and redo to manage the changes.

## Evaluation

The project is tested with various test cases to verify both the correctness and efficiency of the implementation. Additional local tests are recommended to validate functionality.

## Notes

- This project is individual.