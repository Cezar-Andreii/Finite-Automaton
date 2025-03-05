# 🧑‍💻 **Finite Automaton Project** 🤖

Welcome to the **Finite Automaton** project! 🚀 This project implements basic concepts of **Finite Automata** (FA) using C++ and provides functionalities for both **Deterministic** and **Non-Deterministic** automata. It supports operations like building automata from regular expressions, checking word acceptance, and more. 📜

## 🔧 **Features**:

- **Finite Automaton** (FA) 🚶‍♂️:
  - Add states 🏛️ and transitions ↔️
  - Set initial and final states 🔑
  - Add characters to the alphabet 🔡
  - Supports **multi-transition** states 🚥

- **Deterministic Finite Automaton** (DFA) 🧮:
  - Check if transitions are valid ✅
  - Verify automaton structure ✔️
  - Check if an automaton is deterministic 🧑‍🔬
  - Verify if a word is accepted by the DFA 📝

- **Expression Parsing** 🧐:
  - Convert regular expressions into **Polish Notation** 🔄
  - Build automata from regular expressions (concatenation, alternation, and Kleene star) 🔠

- **Closure Operations** 🔒:
  - Calculate epsilon closure for automata 🔐
  - Build new closures based on transitions ➡️

## 🛠️ **How to Use**:

1. **Create a Finite Automaton**:
    - Use `AddState()`, `AddTransitionFunction()`, and `AddCharacterToThealphabet()` methods to set up your automaton.
    - Set the initial and final states with `SetInitialState()` and `SetFinalState()`.

2. **Create a Deterministic Automaton**:
    - Use the `IsDeterministic()` method to check if your automaton is deterministic.
    - Use `VerifyAutomaton()` to check if your DFA is valid.

3. **Test the Automaton**:
    - Use the `CheckWord()` method to check if a given word is accepted by the automaton.

4. **Parse and Evaluate Regular Expressions**:
    - Use `ExpressionEvaluation()` to evaluate a regular expression and convert it into an automaton.

5. **Generate Closures**:
    - Use `InitializationNewClosingSet()` and `GenerateNewClosure()` for generating closure operations in your automaton.
