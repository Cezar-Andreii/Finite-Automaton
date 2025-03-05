#include "AF.h"

void FiniteAutomaton::AddTransitionFunction(const std::string& state1, const std::string& state2, const std::string& transition)
{
    auto element = std::make_pair(std::make_pair(state1, transition), state2);
    transitionFunction.insert(std::move(element));
}

void FiniteAutomaton::AddTransitionFunction(const std::pair<std::pair<std::string, std::string>, std::string>& transition)
{
    transitionFunction.insert(transition);
}

void FiniteAutomaton::AddCharacterToThealphabet(const std::string& character)
{
    alphabet.insert(character);
}

void FiniteAutomaton::AddState(const std::string& state)
{
    states.push_back(state);
}

void FiniteAutomaton::SetInitialState(const std::string& state)
{
    initialState = state;
}

void FiniteAutomaton::SetFinalState(const std::string& state)
{
    finalState = state;
}

std::vector<std::string> FiniteAutomaton::GetStates()
{
    return states;
}

std::unordered_set<std::string> FiniteAutomaton::Getalphabet()
{
    return alphabet;
}

std::unordered_multimap<std::pair<std::string, std::string>, std::string, custom::hash_pair, custom::MyKeyEqual> FiniteAutomaton::GetTransitionFunction()
{
    return transitionFunction;
}

std::string FiniteAutomaton::GetInitialState()
{
    return initialState;
}

std::string FiniteAutomaton::GetFinalState()
{
    return finalState;
}

FiniteAutomaton& FiniteAutomaton::operator=(const FiniteAutomaton& automaton)
{
    if (this != &automaton)
    {
        states = automaton.states;
        alphabet = automaton.alphabet;
        transitionFunction = automaton.transitionFunction;
        initialState = automaton.initialState;
        finalState = automaton.finalState;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const FiniteAutomaton& automata)
{
    os << "M = ( {";
    for (int index = 0; index < automata.states.size() - 1; index++)
        os << automata.states[index] << ", ";
    os << automata.states[automata.states.size() - 1] << "}, {";
    auto it = automata.alphabet.begin();
    for (; it != std::prev(automata.alphabet.end()); it++)
    {
        os << *it << ", ";
    }
    os << *it << "}, delta, " << automata.initialState << ", ";
    os << automata.finalState << " )\n";
    os << "Delta este construita asa:\n";
    it = automata.alphabet.begin();
    for (; it != automata.alphabet.end(); it++)
    {
        os << "      " << *it;
    }
    os << "\n";
    for (int stateIndex = 0; stateIndex < automata.states.size(); stateIndex++)
    {
        os << " " << automata.states[stateIndex] << " ";
        for (const auto& inputSymbol : automata.alphabet)
        {
            auto transitions = automata.transitionFunction.equal_range({ automata.states[stateIndex], inputSymbol });
            if (transitions.first != automata.transitionFunction.end())
            {
                os << " {";
                auto it = transitions.first;
                for (; it != std::prev(transitions.second); it++)
                {
                    os << it->second << ", ";
                }
                os << it->second << "} ";
            }
            else
                os << "   -   ";
        }
        os << "\n";
    }
    return os;
}
