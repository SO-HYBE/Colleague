# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util


class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return [s, s, w, s, w, w, s, w]


def depthFirstSearch(problem):
    """
    Iterative Deepening Depth-First Search (IDDFS) for the CS188 Pacman project.
    Repeatedly performs depth-limited DFS with increasing depth limits until
    the goal state is found.
    """
    from util import Stack

    def depth_limited_dfs(limit):
        """
        Perform DFS but do not expand nodes deeper than <limit>.
        Returns the action path if a goal is found, otherwise None.
        """
        stack = Stack()
        # (state, path, depth)
        stack.push((problem.getStartState(), [], 0))

        # Maintain a visited set per depth iteration (standard IDDFS behavior)
        visited = set()

        while not stack.isEmpty():
            state, path, depth = stack.pop()

            if (state, depth) in visited:
                continue
            visited.add((state, depth))

            # Goal test
            if problem.isGoalState(state):
                return path

            # Do not expand beyond the depth limit
            if depth == limit:
                continue

            # Expand successors
            for successor, action, cost in problem.getSuccessors(state):
                stack.push((successor, path + [action], depth + 1))

        return None  # No solution within this depth

    # Iterative deepening loop
    MAX_DEPTH = 1000  # More than enough for all Pacman layouts
    for limit in range(MAX_DEPTH):
        result = depth_limited_dfs(limit)
        if result is not None:
            return result

    # If nothing is found (should not happen in valid layouts)
    return []


"""
Time and Space Complexity of IDDFS:
----------------------------------
Let b = branching factor, and d = depth of the shallowest goal.

Time Complexity:
    O(b^d)
IDDFS runs DFS repeatedly, increasing the limit each time. Although it re-expands
upper-level nodes many times, the majority of work occurs only at the deepest
level, making its cost asymptotically the same as BFS.

Space Complexity:
    O(b * d)
Only a single DFS branch and the recursion stack (simulated with an explicit stack)
are stored at a time. This is dramatically smaller than BFS (O(b^d)).

Behavior in Pacman:
    IDDFS behaves like a memory-efficient version of BFS. It guarantees finding
    the shallowest goal (optimal in number of actions) while using far less memory.
    It repeatedly performs depth-limited DFS searches over the maze until the depth
    limit is large enough to reach the goal.
"""


def breadthFirstSearch(problem: SearchProblem):
    """Search the shallowest nodes in the search tree first."""
    from util import Queue

    queue = Queue()
    start = problem.getStartState()
    queue.push((start, []))
    visited = {start}

    while not queue.isEmpty():
        state, path = queue.pop()

        if problem.isGoalState(state):
            return path

        for successor, action, _ in problem.getSuccessors(state):
            if successor not in visited:
                visited.add(successor)
                queue.push((successor, path + [action]))

    return []
    util.raiseNotDefined()


def uniformCostSearch(problem: SearchProblem):
    """Search the node of least total cost first."""
    from util import PriorityQueue

    pq = PriorityQueue()
    start = problem.getStartState()
    # Priority Queue stores: (state, path_to_state, cumulative_cost)
    pq.push((start, [], 0), 0)
    # Visited tracks the minimum cost found so far to reach a state: {state: min_cost}
    visited = {}

    while not pq.isEmpty():
        state, path, cost = pq.pop()

        # Pruning check: If we've found a better (or equal) path already, skip this one.
        if state in visited and visited[state] <= cost:
            continue

        # Record the cost for the current state (this is the cheapest path found so far)
        visited[state] = cost

        if problem.isGoalState(state):
            return path

        for successor, action, stepCost in problem.getSuccessors(state):
            newPath = path + [action]
            newCost = problem.getCostOfActions(newPath)

            # Re-check the visited condition for the successor:
            if successor not in visited or newCost < visited[successor]:
                # No need to update visited here, as it will be updated when the item
                # is popped from the PQ and passes the pruning check at the top of the loop.
                # However, for efficiency, some implementations update it here.
                # The crucial step is pushing the new item with its new priority.
                pq.push((successor, newPath, newCost), newCost)

    return []
    util.raiseNotDefined()


def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0


def aStarSearch(problem: SearchProblem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    import util
    frontier = util.PriorityQueue()
    start_state = problem.getStartState()
    start_node = (start_state, [], 0)
    start_priority = 0 + heuristic(start_state, problem)
    frontier.push(start_node, start_priority)
    explored_states = set()
    while not frontier.isEmpty():
        state, actions, path_cost = frontier.pop()
        if problem.isGoalState(state):
            return actions
        if state not in explored_states:
            explored_states.add(state)
            for next_state, action, step_cost in problem.getSuccessors(state):
                new_actions = actions + [action]
                new_path_cost = path_cost + step_cost
                new_priority = new_path_cost + heuristic(next_state, problem)
                new_node = (next_state, new_actions, new_path_cost)
                frontier.push(new_node, new_priority)
    return []
    util.raiseNotDefined()


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
