# Practical 4: DNS commands + packet analysis

Screenshots: `screenshots/nslookup_with_wireshark_dns_filter.png`, `screenshots/ping_tracert_ipconfig.png`

## COMMANDS (run in Command Prompt / PowerShell) - take a screenshot of each
```
nslookup www.github.com        -> DNS server used + resolved IP (e.g. 20.207.73.82), "Non-authoritative answer"
nslookup -type=MX gmail.com    -> mail servers
nslookup -type=NS google.com   -> name servers
ping 20.207.73.82              -> reachability, RTT, TTL
tracert 20.207.73.82           -> hop-by-hop route ('*' = router didn't reply)
ipconfig /all                  -> host name, MAC (Physical Address), IP, DHCP, DNS server
ipconfig /flushdns             -> clear DNS cache
```
(Linux/Ubuntu equivalents: `nslookup`, `dig`, `ping -c 4`, `traceroute`, `ip a`/`ifconfig`)

## WIRESHARK STEPS (DNS)
1. Start Wireshark capture on active interface.
2. Run `nslookup www.github.com` in terminal.
3. Filter: `dns`. Find "Standard query A www.github.com" and its response.
4. Note: Source IP (client) -> Destination IP (DNS server 10.17.28.42), UDP, port 53, Query type A/AAAA, Answer IP.

## OBSERVATIONS
- DNS server: 10.17.28.42, UDP port 53
- www.github.com is an alias (CNAME) of github.com -> 20.207.73.82
- Non-authoritative answer = came from a cache, not the domain's own name server
- ping: 4 sent, 4 received, 0% loss, TTL=115, avg 127 ms
- tracert: 16 hops; hops 9-15 timed out (firewalls blocking ICMP) but destination reached

## CONCLUSION
DNS resolves domain names to IP addresses over UDP port 53; ping/tracert/ipconfig help diagnose connectivity.
