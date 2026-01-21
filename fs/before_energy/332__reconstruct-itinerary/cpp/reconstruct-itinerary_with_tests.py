# Time:  O(|V| + |E|log|V|)
# Space: O(|V| + |E|)

# Hierholzer Algorithm
import collections


class Solution(object):
    def findItinerary(self, tickets):
        """
        :type tickets: List[List[str]]
        :rtype: List[str]
        """
        adj = collections.defaultdict(list)
        for ticket in tickets:
            adj[ticket[0]].append(ticket[1])
        for x in adj.itervalues():
            x.sort(reverse=True)
        origin = "JFK"
        result = []
        stk = [origin]
        while stk:
            while adj[stk[-1]]: 
                stk.append(adj[stk[-1]].pop())
            result.append(stk.pop())
        result.reverse()
        return result


# Time:  O(t! / (n1! * n2! * ... nk!)), t is the total number of tickets,
#                                       ni is the number of the ticket which from is city i,
#                                       k is the total number of cities.
# Space: O(t)
import collections


class Solution2(object):
    def findItinerary(self, tickets):
        """
        :type tickets: List[List[str]]
        :rtype: List[str]
        """
        def route_helper(origin, ticket_cnt, graph, ans):
            if ticket_cnt == 0:
                return True

            for i, (dest, valid)  in enumerate(graph[origin]):
                if valid:
                    graph[origin][i][1] = False
                    ans.append(dest)
                    if route_helper(dest, ticket_cnt - 1, graph, ans):
                        return ans
                    ans.pop()
                    graph[origin][i][1] = True
            return False

        graph = collections.defaultdict(list)
        for ticket in tickets:
            graph[ticket[0]].append([ticket[1], True])
        for k in graph.keys():
            graph[k].sort()

        origin = "JFK"
        ans = [origin]
        route_helper(origin, len(tickets), graph, ans)
        return ans


if __name__ == "__main__":
    import time

    t1 = [
        ["MUC","LHR"], ["JFK","MUC"], ["SFO","SJC"], ["LHR","SFO"]
    ]
    t2 = [
        ["JFK","KUL"], ["JFK","NRT"], ["NRT","JFK"]
    ]
    t3 = [
        ["JFK","SFO"], ["JFK","ATL"], ["SFO","ATL"], ["ATL","JFK"], ["ATL","SFO"]
    ]
    t4 = [
        ["JFK","A"], ["JFK","A"], ["A","JFK"]
    ]
    t5 = [
        ["JFK","A"], ["A","B"], ["B","C"], ["C","D"], ["D","E"]
    ]
    t6 = [
        ["JFK","A"], ["A","A"], ["A","JFK"]
    ]
    t7 = [
        ["JFK","BBB"], ["JFK","AAA"], ["AAA","JFK"], ["BBB","AAA"]
    ]
    t8 = [
        ["JFK","A"], ["JFK","B"], ["A","C"], ["C","A"], ["B","C"], ["C","JFK"]
    ]
    t9 = [
        ["JFK","SFO"], ["JFK","SFO"], ["SFO","JFK"], ["SFO","LAX"], ["LAX","JFK"]
    ]
    t10 = [
        ["JFK","A"], ["A","JFK"], ["JFK","B"], ["B","C"], ["C","JFK"],
        ["JFK","D"], ["D","E"], ["E","F"], ["F","JFK"]
    ]

    tests = [t1, t2, t3, t4, t5, t6, t7, t8, t9, t10]

    checksum = 0
    start = time.time()

    iterations = 1000
    sol = Solution()
    MASK = 0xFFFFFFFFFFFFFFFF
    for _ in xrange(iterations):
        for tickets in tests:
            # pass a shallow copy of tickets to avoid in-place mutation across iterations
            res = sol.findItinerary([list(p) for p in tickets])
            for s in res:
                for ch in s:
                    checksum = (checksum * 1315423911) ^ ord(ch)
                    checksum &= MASK
                checksum ^= len(s)
                checksum &= MASK
            checksum ^= len(res)
            checksum &= MASK

    end = time.time()
    us = int(round((end - start) * 1000000.0))

    print "Checksum:", checksum
    print "Elapsed time (microseconds):", us