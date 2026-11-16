# Practical 2: Packet Analysis using Wireshark (HTTP + DNS)

Your reference screenshots: `screenshots/wireshark_http_and_dns_reference.png`
(Top: HTTP packet 33064 - GET/200 OK for connecttest.txt. Bottom: DNS response for beacons.gcp.gvt2.com)

## AIM
Capture and analyse Application Layer packets (HTTP and DNS) using Wireshark.

## STEPS - HTTP
1. Open **Wireshark** -> double-click your active interface (Ethernet / Wi-Fi). Capture starts. (Screenshot 1: interface list)
2. Open a browser and visit a plain **http://** site, e.g. `http://www.msftconnecttest.com/connecttest.txt`
   (HTTPS pages are encrypted - you won't see the HTTP content).
3. Type `http` in the display filter bar -> press Enter. (Screenshot 2: filtered list)
4. Click the **GET /connecttest.txt HTTP/1.1** packet, then the **HTTP/1.1 200 OK** reply.
5. In the middle "Packet Details" pane expand:
   - **Frame** -> size in bytes
   - **Ethernet II** -> source/destination MAC
   - **Internet Protocol v4** -> source/destination IP, TTL, Protocol = TCP (6)
   - **Transmission Control Protocol** -> src/dst port (80), Seq, Ack, Flags (PSH, ACK), Window
   - **Hypertext Transfer Protocol** -> Request Method (GET), Request URI, Host, Status Code 200, Content-Type, Content-Length
   (Screenshot 3: expanded details)
6. Optional: right-click packet -> **Follow -> TCP Stream** to see the full request/response text.

## STEPS - DNS
1. Keep capture running. Open Command Prompt and run: `nslookup www.github.com`
2. Type `dns` in the display filter -> Enter. (Screenshot 4)
3. Click the **Standard query** (client -> DNS server, UDP dst port 53) and then the **Standard query response**.
4. Expand **User Datagram Protocol** -> Src port (random), Dst port **53**.
5. Expand **Domain Name System** -> Transaction ID, Flags (Response / Recursion desired / Recursion available),
   Questions, Answer RRs, Queries (Name, Type A/AAAA, Class IN), Answers (IP address, TTL).
   (Screenshot 5)
6. Stop capture (red square) -> File -> Save as `capture.pcapng`.

## OBSERVATIONS TO WRITE
| Item | HTTP | DNS |
|---|---|---|
| Transport protocol | TCP | UDP |
| Port | 80 | 53 |
| Request | GET | Standard query (A / AAAA) |
| Response | 200 OK | Standard query response (IP) |
| Content / Result | connecttest.txt text | Resolved IP address |

## CONCLUSION
HTTP and DNS packets were captured and analysed with Wireshark. HTTP runs over TCP (port 80), DNS runs over UDP (port 53). Header fields of each layer (Ethernet, IP, TCP/UDP, Application) were studied.

## VIVA QUICK ANSWERS
- **Capture filter vs display filter?** Capture filter limits what's captured (BPF, before capture); display filter hides packets already captured.
- **Why DNS uses UDP?** Small, fast request/response, no handshake overhead (TCP used for large responses / zone transfer).
- **What does 200 OK mean?** Request succeeded.
- **Why not see HTTPS content?** Encrypted by TLS.
