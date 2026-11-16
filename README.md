# Computer Networks Lab (T7482) - Ready-to-Run Practicals

All programs are in C and tested on Ubuntu/Linux with gcc.
(Windows: use WSL, or Ubuntu in the lab. Socket programs use Linux headers.)

## 0. Before you start

Check gcc is installed:
    gcc --version
If missing:
    sudo apt update && sudo apt install gcc -y

Unzip and open a terminal inside the folder:
    unzip CN_Practicals.zip
    cd CN_Practicals

## Folder map

| Folder | Practical | Files |
|---|---|---|
| 1_TCP | TCP socket programming | server.c, client.c |
| 2_UDP | UDP socket programming | udpserver.c, udpclient.c |
| 3_Wireshark_DNS_HTTP | Packet analysis (HTTP + DNS) | STEPS file + screenshots |
| 4_DNS_commands | nslookup / ping / tracert / ipconfig | STEPS file + screenshots |
| 5_Sliding_Window | Sliding window (Go-Back-N) | sliding_window.c |
| 6_Traffic_Shaping | Token bucket + Leaky bucket | token_bucket.c, leaky_bucket.c |
| 7_Distance_Vector | Distance vector routing | distance_vector.c |

---

## 1. TCP (needs TWO terminals)

Terminal 1 (server - start FIRST):
    cd 1_TCP
    gcc server.c -o server
    ./server
-> prints: TCP Echo Server listening on port 10012...

Terminal 2 (client):
    cd 1_TCP
    gcc client.c -o client
    ./client
-> type a message + Enter. Client prints "Echo from server: <message>"; server prints "Received: <message>".
-> Quit: Ctrl+D in the client (server then exits automatically). Ctrl+C also works.

Concept for viva: socket() -> bind() -> listen() -> accept() -> read()/send() (server);
socket() -> connect() -> send()/read() (client). TCP is connection-oriented, reliable.

## 2. UDP (needs TWO terminals)

Terminal 1:
    cd 2_UDP
    gcc udpserver.c -o udpserver
    ./udpserver
-> prints: UDP Echo Server listening on port 10055...

Terminal 2:
    cd 2_UDP
    gcc udpclient.c -o udpclient
    ./udpclient
-> type messages; they are echoed back. Quit client with Ctrl+D; stop server with Ctrl+C.

Concept: socket(SOCK_DGRAM) -> bind() (server) -> recvfrom()/sendto(). Connectionless, no handshake.
NOTE: client and server both use port 10055 (original client had a mismatched port - fixed).

## 3. Wireshark (HTTP + DNS)
Open 3_Wireshark_DNS_HTTP/STEPS_Wireshark_HTTP_DNS.md - follow the steps and take your own
screenshots in the lab. Reference screenshot is in the screenshots/ folder.
Install if needed: sudo apt install wireshark -y   (run as sudo or add user to wireshark group)
Filters to remember: http   dns   tcp   udp   ip.addr == x.x.x.x

## 4. DNS commands
Open 4_DNS_commands/STEPS_DNS_commands.md. Windows commands (cmd): nslookup, ping, tracert, ipconfig /all.
Linux equivalents: nslookup, ping -c 4, traceroute, ip a.

## 5. Sliding Window (Go-Back-N)
    cd 5_Sliding_Window
    gcc sliding_window.c -o sw
    ./sw
Sample input: frames = 7, window size = 2, then answer y at each prompt.
Answer n to see Go-Back-N retransmission ("Resending from frame ...").

## 6. Traffic Shaping
Token bucket:
    cd 6_Traffic_Shaping
    gcc token_bucket.c -o tb
    ./tb
Sample: bucket 10, rate 4, time units 3, packets 3, 6, 7
Expected: sent 3 (left 1) -> sent 5, dropped 1 -> sent 4, dropped 3.

Leaky bucket:
    gcc leaky_bucket.c -o lb
    ./lb
Sample: bucket 10, outgoing rate 4, time units 3, packets 3, 8, 2
Expected: sent 3 (0 left) -> sent 4 (4 left) -> sent 4 (2 left).

Difference: Leaky bucket = constant output rate, smooths bursts, drops on overflow.
Token bucket = allows bursts (up to saved tokens), more flexible.

## 7. Distance Vector
    cd 7_Distance_Vector
    gcc distance_vector.c -o dv
    ./dv
Sample input:
    3
    0 2 7
    2 0 1
    7 1 0
(use 999 for "no direct link")
Expected: node 0 reaches node 2 via node 1 with distance 3 (Next Hop -1 = itself).

---

## Troubleshooting

| Problem | Fix |
|---|---|
| bind: Address already in use | Wait ~30 s, or change PORT in BOTH server and client |
| connect: Connection refused | Server isn't running - start the server first |
| Client hangs in UDP | Server not running or ports differ - both must be 10055 |
| gcc: command not found | sudo apt install gcc |
| Programs are on Windows | Use WSL/Ubuntu; socket code won't compile with plain MinGW |
| Using two PCs | Replace "127.0.0.1" in the client with the server PC's IP (find with ip a / ipconfig) |

## Exam-day checklist
1. Open terminal, cd into the folder. 2. Compile with gcc. 3. Run (server first for TCP/UDP).
4. Take screenshot of code + output. 5. Write Aim / Theory / Code / Output / Conclusion.
