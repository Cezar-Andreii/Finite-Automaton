#pragma once
#include <string>
#include <stack>
#include <vector>
#include "AFD.h"
#include "AF.h"

int Priority(char caracter)
{

	if (caracter == '(' || caracter == ')') return 0;
	else if (caracter == '|') return 1;
	else if (caracter == '.') return 2;
	else if (caracter == '*') return 3;
}

void PolishForm(std::stack<char>& polishForm, std::string expression)
{
	std::stack<char>operations;
	int nr = 0;
	for (char character : expression)
	{
		if (std::isalpha(character))
		{
			polishForm.push(character);
		}
		else
		{
			if (character == '(')
			{
				operations.push(character);
				nr++;
			}
			else
			{
				if (character == ')')
				{
					if (nr < 0)
					{
						while (!polishForm.empty())
						{
							polishForm.pop();
						}
						return;
					}
					nr--;
					while (!(operations.empty()) && (operations.top() != '('))
					{
						polishForm.push(operations.top());
						operations.pop();
					}
					if (!(operations.empty()))
						operations.pop();
				}
				else
				{
					while (!(operations.empty()) &&
						(Priority(operations.top()) >= Priority(character)))
					{
						polishForm.push(operations.top());
						operations.pop();
					}
					operations.push(character);
				}
			}
		}
	}
	while (!(operations.empty()))
	{
		polishForm.push(operations.top());
		operations.pop();
	}
}

std::string CreatePolishForm(std::stack<char>& polishForm)
{
	std::string newExpression;
	char part = polishForm.top();
	while (!(polishForm.empty()))
	{
		newExpression.push_back(part);
		polishForm.pop();
		if (!(polishForm.empty()))
			part = polishForm.top();
	}
	reverse(newExpression.begin(), newExpression.end());
	return newExpression;
}

void TransferAutomaton(FiniteAutomaton automaton, FiniteAutomaton& automaton3)
{
	for (const auto& state : automaton.GetStates())
	{
		automaton3.AddState(state);
	}
	for (const auto& character : automaton.Getalphabet())
	{
		automaton3.AddCharacterToThealphabet(character);
	}
	for (const auto& transition : automaton.GetTransitionFunction())
	{
		automaton3.AddTransitionFunction(transition);
	}
}

void BuildAutomaton(FiniteAutomaton& automaton, const std::string& character, int counter)
{
	std::string state1 = "q" + std::to_string(counter);
	automaton.AddState(state1);
	std::string state2 = "q" + std::to_string(counter + 1);
	automaton.AddState(state2);
	automaton.SetInitialState(state1);
	automaton.SetFinalState(state2);
	automaton.AddCharacterToThealphabet(character);
	automaton.AddTransitionFunction(state1, state2, character);
}

void BuildAutomatonOR(FiniteAutomaton automaton1, FiniteAutomaton automaton2, FiniteAutomaton& automaton3, int counter)
{
	std::string state1 = "q" + std::to_string(counter);
	automaton3.AddState(state1);
	automaton3.SetInitialState(state1);
	std::string state2 = "q" + std::to_string(counter + 1);
	automaton3.AddState(state2);
	automaton3.SetFinalState(state2);

	TransferAutomaton(automaton1, automaton3);
	TransferAutomaton(automaton2, automaton3);

	automaton3.AddTransitionFunction(state1, automaton1.GetInitialState(), "&");
	automaton3.AddTransitionFunction(state1, automaton2.GetInitialState(), "&");
	automaton3.AddTransitionFunction(automaton1.GetFinalState(), state2, "&");
	automaton3.AddTransitionFunction(automaton2.GetFinalState(), state2, "&");
	automaton3.AddCharacterToThealphabet("&");
}

void BuildAutomatonConcatenation(FiniteAutomaton automaton1, FiniteAutomaton automaton2, FiniteAutomaton& automaton3)
{
	automaton3.SetInitialState(automaton1.GetInitialState());
	automaton3.SetFinalState(automaton2.GetFinalState());

	for (const auto& state : automaton1.GetStates())
	{
		if (state != automaton1.GetFinalState())
			automaton3.AddState(state);
	}
	for (const auto& state : automaton2.GetStates())
	{
		if (state != automaton2.GetInitialState())
			automaton3.AddState(state);
	}

	std::string newState = automaton1.GetFinalState() + automaton2.GetInitialState();
	automaton3.AddState(newState);

	for (const auto& character : automaton1.Getalphabet())
	{
		automaton3.AddCharacterToThealphabet(character);
	}
	for (const auto& character : automaton2.Getalphabet())
	{
		automaton3.AddCharacterToThealphabet(character);
	}

	for (const auto& transition : automaton1.GetTransitionFunction())
	{
		if (transition.second != automaton1.GetFinalState())
			automaton3.AddTransitionFunction(transition);
		else
			automaton3.AddTransitionFunction(transition.first.first, newState, transition.first.second);
	}
	for (const auto& transition : automaton2.GetTransitionFunction())
	{
		if (transition.first.first != automaton2.GetInitialState())
			automaton3.AddTransitionFunction(transition);
		else
			automaton3.AddTransitionFunction(newState, transition.second, transition.first.second);
	}
}

