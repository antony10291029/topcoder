# -*- coding: utf-8 -*-
import math,string,itertools,fractions,heapq,collections,re,array,bisect
def rl(s): return xrange(len(s))

class SuccessfulMerger:
    def minimumMergers(self, road):
        road = list(road)
        N = len(road)
        al = [set([road[i]]) for i in rl(road)]
        for i, nei in enumerate(road):
            al[nei].add(i)

        loop = getloop(al)
        nleaves = 0
        for neis in al:
            if len(neis) == 1:
                nleaves += 1
        if loop is None:
            if 2 == N:
                return 0
            return N - nleaves - 1
        if len(loop) == len(road):
            return N - 2
        nloopbeads = 0
        for i,k in enumerate(loop):
            if len(al[k]) == 2:
                nloopbeads += 1
        final = nleaves + 1
        if nloopbeads >= 1:
            final += 1
        return N - final

def getloop(al):
    visited = [False] * len(al)
    parents = [None] * len(al)
    return dfs(al, 0, visited, parents)
def dfs(al, here, visited, parents):
    visited[here] = True;
    for nei in al[here]:
        if parents[here] == nei:
            continue
        if visited[nei]:
            loop = [here]
            while loop[-1] != nei:
                loop.append(parents[loop[-1]])
            return loop
        parents[nei] = here
        sub = dfs(al, nei, visited, parents)
        if sub is not None:
            return sub

# CUT begin
# TEST CODE FOR PYTHON {{{
import sys, time, math

def tc_equal(expected, received):
    try:
        _t = type(expected)
        received = _t(received)
        if _t == list or _t == tuple:
            if len(expected) != len(received): return False
            return all(tc_equal(e, r) for (e, r) in zip(expected, received))
        elif _t == float:
            eps = 1e-9
            d = abs(received - expected)
            return not math.isnan(received) and not math.isnan(expected) and d <= eps * max(1.0, abs(expected))
        else:
            return expected == received
    except:
        return False

def pretty_str(x):
    if type(x) == str:
        return '"%s"' % x
    elif type(x) == tuple:
        return '(%s)' % (','.join( (pretty_str(y) for y in x) ) )
    else:
        return str(x)

def do_test(road, __expected):
    startTime = time.time()
    instance = SuccessfulMerger()
    exception = None
    try:
        __result = instance.minimumMergers(road);
    except:
        import traceback
        exception = traceback.format_exc()
    elapsed = time.time() - startTime   # in sec

    if exception is not None:
        sys.stdout.write("RUNTIME ERROR: \n")
        sys.stdout.write(exception + "\n")
        return 0

    if tc_equal(__expected, __result):
        sys.stdout.write("PASSED! " + ("(%.3f seconds)" % elapsed) + "\n")
        return 1
    else:
        sys.stdout.write("FAILED! " + ("(%.3f seconds)" % elapsed) + "\n")
        sys.stdout.write("           Expected: " + pretty_str(__expected) + "\n")
        sys.stdout.write("           Received: " + pretty_str(__result) + "\n")
        return 0

def run_tests():
    sys.stdout.write("SuccessfulMerger (450 Points)\n\n")

    passed = cases = 0
    case_set = set()
    for arg in sys.argv[1:]:
        case_set.add(int(arg))

    with open("SuccessfulMerger.sample", "r") as f:
        while True:
            label = f.readline()
            if not label.startswith("--"): break

            road = []
            for i in range(0, int(f.readline())):
                road.append(int(f.readline().rstrip()))
            road = tuple(road)
            f.readline()
            __answer = int(f.readline().rstrip())

            cases += 1
            if len(case_set) > 0 and (cases - 1) in case_set: continue
            sys.stdout.write("  Testcase #%d ... " % (cases - 1))
            passed += do_test(road, __answer)

    sys.stdout.write("\nPassed : %d / %d cases\n" % (passed, cases))

    T = time.time() - 1470527993
    PT, TT = (T / 60.0, 75.0)
    points = 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
    sys.stdout.write("Time   : %d minutes %d secs\n" % (int(T/60), T%60))
    sys.stdout.write("Score  : %.2f points\n" % points)

if __name__ == '__main__':
    run_tests()

# }}}
# CUT end
