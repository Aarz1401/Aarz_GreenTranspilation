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
    tests = [
        [["MUC","LHR"], ["JFK","MUC"], ["SFO","SJC"], ["LHR","SFO"]],
        [["JFK","KUL"], ["JFK","NRT"], ["NRT","JFK"]],
        [["JFK","AAA"], ["JFK","AAA"], ["AAA","JFK"]],
        [["JFK","ATL"], ["ATL","SFO"], ["SFO","JFK"]],
        [["JFK","SFO"], ["JFK","ATL"], ["SFO","ATL"], ["ATL","JFK"], ["ATL","SFO"]],
        [["JFK","AAA"], ["JFK","BBB"], ["AAA","CCC"], ["CCC","JFK"], ["BBB","DDD"], ["DDD","EEE"]],
        [["JFK","AAB"], ["JFK","AAA"], ["AAA","JFK"], ["AAB","AAA"]],
        [["JFK","LAX"], ["JFK","LAX"], ["LAX","JFK"], ["LAX","SFO"], ["SFO","LAX"]],
        [["JFK","AAA"], ["AAA","BBB"], ["BBB","AAA"], ["AAA","JFK"], ["JFK","CCC"], ["CCC","DDD"], ["DDD","JFK"], ["CCC","EEE"], ["EEE","CCC"]],
        [["JFK","MUC"], ["JFK","LHR"], ["LHR","MUC"], ["MUC","SFO"], ["SFO","ATL"], ["ATL","JFK"]]
    ]

    sol = Solution()

    iterations = 1
    sink = 0
    for iter in xrange(iterations):
        checksum = 0
        for tickets in tests:
            res = sol.findItinerary(tickets)
            checksum += len(res)
            if res:
                checksum += ord(res[0][0])
                checksum += ord(res[-1][0])
        sink += checksum
    print(sink)
    # print sink