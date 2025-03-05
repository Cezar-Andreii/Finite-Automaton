#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include "PairHashSpecialization.h"

class FiniteAutomaton
{
private:
	std::vector<std::string> states;
	std::unordered_set<std::string> alphabet;
	std::unordered_multimap<std::pair<std::string, std::string>, std::string, custom::hash_pair, custom::MyKeyEqual> transitionFunction;
	std::string initialState;
	std::string finalState;
public:
	void AddState(const std::string& state);
	void AddTransitionFunction(const std::string& state1, const std::string& state2, const std::string& transition);
	void AddTransitionFunction(const std::pair<std::pair<std::string, std::string>, std::string>& transition);
	void AddCharacterToThealphabet(const std::string& character);

	void SetInitialState(const std::string& state);
	void SetFinalState(const std::string& state);
	std::vector<std::string> GetStates();
	std::unordered_set<std::string> Getalphabet();
	std::unordered_multimap<std::pair<std::string, std::string>, std::string, custom::hash_pair, custom::MyKeyEqual> GetTransitionFunction();
	std::string GetInitialState();
	std::string GetFinalState();

	FiniteAutomaton& operator=(const FiniteAutomaton& automaton);
	friend std::ostream& operator<<(std::ostream& os, const FiniteAutomaton& automata);
};