#include "AFD.h"


bool DeterministicFiniteAutomaton::IsValidTransition()
{
	for (const auto& element : transitionFunction)
	{
		if (std::find(states.begin(), states.end(), element.first.first) == states.end())
			return false;
		if (std::find(alphabet.begin(), alphabet.end(), element.first.second) == alphabet.end())
			return false;
		if (std::find(states.begin(), states.end(), element.second) == states.end())
			return false;
	}
	return true;
}

bool DeterministicFiniteAutomaton::VerifyAutomaton()
{
	if (states.empty())
		return false;
	if (alphabet.empty())
		return false;
	if (std::find(states.begin(), states.end(), initialState) == states.end())
		return false;
	for (const auto& finalState : finalStates)
	{
		if (std::find(states.begin(), states.end(), finalState) == states.end())
			return false;
	}
	if (!IsValidTransition() || !IsDeterministic())
		return false;
	if (!IsDeterministic())
		return false;
	return true;
}

bool DeterministicFiniteAutomaton::CheckWord(std::string word)
{
	std::string currentState = { initialState };

	while (!word.empty())
	{
		std::pair<std::string, std::string> currentTransition = std::make_pair(currentState, std::string(1, word[0]));

		auto transition = transitionFunction.find(currentTransition);

		if (transition == transitionFunction.end())
			return false;

		currentState = transition->second;
		word = word.substr(1);
	}

	if (std::find(finalStates.begin(), finalStates.end(), currentState) != finalStates.end())
		return true;

	return false;
}

bool DeterministicFiniteAutomaton::IsDeterministic()
{
	std::unordered_set<std::pair<std::string, std::string>, custom::hash_pair, custom::MyKeyEqual> seenTransitions;
	for (const auto& element : transitionFunction)
	{
		const auto& pair = element.first;
		if (seenTransitions.find(pair) != seenTransitions.end())
			return false;
		seenTransitions.insert(pair);
	}
	return true;
}

void DeterministicFiniteAutomaton::AddState(const std::string& state)
{
	states.push_back(state);
}

void DeterministicFiniteAutomaton::AddTransitionFunction(const std::string& state1, const std::string& state2, const std::string& transition)
{
	auto element = std::make_pair(std::make_pair(state1, transition), state2);
	transitionFunction.insert(std::move(element));
}

void DeterministicFiniteAutomaton::AddCharacterToThealphabet(const std::string& character)
{
	alphabet.push_back(character);
}

void DeterministicFiniteAutomaton::SetInitialState(const std::string& state)
{
	initialState = state;
}

void DeterministicFiniteAutomaton::AddFinalState(const std::string& state)
{
	finalStates.push_back(state);
}

DeterministicFiniteAutomaton& DeterministicFiniteAutomaton::operator=(const DeterministicFiniteAutomaton& automaton)
{
	if (this != &automaton)
	{
		states = automaton.states;
		alphabet = automaton.alphabet;
		transitionFunction = automaton.transitionFunction;
		initialState = automaton.initialState;
		finalStates = automaton.finalStates;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const DeterministicFiniteAutomaton& automata)
{
	os << "M = ( {";
	for (int index = 0; index < automata.states.size() - 1; index++)
		os << automata.states[index] << ", ";
	os << automata.states[automata.states.size() - 1] << "}, {";
	for (int index = 0; index < automata.alphabet.size() - 1; index++)
		os << automata.alphabet[index] << ", ";
	os << automata.alphabet[automata.alphabet.size() - 1] << "}, delta, " << automata.initialState << ", {";
	for (int index = 0; index < automata.finalStates.size() - 1; index++)
		os << automata.finalStates[index] << ", ";
	os << automata.finalStates[automata.finalStates.size() - 1] << "} )\n";
	os << "Delta este construita asa:\n";
	for (int index = 0; index < automata.alphabet.size(); index++)
		os << "         " << automata.alphabet[index];
	os << "\n";
	for (int stateIndex = 0; stateIndex < automata.states.size(); stateIndex++)
	{
		os << " " << automata.states[stateIndex] << " ";
		for (int inputIndex = 0; inputIndex < automata.alphabet.size(); inputIndex++)
		{
			auto transitions = automata.transitionFunction.equal_range({ automata.states[stateIndex], automata.alphabet[inputIndex] });
			if (transitions.first != automata.transitionFunction.end())
			{
				os << " { ";
				for (auto it = transitions.first; it != transitions.second; it++)
				{
					os << it->second << " ";
				}
				os << "} ";
			}
			else
				os << "   -   ";
		}
		os << "\n";
	}
	return os;
}
