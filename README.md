# C Network Chat

A lightweight, open-source UDP messaging application written in C using Linux socket programming.

This project is designed to demonstrate the fundamentals of network communication, UDP sockets, and client-server programming.

## Features

- UDP-based message transmission
- Simple command-line interface
- Dedicated sender and receiver programs
- Continuous message receiving
- Basic socket error handling
- Lightweight implementation using standard C and POSIX socket APIs

## Project Structure

- `udp_sender.c` — Sends UDP messages to the receiver.
- `udp_receiver.c` — Listens for and displays incoming UDP messages.
- `README.md` — Project documentation.

## Requirements

- Linux operating system
- GCC compiler
- Standard POSIX networking libraries

## Installation

Clone the repository:

```bash
git clone https://github.com/aziz46ce/c-network-chat.git
cd c-network-chat
```

Compile the programs:

```bash
gcc -Wall -Wextra udp_receiver.c -o receiver
gcc -Wall -Wextra udp_sender.c -o sender
```

## Usage

Open two terminal windows.

**Terminal 1 — Start the receiver**

```bash
./receiver
```

**Terminal 2 — Start the sender**

```bash
./sender
```

Type a message in the sender terminal and press Enter.

The receiver is configured to listen on UDP port `8080`, while the sender transmits messages to `127.0.0.1`.

Type `exit` in the sender terminal to stop sending messages.

## Roadmap

- [x] Implement basic UDP receiver
- [x] Implement basic UDP sender
- [x] Add basic socket error handling
- [ ] Test sender and receiver communication
- [ ] Add two-way messaging
- [ ] Support configurable IP addresses and ports
- [ ] Add automated tests
- [ ] Improve error handling
- [ ] Support communication between multiple computers

## Contributing

Contributions, bug reports, and suggestions are welcome!

If you would like to contribute, please open an issue describing your proposed improvement or submit a pull request.

## Project Status

**Early development — not yet tested.**

The initial sender and receiver implementations are available. Functionality and compatibility will be verified as development continues.

## License

This project is released under the MIT License.

## Author

GitHub: [@aziz46ce](https://github.com/aziz46ce)
