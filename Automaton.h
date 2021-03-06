//Max Blankestijn s1819658 & Loes Dekker s1850024

#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <iostream>
#include <cmath>

typedef std::map<unsigned, bool> BitVector;
typedef int State;

class Automaton {
	public:
		/**
      * Add the given state (an integer) to the automaton
     */
		void addState(const State state);

		/**
      * Add transition with the given label (a bitvector) between State from and State to.
      * If this is the first transition added to the automaton: initialize the field alphabet with all variables
		  * in BitVector label (i.e., the domain of the BitVector map)
     */
		void addTransition(const State from, const BitVector label, const State to);

		/**
      * Mark the given state as an initial state
    */
		void markInitial(const State state);

		/**
      * Mark the given state as a final state
    */
		void markFinal(const State state);

		/**
     * Read the list of bitvectors and move to the next states according to the
     * transitions, starting from the initial states
    */
		void parseInput(const std::list<BitVector> input);

		/**
     * Return whether the current states contain a final state
    */
		bool inFinalState() const;

		/**
     * Compute intersection of automata fa1 and fa2 and store the result in the current automaton
     * (implementation calculates cartesian product of automata)
    */
		void intersect(Automaton& fa1, Automaton& fa2);

    /**
      * Replace every bitvector in the transitions with two new bitvectors that additionally contain the new variable varnr:
      * 1. a transition where variable varnr has value 0
      * 2. a transition where variable varnr has value 1
      * The values for the other variables are unchanged from the original bitvector.
      * Finally, add the given variable to the alphabet.
		  * If the variable was already part of the alphabet: do nothing.
    */
    void addToAlphabet(unsigned varnr);

		/**
      * OPTIONEEL (voor bonus)!!!
      * Compute the complement of the current automaton
      * (for non-deterministic automata: uses makeDeterministic() )
    */
		void complement(Automaton& fa);

		/**
      * OPTIONEEL (voor bonus)!!!
      * Remove the variable with the given index from all transitions of this automaton
    */
		void project(const unsigned variable);

		/**
      * OPTIONEEL (voor bonus)!!!
      * Make automata fa deterministic, eliminate epsilon transitions, and store the result in the current automaton
    */
		void makeDeterministic(Automaton& fa);

   /**
     * Prints the current automaton to the specified stream
   */
		void print(std::ostream &str) const;

		/**
			* contains (PART II)
		  * Returns true when given state is in the set of states of the automaton
			* Param: state: State to check
		**/
		bool contains (State state) const;

		/**
			* addVar (PART II)
		  * Inserts given unsigned to the alphabet of the automaton
			* param: x: unsigned that should be added to the alphabet
			* pre: automaton
			* post: automaton whose alphabet contains the given unsigned
		**/
		void addVar(unsigned x);

		/**
			* insertFreeVars (PART II)
		  * Inserts the unsigneds to the alphabet that are in the alphabet of the
		  given automaton and not in the alphabet of the automaton itself
			* param: fa2: Automaton that has an alphabet
			* pre: automaton exists
			* post: automaton containing all unsigneds in the alphabet of fa2
		**/
		void insertFreeVars(Automaton fa2);

		/**
			* restate
			* Abstract: converts the current automaton to an equivalent one with
				states 0,1..n
			* pre: an automaton exists
			* post: automaton where all states are renamed to 0,1...n
		**/
		void restate();

	private:
		/**
      * Read a single BitVector as input and move from the set of current states to the set of next states
    */
		void next(const BitVector input);

		/**
      * OPTIONEEL (voor bonus)!!!
      * Eliminate epsilon transitions, and store the result in the current automaton
    */
    void eliminateLambda(Automaton& fa);

		/**
			* recLam
			* Abstract:recursive function used by eliminateLambda, used for determining
				if a finalState can be reached through epsilon transitions
			*	parameters: fa: automaton to be reviewed, visited: set of already
				visited states, used to prevent getting stuck in cycles, state: state to
				be reviewed
			* pre: An automaton without free variables (only then it's called)
			* post: True if a final state can be reached else false
			* return: Boolean
		**/
		bool recLam(Automaton& fa, std::set<State>& visited, State state);

    /**
      * Prints the set of states s to the specified stream
    */
 		static void printStates(std::ostream &str, const std::set<State> s);

    /**
      * Prints the BitVector t to the specified stream
    */
    static void printTransitionLabel(std::ostream &str, const BitVector t);

		/**
			* Name: recDet
			* Abstract: Recursive function to make a an Automaton deterministic using the subset
			  construction
			* parameters: fa: automaton to be made deterministic, visited: set of visited states
			  to avoid cycles, newTrans: the transitions of the new deterministic
			  automaton, newState: states one can reach from initial states, Q: a
			  queue containing the states to be visited
			* preconditions: there exists an automaton to be made deterministic and
				one to save de result in
			* postconditions: a deterministic automaton in at the this-pointer
		*/
		void recDet(Automaton fa, std::set<State> &visited,
							std::map<State, std::map<BitVector, std::set<State> > >& newTrans,
							State newState, std::queue<State> &Q);

		/**
			* merge
			* Abstract: combines a set of states into single state
			* parameters: mStates: set of states to be merged
			* pre: a non-empty set of states
			* post: a 'merged' state that can be converted back into the original set
			* return: 'merged' state
		**/
		State merge(std::set<State> mStates, State largest) const;

		/**
			* unmerge
			* Abstract: constructs set of state from a State
			* parameters: state: state to be unmerged, largest: biggest State in then
				automaton,
			* pre: a non-empty set of states
			* post: a 'merged' state that can be converted back into the original set
			* return: 'merged' state
		**/
		std::set<State> unmerge(State state, std::set<State> original) const;

		/**
			* clearAuto
			* Abstract: roept .clear() aan op alle private containers van Automaton
			* pre: existing automaton
			* post: geclearde automaton
		**/
		void clearAuto();

    // the set of all states
		std::set<State> states;

    // the set of initial states
		std::set<State> initialStates;

    // the set of final states
		std::set<State> finalStates;

    // the map containing all transitions of the automton
		std::map<State, std::map<BitVector, std::set<State> > > transitions;

    // the set of current states
		std::set<State> currentStates;

    // the set of variables used in transitions
		std::set<unsigned> alphabet;

};

#endif