void BuildAutomatonStar(FiniteAutomaton automaton1, FiniteAutomaton& automaton3, int counter)
{
	std::string state1 = "q" + std::to_string(counter);
	automaton3.AddState(state1);
	automaton3.SetInitialState(state1);
	std::string state2 = "q" + std::to_string(counter + 1);
	automaton3.AddState(state2);
	automaton3.SetFinalState(state2);

	TransferAutomaton(automaton1, automaton3);
	automaton3.AddTransitionFunction(state1, automaton1.GetInitialState(), "&");
	automaton3.AddTransitionFunction(state1, state2, "&");
	automaton3.AddTransitionFunction(automaton1.GetFinalState(), automaton1.GetInitialState(), "&");
	automaton3.AddTransitionFunction(automaton1.GetFinalState(), state2, "&");
	automaton3.AddCharacterToThealphabet("&");
}

FiniteAutomaton ExpressionEvaluation(std::string expression)
{
	std::stack<FiniteAutomaton> StacksOfAutomatons;
	int counter = 0;
	for (int index = 0; index < expression.size(); index++)
	{
		if (std::isalpha(expression[index]))
		{
			FiniteAutomaton automaton;
			BuildAutomaton(automaton, std::string(1, expression[index]), counter);
			StacksOfAutomatons.push(automaton);
			counter = counter + 2;
		}
		else if (expression[index] == '|')
		{
			FiniteAutomaton automaton1, automaton2, automaton3;
			automaton2 = StacksOfAutomatons.top();
			StacksOfAutomatons.pop();
			automaton1 = StacksOfAutomatons.top();
			StacksOfAutomatons.pop();
			BuildAutomatonOR(automaton1, automaton2, automaton3, counter);
			StacksOfAutomatons.push(automaton3);
			counter = counter + 2;
		}
		else if (expression[index] == '.')
		{
			FiniteAutomaton automaton1, automaton2, automaton3;
			automaton2 = StacksOfAutomatons.top();
			StacksOfAutomatons.pop();
			automaton1 = StacksOfAutomatons.top();
			StacksOfAutomatons.pop();
			BuildAutomatonConcatenation(automaton1, automaton2, automaton3);
			StacksOfAutomatons.push(automaton3);
		}
		else if (expression[index] == '*')
		{
			FiniteAutomaton automaton1, automaton3;
			automaton1 = StacksOfAutomatons.top();
			StacksOfAutomatons.pop();
			BuildAutomatonStar(automaton1, automaton3, counter);
			counter = counter + 2;
			StacksOfAutomatons.push(automaton3);
		}
	}
	return StacksOfAutomatons.top();
}

void InitializationNewClosingSet(std::vector<std::vector<std::string>>& closingSets, FiniteAutomaton automaton)
{
	std::vector<std::string> currentStates = { automaton.GetInitialState() };
	std::vector<std::string> nextStates;
	std::vector<std::string> states = { automaton.GetInitialState() };
	while (1)
	{
		bool foundNewStates = false;
		for (const auto& currentState : currentStates)
		{
			std::pair<std::string, std::string> currentTransition = std::make_pair(currentState, "&");
			std::unordered_multimap<std::pair<std::string, std::string>, std::string, custom::hash_pair, custom::MyKeyEqual> transitionFunction = automaton.GetTransitionFunction();
			auto transitions = transitionFunction.equal_range(currentTransition);
			for (auto it = transitions.first; it != transitions.second; it++)
			{
				nextStates.push_back(it->second);
			}
			if (!nextStates.empty())
			{
				for (const auto& newState : nextStates)
				{
					if (std::find(states.begin(), states.end(), newState) == states.end())
					{
						states.push_back(newState);
						foundNewStates = true;
					}
				}
				currentStates = nextStates;
				nextStates.clear();
			}
		}
		if (!foundNewStates)
		{
			break;
		}
	}
	closingSets.push_back(states);
	states.clear();
}

