#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include "PairHashSpecialization.h"

class DeterministicFiniteAutomaton
{
private:
	std::vector<std::string> states;
	std::vector<std::string> alphabet;
	std::unordered_map<std::pair<std::string, std::string>, std::string, custom::hash_pair, custom::MyKeyEqual> transitionFunction;
	std::string initialState;
	std::vector<std::string> finalStates;

public:
	bool IsValidTransition();
	bool VerifyAutomaton();
	bool CheckWord(std::string word);
	bool IsDeterministic();

	void AddState(const std::string& state);
	void AddTransitionFunction(const std::string& state1, const std::string& state2, const std::string& transition);
	void AddCharacterToThealphabet(const std::string& character);
	void SetInitialState(const std::string& state);
	void AddFinalState(const std::string& state);

	DeterministicFiniteAutomaton& operator=(const DeterministicFiniteAutomaton& automaton);
	friend std::ostream& operator<<(std::ostream& os, const DeterministicFiniteAutomaton& automata);
};

