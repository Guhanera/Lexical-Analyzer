🧠 Lexical Analyzer (C Project)

📌 Overview
- Lexical Analyzer is a C-based program that converts a sequence of characters into tokens.
- It is a fundamental phase in compiler design.
- Also known as a lexer or scanner.
- Processes input C source code and categorizes elements into meaningful tokens.

🎯 Objective
- Implement a basic lexical analyzer for C programs.
- Identify and classify tokens from source code.
- Build a strong foundation in compiler design concepts.

🧠 Concept
- Lexical analysis is the first phase of a compiler.
- Converts input stream of characters into tokens.
- Tokens are categorized symbols like identifiers, keywords, operators, etc.
- Works based on predefined rules (grammar).
- Invalid tokens result in lexical errors.

📚 Key Definitions
- Token: A sequence of characters with a meaning (e.g., keyword, identifier).
- Lexeme: Actual string in the source code corresponding to a token.
- Tokenization: Process of converting input into tokens.
- Lexer: Program that performs lexical analysis.

⚙️ Features

🔍 Token Identification
- Identifies all keywords (e.g., int, float, if, while).
- Identifies identifiers (variable names, function names).
- Identifies operators (arithmetic, assignment, logical).
- Identifies separators (commas, semicolons, brackets).

🔢 Literal Detection
- Detects integer literals.
- Detects floating-point numbers.
- Detects character literals.
- Detects string literals.

📋 Output
- Displays tokenized output in structured format.
- Shows token and corresponding token type.

🧾 Requirements
- Language: C
- Platform: Command-line (Linux/Windows)
- Concepts used:
  - File handling
  - String manipulation
  - Pattern matching
  - Parsing basics

🧪 Working Flow

Input Processing
- Read C source code file.
- Scan character by character.

Tokenization
- Group characters into lexemes.
- Match lexemes with token types.
- Classify into categories:
  - Keyword
  - Identifier
  - Operator
  - Literal
  - Separator

Output Generation
- Display tokens in tabular format.
- Report invalid tokens if found.


📊 Advantages
- Helps understand compiler design basics.
- Improves knowledge of C programming.
- Simple and efficient implementation.
- Foundation for building compilers/interpreters.

⚠️ Limitations
- Covers only basic C syntax.
- Does not handle full grammar or parsing.
- Limited support for complex constructs.

🚀 Applications
- Compiler design learning.
- Code analysis tools.
- Syntax highlighting systems.
- Preprocessing tools.
