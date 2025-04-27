def solve():
    import sys
    data = sys.stdin.read().split()
    if not data:
        return
    t = int(data[0])
    pos = 1
    out_lines = []
    for _ in range(t):
        n = int(data[pos]); m = int(data[pos+1])
        pos += 2
        nm = n * m
        S = nm * (nm + 1) // 2
        best_sol = None
        if m >= 2:
            def F(x):
                return n * (x - 1) * (m * (n - 1) + x)
            def diffV(x):
                return abs(F(x) - S)
            lo, hi = 2, m
            cand = None
            while lo <= hi:
                mid = (lo + hi) // 2
                if F(mid) <= S:
                    cand = mid
                    lo = mid + 1
                else:
                    hi = mid - 1
            candidates = set()
            if cand is not None:
                candidates.add(cand)
                if cand + 1 <= m:
                    candidates.add(cand + 1)
                if cand - 1 >= 2:
                    candidates.add(cand - 1)
            best_v = None
            best_v_diff = None
            for x in candidates:
                d = diffV(x)
                if best_v is None or d < best_v_diff or (d == best_v_diff and x < best_v):
                    best_v = x
                    best_v_diff = d
            best_sol = ('V', best_v, best_v_diff)
        if n >= 2:
            def G(y):
                return (y - 1) * (m * m * (y - 2) + m * (m + 1))
            def diffH(y):
                return abs(G(y) - S)
            lo, hi = 2, n
            cand = None
            while lo <= hi:
                mid = (lo + hi) // 2
                if G(mid) <= S:
                    cand = mid
                    lo = mid + 1
                else:
                    hi = mid - 1
            candidates = set()
            if cand is not None:
                candidates.add(cand)
                if cand + 1 <= n:
                    candidates.add(cand + 1)
                if cand - 1 >= 2:
                    candidates.add(cand - 1)
            best_h = None
            best_h_diff = None
            for y in candidates:
                d = diffH(y)
                if best_h is None or d < best_h_diff or (d == best_h_diff and y < best_h):
                    best_h = y
                    best_h_diff = d
            if best_sol is None:
                best_sol = ('H', best_h, best_h_diff)
            else:
                if best_h_diff < best_sol[2]:
                    best_sol = ('H', best_h, best_h_diff)
                elif best_h_diff == best_sol[2]:
                    if best_sol[0] == 'V':
                        pass
                    else:
                        if best_h < best_sol[1]:
                            best_sol = ('H', best_h, best_h_diff)
        orient, cut, _ = best_sol
        out_lines.append(f"{orient} {cut}")
    sys.stdout.write("\n".join(out_lines))
    
if __name__ == '__main__':
    solve()
