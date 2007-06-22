/**
 * \brief Solve an instance of the "Variable Placement with Separation
 * Constraints" problem.
 *
 * Authors:
 *   Tim Dwyer <tgdwyer@gmail.com>
 *
 * Copyright (C) 2005 Authors
 *
 * Released under GNU LGPL.  Read the file 'COPYING' for more information.
 */

//
// TODO: Really, we should have three classes: VPSC, IncrementalVPSC and
// StaticVPSC, where the latter two inherit from VPSC.  StaticVPSC would be
// the equivalent of what is currently VPSC.
// Also, a lot of the code specific to one or other of these concrete
// implementations should be moved from Block and Blocks: e.g. mergeLeft etc.
//
#ifndef SEEN_LIBVPSC_SOLVE_VPSC_H
#define SEEN_LIBVPSC_SOLVE_VPSC_H

#include <vector>
#include "exceptions.h"

namespace vpsc {
class Variable;
class Constraint;
class Blocks;
typedef std::vector<Constraint*> Constraints;

/**
 * Variable Placement with Separation Constraints problem instance
 */
class Solver {
public:
	// the following two methods both attempt to solve a least-squares
	// problem subject to a set of sepation constraints.  They return
	// true if any constraints are active, in both cases false means
	// an unconstrained optimum has been found.
	// satisfy returns an approximate solution subject to the constraints
	virtual bool satisfy();
	// solve returns an optimum solution subject to the constraints
	virtual bool solve();

	Solver(const unsigned n, Variable* const vs[], const unsigned m, Constraint *cs[]);
	virtual ~Solver();
	Constraint** getConstraints(unsigned &m) { m=this->m; return cs; }
	const Variable* const * getVariables(unsigned &n) { n=this->n; return vs; }
protected:
	Blocks *bs;
	unsigned m;
	Constraint **cs;
	unsigned n;
	const Variable* const *vs;
	void printBlocks();
private:
	void refine();
	bool constraintGraphIsCyclic(const unsigned n, Variable* const vs[]);
	bool blockGraphIsCyclic();
};

class IncSolver : public Solver {
public:
	unsigned splitCnt;
	bool satisfy();
	bool solve();
	void moveBlocks();
	void splitBlocks();
	IncSolver(const unsigned n, Variable* const vs[], const unsigned m, Constraint *cs[]);
private:
	Constraints inactive;
	Constraints violated;
	Constraint* mostViolated(Constraints &l);
};
}
#endif // SEEN_LIBVPSC_SOLVE_VPSC_H