std::vector<std::string> GenerateNewClosure(FiniteAutomaton automaton, std::vector<std::string> currentClosure, std::string character)
{
	std::vector<std::string> newClosure;
	for (const auto& currentState : currentClosure)
	{
		std::pair<std::string, std::string> currentTransition = std::make_pair(currentState, character);
		std::unordered_multimap<std::pair<std::string, std::string>, std::string, custom::hash_pair, custom::MyKeyEqual> transitionFunction = automaton.GetTransitionFunction();
		auto transitions = transitionFunction.equal_range(currentTransition);
		for (auto it = transitions.first; it != transitions.second; it++)
		{
			newClosure.push_back(it->second);
		}
	}
	std::sort(newClosure.begin(), newClosure.end());
	newClosure.erase(std::unique(newClosure.begin(), newClosure.end()), newClosure.end());
	return newClosure;
}

std::vector<std::string> GenerateClosingSet(FiniteAutomaton automaton, std::vector<std::string> currentClosure)
{
	std::vector<std::string> newClosure;
	for (const auto& currentState : currentClosure)
	{
		std::vector<std::string> currentStates = { currentState };
		std::vector<std::string> nextStates;
		std::vector<std::string> states = { currentState };
		while (1)
		{
			bool foundNewStates = false;
			for (const auto& currentState : currentStates)
			{
				std::pair<std::string, std::string> currentTransition = std::make_pair(currentState, "&");
				std::unordered_multimap<std::pair<std::string, std::string>, std::string, custom::hash_pair, custom::MyKeyEqual> transitionFunction = automaton.GetTransitionFunction();
				auto transitions = transitionFunction.equal_range(currentTransition);
				for (auto it = transitions.first; it != transitions.second; it++)
				{
					nextStates.push_back(it->second);
				}
				if (!nextStates.empty())
				{
					for (const auto& newState : nextStates)
					{
						if (std::find(states.begin(), states.end(), newState) == states.end())
						{
							states.push_back(newState);
							foundNewStates = true;
						}
					}
					currentStates = nextStates;
					nextStates.clear();
				}
			}
			if (!foundNewStates)
			{
				break;
			}
		}
		newClosure.insert(newClosure.end(), states.begin(), states.end());
	}
	std::sort(newClosure.begin(), newClosure.end());
	newClosure.erase(std::unique(newClosure.begin(), newClosure.end()), newClosure.end());
	return newClosure;
}

void SetFinalState(DeterministicFiniteAutomaton& automatonAFD, std::vector<std::vector<std::string>> closingSets, FiniteAutomaton automaton)
{
	std::string finalState = automaton.GetFinalState();
	std::vector<int> finalStates;
	for (int index = 0; index < closingSets.size(); index++)
	{
		const auto& currentStateVector = closingSets[index];
		auto it = std::find(currentStateVector.begin(), currentStateVector.end(), finalState);
		if (it != currentStateVector.end())
		{
			finalStates.push_back(index);
		}
	}
	for (int index = 0; index < finalStates.size(); index++)
	{
		automatonAFD.AddFinalState("q'" + std::to_string(finalStates[index]));
	}
}

DeterministicFiniteAutomaton ConvertToAFD(FiniteAutomaton automaton)
{
	DeterministicFiniteAutomaton automatonAFD;
	std::vector<std::vector<std::string>> closingSets;
	InitializationNewClosingSet(closingSets, automaton);
	int counter = 0;
	std::vector<std::string> newClosure, newClosingSet;
	automatonAFD.AddState("q'" + std::to_string(counter));
	automatonAFD.SetInitialState("q'" + std::to_string(counter));
	for (int index = 0; index < closingSets.size(); index++)
	{
		auto currentSet = closingSets[index];
		for (const auto& character : automaton.Getalphabet())
		{
			if (character != "&")
			{
				newClosure = GenerateNewClosure(automaton, currentSet, character);
				if (!newClosure.empty())
				{
					newClosingSet = GenerateClosingSet(automaton, newClosure);
					auto it2 = std::find(closingSets.begin(), closingSets.end(), newClosingSet);
					auto it3 = std::find(closingSets.begin(), closingSets.end(), currentSet);
					int jndex = std::distance(closingSets.begin(), it3);
					if (it2 == closingSets.end())
					{
						closingSets.push_back(newClosingSet);
						counter++;
						automatonAFD.AddState("q'" + std::to_string(counter));
						automatonAFD.AddTransitionFunction("q'" + std::to_string(jndex), "q'" + std::to_string(counter), character);
					}
					else
					{
						int index = std::distance(closingSets.begin(), it2);
						automatonAFD.AddTransitionFunction("q'" + std::to_string(jndex), "q'" + std::to_string(index), character);
					}

				}
			}
		}
	}

	SetFinalState(automatonAFD, closingSets, automaton);
	for (const auto& character : automaton.Getalphabet())
	{
		if (character != "&")
		{
			automatonAFD.AddCharacterToThealphabet(character);
		}
	}
	return automatonAFD;
}